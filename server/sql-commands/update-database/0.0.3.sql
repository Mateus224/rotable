UPDATE `%1configs` SET `value` = "0.0.3" WHERE `name` = "2";;
ALTER TABLE `%1products` ADD `sequence` INTEGER NOT NULL DEFAULT 0;;
UPDATE `%1products` SET `sequence` = (
    SELECT COUNT(*) FROM `%1products` as `p1` WHERE
    `removed` = 0 and `p1`.`category_id` = `rotable_products`.`category_id` and `p1`.`id` <= `rotable_products`.`id`
) WHERE  `removed` = 0;;
CREATE TRIGGER IF NOT EXISTS `%1remove_product` DELETE ON `%1products`
  BEGIN
    UPDATE `%1configs` SET `value` = '0' WHERE `name` = 'active_trigger_update_product';
    UPDATE `%1products` SET `sequence` = `sequence` - 1 WHERE `id` >  `old`.`id` AND `category_id` = `old`.`category_id`;
    UPDATE `%1configs` SET `value` = '1' WHERE `name` = 'active_trigger_update_product';
END;;
CREATE TRIGGER IF NOT EXISTS `rotable_update_product` UPDATE OF `sequence` ON `rotable_products`
WHEN EXISTS(
    SELECT `value` FROM `rotable_configs`
    WHERE `name` = 'active_trigger_update_product' AND `value` = '1')
BEGIN
        UPDATE `rotable_configs` SET `value` = '0' WHERE `name` = 'active_trigger_update_product';
        UPDATE `rotable_products` SET `sequence` = `old`.`sequence` WHERE
                `sequence` = `new`.`sequence` AND `id` <> `new`.`id`;
        UPDATE `rotable_configs` SET `value` = '1' WHERE `name` = 'active_trigger_update_product';
END;
INSERT INTO `%1configs` (`name`, `value`) VALUES ('active_trigger_update_product', '1');;

