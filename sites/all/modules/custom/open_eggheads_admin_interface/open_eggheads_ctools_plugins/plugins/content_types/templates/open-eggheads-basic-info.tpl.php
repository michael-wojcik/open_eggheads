<div class="open-eggheads-basic-info">
  <h1><?php print $basic_info['first_name'] . ' ' . $basic_info['last_name']; ?></h1>
  <p>
    <?php print $basic_info['title']; ?>
    <br />
    <?php print $basic_info['affiliation']; ?>
  </p>
  <p>
    <a href="mailto:<?php print $basic_info['email']; ?>"><?php print $basic_info['email']; ?></a>
    <br />
    <?php print $basic_info['phone']; ?>
  </p>
</div>
