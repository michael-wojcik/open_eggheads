<?php

/**
 * @file
 * The "Open Eggheads CV" content type is one of the CTools content type plugins created for Open Eggheads sites.
 * This plugin functions as a customized, encapsulated content pane whose primary purpose is to display part of the
 * personal data entered by the user in their Open Eggheads "Personal Data" form (found at "/admin/open-eggheads/personal-data").
 * This plugin can be inserted into the Open Eggheads site as a Panel pane on a Panels-enabled page.
 * To learn more about Panels, see this project: https://www.drupal.org/project/panels
 *
 * The "Open Eggheads CV" content type plugin helps display the information entered under the "Personal Files"
 * fieldset within the "Personal Data" form (located at "/admin/open-eggheads/personal-data"), which is accessible from the
 * Open Eggheads Dashboard (located at "/admin/open-eggheads").
 */

/**
 * Array that defines the basic details and callback functions associated with this CTools content type plugin.
 * The "edit form", "render callback", and "hook theme" values all refer to functions defined below in this same file.
 */
$plugin = array(
  'title' => t('Open Eggheads CV'),
  'description' => t('A basic ctools content plugin for displaying a PDF panel pane.'),
  'category' => t('Open Eggheads'),
  'single' => TRUE,
  'content_types' => 'open_eggheads_pdf',
  'edit form' => 'open_eggheads_ctools_plugins_open_eggheads_pdf_content_type_edit_form',
  'render callback' => 'open_eggheads_ctools_plugins_open_eggheads_pdf_content_type_render',
  'hook theme' => 'open_eggheads_ctools_plugins_open_eggheads_pdf_content_type_theme',
);

/**
 * 'Edit form' callback for the content type.
 * This form can be accessed by the user when using the Panels In-Place Editor, usually triggered with the contextual button
 * labeled "Customize this page" at the bottom of a Panels-enabled page.
 * 
 * @access public
 * @param mixed $form
 * @param mixed &$form_state
 * @return void
 */
function open_eggheads_ctools_plugins_open_eggheads_pdf_content_type_edit_form($form, &$form_state) {
  $conf = $form_state['conf'];
  
  $form['#tree'] = TRUE;
  
  // Add some custom CSS to help style the appearance of the Edit Form itself for better ease-of-use.
  $form['#attached']['css'][] = array(
    'data' => drupal_get_path('module', 'open_eggheads_ctools_plugins') . '/css/open_eggheads_ctools_plugins.css',
    'options' => array(
      'type' => 'file',
      'group' => CSS_THEME,
      'weight' => 100,
    ),
  );
  
  // Define some basic options that a user might want to change about how the content is displayed.
  $form['open_eggheads_pdf_display_settings'] = array(
    '#type' => 'fieldset',
    '#title' => t('PDF Display Settings'),
  );
  // Allow the user to change the width of the PDF viewer relative to the page.
  $form['open_eggheads_pdf_display_settings']['open_eggheads_pdf_width'] = array(
    '#title' => t('Width'),
    '#description' => t('The percentage width of the PDF viewer relative to the page.'),
    '#type' => 'select',
    '#options' => array(
      '100' => t('100%'),
      '75' => t('75%'),
      '66' => t('66%'),
      '50' => t('50%'),
      '33' => t('33%'),
      '25' => t('25%'),
    ),
    '#default_value' => (isset($conf['open_eggheads_pdf_display_settings']['open_eggheads_pdf_width']))
      ? $conf['open_eggheads_pdf_display_settings']['open_eggheads_pdf_width']
      : '100',
    '#required' => TRUE,
  );
  // Allow the user to change the height of the PDF viewer on the page.
  $form['open_eggheads_pdf_display_settings']['open_eggheads_pdf_height'] = array(
    '#title' => t('Height'),
    '#description' => t('The height of the PDF viewer on the page.'),
    '#type' => 'select',
    '#options' => array(
      '2160' => t('2160px'),
      '1440' => t('1440px'),
      '1080' => t('1080px'),
      '720' => t('720px'),
      '480' => t('480px'),
      '360' => t('360px'),
      '240' => t('240px'),
    ),
    '#default_value' => (isset($conf['open_eggheads_pdf_display_settings']['open_eggheads_pdf_height']))
      ? $conf['open_eggheads_pdf_display_settings']['open_eggheads_pdf_height']
      : '720',
    '#required' => TRUE,
  );
  // Allow the user to change the default zoom level when viewing the PDF on the page.
  $form['open_eggheads_pdf_display_settings']['open_eggheads_pdf_zoom'] = array(
    '#title' => t('Zoom'),
    '#description' => t('The zoom level when viewing the PDF on the page.'),
    '#type' => 'select',
    '#options' => array(
      'auto' => t('Automatic Zoom'),
      'page-height' => t('Page Height'),
      'page-fit' => t('Page Fit'),
      'page-width' => t('Page Width'),
      '50' => t('50%'),
      '75' => t('75%'),
      '100' => t('100%'),
      '125' => t('125%'),
      '150' => t('150%'),
      '200' => t('200%'),
      '300' => t('300%'),
      '400' => t('400%'),
    ),
    '#default_value' => (isset($conf['open_eggheads_pdf_display_settings']['open_eggheads_pdf_zoom']))
      ? $conf['open_eggheads_pdf_display_settings']['open_eggheads_pdf_zoom']
      : 'page-width',
    '#required' => TRUE,
  );
  
  return $form;
}

