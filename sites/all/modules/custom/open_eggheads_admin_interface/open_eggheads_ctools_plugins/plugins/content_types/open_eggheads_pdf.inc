<?php
  
$plugin = array(
  'title' => t('Open Eggheads PDF'),
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
 */
function open_eggheads_ctools_plugins_open_eggheads_pdf_content_type_edit_form($form, &$form_state) {
  $conf = $form_state['conf'];
  
  $form['#tree'] = TRUE;
  
  $form['#attached']['css'] = array(
    drupal_get_path('module', 'open_eggheads_ctools_plugins') . '/css/open_eggheads_ctools_plugins.css' => array(
      'type' => 'file',
      'group' => CSS_THEME,
      'weight' => 100,
    ),
  );
  
  $form['open_eggheads_pdf_display_settings'] = array(
    '#type' => 'fieldset',
    '#title' => t('PDF Display Settings'),
  );
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
  $form['open_eggheads_pdf_display_settings']['open_eggheads_pdf_zoom'] = array(
    '#title' => t('Zoom'),
    '#description' => t('The zoom level when viewing the PDF on the page.'),
    '#type' => 'select',
    '#options' => array(
      'auto' => t('Automatic Zoom'),
      'page-width' => t('Page Width'),
      'page-height' => t('Page Height'),
      'page-fit' => t('Page Fit'),
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
      : 'auto',
    '#required' => TRUE,
  );
  
  return $form;
}

/**
 * The submit form stores the data in $conf.
 */
/*
function open_eggheads_ctools_plugins_open_eggheads_pdf_content_type_edit_form_validate($form, &$form_state) {
  $width = $form_state['values']['open_eggheads_pdf_width'];
  // Confirm that width value is a positive integer between 1 and 100.
  if ($width !== '' && (!is_numeric($width) || intval($width) != $width || $width <= 0 || $width > 100)) {
    form_set_error('open_eggheads_pdf_display_settings][open_eggheads_pdf_width', t('Enter an integer between 1 and 100.'));
  }
}
/*

/**
 * The submit form stores the data in $conf.
 */
function open_eggheads_ctools_plugins_open_eggheads_pdf_content_type_edit_form_submit($form, &$form_state) {
  foreach (array('open_eggheads_pdf_width', 'open_eggheads_pdf_height', 'open_eggheads_pdf_zoom') as $key) {
    if (isset($form_state['values']['open_eggheads_pdf_display_settings'][$key])) {
      $form_state['conf']['open_eggheads_pdf_display_settings'][$key] = $form_state['values']['open_eggheads_pdf_display_settings'][$key];
    }
  }
}

/**
 * Render callback for the content type.
 */
function open_eggheads_ctools_plugins_open_eggheads_pdf_content_type_render($subtype, $conf, $args, $context = NULL) {  
  $personal_data = variable_get('open_eggheads_admin_interface_personal_data');
  
  $pane = new stdClass();
  $pane->title = t('Curriculum Vitae');
  $pdf_fid = $personal_data['files']['cv'];
  if ($pdf_fid) { // If user has uploaded their CV as a PDF…
    $file_path = file_create_url(file_load($pdf_fid)->uri); // Fetch URL of user's cv.
    $pane_content = array(
      '#type' => 'markup',
      '#markup' => theme(
        'open_eggheads_pdf', array(
          'file_path' => $file_path,
          'width' => (isset($conf['open_eggheads_pdf_display_settings']['open_eggheads_pdf_width']))
            ? $conf['open_eggheads_pdf_display_settings']['open_eggheads_pdf_width']
            : '100',
          'height' => (isset($conf['open_eggheads_pdf_display_settings']['open_eggheads_pdf_height']))
            ? $conf['open_eggheads_pdf_display_settings']['open_eggheads_pdf_height']
            : '720',
          'zoom' => (isset($conf['open_eggheads_pdf_display_settings']['open_eggheads_pdf_zoom']))
            ? $conf['open_eggheads_pdf_display_settings']['open_eggheads_pdf_zoom']
            : 'auto',
        )
      ),
      /*
      '#cache' => array(
        'keys' => array('open_eggheads_admin_interface', 'open_eggheads_ctools_plugins', 'open_eggheads_pdf'),
        'bin' => 'cache',
        'expire' => CACHE_TEMPORARY,
        'granularity' => DRUPAL_CACHE_GLOBAL,
      ),
      */
    );
  }
  else { // User has NOT uploaded their CV as a PDF…
    $pane_content = array(
      '#type' => 'markup',
      '#markup' => t('<em>User has not uploaded their CV as a PDF file.<br />Use the Open Eggheads Dashboard ("/admin/open-eggheads") to upload a CV.</em>'),
      '#prefix' => '<div class="alert alert-danger" role="alert">',
      '#suffix' => '</div>',
      /*
      '#cache' => array(
        'keys' => array('open_eggheads_admin_interface', 'open_eggheads_ctools_plugins', 'open_eggheads_pdf'),
        'bin' => 'cache',
        'expire' => CACHE_TEMPORARY,
        'granularity' => DRUPAL_CACHE_GLOBAL,
      ),
      */
    );
  }
  $pane->content = render($pane_content);
  return $pane;
}

/**
 * Hook theme callback for the content type, to register its template with Drupal theme system.
 */
function open_eggheads_ctools_plugins_open_eggheads_pdf_content_type_theme(&$theme, $plugin) {
  $theme['open_eggheads_pdf'] = array(
    'arguments' => array(
      'file_path' => NULL,
      'width' => '100',
      'height' => '720',
      'zoom' => 'auto',
    ),
    'template' => 'open-eggheads-pdf',
    'path' => $plugin['path'] . '/templates',
  );
}
