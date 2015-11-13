<?php
/**
* Defines a style plugin
*
*  - panestyles: corresponds to directory name of plugin
*  - render pane: the suffix of the theme function for the pane (without "theme_").
*     - Example: If the function name is "theme_panestyles_render_pane",
*       the value of "render pane" is "panestyles_render_pane".
*  - render region: the suffix of the theme function for the region (without "theme_").
*     - Example: If the function name is "theme_panestyles_render_region",
*       the value of "render region" is "panestyles_render_region".
*  - pane settings form: name of function that returns a settings form
*  - hook theme: array of hook theme information
*    - define an array for pane and region. The key must match the first parameter of the returned theme() in the 
*       corresponding theme_ function.
*       Example: 'hook theme' => 'panestyles_theme_pane' => array();
*        In function theme_panestyles_render_pane:
*          return theme('panestyles_theme_pane'...) [truncated]
*      - template: corresponds to name of tpl.php for pane, i.e. panestyles-pane.tpl.php
*      - path: the path where the template file lives
*      - variables: an array of variables to add to the $variables array in the theme function
*
*/

$plugin =  array(
  'open_eggheads_pane_styles' => array(
    'title' => t('Open Eggheads Pane Styles'),
    'description'   => t('Simple styles that highlight sections of your page.'),
    'render pane' => 'open_eggheads_pane_styles_render_pane',
    'render region' => 'open_eggheads_pane_styles_render_region',
    'pane settings form' => 'open_eggheads_pane_styles_settings_form',
    'hook theme'    => array(
      'open_eggheads_pane_styles_theme_pane' => array(
        'template' => 'open-eggheads-pane-styles-pane',
         'path' => drupal_get_path('module', 'open_eggheads_ctools_plugins') . '/plugins/styles/templates',
         'variables' => array(
           'content' => NULL,
           'settings' => NULL,
         ),
       ),
      'open_eggheads_pane_styles_theme_region' => array(
        'template' => 'open-eggheads-pane-styles-region',
         'path' => drupal_get_path('module', 'open_eggheads_ctools_plugins') . '/plugins/styles/templates',
         'variables' => array(
           'content' => NULL,
         ),
       ),
    ),
  ),
);

function theme_open_eggheads_pane_styles_render_pane($vars) {
  $settings = $vars['settings'];
  $content = $vars['content'];

  return theme('open_eggheads_pane_styles_theme_pane', array('content' => $content, 'settings' => $settings));
}

function theme_open_eggheads_pane_styles_render_region($vars) {
    $content = '';

  foreach ($vars['panes'] as $pane_id => $pane_output) {
    $content .= $pane_output;
  }
  if (empty($content)) {
    return;
  }
  return theme('open_eggheads_pane_styles_theme_region', array('content' => $content));
}

function open_eggheads_pane_styles_settings_form($style_settings) {
  $form['description'] = array(
    '#markup' => 'NOTE: To use these styles, your site must use a Bootstrap-based theme, as is provided by default with your Open Eggheads site.',
    '#prefix' => '<div class="alert alert-warning" role="alert">',
    '#suffix' => '</div>',
  );
  
  $options = array(
    '' => t('Default'),
    'text-left' => t('Left-aligned'),
    'text-center' => t('Center-aligned'),
    'text-right' => t('Right-aligned'),
  );
  $headings = array(
    'pane-heading-default' => t('Default pane heading style.'),
    'pane-heading-secondary' => t('Bold heading style.'),
    'pane-heading-tertiary' => t('Small caps heading style.')
  );
 
  $form['my_pane_classes'] = array(
    '#type' => 'radios',
    '#title' => t('Pane Styles'),
    '#description' => t('Choose a style for your panel pane.'),
    '#options' => $options,
    '#required' => FALSE,
    '#default_value' => (isset($style_settings['my_pane_classes'])) ? $style_settings['my_pane_classes'] : '',
  );
  $form['heading_classes'] = array(
    '#type' => 'radios',
    '#title' => t('Header Styles'),
    '#description' => t('Choose a header style for your panel pane.'),
    '#options' => $headings,
    '#required' => FALSE,
    '#default_value' => (isset($style_settings['heading_classes'])) ? $style_settings['heading_classes'] : '',
  );
  
  return $form;
}
