<?php
/*-------------------------------------------------------+
| PHP-Fusion Content Management System
| Copyright (C) PHP-Fusion Inc
| https://www.php-fusion.co.uk/
+--------------------------------------------------------+
| Filename: Czechia/classes/Templates/Login.inc
| Author: RobiNN
+--------------------------------------------------------+
| This program is released as free software under the
| Affero GPL license. You can redistribute it and/or
| modify it under the terms of this license which you
| can read by viewing the included agpl.txt or online
| at www.gnu.org/licenses/agpl.html. Removal of this
| copyright header is strictly prohibited without
| written permission from the original author(s).
+--------------------------------------------------------*/
namespace CzechiaTheme\Templates;

use CzechiaTheme\Core;
use CzechiaTheme\Main;
use \PHPFusion\Panels;

/**
 * Class Login
 *
 * @package CzechiaTheme\Templates
 */
class Login extends Core {
    public static function LoginForm($info) {
        $locale = fusion_get_locale();
        $aidlink = fusion_get_aidlink();
        $userdata = fusion_get_userdata();
        Main::HideAll();

        echo '<div class="panel panel-default" style="max-width: 500px; margin: 30px auto;">';
            echo '<div class="panel-heading" style="background: #fff;">';
                echo '<h3 class="panel-title"><strong>'.$locale['global_100'].'</strong></h3>';

                if (!iMEMBER) {
                    echo '<div class="pull-right" style="margin-top: -20px;">'.$info['forgot_password_link'].'</div>';
                }
            echo '</div>';

        echo '<div class="panel-body">';

        if (iMEMBER) {
            $msg_count = dbcount("(message_id)", DB_MESSAGES, "message_to='".$userdata['user_id']."' AND message_read='0' AND message_folder='0'");
            echo '<h3 class="text-center">'.$userdata['user_name'].'</h3>';
            echo "<div class='text-center'><br />\n";
            echo THEME_BULLET." <a href='".BASEDIR."edit_profile.php' class='side'>".$locale['global_120']."</a><br />\n";
            echo THEME_BULLET." <a href='".BASEDIR."messages.php' class='side'>".$locale['global_121']."</a><br />\n";
            echo THEME_BULLET." <a href='".BASEDIR."members.php' class='side'>".$locale['global_122']."</a><br />\n";
            if (iADMIN && (iUSER_RIGHTS != "" || iUSER_RIGHTS != "C")) {
                echo THEME_BULLET." <a href='".ADMIN."index.php".$aidlink."' class='side'>".$locale['global_123']."</a><br />\n";
            }
            echo THEME_BULLET." <a href='".BASEDIR."index.php?logout=yes' class='side'>".$locale['global_124']."</a><br />\n";
            if ($msg_count) {
                echo "<br /><br />\n";
                echo "<strong><a href='".BASEDIR."messages.php' class='side'>".sprintf($locale['global_125'], $msg_count);
                echo ($msg_count == 1 ? $locale['global_126'] : $locale['global_127'])."</a></strong><br/>\n";
            }

            echo '<a href="'.BASEDIR.fusion_get_settings('opening_page').'">'.$locale['home'].'</a>';
            echo "</div>\n";
        } else {
            echo renderNotices(getNotices(['all', FUSION_SELF]));

            echo '<a href="'.BASEDIR.fusion_get_settings('opening_page').'"><img style="margin: 5px auto;" class="img-responsive m-b-20" src="'.BASEDIR.fusion_get_settings('sitebanner').'" alt="'.fusion_get_settings('sitename').'"/></a>';

            switch (fusion_get_settings('login_method')) {
                case 2:
                    $placeholder = $locale['global_101c'];
                    break;
                case 1:
                    $placeholder = $locale['global_101b'];
                    break;
                default:
                    $placeholder = $locale['global_101a'];
            }

            echo $info['open_form'];
            echo form_text('user_name', '', isset($_POST['user_name']) ? $_POST['user_name'] : '', ['placeholder' => $placeholder]);
            echo form_text('user_pass', '', '', ['placeholder' => $locale['global_102'], 'type' => 'password']);
            echo form_checkbox('remember_me', $locale['global_103'], '', ['reverse_label' => TRUE]);
            echo $info['login_button'];
            echo '<div class="display-block text-center m-t-10">'.$info['registration_link'].'</div>';
            echo $info['close_form'];
        }

        echo '</div>';
        echo '</div>';
    }

    public static function RegisterForm($info) {
        $locale = fusion_get_locale();

        Main::HideAll();

        echo '<div class="panel panel-default" style="max-width: 500px; margin: 30px auto;">';
            echo '<div class="panel-heading" style="background: #fff;">';
                echo '<h3 class="panel-title"><strong>'.$locale['global_107'].'</strong></h3>';
            echo '</div>';

            echo '<div class="panel-body">';
                echo renderNotices(getNotices(['all', FUSION_SELF]));

                echo '<a href="'.BASEDIR.fusion_get_settings('opening_page').'"><img style="margin: 5px auto;" class="img-responsive" src="'.BASEDIR.fusion_get_settings('sitebanner').'" alt="'.fusion_get_settings('sitename').'"/></a>';

                $open = '';
                $close = '';
                if (isset($info['section']) && count($info['section']) > 1) {
                    foreach ($info['section'] as $page_section) {
                        $tab_title['title'][$page_section['id']] = $page_section['name'];
                        $tab_title['id'][$page_section['id']] = $page_section['id'];
                        $tab_title['icon'][$page_section['id']] = '';
                    }
                    $open = opentab($tab_title, $_GET['section'], 'user-profile-form', TRUE);
                    $close = closetab();
                }

                echo $open;

                if (empty($info['user_name']) && empty($info['user_field'])) {
                    echo '<div class="text-white text-center">'.$locale['uf_108'].'</div>';
                } else {
                    echo !empty($info['openform']) ? $info['openform'] : '';
                    echo !empty($info['user_name']) ? $info['user_name'] : '';
                    echo !empty($info['user_email']) ? $info['user_email'] : '';
                    echo !empty($info['user_hide_email']) ? $info['user_hide_email'] : '';
                    echo !empty($info['user_avatar']) ? $info['user_avatar'] : '';
                    echo !empty($info['user_password']) ? $info['user_password'] : '';
                    echo !empty($info['user_admin_password']) && iADMIN ? $info['user_admin_password'] : '';

                    if (!empty($info['user_field'])) {
                        foreach ($info['user_field'] as $field => $fieldData) {
                            echo !empty($fieldData['title']) ? $fieldData['title'] : '';
                            if (!empty($fieldData['fields']) && is_array($fieldData['fields'])) {
                                foreach ($fieldData['fields'] as $cField => $cFieldData) {
                                    echo !empty($cFieldData) ? $cFieldData : '';
                                }
                            }
                        }
                    }

                    echo !empty($info['validate']) ? $info['validate'] : '';
                    echo !empty($info['terms']) ? $info['terms'] : '';
                    echo !empty($info['button']) ? $info['button'] : '';
                    echo !empty($info['closeform']) ? $info['closeform'] : '';
                }

                echo $close;
            echo '</div>';
        echo '</div>';
    }
}