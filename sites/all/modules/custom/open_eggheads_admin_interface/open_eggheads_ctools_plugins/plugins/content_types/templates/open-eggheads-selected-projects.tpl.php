<!-- Template for "Open Eggheads Selected Projects" CTools content type plugin -->
<div class="open-eggheads-selected-projects">
  <<?php print $selected_projects_heading_size; ?>><?php print $selected_projects_heading; ?></<?php print $selected_projects_heading_size; ?>>
  <<?php print $selected_projects_list_type; ?>
    <?php if ($selected_projects_list_type == 'ul'): ?>
      style="list-style-type:<?php print $selected_projects_list_style_ul; ?>"
    <?php elseif ($selected_projects_list_type == 'ol'): ?>
      type="<?php print $selected_projects_list_style_ol; ?>"
    <?php endif; ?>
  >
    <?php foreach ($selected_projects as $selected_project): // Print all selected projects provided by user. ?>
      <?php if ($selected_project): // Don't show selected project fields that were left blank. ?>
        <li><?php print $selected_project; ?></li>
      <?php endif; ?>
    <?php endforeach; ?>
  </<?php print $selected_projects_list_type; ?>>
</div>
