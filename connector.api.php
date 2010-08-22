<?php
// $Id$

/**
 * @file
 * Hooks provided by the Connector module.
 */

/**
 * @addtogroup hooks
 * @{
 */

 /**
  * Define Connector support and options.
  *
  * This hook enables modules to register Connector support.
  *
  * @return
  *   An array of connectors that the module defines. Each connector's key should be a
  *   machine name for that connector. Each connector should contain an associative array
  *   that may contain the following key-value pairs, defining the connector:
  *   - "id callback": Required. A function that returns the external id of a connected user.
  *   - "button callback": A function returning an array defining a button for one-click login.
  *   - "logout callback": A function...
  *   - "information callback": A function...
  *   - "avatar callback": A function...
  *   - "cache": A number defining the maximum amount of seconds to cache external data.
  */
function hook_connector() {
  return array(
    'exampleconnector' => array(
      'title'                => 'Example',
      'id callback'          => '_exampleconnector_id',
      'button callback'      => '_exampleconnector_button',
      'logout callback'      => '_exampleconnector_logout',
      'information callback' => '_exampleconnector_info',
      'avatar callback'      => '_exampleconnector_avatar',
      'cache'                => 72000, //20 hours x 3600 seconds per hour
      'invalidate old info'  => TRUE,
    ),
  );
}