<?php

function open_eggheads_admin_interface_personal_data_form($form, &$form_state) {
  // Build the breadcrumbs in the format Home > News > Title Of Post
  $breadcrumb = array();
  $breadcrumb[] = l(t('Home'), '<front>');
  $breadcrumb[] = l(t('Open Eggheads Dashboard'), 'admin/open-eggheads');
  $breadcrumb[] = l(drupal_get_title(), request_path()); // Link to current URL
  // Set the breadcrumbs
  drupal_set_breadcrumb($breadcrumb);
  
  $form = array();
  
  $form['#tree'] = TRUE;
  
  $default_data = variable_get('open_eggheads_admin_interface_personal_data');
  
  /***************************************************************************
   * Basic Information
   ***************************************************************************/
  
  $form['open_eggheads_admin_interface_personal_data']['basic_info'] = array(
    '#type' => 'fieldset',
    '#title' => t('Basic Information'),
  );
  $form['open_eggheads_admin_interface_personal_data']['basic_info']['first_name'] = array(
    '#type' => 'textfield',
    '#title' => t('First Name'),
    '#default_value' => $default_data['basic_info']['first_name'],
    '#required' => TRUE,
  );
  $form['open_eggheads_admin_interface_personal_data']['basic_info']['last_name'] = array(
    '#type' => 'textfield',
    '#title' => t('Last Name'),
    '#default_value' => $default_data['basic_info']['last_name'],
    '#required' => TRUE,
  );
  $form['open_eggheads_admin_interface_personal_data']['basic_info']['title'] = array(
    '#type' => 'textfield',
    '#title' => t('Title'),
    '#default_value' => $default_data['basic_info']['title'],
    '#required' => TRUE,
    '#description' => t('Your level of study or employment.<br />E.g., "PhD Student", "Associate Professor", etc.'),
  );
  $form['open_eggheads_admin_interface_personal_data']['basic_info']['affiliation'] = array(
    '#type' => 'textfield',
    '#title' => t('Affiliation'),
    '#default_value' => $default_data['basic_info']['affiliation'],
    '#required' => TRUE,
    '#description' => t('Your current home institution.<br />E.g., "Hamburger University"'),
  );
  $form['open_eggheads_admin_interface_personal_data']['basic_info']['email'] = array(
    '#type' => 'textfield',
    '#title' => t('Email'),
    '#default_value' => $default_data['basic_info']['email'],
    '#description' => t('E.g., <em>yourname@example.com</em>'),
  );
  $form['open_eggheads_admin_interface_personal_data']['basic_info']['phone'] = array(
    '#type' => 'textfield',
    '#title' => t('Phone'),
    '#default_value' => $default_data['basic_info']['phone'],
    '#description' => t('Must be at least 10 characters long.<br />Can only contain digits, hyphens, parentheses, spaces, and plus signs (for international phone numbers).'),
  );
  
  /***************************************************************************
   * File Uploads
   ***************************************************************************/
  
  $form['open_eggheads_admin_interface_personal_data']['files'] = array(
    '#type' => 'fieldset',
    '#title' => t('Personal Files'),
  );
  $form['open_eggheads_admin_interface_personal_data']['files']['photo'] = array(
    '#type' => 'managed_file',
    '#title' => t('Photo'),
    '#description' => t('Upload your photo.<br />Must be in JPG, JPEG, PNG, or GIF format.'),
    '#default_value' => $default_data['files']['photo'],
    '#upload_validators' => array(
      'file_validate_extensions' => array('jpg jpeg png gif'),
    ),
    '#upload_location' => 'public://personal_data/photo/',
    '#progress_message' => t('Uploading…'),
  );
  $form['open_eggheads_admin_interface_personal_data']['files']['cv'] = array(
    '#type' => 'managed_file',
    '#title' => t('CV'),
    '#description' => t('Upload your CV.<br />Must be in PDF format.'),
    '#default_value' => $default_data['files']['cv'],
    '#upload_validators' => array(
      'file_validate_extensions' => array('pdf'),
    ),
    '#upload_location' => 'public://personal_data/cv/',
    '#progress_message' => t('Uploading…'),
  );
  
  /***************************************************************************
   * Research Interests
   ***************************************************************************/
  
  $form['open_eggheads_admin_interface_personal_data']['research_interests_fieldset'] = array(
    '#type' => 'fieldset',
    '#title' => t('Research Interests'),
    '#description' => t('Make a list of your current research interests, so that visitors can know what you study.'),
    // Set up the wrapper so that AJAX will be able to replace the fieldset.
    '#prefix' => '<div id="research-interests-fieldset-wrapper">',
    '#suffix' => '</div>',
  );

  // Build the fieldset with the proper number of research interests. We'll use
  // $form_state['num_research_interests'] to determine the number of textfields to build.
  
  //First, get number of research interests (if any) that were previously saved in the database.
  $num_research_interests = (isset($default_data['research_interests_fieldset'])) ? count($default_data['research_interests_fieldset']['research_interest']) : 0;
  // If user has not previously saved any reseach interests…
  if (empty($form_state['num_research_interests']) && empty($num_research_interests)) {
    // Set default number of research intersts fields to 1.
    $form_state['num_research_interests'] = 1;
  }
  // Else, set number of research interest fields equal to number of previously saved interests.
  // But only if form was not rebuilt due to user clicking "Add" or "Remove" buttons to change number of fields.
  elseif (!$form_state['rebuild']) {
    $form_state['num_research_interests'] = $num_research_interests;
  }
  
  for ($i = 0; $i < $form_state['num_research_interests']; $i++) {
    $form['open_eggheads_admin_interface_personal_data']['research_interests_fieldset']['research_interest'][$i] = array(
      '#type' => 'textfield',
      '#title' => t('Research Interest'),
      // Load user's previously saved interests, if available.
      '#default_value' => (isset($default_data['research_interests_fieldset']['research_interest'][$i]))
                               ? $default_data['research_interests_fieldset']['research_interest'][$i]
                               : '',
    );
  }
  $form['open_eggheads_admin_interface_personal_data']['research_interests_fieldset']['add_research_interest'] = array(
    '#type' => 'submit',
    '#name' => 'add_research_interest_button',
    '#value' => t('Add Another Interest'),
    '#submit' => array('_open_eggheads_admin_interface_personal_data_form_multiple_value_add_one'),
    '#ajax' => array(
      'callback' => '_open_eggheads_admin_interface_personal_data_form_multiple_value_callback',
      'wrapper' => 'research-interests-fieldset-wrapper',
    ),
  );
  if ($form_state['num_research_interests'] > 1) {
    $form['open_eggheads_admin_interface_personal_data']['research_interests_fieldset']['remove_research_interest'] = array(
      '#type' => 'submit',
      '#name' => 'remove_research_interest_button',
      '#value' => t('Remove An Interest'),
      '#submit' => array('_open_eggheads_admin_interface_personal_data_form_multiple_value_remove_one'),
      '#ajax' => array(
        'callback' => '_open_eggheads_admin_interface_personal_data_form_multiple_value_callback',
        'wrapper' => 'research-interests-fieldset-wrapper',
      ),
    );
  }
  
  /***************************************************************************
   * Selected Projects
   ***************************************************************************/
  
  $form['open_eggheads_admin_interface_personal_data']['selected_projects_fieldset'] = array(
    '#type' => 'fieldset',
    '#title' => t('Selected Projects'),
    '#description' => t('Make a list of some selected projects of yours, so that visitors can know what you\'re working on.'),
    // Set up the wrapper so that AJAX will be able to replace the fieldset.
    '#prefix' => '<div id="selected-projects-fieldset-wrapper">',
    '#suffix' => '</div>',
  );

  // Build the fieldset with the proper number of selected projects. We'll use
  // $form_state['num_selected_projects'] to determine the number of textfields to build.
  
  //First, get number of selected projects (if any) that were previously saved in the database.
  $num_selected_projects = (isset($default_data['selected_projects_fieldset'])) ? count($default_data['selected_projects_fieldset']['selected_project']) : 0;
  // If user has not previously saved any reseach interests…
  if (empty($form_state['num_selected_projects']) && empty($num_selected_projects)) {
    // Set default number of research intersts fields to 1.
    $form_state['num_selected_projects'] = 1;
  }
  // Else, set number of selected project fields equal to number of previously saved projects.
  // But only if form was not rebuilt due to user clicking "Add" or "Remove" buttons to change number of fields.
  elseif (!$form_state['rebuild']) {
    $form_state['num_selected_projects'] = $num_selected_projects;
  }
  
  for ($i = 0; $i < $form_state['num_selected_projects']; $i++) {
    $form['open_eggheads_admin_interface_personal_data']['selected_projects_fieldset']['selected_project'][$i] = array(
      '#type' => 'textfield',
      '#title' => t('Selected Project'),
      // Load user's previously saved projects, if available.
      '#default_value' => (isset($default_data['selected_projects_fieldset']['selected_project'][$i]))
                               ? $default_data['selected_projects_fieldset']['selected_project'][$i]
                               : '',
    );
  }
  $form['open_eggheads_admin_interface_personal_data']['selected_projects_fieldset']['add_selected_project'] = array(
    '#type' => 'submit',
    '#name' => 'add_selected_project_button',
    '#value' => t('Add Another Project'),
    '#submit' => array('_open_eggheads_admin_interface_personal_data_form_multiple_value_add_one'),
    '#ajax' => array(
      'callback' => '_open_eggheads_admin_interface_personal_data_form_multiple_value_callback',
      'wrapper' => 'selected-projects-fieldset-wrapper',
    ),
  );
  if ($form_state['num_selected_projects'] > 1) {
    $form['open_eggheads_admin_interface_personal_data']['selected_projects_fieldset']['remove_selected_project'] = array(
      '#type' => 'submit',
      '#name' => 'remove_selected_project_button',
      '#value' => t('Remove A Project'),
      '#submit' => array('_open_eggheads_admin_interface_personal_data_form_multiple_value_remove_one'),
      '#ajax' => array(
        'callback' => '_open_eggheads_admin_interface_personal_data_form_multiple_value_callback',
        'wrapper' => 'selected-projects-fieldset-wrapper',
      ),
    );
  }
  
  /***************************************************************************
   * End Of Form
   ***************************************************************************/
  
  $form['#submit'][] = 'open_eggheads_admin_interface_personal_data_form_submit';
  
  return system_settings_form($form);
}

