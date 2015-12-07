<div class="open-eggheads-research-interests">
  <<?php print $research_interests_heading_size; ?>><?php print $research_interests_heading; ?></<?php print $research_interests_heading_size; ?>>
  <<?php print $research_interests_list_type; ?>
    <?php if ($research_interests_list_type == 'ul'): ?>
      style="list-style-type:<?php print $research_interests_list_style_ul; ?>"
    <?php elseif ($research_interests_list_type == 'ol'): ?>
      type="<?php print $research_interests_list_style_ol; ?>"
    <?php endif; ?>
  >
    <?php foreach ($research_interests as $research_interest): // Print all research interests provided by user. ?>
      <?php if ($research_interest): // Don't show research interest fields that were left blank. ?>
        <li><?php print $research_interest; ?></li>
      <?php endif; ?>
    <?php endforeach; ?>
  </<?php print $research_interests_list_type; ?>>
</div>
