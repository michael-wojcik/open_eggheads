<?php

/**
 * @file
 * The "Open Eggheads Basic Personal Info" content type is one of the CTools content type plugins created for Open Eggheads sites.
 * This plugin functions as a customized, encapsulated content pane whose primary purpose is to display part of the
 * personal data entered by the user in their Open Eggheads "Personal Data" form (found at "/admin/open-eggheads/personal-data").
 * This plugin can be inserted into the Open Eggheads site as a Panel pane on a Panels-enabled page.
 * To learn more about Panels, see this project: https://www.drupal.org/project/panels
 *
 * The "Open Eggheads Basic Personal Info" content type plugin helps display the information entered under the "Basic Information"
 * fieldset within the "Personal Data" form (located at "/admin/open-eggheads/personal-data"), which is accessible from the
 * Open Eggheads Dashboard (located at "/admin/open-eggheads").
 */

/**
 * Array that defines the basic details and callback functions associated with this CTools content type plugin.
 * The "edit form", "render callback", and "hook theme" values all refer to functions defined below in this same file.
 */
$plugin = array(
  'title' => t('Open Eggheads Basic Personal Info'),
  'description' => t('A ctools content plugin for displaying the site owner\'s basic public information: name, title, affiliation, email, phone.'),
  'category' => t('Open Eggheads'),
  'single' => TRUE,
  'content_types' => 'open_eggheads_basic_info',
  'edit form' => 'open_eggheads_ctools_plugins_open_eggheads_basic_info_content_type_edit_form',
  'render callback' => 'open_eggheads_ctools_plugins_open_eggheads_basic_info_content_type_render',
  'hook theme' => 'open_eggheads_ctools_plugins_open_eggheads_basic_info_content_type_theme',
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
function open_eggheads_ctools_plugins_open_eggheads_basic_info_content_type_edit_form($form, &$form_state) {
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
  $form['open_eggheads_basic_info_display_settings'] = array(
    '#type' => 'fieldset',
    '#title' => t('Basic Info Display Settings'),
  );
  // Allow the user to change the size of the content's heading.
  $form['open_eggheads_basic_info_display_settings']['open_eggheads_basic_info_heading_size'] = array(
    '#title' => t('Heading Size'),
    '#description' => t('The size of your name, as it will appear on the page.'),
    '#type' => 'select',
    '#options' => array(
      'h1' => t('H1 (Biggest)'),
      'h2' => t('H2'),
      'h3' => t('H3'),
      'h4' => t('H4'),
      'h5' => t('H5'),
      'h6' => t('H6 (Smallest)'),
    ),
    '#default_value' => (isset($conf['open_eggheads_basic_info_display_settings']['open_eggheads_basic_info_heading_size']))
                             ? $conf['open_eggheads_basic_info_display_settings']['open_eggheads_basic_info_heading_size']
                             : 'h1',
    '#required' => TRUE,
  );
  // Allow the user to change the text size of the content.
  $form['open_eggheads_basic_info_display_settings']['open_eggheads_basic_info_text_size'] = array(
    '#title' => t('Text Size'),
    '#description' => t('The size of the rest of the text, as it will appear on the page.'),
    '#type' => 'select',
    '#options' => array(
      'lead' => t('Big'),
      'normal' => t('Normal'),
      'small' => t('Small'),
    ),
    '#default_value' => (isset($conf['open_eggheads_basic_info_display_settings']['open_eggheads_basic_info_text_size']))
                             ? $conf['open_eggheads_basic_info_display_settings']['open_eggheads_basic_info_text_size']
                             : 'normal',
    '#required' => TRUE,
  );
  // Allow the user to change the text alignment of the content.
  $form['open_eggheads_basic_info_display_settings']['open_eggheads_basic_info_alignment'] = array(
    '#title' => t('Alignment'),
    '#description' => t('The alignment of the photo within its container.'),
    '#type' => 'select',
    '#options' => array(
      'text-left' => t('Left aligned text'),
      'text-center' => t('Center aligned text'),
      'text-right' => t('Right aligned text'),
      'text-justify' => t('Justified text'),
      'text-nowrap' => t('No wrap text'),
    ),
    '#default_value' => (isset($conf['open_eggheads_basic_info_display_settings']['open_eggheads_basic_info_alignment']))
                             ? $conf['open_eggheads_basic_info_display_settings']['open_eggheads_basic_info_alignment']
                             : 'text-left',
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
function open_eggheads_ctools_plugins_open_eggheads_basic_info_content_type_edit_form_submit($form, &$form_state) {
  // Store the values from the Edit Form fields in the $conf variable that CTools uses to render its plugins.
  foreach (array_keys($form_state['values']['open_eggheads_basic_info_display_settings']) as $key) {
    if (isset($form_state['values']['open_eggheads_basic_info_display_settings'][$key])) {
      $form_state['conf']['open_eggheads_basic_info_display_settings'][$key] = $form_state['values']['open_eggheads_basic_info_display_settings'][$key];
    }
  }
  
  // Clear previously cached version of open_eggheads_photo content type.
  cache_clear_all('open_eggheads_admin_interface:open_eggheads_ctools_plugins:open_eggheads_basic_info', 'cache', TRUE);
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
function open_eggheads_ctools_plugins_open_eggheads_basic_info_content_type_render($subtype, $conf, $args, $context = NULL) {  
  // Load the user's personal data saved in the Open Eggheads "Personal Data" form ("/admin/open-eggheads/personal-data").
  $personal_data = variable_get('open_eggheads_admin_interface_personal_data');
  
  $pane = new stdClass();
  
  // Get the relevant data.
  $basic_info = $personal_data['basic_info'];
  
  // Check to see if user has filled out the basic info form.
  $has_basic_info = FALSE;
  foreach ($basic_info as $info) {
    if ($info) {
      $has_basic_info = TRUE;
      break;
    }
  }
  
  if ($has_basic_info) { // User has filled out some basic info.
    // Sanitize all data.
    foreach ($basic_info as &$value) {
      $value = check_plain($value);
    }
    unset($value); // Break the reference with the last element.
    
    // Get heading size from the Edit Form above.
    $basic_info_heading_size = (isset($conf['open_eggheads_basic_info_display_settings']['open_eggheads_basic_info_heading_size']))
                                    ? $conf['open_eggheads_basic_info_display_settings']['open_eggheads_basic_info_heading_size']
                                    : 'h1';
    // Get text size from the Edit Form above.
    $basic_info_text_size = (isset($conf['open_eggheads_basic_info_display_settings']['open_eggheads_basic_info_text_size']))
                                 ? $conf['open_eggheads_basic_info_display_settings']['open_eggheads_basic_info_text_size']
                                 : 'normal';
    // Get text alignment CSS class from the Edit Form above.
    $basic_info_alignment = (isset($conf['open_eggheads_basic_info_display_settings']['open_eggheads_basic_info_alignment']))
                                 ? $conf['open_eggheads_basic_info_display_settings']['open_eggheads_basic_info_alignment']
                                 : 'text-left';
    // Concatenate all CSS classes.
    $basic_info_classes = $basic_info_alignment;
    
    // Define the CTools content pane array to be rendered on the page.
    $pane_content = array(
      '#type' => 'markup',
      '#markup' => theme(
        'open_eggheads_basic_info', array(
          'basic_info' => $basic_info,
          'basic_info_heading_size' => $basic_info_heading_size,
          'basic_info_text_size' => $basic_info_text_size,
          'basic_info_classes' => $basic_info_classes,
        )
      ),
      '#cache' => array(
        'keys' => array('open_eggheads_admin_interface', 'open_eggheads_ctools_plugins', 'open_eggheads_basic_info'),
        'bin' => 'cache',
        'expire' => CACHE_TEMPORARY,
        'granularity' => DRUPAL_CACHE_GLOBAL,
      ),
    );
  }
  else { // User has not specified any basic info.
    // Set a warning message, so the user knows that their data is missing.
    $pane_content = array(
      '#type' => 'markup',
      '#markup' => t('<em>You haven\'t filled out any basic information in the Open Eggheads Personal Data form.<br />You can find the form in the Open Eggheads Dashboard ("YOURDOMAIN.COM/admin/open-eggheads/data").</em>'),
      '#prefix' => '<div class="alert alert-danger" role="alert">',
      '#suffix' => '</div>',
      '#cache' => array(
        'keys' => array('open_eggheads_admin_interface', 'open_eggheads_ctools_plugins', 'open_eggheads_basic_info'),
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
function open_eggheads_ctools_plugins_open_eggheads_basic_info_content_type_theme(&$theme, $plugin) {
  $theme['open_eggheads_basic_info'] = array(
    'arguments' => array(
      'basic_info' => NULL,
      'basic_info_heading_size' => NULL,
      'basic_info_text_size' => NULL,
      'basic_info_classes' => NULL,
    ),
    'template' => 'open-eggheads-basic-info',
    'path' => $plugin['path'] . '/templates',
  );
}
