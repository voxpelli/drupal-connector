<?php
// $Id$

/**
 * @file
 * Contains the administraive pages for Facebook Connector
 */

function fbconnector_settings_form() {
  $form['fbconnector_api_key'] = array(
    '#type'          => 'textfield',
    '#title'         => t('API-Key'),
    '#default_value' => variable_get('fbconnector_api_key', NULL),
    '#size'          => 60,
    '#maxlength'     => 128,
    '#required'      => TRUE,
  );

  $form['fbconnector_application_secret'] = array(
    '#type'          => 'textfield',
    '#title'         => t('Application Secret'),
    '#default_value' => variable_get('fbconnector_application_secret', NULL),
    '#size'          => 60,
    '#maxlength'     => 128,
    '#required'      => TRUE,
  );

  $form = system_settings_form($form);

  unset($form['buttons']['reset']);

  return $form;
}

function fbconnector_settings_form_validate($form, &$form_state) {
  if (!class_exists('Facebook')) {
    include_once(drupal_get_path('module', 'fbconnector') . '/facebook-platform/facebook.php');
  }
  try {
    $fb = new Facebook($form_state['values']['fbconnector_api_key'], $form_state['values']['fbconnector_application_secret']);
    $result = $fb->api_client->admin_getAppProperties(array('application_name'));
    drupal_set_message(t('This site is now using the Facebook application %application_name', array(
      '%application_name' => $result['application_name'],
    )));
  } catch (Exception $e) {
    form_set_error('fbconnector_api_key', t("Couldn't access the Facebook API with those credentials."));
  }
}

function fbconnector_setup_form() {
  //TODO: Finish this function and remove this notice
  drupal_set_message(t('This function is yet to be finished.'));
  return array();

  if (!variable_get('fbconnector_api_key', NULL) || !variable_get('fbconnector_application_secret', NULL)) {
    drupal_set_message(t('You need to !enter your Facebook applications credentials first.', array(
      '!enter' => l(t('enter'), 'admin/settings/fbconnector'),
    )), 'error');
    return array();
  }

  return confirm_form(
    array(),
    t('Auto-configure Facebook application'),
    'admin/settings/fbconnector',
    t("This site will configurate your Facebook application to be used with this site's Facebook Connect feature, settings the right URL:s etc."),
    t('Configure now'),
    t('Cancel')
  );
}

function fbconnector_setup_form_submit($form, &$form_state) {
  //TODO: Auto-configure it!
  drupal_set_message(t('Your Facebook application has now been configured.'));
  $form_state['redirect'] = 'admin/settings/fbconnector';
}