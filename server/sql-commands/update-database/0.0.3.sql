ALTER TABLE `%1products` ADD `sequence` INTEGER NOT NULL DEFAULT 0;;
--ALTER TABLE `%1categories` ADD `sequence_last` INTEGER NOT NULL DEFAULT 0;;
UPDATE `%1products` SET `sequence` = (
    SELECT COUNT(*) FROM `%1products` as `p1` WHERE
    `removed` = 0 and `p1`.`category_id` = `rotable_products`.`category_id` and `p1`.`id` <= `rotable_products`.`id`
) WHERE  `removed` = 0;;
