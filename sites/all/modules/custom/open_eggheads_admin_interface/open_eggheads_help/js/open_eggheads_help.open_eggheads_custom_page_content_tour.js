(function($) {
  /**
   * Custom function to listen for a right-arrow keyboard press used to advance to the next Bootstrap Tour step.
   * This function triggers the Panels In-Place Editor page editor overlay at the appropriate time in the tour.
   * Used in the Custom Page Content tour (machine name: open_eggheads_custom_page_content_tour).
   */
  function keydownTriggeredContentEditorOverlay() {
    $(document).on('keydown', function(event) {
      if ($('#step-0').length && event.which == 39) { // 39 is the cross-browser keycode for the right-arrow key.
        $('#panels-ipe-customize-page').click();
      }
    });
  }
  
  /**
   * Custom function to listen for a mouse click used to advance to the next Bootstrap Tour step.
   * This function triggers the Panels In-Place Editor page editor overlay at the appropriate time in the tour.
   * Used in the Custom Page Content tour (machine name: open_eggheads_custom_page_content_tour).
   */
  function clickTriggeredContentEditorOverlay() {
    $(document).on('click', '.tour.popover .popover-navigation .btn-group .btn[data-role="next"]', function(event) {
      if ($('#step-1').length && !$('#panels-ipe-edit-control-form').length) {
        $('#panels-ipe-customize-page').click();
      }
    });
  }
  
  Drupal.behaviors.openEggheadsHelpCustomPageContentTour = {
    // Called when new content is added to the DOM, e.g. via an AJAX request
    // 'context' is the (newly) relevant portion of the DOM
    attach: function(context, settings) {
      keydownTriggeredContentEditorOverlay();
      clickTriggeredContentEditorOverlay();
    },
    detach: function(context, settings) {
      keydownTriggeredContentEditorOverlay();
      clickTriggeredContentEditorOverlay();
    }
  };
})(jQuery);
