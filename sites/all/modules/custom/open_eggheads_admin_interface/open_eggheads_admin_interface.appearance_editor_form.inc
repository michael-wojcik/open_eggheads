<?php

/**
 * Helper function for open_eggheads_admin_interface_menu().
 */
function _open_eggheads_admin_interface_appearance_editor_form() {  
  // Check to see if Radix Colorizer module is enabled.
  if (!module_exists('radix_colorizer')) {
    drupal_set_message(t('The Radix Colorizer module needs to be enabled in order to use the Appearance Editor.'), 'error');
    drupal_goto('admin/open-eggheads');
  }
  
  // Need to load admin form from the Radix Colorizer module.
  // See: http://cgit.drupalcode.org/radix_colorizer/tree/radix_colorizer.admin.inc
  module_load_include('admin.inc', 'radix_colorizer');
  return drupal_get_form('radix_colorizer_admin_settings', $GLOBALS['theme']);
}
