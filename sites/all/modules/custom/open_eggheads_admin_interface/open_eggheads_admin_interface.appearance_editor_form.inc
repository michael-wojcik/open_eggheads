<?php

/**
 * @file
 * File called in open_eggheads_admin_interface.module to set up the "Appearance Editor" form,
 * which is accessible from the Open Eggheads Dashboard.
 * The Appearance Editor form provides the user with a simple interface for altering the color scheme of their site.
 * The form comes preloaded with four default color schemes that a user may choose from:
 * - "Grayscale"
 * - "Duke Blue"
 * - "Harvard Crimson"
 * - "Jet Black"
 * The user also has the option to select a "Custom" color scheme, choose their own colors for different page elements,
 * and save that color scheme for their site.
 *
 * @dependencies:
 * - Radix theme: https://www.drupal.org/project/radix
 * - Radix Colorizer module: https://www.drupal.org/project/radix_colorizer
 */

/**
 * Helper function for open_eggheads_admin_interface_menu().
 * This function loads the Radix Colorizer module's "radix_colorizer_admin_settings" form, to be displayed on a custom page.
 * This form from the Radix Colorizer module is what allows the user to choose their site's color scheme.
 * 
 * @access private
 * @return void
 */
function _open_eggheads_admin_interface_appearance_editor_form() {  
  // Check to see if Radix Colorizer module is enabled. If not, send an error message.
  if (!module_exists('radix_colorizer')) {
    drupal_set_message(t('The Radix Colorizer module needs to be enabled in order to use the Appearance Editor.'), 'error');
    drupal_goto('admin/open-eggheads');
  }
  
  // Build the breadcrumbs in the format Home > News > Title Of Post
  $breadcrumb = array();
  $breadcrumb[] = l(t('Home'), '<front>');
  $breadcrumb[] = l(t('Open Eggheads Dashboard'), 'admin/open-eggheads');
  $breadcrumb[] = l(drupal_get_title(), request_path()); // Link to current URL
  // Set the breadcrumbs
  drupal_set_breadcrumb($breadcrumb);
  
  // Need to load admin form from the Radix Colorizer module.
  // See: http://cgit.drupalcode.org/radix_colorizer/tree/radix_colorizer.admin.inc
  module_load_include('admin.inc', 'radix_colorizer');
  return drupal_get_form('radix_colorizer_admin_settings', $GLOBALS['theme']);
}