function open_eggheads_admin_interface_personal_data_form_validate(&$form, &$form_state) {
  $email = $form_state['values']['open_eggheads_admin_interface_personal_data']['basic_info']['email'];
  if (!empty($email) && !valid_email_address($email)) {
    form_set_error('open_eggheads_admin_interface_personal_data][basic_info][email', t('Invalid email address.'));
  }
  
  $phone = $form_state['values']['open_eggheads_admin_interface_personal_data']['basic_info']['phone'];
  // Make sure phone number is in a valid format.
  $phone_regex = '/^[\d\+\(][\d\(\)\-\ \.]{8,32}[\d]$/';
  if (!empty($phone) && !preg_match($phone_regex, $phone)) {
    form_set_error('open_eggheads_admin_interface_personal_data][basic_info][phone', t('Invalid phone number.'));
  }
}

function open_eggheads_admin_interface_personal_data_form_submit(&$form, &$form_state) {
  global $user;
  $account_uid = $user->uid;
    
  $old_photo_fid = $form['open_eggheads_admin_interface_personal_data']['files']['photo']['#default_value'];
  $new_photo_fid = $form_state['values']['open_eggheads_admin_interface_personal_data']['files']['photo'];
  _open_eggheads_admin_interface_personal_data_form_submit_file_handler($old_photo_fid, $new_photo_fid, $account_uid);
    
  $old_cv_fid = $form['open_eggheads_admin_interface_personal_data']['files']['cv']['#default_value'];
  $new_cv_fid = $form_state['values']['open_eggheads_admin_interface_personal_data']['files']['cv'];
  _open_eggheads_admin_interface_personal_data_form_submit_file_handler($old_cv_fid, $new_cv_fid, $account_uid);
  
  // Clear previously cached versions of user's data and files being displayed on site.
  cache_clear_all('open_eggheads_admin_interface', 'cache', TRUE);
}

