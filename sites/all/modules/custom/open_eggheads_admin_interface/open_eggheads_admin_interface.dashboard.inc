<?php

/**
 * Helper function for open_eggheads_admin_interface_menu().
 */
function _open_eggheads_admin_interface_dashboard() {
  $content = array();
  
  // Build the breadcrumbs in the format Home > News > Title Of Post
  $breadcrumb = array();
  $breadcrumb[] = l(t('Home'), '<front>');
  $breadcrumb[] = l(drupal_get_title(), request_path()); // Link to current URL
  // Set the breadcrumbs
  drupal_set_breadcrumb($breadcrumb);
  
  $content['dashboard_links'] = array(
    '#theme' => 'item_list',
    '#title' => t('Manage your website:'),
    '#items' => array(
      array(
        'data' => t('<a href="@url" class="@class"><strong>Personal Data</strong></a>', array(
          '@url' => url('admin/open-eggheads/personal-data'),
          '@class' => 'open-eggheads-personal-data',
        )),
        'children' => array(
          'description' => t('<em class="text-muted">Enter in your personal data to be displayed publicly on your site.</em>'),
        ),
      ),
      array(
        'data' => t('<a href="@url" class="@class"><strong>Appearance Editor</strong></a>', array(
          '@url' => url('admin/open-eggheads/appearance-editor'),
          '@class' => 'open-eggheads-appearance-editor',
        )),
        'children' => array(
          'description' => t('<em class="text-muted">Change the overall color scheme of your site.</em>'),
        ),
      ),
      array(
        'data' => t('<a href="@url" class="@class"><strong>Add Content</strong></a>', array(
          '@url' => url('admin/open-eggheads/add-content'),
          '@class' => 'open-eggheads-add-content',
        )),
        'children' => array(
          'description' => t('<em class="text-muted">Add new custom pages to your site.</em>'),
        ),
      ),
      array(
        'data' => t('<a href="@url" class="@class"><strong>Find Content</strong></a>', array(
          '@url' => url('admin/open-eggheads/find-content'),
          '@class' => 'open-eggheads-find-content',
        )),
        'children' => array(
          'description' => t('<em class="text-muted">View a list of any custom pages/content that you\'ve created.</em>'),
        ),
      ),
    ),
  );
  
  return $content;
}
