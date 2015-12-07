(function($) {
  Drupal.behaviors.openEggheadsResearchBilbioNodeForm = {
    // Called when new content is added to the DOM, e.g. via an AJAX request
    // 'context' is the (newly) relevant portion of the DOM
    attach: function(context, settings) {
      $('#edit-field-biblio-pdf').detach().prependTo('.radix-layouts-sidebar');
    },
    detach: function(context, settings) {
      $('#edit-field-biblio-pdf').detach().prependTo('.radix-layouts-sidebar');
    }
  };
})(jQuery);
