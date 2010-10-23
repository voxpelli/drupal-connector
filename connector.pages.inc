<?php
// $Id$

/**
 * @file
 * Contains all non-admin pages for the Connector module
 */

/**
 * Menu callback for the user settings page
 */
function connector_user_settings($account) {
  $output = '';

  $connections = _connector_get_user_connections($account);
  if (!empty($connections)) {
    $output .= drupal_get_form('connector_connections_list', $connections);
  }
  $output .= drupal_get_form('connector_button_form', $account);

  return $output;
}

function connector_connections_list($form_state, $connections = array()) {
  $form['#tree'] = TRUE;
  $form['connections'] = array();

  foreach ($connections as $connection) {
    $form['connections'][] = _connector_connections_list_row($connection);
  }

  if (!empty($connections)) {
    $form['buttons']['submit'] = array(
      '#type'  => 'submit',
      '#value' => t('Save changes'),
    );
  }

  return $form;
}

function _connector_connections_list_row($connection) {
  $form['#connection'] = $connection;

  $form['cid'] = array(
    '#type'  => 'markup',
    '#value' => check_plain($connection->cid),
  );

  $form['connector'] = array(
    '#type'  => 'markup',
    '#value' => check_plain($connection->connector),
  );

  $form['import'] = array(
    '#type' => 'checkbox',
//    '#default_value' => $account->import,
  );
  
  $form['delete'] = array(
    '#type' => 'checkbox',
  );

  return $form;
}

function theme_connector_connections_list($form) {
  $header = array(t('Connector Id'), t('Connector'), t('Import'), t('Delete')); 

  $rows = array();

  foreach (element_children($form['connections']) as $key) {
    $element = &$form['connections'][$key];

    $row = array();
    foreach ($element as $element_key => $element_value) {
      if (substr($element_key, 0, 1) != '#') {
        $row[] = drupal_render($element[$element_key]);
      }
    }

    $rows[] = $row;
  }

  $output = theme('table', $header, $rows);
  $output .= drupal_render($form);
  return $output;
}

function connector_connections_list_submit($form, &$form_state) {
/*  $accounts = $form_state['values']['accounts'];
  foreach($accounts as $account) {
    if (empty($account['delete'])) {
      twitter_account_save($account);
    }
    else {
      twitter_user_delete($account['id'], $account['screen_name']);
    }
  }*/
}