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
  $header = array(
    'connector'  => t('Connection'),
    'cid'        => t('External Id'),
    'operations' => t('Operations'),
  );

  $options = array();
  foreach ($connections as $connection) {
    $connector = _connector_get_connectors($connection->connector);
    $options[$connection->connector . '__' . $connection->cid] = array(
      'connector'  => $connector['title'],
      'cid'        => $connection->cid,
      'operations' => '<a href="#">remove</a>',
    );
  }

  if (module_exists('elements')) {
    $form['synchronisation'] = array(
      '#type'     => 'tableselect',
      '#header'   => $header,
      '#options'  => $options,
      '#multiple' => FALSE,
      '#empty'    => t('No connections available.'),
    );
  }
  else {
    $radios  = array();
    $form['headers'] = array();
    foreach ($header as $key => $value) {
      $form['header'][$key] = array('#value' => $value);
    }
    foreach ($options as $key => $option) {
      $radios[$key] = '';
      $form['connector'][$key]  = array('#value' => check_plain($option['connector']));
      $form['cid'][$key]        = array('#value' => check_plain($option['cid']));
      $form['operations'][$key] = array('#value' => $option['operations']);
    }
    $form['synchronisation'] = array(
      '#type'    => 'radios',
      '#options' => $radios,
    );
    $form['#theme'] = 'connector_connections_list_tableselect';
  }

  if (!empty($connections)) {
    $form['buttons']['submit'] = array(
      '#type'  => 'submit',
      '#value' => t('Save synchronization source'),
    );
  }

  return $form;
}

function theme_connector_connections_list_tableselect($form) {
  $header = array('');

  foreach (element_children($form['header']) as $key) {
    $header[] = drupal_render($form['header'][$key]);
  }

  $rows = array();

  if (!empty($form['connector'])) {
    foreach (element_children($form['connector']) as $key) {
      $row = array();
      $row[] = drupal_render($form['synchronisation'][$key]);
      $row[] = drupal_render($form['connector'][$key]);
      $row[] = drupal_render($form['cid'][$key]);
      $row[] = drupal_render($form['operations'][$key]);
      $rows[] = $row;
    }
  }
  else {
    $rows[] = array(array('data' => t('No connections available.'), 'colspan' => '6'));
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