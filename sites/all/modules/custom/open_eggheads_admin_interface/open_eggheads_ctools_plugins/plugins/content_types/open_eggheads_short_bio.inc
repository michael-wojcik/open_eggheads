<?php

/**
 * @file
 * The "Open Eggheads Basic Short Bio" content type is one of the CTools content type plugins created for Open Eggheads sites.
 * This plugin functions as a customized, encapsulated content pane whose primary purpose is to display part of the
 * personal data entered by the user in their Open Eggheads "Personal Data" form (found at "/admin/open-eggheads/personal-data").
 * This plugin can be inserted into the Open Eggheads site as a Panel pane on a Panels-enabled page.
 * To learn more about Panels, see this project: https://www.drupal.org/project/panels
 *
 * The "Open Eggheads Short Bio" content type plugin helps display the information entered under the "Biographical Details"
 * fieldset within the "Personal Data" form (located at "/admin/open-eggheads/personal-data"), which is accessible from the
 * Open Eggheads Dashboard (located at "/admin/open-eggheads").
 */

/**
 * Array that defines the basic details and callback functions associated with this CTools content type plugin.
 * The "edit form", "render callback", and "hook theme" values all refer to functions defined below in this same file.
 */
$plugin = array(
  'title' => t('Open Eggheads Short Bio'),
  'description' => t('A ctools content plugin for displaying the site owner\'s short biography: a mini About Me section.'),
  'category' => t('Open Eggheads'),
  'single' => TRUE,
  'content_types' => 'open_eggheads_short_bio',
  'edit form' => 'open_eggheads_ctools_plugins_open_eggheads_short_bio_content_type_edit_form',
  'render callback' => 'open_eggheads_ctools_plugins_open_eggheads_short_bio_content_type_render',
  'hook theme' => 'open_eggheads_ctools_plugins_open_eggheads_short_bio_content_type_theme',
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
function open_eggheads_ctools_plugins_open_eggheads_short_bio_content_type_edit_form($form, &$form_state) {
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
  $form['open_eggheads_short_bio_display_settings'] = array(
    '#type' => 'fieldset',
    '#title' => t('Short Bio Display Settings'),
  );
  // Allow the user to change the size of the content's heading.
  $form['open_eggheads_short_bio_display_settings']['open_eggheads_short_bio_heading_size'] = array(
    '#title' => t('Heading Size'),
    '#description' => t('The size of the pane\'s heading, as it will appear on the page.'),
    '#type' => 'select',
    '#options' => array(
      'h1' => t('H1 (Biggest)'),
      'h2' => t('H2'),
      'h3' => t('H3'),
      'h4' => t('H4'),
      'h5' => t('H5'),
      'h6' => t('H6 (Smallest)'),
    ),
    '#default_value' => (isset($conf['open_eggheads_short_bio_display_settings']['open_eggheads_short_bio_heading_size']))
                             ? $conf['open_eggheads_short_bio_display_settings']['open_eggheads_short_bio_heading_size']
                             : 'h2',
    '#required' => TRUE,
  );
  // Allow the user to change the text size of the content.
  $form['open_eggheads_short_bio_display_settings']['open_eggheads_short_bio_text_size'] = array(
    '#title' => t('Text Size'),
    '#description' => t('The size of the text, as it will appear on the page.'),
    '#type' => 'select',
    '#options' => array(
      'lead' => t('Big'),
      'normal' => t('Normal'),
      'small' => t('Small'),
    ),
    '#default_value' => (isset($conf['open_eggheads_short_bio_display_settings']['open_eggheads_short_bio_text_size']))
                             ? $conf['open_eggheads_short_bio_display_settings']['open_eggheads_short_bio_text_size']
                             : 'normal',
    '#required' => TRUE,
  );
  // Allow the user to change the text alignment of the content.
  $form['open_eggheads_short_bio_display_settings']['open_eggheads_short_bio_text_alignment'] = array(
    '#title' => t('Text Alignment'),
    '#description' => t('The alignment of the text within its container.'),
    '#type' => 'select',
    '#options' => array(
      'text-left' => t('Left aligned text'),
      'text-center' => t('Center aligned text'),
      'text-right' => t('Right aligned text'),
      'text-justify' => t('Justified text'),
      'text-nowrap' => t('No wrap text'),
    ),
    '#default_value' => (isset($conf['open_eggheads_short_bio_display_settings']['open_eggheads_short_bio_text_alignment']))
                             ? $conf['open_eggheads_short_bio_display_settings']['open_eggheads_short_bio_text_alignment']
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
function open_eggheads_ctools_plugins_open_eggheads_short_bio_content_type_edit_form_submit($form, &$form_state) {
  // Store the values from the Edit Form fields in the $conf variable that CTools uses to render its plugins.
  foreach (array_keys($form_state['values']['open_eggheads_short_bio_display_settings']) as $key) {
    if (isset($form_state['values']['open_eggheads_short_bio_display_settings'][$key])) {
      $form_state['conf']['open_eggheads_short_bio_display_settings'][$key] = $form_state['values']['open_eggheads_short_bio_display_settings'][$key];
    }
  }
  
  // Clear previously cached version of open_eggheads_photo content type.
  cache_clear_all('open_eggheads_admin_interface:open_eggheads_ctools_plugins:open_eggheads_short_bio', 'cache', TRUE);
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
function open_eggheads_ctools_plugins_open_eggheads_short_bio_content_type_render($subtype, $conf, $args, $context = NULL) {  
  // Load the user's personal data saved in the Open Eggheads "Personal Data" form ("/admin/open-eggheads/personal-data").
  $personal_data = variable_get('open_eggheads_admin_interface_personal_data');
  
  $pane = new stdClass();
  
  // Get Short Bio and sanitize data.
  $short_bio = check_plain($personal_data['biographical_details']['short_bio']);
  
  // Set pane title using the user's first name, if available.
  $first_name = $personal_data['basic_info']['first_name'];
  $about_whom = ($first_name) ? check_plain($first_name) : 'Me';
  $short_bio_heading = t('About ') . $about_whom;
  
  // Check to see if user has filled out the Short Bio form field.
  $has_short_bio = !empty($short_bio);
  
  if ($has_short_bio) { // User has filled out a Short Bio.
    // Get heading size from the Edit Form above.
    $short_bio_heading_size = (isset($conf['open_eggheads_short_bio_display_settings']['open_eggheads_short_bio_heading_size']))
                                    ? $conf['open_eggheads_short_bio_display_settings']['open_eggheads_short_bio_heading_size']
                                    : 'h2';
    // Get text size from the Edit Form above.
    $short_bio_text_size = (isset($conf['open_eggheads_short_bio_display_settings']['open_eggheads_short_bio_text_size']))
                                ? $conf['open_eggheads_short_bio_display_settings']['open_eggheads_short_bio_text_size']
                                : 'normal';
    // Get text alignment CSS class from the Edit Form above.
    $short_bio_text_alignment = (isset($conf['open_eggheads_short_bio_display_settings']['open_eggheads_short_bio_text_alignment']))
                                     ? $conf['open_eggheads_short_bio_display_settings']['open_eggheads_short_bio_text_alignment']
                                     : 'text-left';
    
    // Define the CTools content pane array to be rendered on the page.
    $pane_content = array(
      '#type' => 'markup',
      '#markup' => theme(
        'open_eggheads_short_bio', array(
          'short_bio' => $short_bio,
          'short_bio_heading' => $short_bio_heading,
          'short_bio_heading_size' => $short_bio_heading_size,
          'short_bio_text_size' => $short_bio_text_size,
          'short_bio_text_alignment' => $short_bio_text_alignment,
        )
      ),
      '#cache' => array(
        'keys' => array('open_eggheads_admin_interface', 'open_eggheads_ctools_plugins', 'open_eggheads_short_bio'),
        'bin' => 'cache',
        'expire' => CACHE_TEMPORARY,
        'granularity' => DRUPAL_CACHE_GLOBAL,
      ),
    );
  }
  else { // User has not specified a Short Bio.
    // Set a warning message, so the user knows that their data is missing.
    $pane_content = array(
      '#type' => 'markup',
      '#markup' => t('<em>You haven\'t filled out a Short Bio in the Open Eggheads Personal Data form.<br />You can find the form in the Open Eggheads Dashboard ("YOURDOMAIN.COM/admin/open-eggheads/data").</em>'),
      '#prefix' => '<div class="alert alert-danger" role="alert">',
      '#suffix' => '</div>',
      '#cache' => array(
        'keys' => array('open_eggheads_admin_interface', 'open_eggheads_ctools_plugins', 'open_eggheads_short_bio'),
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
function open_eggheads_ctools_plugins_open_eggheads_short_bio_content_type_theme(&$theme, $plugin) {
  $theme['open_eggheads_short_bio'] = array(
    'arguments' => array(
      'short_bio' => NULL,
      'short_bio_heading' => NULL,
      'short_bio_heading_size' => NULL,
      'short_bio_text_size' => NULL,
      'short_bio_text_alignment' => NULL,
    ),
    'template' => 'open-eggheads-short-bio',
    'path' => $plugin['path'] . '/templates',
  );
}
