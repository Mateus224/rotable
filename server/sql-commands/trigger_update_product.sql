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
