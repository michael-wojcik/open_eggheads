<?php
  
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
 */
function open_eggheads_ctools_plugins_open_eggheads_basic_info_content_type_edit_form($form, &$form_state) {
  $conf = $form_state['conf'];
  
  $form['#tree'] = TRUE;
  
  $form['#attached']['css'] = array(
    drupal_get_path('module', 'open_eggheads_ctools_plugins') . '/css/open_eggheads_ctools_plugins.css' => array(
      'type' => 'file',
      'group' => CSS_THEME,
      'weight' => 100,
    ),
  );
  
  $form['open_eggheads_basic_info_display_settings'] = array(
    '#type' => 'fieldset',
    '#title' => t('Basic Info Display Settings'),
  );
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
 * The submit form stores the data in $conf.
 */
function open_eggheads_ctools_plugins_open_eggheads_basic_info_content_type_edit_form_submit($form, &$form_state) {
  foreach (array_keys($form_state['values']['open_eggheads_basic_info_display_settings']) as $key) {
    if (isset($form_state['values']['open_eggheads_basic_info_display_settings'][$key])) {
      $form_state['conf']['open_eggheads_basic_info_display_settings'][$key] = $form_state['values']['open_eggheads_basic_info_display_settings'][$key];
    }
  }
  
  // Clear previously cached version of open_eggheads_photo content type.
  cache_clear_all('open_eggheads_admin_interface:open_eggheads_ctools_plugins:open_eggheads_basic_info', 'cache', TRUE);
}

function open_eggheads_ctools_plugins_open_eggheads_basic_info_content_type_render($subtype, $conf, $args, $context = NULL) {  
  $personal_data = variable_get('open_eggheads_admin_interface_personal_data');
  
  $pane = new stdClass();
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
    
    // Get heading size.
    $basic_info_heading_size = (isset($conf['open_eggheads_basic_info_display_settings']['open_eggheads_basic_info_heading_size']))
                                    ? $conf['open_eggheads_basic_info_display_settings']['open_eggheads_basic_info_heading_size']
                                    : 'h1';
    // Get text size.
    $basic_info_text_size = (isset($conf['open_eggheads_basic_info_display_settings']['open_eggheads_basic_info_text_size']))
                                 ? $conf['open_eggheads_basic_info_display_settings']['open_eggheads_basic_info_text_size']
                                 : 'normal';
    // Get photo alignment CSS class.
    $basic_info_alignment = (isset($conf['open_eggheads_basic_info_display_settings']['open_eggheads_basic_info_alignment']))
                                 ? $conf['open_eggheads_basic_info_display_settings']['open_eggheads_basic_info_alignment']
                                 : 'text-left';
    // Concatenate all photo CSS classes.
    $basic_info_classes = $basic_info_alignment;
    
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
