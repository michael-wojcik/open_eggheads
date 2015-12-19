<?php

/**
 * @file
 * File called in open_eggheads_admin_interface.module to set up the "Open Eggheads Dashboard" page.
 * The "Open Eggheads Dashboard" page functions as the main administrative hub for the user.
 * This page aims to allow the user to manage the vast majority of basic uses of their site.
 * The page consists of a list of five links:
 * - Personal Data (where the user can enter their pubicly available information and files)
 * - Appearance Editor (where the user can alter the color scheme of their site)
 * - Add Content (where the user can add new content to their site, including publications and custom pages)
 * - Find Content (where the user can locate and edit existing content on their site, including publications and custom pages)
 * - Frequently Asked Questions (where the user can find links to interactive tours that answer questions on how to use the site)
 */

/**
 * Helper function for open_eggheads_admin_interface_menu() to create the markup for the "Open Eggheads Dashboard" page.
 * 
 * @access private
 * @return void
 */
function _open_eggheads_admin_interface_dashboard() {
  $content = array();
  
  // Build the breadcrumbs in the format Home > News > Title Of Post
  $breadcrumb = array();
  $breadcrumb[] = l(t('Home'), '<front>');
  $breadcrumb[] = l(drupal_get_title(), request_path()); // Link to current URL
  // Set the breadcrumbs
  drupal_set_breadcrumb($breadcrumb);
  
  // Create page heading.
  $content['dashboard_links_heading'] = array(
    '#markup' => t('Manage Your Website'),
    '#prefix' => '<h2>',
    '#suffix' => '</h2>',
  );
  
  // Create list of links for the "Open Eggheads Dashboard" page.
  $content['dashboard_links'] = array(
    '#theme' => 'item_list',
    '#items' => array(
      // Create link to Open Eggheads "Personal Data" form.
      array(
        'data' => t('<a href="@url" class="@class"><strong>Personal Data</strong></a>', array(
          '@url' => url('admin/open-eggheads/personal-data'),
          '@class' => 'open-eggheads-personal-data h4',
        )),
        'children' => array(
          'description' => t('<em class="text-muted">Enter in your personal data to be displayed publicly on your site.</em>'),
        ),
      ),
      // Create link to Open Eggheads "Appearance Editor" page.
      array(
        'data' => t('<a href="@url" class="@class"><strong>Appearance Editor</strong></a>', array(
          '@url' => url('admin/open-eggheads/appearance-editor'),
          '@class' => 'open-eggheads-appearance-editor h4',
        )),
        'children' => array(
          'description' => t('<em class="text-muted">Change the overall color scheme of your site.</em>'),
        ),
      ),
      // Create link to Open Eggheads "Add Content" page.
      array(
        'data' => t('<a href="@url" class="@class"><strong>Add Content</strong></a>', array(
          '@url' => url('admin/open-eggheads/add-content'),
          '@class' => 'open-eggheads-add-content h4',
        )),
        'children' => array(
          'description' => t('<em class="text-muted">Add new custom pages to your site.</em>'),
        ),
      ),
      // Create link to Open Eggheads "Find Content" page.
      array(
        'data' => t('<a href="@url" class="@class"><strong>Find Content</strong></a>', array(
          '@url' => url('admin/open-eggheads/find-content'),
          '@class' => 'open-eggheads-find-content h4',
        )),
        'children' => array(
          'description' => t('<em class="text-muted">View a list of any publications, custom pages, and other content that you\'ve created.</em>'),
        ),
      ),
      // Create link to Open Eggheads "Frequently Asked Questions" page.
      array(
        'data' => t('<a href="@url" class="@class"><strong>Frequently Asked Questions</strong></a>', array(
          '@url' => url('admin/open-eggheads/faq'),
          '@class' => 'open-eggheads-faq h4',
        )),
        'children' => array(
          'description' => t('<em class="text-muted">Get information on how to use your Open Eggheads website.</em>'),
        ),
      ),
    ),
  );
  
  return $content;
}
