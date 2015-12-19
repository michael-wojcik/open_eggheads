<!-- Template for "Open Eggheads Basic Personal Info" CTools content type plugin -->
<div class="open-eggheads-basic-info <?php print $basic_info_classes; ?>">
  <<?php print $basic_info_heading_size; ?>><?php print $basic_info['first_name'] . ' ' . $basic_info['last_name']; ?></<?php print $basic_info_heading_size; ?>>
  <p class="<?php print $basic_info_text_size; ?>">
    <?php print $basic_info['title']; ?>
    <br />
    <?php print $basic_info['affiliation']; ?>
  </p>
  <?php if ($basic_info['email'] || $basic_info['phone']): // Optionally print user's email and phone number, if available. This is optional data for the user. ?>
    <p class="<?php print $basic_info_text_size; ?>">
      <?php if ($basic_info['email']): ?>
        <a href="mailto:<?php print $basic_info['email']; ?>"><?php print $basic_info['email']; ?></a>
      <?php endif; ?>
      <?php if ($basic_info['email'] && $basic_info['phone']): ?>
        <br />
      <?php endif; ?>
      <?php if ($basic_info['phone']): ?>
        <?php print $basic_info['phone']; ?>
      <?php endif; ?>
    </p>
  <?php endif; ?>
</div>
