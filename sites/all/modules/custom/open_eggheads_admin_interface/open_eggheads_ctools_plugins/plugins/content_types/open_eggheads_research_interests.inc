<?php
  
$plugin = array(
  'title' => t('Open Eggheads Research Interests'),
  'description' => t('A ctools content plugin for displaying the site owner\' research interests.'),
  'category' => t('Open Eggheads'),
  'single' => TRUE,
  'content_types' => 'open_eggheads_research_interests',
  'edit form' => 'open_eggheads_ctools_plugins_open_eggheads_research_interests_content_type_edit_form',
  'render callback' => 'open_eggheads_ctools_plugins_open_eggheads_research_interests_content_type_render',
  'hook theme' => 'open_eggheads_ctools_plugins_open_eggheads_research_interests_content_type_theme',
);

/**
 * 'Edit form' callback for the content type.
 */
function open_eggheads_ctools_plugins_open_eggheads_research_interests_content_type_edit_form($form, &$form_state) {
  $conf = $form_state['conf'];
  
  $form['#tree'] = TRUE;
  
  $form['#attached']['css'] = array(
    drupal_get_path('module', 'open_eggheads_ctools_plugins') . '/css/open_eggheads_ctools_plugins.css' => array(
      'type' => 'file',
      'group' => CSS_THEME,
      'weight' => 100,
    ),
  );
  
  $form['open_eggheads_research_interests_display_settings'] = array(
    '#type' => 'fieldset',
    '#title' => t('Research Interests Display Settings'),
  );
  $form['open_eggheads_research_interests_display_settings']['open_eggheads_research_interests_list_type'] = array(
    '#title' => t('List Type'),
    '#description' => t('The type of list with which your research interests will be displayed.'),
    '#type' => 'select',
    '#options' => array(
      'ul' => t('Bulleted List'),
      'ol' => t('Numbered List'),
    ),
    '#default_value' => (isset($conf['open_eggheads_research_interests_display_settings']['open_eggheads_research_interests_list_type']))
                             ? $conf['open_eggheads_research_interests_display_settings']['open_eggheads_research_interests_list_type']
                             : 'ul',
    '#required' => TRUE,
  );
  $form['open_eggheads_research_interests_display_settings']['open_eggheads_research_interests_list_style_ul'] = array(
    '#title' => t('Bulleted List Style'),
    '#description' => t('The style of the bulleted list.'),
    '#type' => 'select',
    '#options' => array(
      'disc' => t('Disc'),
      'circle' => t('Circle'),
      'square' => t('Square'),
      'none' => t('None'),
    ),
    '#default_value' => (isset($conf['open_eggheads_research_interests_display_settings']['open_eggheads_research_interests_list_style_ul']))
                             ? $conf['open_eggheads_research_interests_display_settings']['open_eggheads_research_interests_list_style_ul']
                             : 'disc',
    // Bulleted List Style only visible/required when List Type is Bulleted List.
    '#states' => array(
      'visible' => array(
        ':input[name="open_eggheads_research_interests_display_settings[open_eggheads_research_interests_list_type]"]' => array(
          'value' => 'ul',
        ),
      ),
      'required' => array(
        ':input[name="open_eggheads_research_interests_display_settings[open_eggheads_research_interests_list_type]"]' => array(
          'value' => 'ul',
        ),
      ),
    ),
  );
  $form['open_eggheads_research_interests_display_settings']['open_eggheads_research_interests_list_style_ol'] = array(
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
    '#default_value' => (isset($conf['open_eggheads_research_interests_display_settings']['open_eggheads_research_interests_list_style_ol']))
                             ? $conf['open_eggheads_research_interests_display_settings']['open_eggheads_research_interests_list_style_ol']
                             : '1',
    // Bulleted List Style only visible/required when List Type is Bulleted List.
    '#states' => array(
      'visible' => array(
        ':input[name="open_eggheads_research_interests_display_settings[open_eggheads_research_interests_list_type]"]' => array(
          'value' => 'ol',
        ),
      ),
      'required' => array(
        ':input[name="open_eggheads_research_interests_display_settings[open_eggheads_research_interests_list_type]"]' => array(
          'value' => 'ol',
        ),
      ),
    ),
  );
  
  return $form;
}

/**
 * The submit form stores the data in $conf.
 */
