<?php

$info = array(
  // Available colors and color labels used in theme.
  'fields' => array(
    'primary' => t('Primary'),
    'navbar' => t('Navbar'),
    'link' => t('Link'),
    'linkhover' => t('Link Hover'),
  ),
  // Pre-defined color schemes.
  'schemes' => array(
    'default' => array(
      'title' => t('Black & White [Default Color Scheme]'),
      'colors' => array(
        'primary' => '#1abc9c',
        'navbar' => '#1abc9c',
        'link' => '#1abc9c',
        'linkhover' => '#7b7b7b',
      ),
    ),
    'duke_blue' => array(
      'title' => t('Duke Blue'),
      'colors' => array(
        'primary' => '#0736A4',
        'navbar' => '#0736A4',
        'link' => '#0736A4',
        'linkhover' => '#0680CD',
      ),
    ),
  ),

  // Gradient definitions.
  'gradients' => array(
    array(
      // (x, y, width, height).
      'dimension' => array(0, 0, 0, 0),
      // Direction of gradient ('vertical' or 'horizontal').
      'direction' => 'vertical',
      // Keys of colors to use for the gradient.
      'colors' => array('top', 'bottom'),
    ),
  ),

);
