<?php
// $Id$

/**
 * @file
 * Field handler to provide simple renderer that allows using a themed user link
 */

class connector_handler_field_facebook_name extends views_handler_field_user_name {
  function init(&$view, &$data) {
    parent::init($view, $data);
    $this->additional_fields['uid'] = array(
      'table' => 'users',
      'field' => 'uid',
    );
  }

  function query() {
    parent::query();
    $this->query->add_where(0, $this->table_alias . ".type = 'real name'");
  }

  function render_link($data, $values) {
    if (!$values->{$this->aliases['uid']}) {
      if (!empty($this->options['overwrite_anonymous'])) {
        // This is an anonymous user, and we're overriting the text.
        $data = check_plain($this->options['anonymous_text']);
      }
      else {
        $data = check_plain(variable_get('anonymous', t('Anonymous')));
      }
    }
    else {
      $data = empty($data) ? check_plain(t('Hidden name')) : $data;
      if (!empty($this->options['link_to_user']) && user_access('access user profiles')) {
        $data = l($data, 'user/'. $values->{$this->aliases['uid']}, array('attributes' => array('title' => t('View user profile.'))));
      }
    }
    return $data;
  }
}