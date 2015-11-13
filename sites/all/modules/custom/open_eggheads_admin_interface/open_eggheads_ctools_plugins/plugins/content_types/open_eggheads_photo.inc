<?php
  
$plugin = array(
  'title' => t('Open Eggheads Photo'),
  'description' => t('A basic ctools content plugin for displaying a photo panel pane.'),
  'category' => t('Open Eggheads'),
  'single' => TRUE,
  'content_types' => 'open_eggheads_photo',
  'render callback' => 'open_eggheads_ctools_plugins_open_eggheads_photo_content_type_render',
  'hook theme' => 'open_eggheads_ctools_plugins_open_eggheads_photo_content_type_theme',
);

function open_eggheads_ctools_plugins_open_eggheads_photo_content_type_render($subtype, $conf, $args, $context = NULL) {  
  $personal_data = variable_get('open_eggheads_admin_interface_personal_data');
  
  $pane = new stdClass();
  $photo_fid = $personal_data['files']['photo'];
  if ($photo_fid) { // If user has uploaded their photo…
    $file_path = file_create_url(file_load($photo_fid)->uri); // Fetch URL of user's photo.
    $pane_content = array(
      '#type' => 'markup',
      '#markup' => theme('open_eggheads_photo', array('file_path' => $file_path)),
      '#cache' => array(
        'keys' => array('open_eggheads_admin_interface', 'open_eggheads_ctools_plugins', 'open_eggheads_photo'),
        'bin' => 'cache',
        'expire' => CACHE_TEMPORARY,
        'granularity' => DRUPAL_CACHE_GLOBAL,
      ),
    );
  }
  else { // User has NOT uploaded their photo…
    $pane_content = array(
      '#type' => 'markup',
      '#markup' => t('<em>User has not uploaded their photo.<br />Use the Open Eggheads Dashboard ("/admin/open-eggheads") to upload a photo.</em>'),
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

function open_eggheads_ctools_plugins_open_eggheads_photo_content_type_theme(&$theme, $plugin) {
  $theme['open_eggheads_photo'] = array(
    'arguments' => array('file_path' => NULL),
    'template' => 'open-eggheads-photo',
    'path' => $plugin['path'] . '/templates',
  );
}
