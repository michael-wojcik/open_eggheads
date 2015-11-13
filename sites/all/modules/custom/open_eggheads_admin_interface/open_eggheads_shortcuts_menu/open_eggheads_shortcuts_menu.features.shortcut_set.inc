<?php
/**
 * @file
 * open_eggheads_shortcuts_menu.features.shortcut_set.inc
 */

/**
 * Implements hook_shortcut_default_shortcut_set().
 */
function open_eggheads_shortcuts_menu_shortcut_default_shortcut_set() {
  $shortcut_sets = array();
  $shortcut_sets['shortcut-set-1'] = array(
    'set_name' => 'shortcut-set-1',
    'title' => 'Shortcuts',
  );
  return $shortcut_sets;
}
