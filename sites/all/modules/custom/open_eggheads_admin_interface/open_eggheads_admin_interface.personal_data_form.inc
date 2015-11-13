<?php

function open_eggheads_admin_interface_personal_data_form($form, &$form_state) {
  $form = array();
  
  $form['#tree'] = TRUE;
  
  $default_data = variable_get('open_eggheads_admin_interface_personal_data');
    
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
  
  $form['#submit'][] = 'open_eggheads_admin_interface_personal_data_form_submit';
  
  return system_settings_form($form);
}

function open_eggheads_admin_interface_personal_data_form_validate(&$form, &$form_state) {
  $email = $form_state['values']['open_eggheads_admin_interface_personal_data']['basic_info']['email'];
  if (!empty($email) && !valid_email_address($email)) {
    form_set_error('open_eggheads_admin_interface_personal_data][basic_info][email', t('Invalid email address.'));
  }
  
  $phone = $form_state['values']['open_eggheads_admin_interface_personal_data']['basic_info']['phone'];
  $phone_regex = '/^[\d\+\(][\d\(\)\-\ \.]{8,32}[\d]$/';
  if (!empty($phone) && !preg_match($phone_regex, $phone)) {
    form_set_error('open_eggheads_admin_interface_personal_data][basic_info][phone', t('Invalid phone number.'));
  }
}

function open_eggheads_admin_interface_personal_data_form_submit(&$form, &$form_state) {
  global $user;
  $account_uid = $user->uid;
  
  dpm($form_state);
  dpm($form['open_eggheads_admin_interface_personal_data']['files']['cv']['#default_value']);
  
  $old_photo_fid = $form['open_eggheads_admin_interface_personal_data']['files']['photo']['#default_value'];
  $new_photo_fid = $form_state['values']['open_eggheads_admin_interface_personal_data']['files']['photo'];
  _open_eggheads_admin_interface_personal_data_form_submit_file_handler($old_photo_fid, $new_photo_fid, $account_uid);
    
  $old_cv_fid = $form['open_eggheads_admin_interface_personal_data']['files']['cv']['#default_value'];
  $new_cv_fid = $form_state['values']['open_eggheads_admin_interface_personal_data']['files']['cv'];
  _open_eggheads_admin_interface_personal_data_form_submit_file_handler($old_cv_fid, $new_cv_fid, $account_uid);
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
