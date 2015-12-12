(function($) {
  /**
   * Custom function to listen for a right-arrow keyboard press used to advance to the next Bootstrap Tour step.
   * This function selects the 'Journal Article' publication type, as part of a demonstration tour.
   * Used in the Add Publication tour (machine name: open_eggheads_add_publication_tour).
   */
  function keydownTriggeredSelectPublicationType() {
    $(document).on('keydown', function(event) {
      if ($('#step-5').length && event.which == 39) { // 39 is the cross-browser keycode for the right-arrow key.
        selectPublicationType();
      }
    });
  }
  
  /**
   * Custom function to listen for a mouse click used to advance to the next Bootstrap Tour step.
   * This function selects the 'Journal Article' publication type, as part of a demonstration tour.
   * Also adds extra classes to the publication creation form, to create better references points for the tour.
   * Used in the Add Publication tour (machine name: open_eggheads_add_publication_tour).
   */
  function clickTriggeredSelectPublicationType() {
    $(document).on('click', '.tour.popover .popover-navigation .btn-group .btn[data-role="next"]', function(event) {
      if ($('#step-6').length) {
        if ($('#edit-biblio-type').val() != 102) { // If publication type is not yet set to 'Journal Article' (Numeric value: 102).
          selectPublicationType();
        }
        addVerticalTabClasses();
      }
    });
  }
  
  /**
   * Helper function for selecting the 'Journal Article' publication type, as part of a demonstration tour.
   * Used in the Add Publication tour (machine name: open_eggheads_add_publication_tour).
   */
  function selectPublicationType() {
    $('#edit-biblio-type').val(102); // Select 'Journal Article' (Numeric value: 102) as an example.
    $('#biblio-node-form').submit(); // Submit form to bring up further form fields for demo purposes.
  }
  
  /**
   * Helper function for adding extra classes to the publication creation form, to create better references points for the tour.
   * Used in the Add Publication tour (machine name: open_eggheads_add_publication_tour).
   */
  function addVerticalTabClasses() {
    $('li.vertical-tab-button strong').each(function(index) {
      var classToAdd = $(this).text().replace(' ', '-').toLowerCase() + '-vertical-tab-button';
      $(this).parents('li.vertical-tab-button').addClass(classToAdd);
    });
  }
  
  Drupal.behaviors.openEggheadsHelpAddPublicationTour = {
    // Called when new content is added to the DOM, e.g. via an AJAX request
    // 'context' is the (newly) relevant portion of the DOM
    attach: function(context, settings) {
      keydownTriggeredSelectPublicationType();
      clickTriggeredSelectPublicationType();
      addVerticalTabClasses();
    },
    detach: function(context, settings) {
      keydownTriggeredSelectPublicationType();
      clickTriggeredSelectPublicationType();
      addVerticalTabClasses();
    }
  };
})(jQuery);
