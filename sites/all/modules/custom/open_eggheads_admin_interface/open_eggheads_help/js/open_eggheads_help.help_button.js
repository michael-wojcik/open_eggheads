(function($) {
  // Define Help button in HTML.
  var $helpButton = $('<button id="open-eggheads-help-button" class="btn btn-sm btn-success"><i class="fa fa-question-circle fa-lg"></i> <strong>Help</strong></button>');
  
  // Append Help button to Admin Menu bar and position it below the bar.
  function openEggheadsHelpButtonInit() {
    $('#admin-menu').append($helpButton);
    $($helpButton).click(function() {
      // Redirect to the FAQ page.
      window.location.href = '/admin/open-eggheads/faq';
    });
  }
  
  // Create Help button on page according to Drupal.behaviors standards.
  Drupal.behaviors.openEggheadsHelpButton = {
    // Called when new content is added to the DOM, e.g. via an AJAX request
    // 'context' is the (newly) relevant portion of the DOM
    attach: function(context, settings) {
      openEggheadsHelpButtonInit();
    },
    detach: function(context, settings) {
      openEggheadsHelpButtonInit();
    }
  };
})(jQuery);
