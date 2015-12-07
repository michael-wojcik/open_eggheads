<?php
  
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
 */
function open_eggheads_ctools_plugins_open_eggheads_photo_content_type_edit_form($form, &$form_state) {
  $conf = $form_state['conf'];
  
  $form['#tree'] = TRUE;
  
  $form['#attached']['css'] = array(
    drupal_get_path('module', 'open_eggheads_ctools_plugins') . '/css/open_eggheads_ctools_plugins.css' => array(
      'type' => 'file',
      'group' => CSS_THEME,
      'weight' => 100,
    ),
  );
  
  $form['open_eggheads_photo_display_settings'] = array(
    '#type' => 'fieldset',
    '#title' => t('Photo Display Settings'),
  );
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
 * The submit form stores the data in $conf.
 */
function open_eggheads_ctools_plugins_open_eggheads_photo_content_type_edit_form_submit($form, &$form_state) {
  foreach (array_keys($form_state['values']['open_eggheads_photo_display_settings']) as $key) {
    if (isset($form_state['values']['open_eggheads_photo_display_settings'][$key])) {
      $form_state['conf']['open_eggheads_photo_display_settings'][$key] = $form_state['values']['open_eggheads_photo_display_settings'][$key];
    }
  }
  
  // Clear previously cached version of open_eggheads_photo content type.
  cache_clear_all('open_eggheads_admin_interface:open_eggheads_ctools_plugins:open_eggheads_photo', 'cache', TRUE);
}

function open_eggheads_ctools_plugins_open_eggheads_photo_content_type_render($subtype, $conf, $args, $context = NULL) {  
  $personal_data = variable_get('open_eggheads_admin_interface_personal_data');
  
  $pane = new stdClass();
  $photo_fid = $personal_data['files']['photo'];
  if ($photo_fid) { // If user has uploaded their photo…
    $file_path = file_create_url(file_load($photo_fid)->uri); // Fetch URL of user's photo.
    // Get photo width as percentage out of 100.
    $photo_width = (isset($conf['open_eggheads_photo_display_settings']['open_eggheads_photo_width']))
                        ? $conf['open_eggheads_photo_display_settings']['open_eggheads_photo_width']
                        : '100';
    // Get photo alignment CSS class.
    $photo_alignment = (isset($conf['open_eggheads_photo_display_settings']['open_eggheads_photo_alignment']))
                            ? $conf['open_eggheads_photo_display_settings']['open_eggheads_photo_alignment']
                            : 'pull-left';
    // Get photo shape CSS class.
    $photo_shape = (isset($conf['open_eggheads_photo_display_settings']['open_eggheads_photo_shape']))
                        ? $conf['open_eggheads_photo_display_settings']['open_eggheads_photo_shape']
                        : 'img-default';
    // Concatenate all photo CSS classes.
    $photo_classes = $photo_alignment.' '.$photo_shape;
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
