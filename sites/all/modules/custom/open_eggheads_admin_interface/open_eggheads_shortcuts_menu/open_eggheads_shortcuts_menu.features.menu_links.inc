<?php
/**
 * @file
 * open_eggheads_shortcuts_menu.features.menu_links.inc
 */

/**
 * Implements hook_menu_default_menu_links().
 */
function open_eggheads_shortcuts_menu_menu_default_menu_links() {
  $menu_links = array();

  // Exported menu link: shortcut-set-1_add-content:node/add
  $menu_links['shortcut-set-1_add-content:node/add'] = array(
    'menu_name' => 'shortcut-set-1',
    'link_path' => 'node/add',
    'router_path' => 'node/add',
    'link_title' => 'Add content',
    'options' => array(
      'identifier' => 'shortcut-set-1_add-content:node/add',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -50,
    'customized' => 0,
  );
  // Exported menu link: shortcut-set-1_edit-theme:admin/appearance/settings/yeti
  $menu_links['shortcut-set-1_edit-theme:admin/appearance/settings/yeti'] = array(
    'menu_name' => 'shortcut-set-1',
    'link_path' => 'admin/appearance/settings/yeti',
    'router_path' => 'admin/appearance/settings/yeti',
    'link_title' => 'Edit theme',
    'options' => array(
      'identifier' => 'shortcut-set-1_edit-theme:admin/appearance/settings/yeti',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -48,
    'customized' => 0,
  );
  // Exported menu link: shortcut-set-1_find-content:admin/content
  $menu_links['shortcut-set-1_find-content:admin/content'] = array(
    'menu_name' => 'shortcut-set-1',
    'link_path' => 'admin/content',
    'router_path' => 'admin/content',
    'link_title' => 'Find content',
    'options' => array(
      'identifier' => 'shortcut-set-1_find-content:admin/content',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -49,
    'customized' => 0,
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('Add content');
  t('Edit theme');
  t('Find content');

  return $menu_links;
}
