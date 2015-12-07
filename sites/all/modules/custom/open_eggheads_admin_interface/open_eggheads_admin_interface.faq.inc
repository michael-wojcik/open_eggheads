<?php

/**
 * Helper function for open_eggheads_admin_interface_menu().
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
        'href' => 'admin/open-eggheads/add-content',
        'attributes' => array(
          'title' => t('Find out how to update your publicly available information.'),
          'class' => array('h4'),
        ),
        'query' => array(
          'tour' => '',
        ),
      ),
      'list-group-item 4' => array(
        'title' => t('How do I find/edit publications on my Research page?'),
        'href' => 'admin/open-eggheads/add-content',
        'attributes' => array(
          'title' => t('Find out how to update your publicly available information.'),
          'class' => array('h4'),
        ),
        'query' => array(
          'tour' => '',
        ),
      ),
    ),
  );
  
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
        'href' => '',
        'attributes' => array(
          'title' => t(''),
          'class' => array('h4'),
        ),
        'query' => array(
          'tour' => '',
        ),
      ),
      'list-group-item 1' => array(
        'title' => t('How do I customize the layout of a page?'),
        'href' => '',
        'attributes' => array(
          'title' => t(''),
          'class' => array('h4'),
        ),
        'query' => array(
          'tour' => '',
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
