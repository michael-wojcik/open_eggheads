<?php
  
$plugin = array(
  'title' => t('Open Eggheads Basic Personal Info'),
  'description' => t('A ctools content plugin for displaying the site owner\' basic public information: name, title, affiliation, email, phone.'),
  'category' => t('Open Eggheads'),
  'single' => TRUE,
  'content_types' => 'open_eggheads_basic_info',
  'render callback' => 'open_eggheads_ctools_plugins_open_eggheads_basic_info_content_type_render',
  'hook theme' => 'open_eggheads_ctools_plugins_open_eggheads_basic_info_content_type_theme',
);

function open_eggheads_ctools_plugins_open_eggheads_basic_info_content_type_render($subtype, $conf, $args, $context = NULL) {  
  $personal_data = variable_get('open_eggheads_admin_interface_personal_data');
  
  $pane = new stdClass();
  $basic_info = $personal_data['basic_info'];
  // Sanitize all data.
  foreach ($basic_info as &$value) {
    $value = check_plain($value);
  }
  unset($value); // Break the reference with the last element.
  $pane_content = array(
    '#type' => 'markup',
    '#markup' => theme('open_eggheads_basic_info', array('basic_info' => $basic_info)),
    '#cache' => array(
      'keys' => array('open_eggheads_admin_interface', 'open_eggheads_ctools_plugins', 'open_eggheads_basic_info'),
      'bin' => 'cache',
      'expire' => CACHE_TEMPORARY,
      'granularity' => DRUPAL_CACHE_GLOBAL,
    ),
  );
  $pane->content = render($pane_content);
  return $pane;
}

function open_eggheads_ctools_plugins_open_eggheads_basic_info_content_type_theme(&$theme, $plugin) {
  $theme['open_eggheads_basic_info'] = array(
    'arguments' => array('basic_info' => NULL),
    'template' => 'open-eggheads-basic-info',
    'path' => $plugin['path'] . '/templates',
  );
}
