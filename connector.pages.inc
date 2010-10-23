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
  $primary     = _connector_get_primary_connection($account);

  if (!empty($connections)) {
    $output .= drupal_get_form('connector_connections_list', $connections, $primary, $account);
  }
  $output .= drupal_get_form('connector_button_form', $account);

  return $output;
}

function connector_connections_list($form_state, $connections, $primary, $account) {
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

  $primary = ($primary->connector . '__' . $primary->cid);

  if (module_exists('elements')) {
    $form['primary'] = array(
      '#type'          => 'tableselect',
      '#header'        => $header,
      '#options'       => $options,
      '#multiple'      => FALSE,
      '#empty'         => t('No connections available.'),
      '#default_value' => $primary,
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
    $form['primary'] = array(
      '#type'          => 'radios',
      '#options'       => $radios,
      '#default_value' => $primary,
    );
    $form['#theme'] = 'connector_connections_list_tableselect';
  }

  $form['account'] = array(
    '#type'  => 'value',
    '#value' => $account,
  );

  if (!empty($connections)) {
    $form['buttons']['submit'] = array(
      '#type'  => 'submit',
      '#value' => t('Set primary connection'),
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
      $row[] = drupal_render($form['primary'][$key]);
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
  $primary = $form_state['values']['primary'];
  $account = $form_state['values']['account'];
  _connector_set_primary_connection($account, $primary);
  //TODO: Trigger an update of the users information somehow?
  //TODO: Need to make sure that all values are rechecked - eg checking for an avatar even if the old source didn't have one
}