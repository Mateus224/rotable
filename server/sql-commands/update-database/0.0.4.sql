UPDATE `%1configs` SET `value` = "0.0.4" WHERE `name` = "2";;
CREATE TABLE IF NOT EXISTS `%1waitercategories` (
  `waiter_id` INTEGER PRIMARY KEY,
  `category_id` INTEGER PRIMARY KEY
);;
