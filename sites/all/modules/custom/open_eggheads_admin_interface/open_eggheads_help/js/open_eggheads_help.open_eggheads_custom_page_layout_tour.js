(function($) {
  /**
   * Custom function to listen for a right-arrow keyboard press used to advance to the next Bootstrap Tour step.
   * This function triggers the Panels In-Place Editor layout editor overlay at the appropriate time in the tour.
   * Used in the Custom Page Layout tour (machine name: open_eggheads_custom_page_layout_tour).
   */
  function keydownTriggeredLayoutEditorOverlay() {
    $(document).on('keydown', function(event) {
      if ($('#step-0').length && event.which == 39) { // 39 is the cross-browser keycode for the right-arrow key.
        $('.panels-ipe-change-layout').click(); // Trigger Panels In-Place Editor layout editor overlay.
        // Set up interval to ensure that Panels In-Place Editor layout editor overlay is centered to browser window.
        var checkExist = setInterval(function() {
          if ($('#modalContent').length) {
            var isCentered = $('#modalContent').center(); // Call custom function used to center the overlay.
            if (isCentered) {
              clearInterval(checkExist); // Exit interval if overlay has stopped moving and is now centered.
            }
          }
        }, 100); // check every 100ms
      }
    });
  }
  
  /**
   * Custom function to listen for a mouse click used to advance to the next Bootstrap Tour step.
   * This function triggers the Panels In-Place Editor layout editor overlay at the appropriate time in the tour.
   * Used in the Custom Page Layout tour (machine name: open_eggheads_custom_page_layout_tour).
   */
  function clickTriggeredLayoutEditorOverlay() {
    $(document).on('click', '.tour.popover .popover-navigation .btn-group .btn[data-role="next"]', function(event) {
      if ($('#step-1').length && !$('.panels-choose-layout').length) {
        $('.panels-ipe-change-layout').click(); // Trigger Panels In-Place Editor layout editor overlay.
        // Set up interval to ensure that Panels In-Place Editor layout editor overlay is centered to browser window.
        var checkExist = setInterval(function() {
            if ($('#modalContent').length) {
              var isCentered = $('#modalContent').center(); // Call custom function used to center the overlay.
              if (isCentered) {
                clearInterval(checkExist); // Exit interval if overlay has stopped moving and is now centered.
              }
            }
        }, 100); // check every 100ms
      }
    });
  }
  
  /**
  * Custom helper function for centering an element on screen.
  * Source: http://stackoverflow.com/a/210733
  */
  jQuery.fn.center = function() {
    this.css('position', 'absolute');
    
    var oldTop = this.css('top'); // Save old 'top' value.
    // Calculate new 'top' value based on current screen size and current element size.
    this.css('top', Math.max(0, parseInt(($(window).height() - $(this).outerHeight()) / 2) + $(window).scrollTop()) + 'px');
    var newTop = this.css('top'); // Save new 'top' value.
    
    var oldLeft = this.css('left'); // Save old 'left' value.
    // Calculate new 'left' value based on current screen size and current element size.
    this.css('left', Math.max(0, parseInt(($(window).width() - $(this).outerWidth()) / 2) + $(window).scrollLeft()) + 'px');
    var newLeft = this.css('left'); // Save new 'left' value.
    
    var isCentered = false;
    if (oldTop == newTop && oldLeft == newLeft) { // Compare element's old position to its new position.
      isCentered = true; // If old and new positions are identical, the element has not moved and is now centered.
    }
    
    return isCentered;
  }
  
  Drupal.behaviors.openEggheadsHelpCustomPageLayoutTour = {
    // Called when new content is added to the DOM, e.g. via an AJAX request
    // 'context' is the (newly) relevant portion of the DOM
    attach: function(context, settings) {
      keydownTriggeredLayoutEditorOverlay();
      clickTriggeredLayoutEditorOverlay();
    },
    detach: function(context, settings) {
      keydownTriggeredLayoutEditorOverlay();
      clickTriggeredLayoutEditorOverlay();
    }
  };
})(jQuery);
