(function($) {
  /**
   * Custom function to listen for a right-arrow keyboard press used to advance to the next Bootstrap Tour step.
   * This function selects the 'Research (Projects, Papers, Publications, etc.)' content type, as part of a demonstration tour.
   * Used in the Update Publication tour (machine name: open_eggheads_update_publication_tour).
   */
  function keydownTriggeredSelectContentType() {
    $(document).on('keydown', function(event) {
      if ($('#step-3').length && event.which == 39) { // 39 is the cross-browser keycode for the right-arrow key.
        selectContentType();
      }
    });
  }
  
  /**
   * Custom function to listen for a mouse click used to advance to the next Bootstrap Tour step.
   * This function selects the 'Research (Projects, Papers, Publications, etc.)' content type, as part of a demonstration tour.
   * Used in the Update Publication tour (machine name: open_eggheads_update_publication_tour).
   */
  function clickTriggeredSelectContentType() {
    $(document).on('click', '.tour.popover .popover-navigation .btn-group .btn[data-role="next"]', function(event) {
      if ($('#step-3').length) {
        // If content type is not yet set to 'Research (Projects, Papers, Publications, etc.)' (machine name: 'biblio').
        if ($('#edit-type').val() != 'biblio') {
          selectContentType();
        }
      }
    });
  }
  
  /**
   * Helper function for selecting the 'Research (Projects, Papers, Publications, etc.)' content type, as part of a demonstration tour.
   * Used in the Update Publication tour (machine name: open_eggheads_update_publication_tour).
   */
  function selectContentType() {
    $('#edit-type').val('biblio'); // Select 'Research (Projects, Papers, Publications, etc.)' (machine name: 'biblio').
  }
  
  Drupal.behaviors.openEggheadsHelpUpdatePublicationTour = {
    // Called when new content is added to the DOM, e.g. via an AJAX request
    // 'context' is the (newly) relevant portion of the DOM
    attach: function(context, settings) {
      keydownTriggeredSelectContentType();
      clickTriggeredSelectContentType();
    },
    detach: function(context, settings) {
      keydownTriggeredSelectContentType();
      clickTriggeredSelectContentType();
    }
  };
})(jQuery);