function open_eggheads_ctools_plugins_open_eggheads_research_interests_content_type_edit_form_submit($form, &$form_state) {
  foreach (array_keys($form_state['values']['open_eggheads_research_interests_display_settings']) as $key) {
    if (isset($form_state['values']['open_eggheads_research_interests_display_settings'][$key])) {
      $form_state['conf']['open_eggheads_research_interests_display_settings'][$key] = $form_state['values']['open_eggheads_research_interests_display_settings'][$key];
    }
  }
  
  // Clear previously cached version of open_eggheads_photo content type.
  cache_clear_all('open_eggheads_admin_interface:open_eggheads_ctools_plugins:open_eggheads_research_interests', 'cache');
}

function open_eggheads_ctools_plugins_open_eggheads_research_interests_content_type_render($subtype, $conf, $args, $context = NULL) {  
  $personal_data = variable_get('open_eggheads_admin_interface_personal_data');
  
  $pane = new stdClass();
  $pane->title = t('Research Interests');
  $research_interests = $personal_data['research_interests_fieldset']['research_interest'];
  // Check to see if user has filled out any research interests.
  $has_research_interests = FALSE;
  foreach ($research_interests as $research_interest) {
    if ($research_interest) {
      $has_research_interests = TRUE;
      break;
    }
  }
  
  if ($has_research_interests) { // User has filled out some research interests.
    // Sanitize all data.
    foreach ($research_interests as &$value) {
      $value = check_plain($value);
    }
    unset($value); // Break the reference with the last element.
    
    // Get list type.
    $research_interests_list_type = (isset($conf['open_eggheads_research_interests_display_settings']['open_eggheads_research_interests_list_type']))
                                    ? $conf['open_eggheads_research_interests_display_settings']['open_eggheads_research_interests_list_type']
                                    : 'ul';
    // Get bulleted list style.
    $research_interests_list_style_ul = (isset($conf['open_eggheads_research_interests_display_settings']['open_eggheads_research_interests_list_style_ul']))
                                             ? $conf['open_eggheads_research_interests_display_settings']['open_eggheads_research_interests_list_style_ul']
                                             : 'disc';
    // Get numbered list style.
    $research_interests_list_style_ol = (isset($conf['open_eggheads_research_interests_display_settings']['open_eggheads_research_interests_list_style_ol']))
                                             ? $conf['open_eggheads_research_interests_display_settings']['open_eggheads_research_interests_list_style_ol']
                                             : '1';
    
    $pane_content = array(
      '#type' => 'markup',
      '#markup' => theme(
        'open_eggheads_research_interests', array(
          'research_interests' => $research_interests,
          'research_interests_list_type' => $research_interests_list_type,
          'research_interests_list_style_ul' => $research_interests_list_style_ul,
          'research_interests_list_style_ol' => $research_interests_list_style_ol,
        )
      ),
      '#cache' => array(
        'keys' => array('open_eggheads_admin_interface', 'open_eggheads_ctools_plugins', 'open_eggheads_research_interests'),
        'bin' => 'cache',
        'expire' => CACHE_TEMPORARY,
        'granularity' => DRUPAL_CACHE_GLOBAL,
      ),
    );
  }
  else { // User has not specified any research interests.
    $pane_content = array(
      '#type' => 'markup',
      '#markup' => t('<em>You haven\'t filled out any research interests in the Open Eggheads Personal Data form.<br />You can find the form in the Open Eggheads Dashboard ("YOURDOMAIN.COM/admin/open-eggheads/data").</em>'),
      '#prefix' => '<div class="alert alert-danger" role="alert">',
      '#suffix' => '</div>',
      '#cache' => array(
        'keys' => array('open_eggheads_admin_interface', 'open_eggheads_ctools_plugins', 'open_eggheads_research_interests'),
        'bin' => 'cache',
        'expire' => CACHE_TEMPORARY,
        'granularity' => DRUPAL_CACHE_GLOBAL,
      ),
    );
  }
  $pane->content = render($pane_content);
  return $pane;
}

function open_eggheads_ctools_plugins_open_eggheads_research_interests_content_type_theme(&$theme, $plugin) {
  $theme['open_eggheads_research_interests'] = array(
    'arguments' => array(
      'research_interests' => NULL,
      'research_interests_list_type' => NULL,
      'research_interests_list_style_ul' => NULL,
      'research_interests_list_style_ol' => NULL,
    ),
    'template' => 'open-eggheads-research-interests',
    'path' => $plugin['path'] . '/templates',
  );
}
