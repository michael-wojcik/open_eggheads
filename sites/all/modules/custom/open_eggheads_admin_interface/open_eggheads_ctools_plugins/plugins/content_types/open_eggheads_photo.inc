<?php

/**
 * @file
 * The "Open Eggheads Photo" content type is one of the CTools content type plugins created for Open Eggheads sites.
 * This plugin functions as a customized, encapsulated content pane whose primary purpose is to display part of the
 * personal data entered by the user in their Open Eggheads "Personal Data" form (found at "/admin/open-eggheads/personal-data").
 * This plugin can be inserted into the Open Eggheads site as a Panel pane on a Panels-enabled page.
 * To learn more about Panels, see this project: https://www.drupal.org/project/panels
 *
 * The "Open Eggheads Photo" content type plugin helps display the information entered under the "Personal Files"
 * fieldset within the "Personal Data" form (located at "/admin/open-eggheads/personal-data"), which is accessible from the
 * Open Eggheads Dashboard (located at "/admin/open-eggheads").
 */

/**
 * Array that defines the basic details and callback functions associated with this CTools content type plugin.
 * The "edit form", "render callback", and "hook theme" values all refer to functions defined below in this same file.
 */
$plugin = array(
  'title' => t('Open Eggheads Photo'),
  'description' => t('A basic ctools content plugin for displaying a photo panel pane.'),
  'category' => t('Open Eggheads'),
  'single' => TRUE,
  'content_types' => 'open_eggheads_photo',
  'edit form' => 'open_eggheads_ctools_plugins_open_eggheads_photo_content_type_edit_form',
  'render callback' => 'open_eggheads_ctools_plugins_open_eggheads_photo_content_type_render',
  'hook theme' => 'open_eggheads_ctools_plugins_open_eggheads_photo_content_type_theme',
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
function open_eggheads_ctools_plugins_open_eggheads_photo_content_type_edit_form($form, &$form_state) {
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
  $form['open_eggheads_photo_display_settings'] = array(
    '#type' => 'fieldset',
    '#title' => t('Photo Display Settings'),
  );
  // Allow the user to change the width of the photo relative to its container.
  $form['open_eggheads_photo_display_settings']['open_eggheads_photo_width'] = array(
    '#title' => t('Width'),
    '#description' => t('The percentage width of the photo relative to its container.'),
    '#type' => 'select',
    '#options' => array(
      '100' => t('100%'),
      '75' => t('75%'),
      '66' => t('66%'),
      '50' => t('50%'),
      '33' => t('33%'),
      '25' => t('25%'),
    ),
    '#default_value' => (isset($conf['open_eggheads_photo_display_settings']['open_eggheads_photo_width']))
      ? $conf['open_eggheads_photo_display_settings']['open_eggheads_photo_width']
      : '100',
    '#required' => TRUE,
  );
  // Allow the user to change the alignment of the photo relative to its container.
  $form['open_eggheads_photo_display_settings']['open_eggheads_photo_alignment'] = array(
    '#title' => t('Alignment'),
    '#description' => t('The alignment of the photo within its container.'),
    '#type' => 'select',
    '#options' => array(
      'pull-left' => t('Left'),
      'center-block' => t('Center'),
      'pull-right' => t('Right'),
    ),
    '#default_value' => (isset($conf['open_eggheads_photo_display_settings']['open_eggheads_photo_alignment']))
      ? $conf['open_eggheads_photo_display_settings']['open_eggheads_photo_alignment']
      : 'pull-left',
    '#required' => TRUE,
  );
  // Allow the user to change the shape of the photo.
  $form['open_eggheads_photo_display_settings']['open_eggheads_photo_shape'] = array(
    '#title' => t('Shape'),
    '#description' => t('The shape of the photo.'),
    '#type' => 'select',
    '#options' => array(
      'img-default' => t('Default'),
      'img-rounded' => t('Rounded Corners'),
      'img-circle' => t('Circle'),
      'img-thumbnail' => t('Thumbnail'),
    ),
    '#default_value' => (isset($conf['open_eggheads_photo_display_settings']['open_eggheads_photo_shape']))
      ? $conf['open_eggheads_photo_display_settings']['open_eggheads_photo_shape']
      : 'img-default',
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
function open_eggheads_ctools_plugins_open_eggheads_photo_content_type_edit_form_submit($form, &$form_state) {
  // Store the values from the Edit Form fields in the $conf variable that CTools uses to render its plugins.
  foreach (array_keys($form_state['values']['open_eggheads_photo_display_settings']) as $key) {
    if (isset($form_state['values']['open_eggheads_photo_display_settings'][$key])) {
      $form_state['conf']['open_eggheads_photo_display_settings'][$key] = $form_state['values']['open_eggheads_photo_display_settings'][$key];
    }
  }
  
  // Clear previously cached version of open_eggheads_photo content type.
  cache_clear_all('open_eggheads_admin_interface:open_eggheads_ctools_plugins:open_eggheads_photo', 'cache', TRUE);
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
function open_eggheads_ctools_plugins_open_eggheads_photo_content_type_render($subtype, $conf, $args, $context = NULL) {  
  // Load the user's personal data saved in the Open Eggheads "Personal Data" form ("/admin/open-eggheads/personal-data").
  $personal_data = variable_get('open_eggheads_admin_interface_personal_data');
  
  $pane = new stdClass();
  // Get the file ID number.
  $photo_fid = $personal_data['files']['photo'];
  if ($photo_fid) { // If user has uploaded their photo…
    $file_path = file_create_url(file_load($photo_fid)->uri); // Fetch URL of user's photo.
    // Get photo width as percentage out of 100 from the Edit Form above.
    $photo_width = (isset($conf['open_eggheads_photo_display_settings']['open_eggheads_photo_width']))
                        ? $conf['open_eggheads_photo_display_settings']['open_eggheads_photo_width']
                        : '100';
    // Get photo alignment CSS class from the Edit Form above.
    $photo_alignment = (isset($conf['open_eggheads_photo_display_settings']['open_eggheads_photo_alignment']))
                            ? $conf['open_eggheads_photo_display_settings']['open_eggheads_photo_alignment']
                            : 'pull-left';
    // Get photo shape CSS class from the Edit Form above.
    $photo_shape = (isset($conf['open_eggheads_photo_display_settings']['open_eggheads_photo_shape']))
                        ? $conf['open_eggheads_photo_display_settings']['open_eggheads_photo_shape']
                        : 'img-default';
    // Concatenate all photo CSS classes from the Edit Form above.
    $photo_classes = $photo_alignment.' '.$photo_shape;
    
    // Define the CTools content pane array to be rendered on the page.
    $pane_content = array(
      '#type' => 'markup',
      '#markup' => theme(
        'open_eggheads_photo', array(
          'file_path' => $file_path,
          'img_width' => $photo_width,
          'img_classes' => $photo_classes,
        )
      ),
      '#cache' => array(
        'keys' => array('open_eggheads_admin_interface', 'open_eggheads_ctools_plugins', 'open_eggheads_photo'),
        'bin' => 'cache',
        'expire' => CACHE_TEMPORARY,
        'granularity' => DRUPAL_CACHE_GLOBAL,
      ),
    );
  }
  else { // User has NOT uploaded their photo…
    // Set a warning message, so the user knows that their data is missing.
    $pane_content = array(
      '#type' => 'markup',
      '#markup' => t('<em>User has not uploaded their photo.<br />Use the Open Eggheads Dashboard ("YOURDOMAIN.COM/admin/open-eggheads") to upload a photo.</em>'),
      '#prefix' => '<div class="alert alert-danger" role="alert">',
      '#suffix' => '</div>',
      '#cache' => array(
        'keys' => array('open_eggheads_admin_interface', 'open_eggheads_ctools_plugins', 'open_eggheads_photo'),
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
function open_eggheads_ctools_plugins_open_eggheads_photo_content_type_theme(&$theme, $plugin) {
  $theme['open_eggheads_photo'] = array(
    'arguments' => array(
      'file_path' => NULL,
      'img_width' => '100',
      'img_classes' => '',
    ),
    'template' => 'open-eggheads-photo',
    'path' => $plugin['path'] . '/templates',
  );
}
