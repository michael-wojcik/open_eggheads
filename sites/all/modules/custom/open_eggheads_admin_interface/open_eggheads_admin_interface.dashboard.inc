<?php

/**
 * Helper function for open_eggheads_admin_interface_menu().
 */
function _open_eggheads_admin_interface_dashboard() {
  $content = array();
  
  $content['admin_links'] = array(
    '#theme' => 'item_list',
    '#title' => t('Manage your website:'),
    '#items' => array(
      t('<a href="@url">Personal Data</a>', array('@url' => url('admin/open-eggheads/data'))),
      t('<a href="@url">Appearance Editor</a>', array('@url' => url('admin/open-eggheads/appearance'))),
    ),
  );
  
  return $content;
}
