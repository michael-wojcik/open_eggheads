<?php

$info = array(
  // Available colors and color labels used in theme.
  'fields' => array(
    'primary' => t('Primary (for Headings, Progress Bars, etc.)'),
    'navbar' => t('Navbar'),
    'navbartext' => t('Navbar Text'),
    'link' => t('Link'),
    'linkhover' => t('Link Hover'),
    'background' => t('Background'),
    'bodytext' => t('Body Text'),
  ),
  // Pre-defined color schemes.
  'schemes' => array(
    'default' => array(
      'title' => t('Grayscale [Default Color Scheme]'),
      'colors' => array(
        'primary' => '#6F6F6F',
        'navbar' => '#333',
        'navbartext' => '#FFF',
        'link' => '#008CBA',
        'linkhover' => '#00526E',
        'background' => '#FFF',
        'bodytext' => '#222',
      ),
    ),
    'duke_blue' => array(
      'title' => t('Duke Blue'),
      'colors' => array(
        'primary' => '#0736A4',
        'navbar' => '#0736A4',
        'navbartext' => '#FFF',
        'link' => '#0736A4',
        'linkhover' => '#0680CD',
        'background' => '#FFF',
        'bodytext' => '#000',
      ),
    ),
    'harvard_crimson' => array(
      'title' => t('Harvard Crimson'),
      'colors' => array(
        'primary' => '#A51C30',
        'navbar' => '#A51C30',
        'navbartext' => '#FFF',
        'link' => '#A51C30',
        'linkhover' => '#DA253F',
        'background' => '#FFF',
        'bodytext' => '#000',
      ),
    ),
    'jet_black' => array(
      'title' => t('Jet Black'),
      'colors' => array(
        'primary' => '#FFF',
        'navbar' => '#060606',
        'navbartext' => '#FFF',
        'link' => '#FFF',
        'linkhover' => '#CCC',
        'background' => '#060606',
        'bodytext' => '#888',
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