/**
 * Submit handler function for the above Edit Form. 
 * The submit form stores the data in $conf.
 * 
 * @access public
 * @param mixed $form
 * @param mixed &$form_state
 * @return void
 */
function open_eggheads_ctools_plugins_open_eggheads_pdf_content_type_edit_form_submit($form, &$form_state) {
  // Save new edit form values to the CTools config array for the content type.
  foreach (array_keys($form_state['values']['open_eggheads_pdf_display_settings']) as $key) {
    if (isset($form_state['values']['open_eggheads_pdf_display_settings'][$key])) {
      $form_state['conf']['open_eggheads_pdf_display_settings'][$key] = $form_state['values']['open_eggheads_pdf_display_settings'][$key];
    }
  }
  
  // Clear previously cached version of open_eggheads_pdf content type.
  cache_clear_all('open_eggheads_admin_interface:open_eggheads_ctools_plugins:open_eggheads_pdf', 'cache', TRUE);
}

/**
 * Function that defines how the CTools content type plugin should be rendered on the page.
 * 
 * @access public
 * @param mixed $subtype
 * @param mixed $conf
 * @param mixed $args
 * @param mixed $context (default: NULL)
 * @return void
 */
function open_eggheads_ctools_plugins_open_eggheads_pdf_content_type_render($subtype, $conf, $args, $context = NULL) {  
  // Load the user's personal data saved in the Open Eggheads "Personal Data" form ("/admin/open-eggheads/personal-data").
  $personal_data = variable_get('open_eggheads_admin_interface_personal_data');
  
  $pane = new stdClass();
  $pane->title = t('Curriculum Vitae');
  // Get the file ID number.
  $pdf_fid = $personal_data['files']['cv'];
  if ($pdf_fid) { // If user has uploaded their CV as a PDF…
    $file_path = file_create_url(file_load($pdf_fid)->uri); // Fetch URL of user's cv.
    // Define the CTools content pane array to be rendered on the page.
    $pane_content = array(
      '#type' => 'markup',
      '#markup' => theme(
        'open_eggheads_pdf', array(
          'file_path' => $file_path,
          // Get PDF viewer width as percentage out of 100 from the Edit Form above.
          'width' => (isset($conf['open_eggheads_pdf_display_settings']['open_eggheads_pdf_width']))
            ? $conf['open_eggheads_pdf_display_settings']['open_eggheads_pdf_width']
            : '100',
          // Get PDF viewer height from the Edit Form above.
          'height' => (isset($conf['open_eggheads_pdf_display_settings']['open_eggheads_pdf_height']))
            ? $conf['open_eggheads_pdf_display_settings']['open_eggheads_pdf_height']
            : '720',
          // Get default zoom level from the Edit Form above.
          'zoom' => (isset($conf['open_eggheads_pdf_display_settings']['open_eggheads_pdf_zoom']))
            ? $conf['open_eggheads_pdf_display_settings']['open_eggheads_pdf_zoom']
            : 'page-width',
        )
      ),
      '#suffix' => t('Last updated on %time.', array('%time' => date('r'))),
      '#cache' => array(
        'keys' => array('open_eggheads_admin_interface', 'open_eggheads_ctools_plugins', 'open_eggheads_pdf'),
        'bin' => 'cache',
        'expire' => CACHE_TEMPORARY,
        'granularity' => DRUPAL_CACHE_GLOBAL,
      ),
    );
  }
  else { // User has NOT uploaded their CV as a PDF…
    // Set a warning message, so the user knows that their data is missing.
    $pane_content = array(
      '#type' => 'markup',
      '#markup' => t('<em>User has not uploaded their CV as a PDF file.<br />Use the Open Eggheads Dashboard ("/admin/open-eggheads") to upload a CV.</em>'),
      '#prefix' => '<div class="alert alert-danger" role="alert">',
      '#suffix' => '</div>',
      '#cache' => array(
        'keys' => array('open_eggheads_admin_interface', 'open_eggheads_ctools_plugins', 'open_eggheads_pdf'),
        'bin' => 'cache',
        'expire' => CACHE_TEMPORARY,
        'granularity' => DRUPAL_CACHE_GLOBAL,
      ),
    );
  }
  $pane->content = render($pane_content);
  return $pane;
}

/**
 * Implements hook_theme(): https://api.drupal.org/api/drupal/modules%21system%21system.api.php/function/hook_theme/7.
 * Specifies a PHP/HTML template file for rendering the CTools content type plugin, as well as what data should be passed to the template.
 * 
 * @access public
 * @param mixed &$theme
 * @param mixed $plugin
 * @return void
 */
function open_eggheads_ctools_plugins_open_eggheads_pdf_content_type_theme(&$theme, $plugin) {
  $theme['open_eggheads_pdf'] = array(
    'arguments' => array(
      'file_path' => NULL,
      'width' => '100',
      'height' => '720',
      'zoom' => 'page-width',
    ),
    'template' => 'open-eggheads-pdf',
    'path' => $plugin['path'] . '/templates',
  );
}
