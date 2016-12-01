UPDATE `%1configs` SET `value` = "0.0.7" WHERE `name` = "2";;
ALTER TABLE `%1orders` ADD `waiter_state` INTEGER NOT NULL DEFAULT 0;;
UPDATE `%1orders` SET `waiter_status` = (
	SELECT `status` FROM `%1order_items`
    WHERE `%1orders`.`id` = `%1order_items`.`order_id`
    ORDER BY `%1order_items`.`id` LIMIT 1
  );;