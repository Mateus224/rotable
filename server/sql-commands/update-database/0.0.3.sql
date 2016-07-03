UPDATE `%1configs` SET `value` = "0.0.3" WHERE `name` = "2";;
ALTER TABLE `%1products` ADD `sequence` INTEGER NOT NULL DEFAULT 0;;
UPDATE `%1products` SET `sequence` = (
    SELECT COUNT(*) FROM `%1products` as `p1` WHERE
    `removed` = 0 and `p1`.`category_id` = `%1products`.`category_id` and `p1`.`id` <= `%1products`.`id`
) WHERE  `removed` = 0;;
ALTER TABLE `%1categories` ADD `sequence` INTEGER NOT NULL DEFAULT 0;;
UPDATE `%1categories` SET `sequence` = (
    SELECT COUNT(*) FROM `%1categories` as `p1` WHERE
    `removed` = 0  and `p1`.`id` <= `%1categories`.`id`
) WHERE  `removed` = 0;;
