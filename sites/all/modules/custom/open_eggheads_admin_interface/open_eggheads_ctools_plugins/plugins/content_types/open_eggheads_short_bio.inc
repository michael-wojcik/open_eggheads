<?php
  
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
 */
function open_eggheads_ctools_plugins_open_eggheads_short_bio_content_type_edit_form($form, &$form_state) {
  $conf = $form_state['conf'];
  
  $form['#tree'] = TRUE;
  
  $form['#attached']['css'] = array(
    drupal_get_path('module', 'open_eggheads_ctools_plugins') . '/css/open_eggheads_ctools_plugins.css' => array(
      'type' => 'file',
      'group' => CSS_THEME,
      'weight' => 100,
    ),
  );
  
  $form['open_eggheads_short_bio_display_settings'] = array(
    '#type' => 'fieldset',
    '#title' => t('Short Bio Display Settings'),
  );
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
 * The submit form stores the data in $conf.
 */
function open_eggheads_ctools_plugins_open_eggheads_short_bio_content_type_edit_form_submit($form, &$form_state) {
  foreach (array_keys($form_state['values']['open_eggheads_short_bio_display_settings']) as $key) {
    if (isset($form_state['values']['open_eggheads_short_bio_display_settings'][$key])) {
      $form_state['conf']['open_eggheads_short_bio_display_settings'][$key] = $form_state['values']['open_eggheads_short_bio_display_settings'][$key];
    }
  }
  
  // Clear previously cached version of open_eggheads_photo content type.
  cache_clear_all('open_eggheads_admin_interface:open_eggheads_ctools_plugins:open_eggheads_short_bio', 'cache', TRUE);
}

function open_eggheads_ctools_plugins_open_eggheads_short_bio_content_type_render($subtype, $conf, $args, $context = NULL) {  
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
    // Get heading size.
    $short_bio_heading_size = (isset($conf['open_eggheads_short_bio_display_settings']['open_eggheads_short_bio_heading_size']))
                                    ? $conf['open_eggheads_short_bio_display_settings']['open_eggheads_short_bio_heading_size']
                                    : 'h2';
    // Get text size.
    $short_bio_text_size = (isset($conf['open_eggheads_short_bio_display_settings']['open_eggheads_short_bio_text_size']))
                                ? $conf['open_eggheads_short_bio_display_settings']['open_eggheads_short_bio_text_size']
                                : 'normal';
    // Get text alignment CSS class.
    $short_bio_text_alignment = (isset($conf['open_eggheads_short_bio_display_settings']['open_eggheads_short_bio_text_alignment']))
                                     ? $conf['open_eggheads_short_bio_display_settings']['open_eggheads_short_bio_text_alignment']
                                     : 'text-left';
    
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
