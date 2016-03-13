UPDATE `%1configs` SET `value` = "0.0.2" WHERE `name` = "2";;
ALTER TABLE `%1products` ADD `removed` INTEGER NOT NULL DEFAULT 0;;
ALTER TABLE `%1categories` ADD `removed` INTEGER NOT NULL DEFAULT 0;;
