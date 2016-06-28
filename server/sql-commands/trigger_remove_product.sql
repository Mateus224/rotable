CREATE TRIGGER IF NOT EXISTS `%1remove_product` DELETE ON `%1products`
  BEGIN
    UPDATE `%1configs` SET `value` = '0' WHERE `name` = 'active_trigger_update_product';
    UPDATE `%1products` SET `sequence` = `sequence` - 1 WHERE `id` >  `old`.`id` AND `category_id` = `old`.`category_id`;
    UPDATE `%1configs` SET `value` = '1' WHERE `name` = 'active_trigger_update_product';
  END;