function _open_eggheads_admin_interface_personal_data_form_submit_file_handler($old_fid = NULL, $new_fid = NULL, $account_uid = NULL) {  
  // If an old file exists AND if the new file is not the same as the old file…
  if ($old_fid != 0 && $old_fid != $new_fid) {
    $old_file = file_load($old_fid);
    file_usage_delete($old_file, 'open_eggheads_admin_interface', 'user', $account_uid);
    file_delete($old_file);
  }
  
  // If there is a new file AND if the new file is not the same as the old file…
  if ($new_fid != 0 && $new_fid != $old_fid) {
    // Load the new file via file.fid.
    $new_file = file_load($new_fid);
    // Change status to permanent.
    $new_file->status = FILE_STATUS_PERMANENT;
    // Save.
    file_save($new_file);
    // Record that the module is using the new file. 
    file_usage_add($new_file, 'open_eggheads_admin_interface', 'user', $account_uid);
  }
}

###########################################################################

/**
 * Callback for both ajax-enabled buttons.
 *
 * Selects and returns the fieldset with the names in it.
 */
function _open_eggheads_admin_interface_personal_data_form_multiple_value_callback($form, $form_state) {
  if ($form_state['triggering_element']['#name'] == 'add_research_interest_button' ||
      $form_state['triggering_element']['#name'] == 'remove_research_interest_button') {
    return $form['open_eggheads_admin_interface_personal_data']['research_interests_fieldset'];
  }
  elseif ($form_state['triggering_element']['#name'] == 'add_selected_project_button' ||
          $form_state['triggering_element']['#name'] == 'remove_selected_project_button') {
    return $form['open_eggheads_admin_interface_personal_data']['selected_projects_fieldset'];
  }
}

/**
 * Submit handler for the "add-one-more" button.
 *
 * Increments the max counter and causes a rebuild.
 */
function _open_eggheads_admin_interface_personal_data_form_multiple_value_add_one($form, &$form_state) {
  if ($form_state['triggering_element']['#name'] == 'add_research_interest_button') {
    $form_state['num_research_interests']++;
  }
  elseif ($form_state['triggering_element']['#name'] == 'add_selected_project_button') {
    $form_state['num_selected_projects']++;
  }
  $form_state['rebuild'] = TRUE;
}

/**
 * Submit handler for the "remove one" button.
 *
 * Decrements the max counter and causes a form rebuild.
 */
function _open_eggheads_admin_interface_personal_data_form_multiple_value_remove_one($form, &$form_state) {
  if ($form_state['triggering_element']['#name'] == 'remove_research_interest_button') {
    if ($form_state['num_research_interests'] > 1) {
      $form_state['num_research_interests']--;
    }
  }
  elseif ($form_state['triggering_element']['#name'] == 'remove_selected_project_button') {
    if ($form_state['num_selected_projects'] > 1) {
      $form_state['num_selected_projects']--;
    }
  }
  $form_state['rebuild'] = TRUE;
}
