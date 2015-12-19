<?php

/**
 * @file
 * The "Open Eggheads Selected Projects" content type is one of the CTools content type plugins created for Open Eggheads sites.
 * This plugin functions as a customized, encapsulated content pane whose primary purpose is to display part of the
 * personal data entered by the user in their Open Eggheads "Personal Data" form (found at "/admin/open-eggheads/personal-data").
 * This plugin can be inserted into the Open Eggheads site as a Panel pane on a Panels-enabled page.
 * To learn more about Panels, see this project: https://www.drupal.org/project/panels
 *
 * The "Open Eggheads Selected Projects" content type plugin helps display the information entered under the "Selected Projects"
 * fieldset within the "Personal Data" form (located at "/admin/open-eggheads/personal-data"), which is accessible from the
 * Open Eggheads Dashboard (located at "/admin/open-eggheads").
 */

/**
 * Array that defines the basic details and callback functions associated with this CTools content type plugin.
 * The "edit form", "render callback", and "hook theme" values all refer to functions defined below in this same file.
 */
$plugin = array(
  'title' => t('Open Eggheads Selected Projects'),
  'description' => t('A ctools content plugin for displaying the site owner\' selected projects.'),
  'category' => t('Open Eggheads'),
  'single' => TRUE,
  'content_types' => 'open_eggheads_selected_projects',
  'edit form' => 'open_eggheads_ctools_plugins_open_eggheads_selected_projects_content_type_edit_form',
  'render callback' => 'open_eggheads_ctools_plugins_open_eggheads_selected_projects_content_type_render',
  'hook theme' => 'open_eggheads_ctools_plugins_open_eggheads_selected_projects_content_type_theme',
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
function open_eggheads_ctools_plugins_open_eggheads_selected_projects_content_type_edit_form($form, &$form_state) {
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
  $form['open_eggheads_selected_projects_display_settings'] = array(
    '#type' => 'fieldset',
    '#title' => t('Selected Projects Display Settings'),
  );
  // Allow the user to change the size of the content's heading.
  $form['open_eggheads_selected_projects_display_settings']['open_eggheads_selected_projects_heading_size'] = array(
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
    '#default_value' => (isset($conf['open_eggheads_selected_projects_display_settings']['open_eggheads_selected_projects_heading_size']))
                             ? $conf['open_eggheads_selected_projects_display_settings']['open_eggheads_selected_projects_heading_size']
                             : 'h2',
    '#required' => TRUE,
  );
  // Allow the user to change the type of list that the content is displayed in.
  $form['open_eggheads_selected_projects_display_settings']['open_eggheads_selected_projects_list_type'] = array(
    '#title' => t('List Type'),
    '#description' => t('The type of list with which your selected projects will be displayed.'),
    '#type' => 'select',
    '#options' => array(
      'ul' => t('Bulleted List'),
      'ol' => t('Numbered List'),
    ),
    '#default_value' => (isset($conf['open_eggheads_selected_projects_display_settings']['open_eggheads_selected_projects_list_type']))
                             ? $conf['open_eggheads_selected_projects_display_settings']['open_eggheads_selected_projects_list_type']
                             : 'ul',
    '#required' => TRUE,
  );
  // Allow the user to change the style of list that the content is displayed in.
  $form['open_eggheads_selected_projects_display_settings']['open_eggheads_selected_projects_list_style_ul'] = array(
    '#title' => t('Bulleted List Style'),
    '#description' => t('The style of the bulleted list.'),
    '#type' => 'select',
    '#options' => array(
      'disc' => t('Disc'),
      'circle' => t('Circle'),
      'square' => t('Square'),
      'none' => t('None'),
    ),
    '#default_value' => (isset($conf['open_eggheads_selected_projects_display_settings']['open_eggheads_selected_projects_list_style_ul']))
                             ? $conf['open_eggheads_selected_projects_display_settings']['open_eggheads_selected_projects_list_style_ul']
                             : 'disc',
    // Bulleted List Style only visible/required when List Type is Bulleted List.
    '#states' => array(
      'visible' => array(
        ':input[name="open_eggheads_selected_projects_display_settings[open_eggheads_selected_projects_list_type]"]' => array(
          'value' => 'ul',
        ),
      ),
      'required' => array(
        ':input[name="open_eggheads_selected_projects_display_settings[open_eggheads_selected_projects_list_type]"]' => array(
          'value' => 'ul',
        ),
      ),
    ),
  );
  // Allow the user to change the style of list that the content is displayed in.
  $form['open_eggheads_selected_projects_display_settings']['open_eggheads_selected_projects_list_style_ol'] = array(
    '#title' => t('Numbered List Style'),
    '#description' => t('The style of the numbered list.'),
    '#type' => 'select',
    '#options' => array(
      '1' => t('Numbers'),
      'A' => t('Uppercase Letters'),
      'a' => t('Lowercase Letters'),
      'I' => t('Uppercase Roman Numerals'),
      'i' => t('Lowercase Roman Numerals'),
    ),
    '#default_value' => (isset($conf['open_eggheads_selected_projects_display_settings']['open_eggheads_selected_projects_list_style_ol']))
                             ? $conf['open_eggheads_selected_projects_display_settings']['open_eggheads_selected_projects_list_style_ol']
                             : '1',
    // Bulleted List Style only visible/required when List Type is Bulleted List.
    '#states' => array(
      'visible' => array(
        ':input[name="open_eggheads_selected_projects_display_settings[open_eggheads_selected_projects_list_type]"]' => array(
          'value' => 'ol',
        ),
      ),
      'required' => array(
        ':input[name="open_eggheads_selected_projects_display_settings[open_eggheads_selected_projects_list_type]"]' => array(
          'value' => 'ol',
        ),
      ),
    ),
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
function open_eggheads_ctools_plugins_open_eggheads_selected_projects_content_type_edit_form_submit($form, &$form_state) {
  // Store the values from the Edit Form fields in the $conf variable that CTools uses to render its plugins.
  foreach (array_keys($form_state['values']['open_eggheads_selected_projects_display_settings']) as $key) {
    if (isset($form_state['values']['open_eggheads_selected_projects_display_settings'][$key])) {
      $form_state['conf']['open_eggheads_selected_projects_display_settings'][$key] = $form_state['values']['open_eggheads_selected_projects_display_settings'][$key];
    }
  }
  
  // Clear previously cached version of open_eggheads_photo content type.
  cache_clear_all('open_eggheads_admin_interface:open_eggheads_ctools_plugins:open_eggheads_selected_projects', 'cache', TRUE);
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
function open_eggheads_ctools_plugins_open_eggheads_selected_projects_content_type_render($subtype, $conf, $args, $context = NULL) {  
  // Load the user's personal data saved in the Open Eggheads "Personal Data" form ("/admin/open-eggheads/personal-data").
  $personal_data = variable_get('open_eggheads_admin_interface_personal_data');
  
  $pane = new stdClass();
  $selected_projects_heading = t('Selected Projects');
  // Get the relevant data.
  $selected_projects = $personal_data['selected_projects_fieldset']['selected_project'];
  // Check to see if user has filled out any selected projects.
  $has_selected_projects = FALSE;
  foreach ($selected_projects as $selected_project) {
    if ($selected_project) {
      $has_selected_projects = TRUE;
      break;
    }
  }
  
  if ($has_selected_projects) { // User has filled out some selected projects.
    // Sanitize all data.
    foreach ($selected_projects as &$value) {
      $value = check_plain($value);
    }
    unset($value); // Break the reference with the last element.
    
    // Get heading size from the Edit Form above.
    $selected_projects_heading_size = (isset($conf['open_eggheads_selected_projects_display_settings']['open_eggheads_selected_projects_heading_size']))
                                    ? $conf['open_eggheads_selected_projects_display_settings']['open_eggheads_selected_projects_heading_size']
                                    : 'h2';
    // Get list type from the Edit Form above.
    $selected_projects_list_type = (isset($conf['open_eggheads_selected_projects_display_settings']['open_eggheads_selected_projects_list_type']))
                                    ? $conf['open_eggheads_selected_projects_display_settings']['open_eggheads_selected_projects_list_type']
                                    : 'ul';
    // Get bulleted list style from the Edit Form above.
    $selected_projects_list_style_ul = (isset($conf['open_eggheads_selected_projects_display_settings']['open_eggheads_selected_projects_list_style_ul']))
                                             ? $conf['open_eggheads_selected_projects_display_settings']['open_eggheads_selected_projects_list_style_ul']
                                             : 'disc';
    // Get numbered list style from the Edit Form above.
    $selected_projects_list_style_ol = (isset($conf['open_eggheads_selected_projects_display_settings']['open_eggheads_selected_projects_list_style_ol']))
                                             ? $conf['open_eggheads_selected_projects_display_settings']['open_eggheads_selected_projects_list_style_ol']
                                             : '1';
    
    // Define the CTools content pane array to be rendered on the page.
    $pane_content = array(
      '#type' => 'markup',
      '#markup' => theme(
        'open_eggheads_selected_projects', array(
          'selected_projects' => $selected_projects,
          'selected_projects_heading' => $selected_projects_heading,
          'selected_projects_heading_size' => $selected_projects_heading_size,
          'selected_projects_list_type' => $selected_projects_list_type,
          'selected_projects_list_style_ul' => $selected_projects_list_style_ul,
          'selected_projects_list_style_ol' => $selected_projects_list_style_ol,
        )
      ),
      '#cache' => array(
        'keys' => array('open_eggheads_admin_interface', 'open_eggheads_ctools_plugins', 'open_eggheads_selected_projects'),
        'bin' => 'cache',
        'expire' => CACHE_TEMPORARY,
        'granularity' => DRUPAL_CACHE_GLOBAL,
      ),
    );
  }
  else { // User has not specified any selected projects.
    // Set a warning message, so the user knows that their data is missing.
    $pane_content = array(
      '#type' => 'markup',
      '#markup' => t('<em>You haven\'t filled out any selected projects in the Open Eggheads Personal Data form.<br />You can find the form in the Open Eggheads Dashboard ("YOURDOMAIN.COM/admin/open-eggheads/data").</em>'),
      '#prefix' => '<div class="alert alert-danger" role="alert">',
      '#suffix' => '</div>',
      '#cache' => array(
        'keys' => array('open_eggheads_admin_interface', 'open_eggheads_ctools_plugins', 'open_eggheads_selected_projects'),
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
function open_eggheads_ctools_plugins_open_eggheads_selected_projects_content_type_theme(&$theme, $plugin) {
  $theme['open_eggheads_selected_projects'] = array(
    'arguments' => array(
      'selected_projects' => NULL,
      'selected_projects_heading' => NULL,
      'selected_projects_heading_size' => NULL,
      'selected_projects_list_type' => NULL,
      'selected_projects_list_style_ul' => NULL,
      'selected_projects_list_style_ol' => NULL,
    ),
    'template' => 'open-eggheads-selected-projects',
    'path' => $plugin['path'] . '/templates',
  );
}
