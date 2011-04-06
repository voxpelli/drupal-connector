<?php

/**
 * @file
 * Views functions for Connector
 */

/**
 * Implementation of hook_views_data().
 */
function connector_views_data() {
  $data = array();

  $data['connector_info']['table']['group']  = t('Connector');

  // Explain how this table joins to others.
  $data['connector_info']['table']['join'] = array(
     // Directly links to users table.
    'users' => array(
      'left_field' => 'uid',
      'field' => 'uid',
    ),
    'node' => array(
      'left_field' => 'uid',
      'field' => 'uid',
    ),
    'node_revisions' => array(
      'left_table' => 'node',
      'left_field' => 'uid',
      'field' => 'uid',
    ),
  );

  // name
  $data['connector_info']['name'] = array(
    'title' => t('Name'), // The item it appears as on the UI,
    'help' => t('The user or author name.'), // The help that appears on the UI,
    'real field' => 'value',
    'field' => array(
      'handler' => 'connector_handler_field_facebook_name',
      'click sortable' => TRUE,
    ),
  );

  return $data;
}

/**
 * Implementation of hook_views_handlers().
 */
function connector_views_handlers() {
  return array(
    'info' => array(
      'path' => drupal_get_path('module', 'connector') .'/includes',
    ),
    'handlers' => array(
      // field
      'connector_handler_field_facebook_name' => array(
        'parent' => 'views_handler_field_user_name',
      ),
    ),
  );
}
