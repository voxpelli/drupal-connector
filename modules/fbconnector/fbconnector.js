function fbconnector_login() {
  jQuery('#fbconnector-log-in-form').submit();
}

FB.Bootstrap.requireFeatures(["Connect"], function() {
  FB.ensureInit(function () {
    FB.Connect.logout();
  });
  FB.init(Drupal.settings.fbconnector_api_key, Drupal.settings.fbconnector_xd_receiver);
});