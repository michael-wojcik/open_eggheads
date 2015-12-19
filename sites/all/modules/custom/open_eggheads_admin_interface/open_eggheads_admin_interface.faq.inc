<?php

/**
 * @file
 * File called in open_eggheads_admin_interface.module to set up the "Frequently Asked Questions" page.
 * This file sets up the list of links that trigger interactive, JavaScript tours through the Open Eggheads site.
 * Each link is phrased in the form of a common question that a user migh have about how to use their site.
 */

/**
 * Helper function for open_eggheads_admin_interface_menu().
 * Creates the list of links that take users on different tours of their Open Eggheads site.
 * The "Frequently Asked Questions" are divided into two sets of links, based on the user's level of knowledge:
 * - New Users
 * - Advanced Users
 * 
 * @access private
 * @return void
 */
function _open_eggheads_admin_interface_faq() {
  $content = array();
  
  // Build the breadcrumbs in the format Home > News > Title Of Post
  $breadcrumb = array();
  $breadcrumb[] = l(t('Home'), '<front>');
  $breadcrumb[] = l(t('Open Eggheads Dashboard'), 'admin/open-eggheads');
  $breadcrumb[] = l(drupal_get_title(), request_path()); // Link to current URL
  // Set the breadcrumbs
  drupal_set_breadcrumb($breadcrumb);
  
  $content['faq_description'] = array(
    '#markup' => t('Click on any question to start a tour that gives the answer.'),
    '#prefix' => '<p class="text-muted"><em>',
    '#suffix' => '</em></p>',
  );
  
  /****************************************************************
  * Set of FAQs aimed towards New Users of an Open Eggheads site: *
  ****************************************************************/
  $content['faq_new_users'] = array(
    '#theme' => 'links',
    '#heading' => array(
      'text' => t('New Users:'),
      'level' => 'h3',
    ),
    '#attributes' => array(
      'class' => array('list-group'),
    ),
    '#links' => array(
      'list-group-item 0' => array(
        'title' => t('How do I start using Open Eggheads and where do I begin?'),
        'href' => base_path(),
        'attributes' => array(
          'title' => t('First time using Open Eggheads? Start here!'),
          'class' => array('h4'),
        ),
        'query' => array(
          'tour' => 'open_eggheads_welcome_tour',
        ),
      ),
      'list-group-item 1' => array(
        'title' => t('How do I personalize my website with my own information?'),
        'href' => 'admin/open-eggheads',
        'attributes' => array(
          'title' => t('Find out how to update your publicly available information.'),
          'class' => array('h4'),
        ),
        'query' => array(
          'tour' => 'open_eggheads_personal_data_tour',
        ),
      ),
      'list-group-item 2' => array(
        'title' => t('How do I change the color scheme of my website?'),
        'href' => 'admin/open-eggheads',
        'attributes' => array(
          'title' => t('Find out how to change the appearance of your site.'),
          'class' => array('h4'),
        ),
        'query' => array(
          'tour' => 'open_eggheads_appearance_editor_tour',
        ),
      ),
      'list-group-item 3' => array(
        'title' => t('How do I add publications/works-in-progress to my Research page?'),
        'href' => 'admin/open-eggheads',
        'attributes' => array(
          'title' => t('Find out how to add your publications/works-in-progress to your Open Eggheads site.'),
          'class' => array('h4'),
        ),
        'query' => array(
          'tour' => 'open_eggheads_add_publication_tour',
        ),
      ),
      'list-group-item 4' => array(
        'title' => t('How do I update publications/works-in-progress on my Research page?'),
        'href' => 'admin/open-eggheads',
        'attributes' => array(
          'title' => t('Find out how to find and edit your previously entered publications.'),
          'class' => array('h4'),
        ),
        'query' => array(
          'tour' => 'open_eggheads_update_publication_tour',
        ),
      ),
    ),
  );
  
  /*********************************************************************
  * Set of FAQs aimed towards Advanced Users of an Open Eggheads site: *
  *********************************************************************/
  $content['faq_advanced_users'] = array(
    '#theme' => 'links',
    '#heading' => array(
      'text' => t('Advanced Users:'),
      'level' => 'h3',
    ),
    '#attributes' => array(
      'class' => array('list-group'),
    ),
    '#links' => array(
      'list-group-item 0' => array(
        'title' => t('How do I customize the content on a page?'),
        'href' => base_path(),
        'attributes' => array(
          'title' => t('Find out how to alter the content that appears on a specific page.'),
          'class' => array('h4'),
        ),
        'query' => array(
          'tour' => 'open_eggheads_custom_page_content_tour',
        ),
      ),
      'list-group-item 1' => array(
        'title' => t('How do I customize the layout of a page?'),
        'href' => '',
        'attributes' => array(
          'title' => t('Find out how to alter the layout of content on a specific page.'),
          'class' => array('h4'),
        ),
        'query' => array(
          'tour' => 'open_eggheads_custom_page_layout_tour',
        ),
      ),
      'list-group-item 2' => array(
        'title' => t('How do I add a custom page to my site?'),
        'href' => 'admin/open-eggheads',
        'attributes' => array(
          'title' => t('Learn how to add an entirely new page to your site.'),
          'class' => array('h4'),
        ),
        'query' => array(
          'tour' => 'open_eggheads_add_content_tour',
        ),
      ),
    ),
  );
  
  return $content;
}
