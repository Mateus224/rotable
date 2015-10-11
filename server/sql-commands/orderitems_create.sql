CREATE TABLE IF NOT EXISTS `%1order_items` (
  `id` INTEGER PRIMARY KEY AUTOINCREMENT,
  `order_id` INTEGER NOT NULL,
  `product_id` INTEGER NOT NULL,
  `amount` INTEGER NOT NULL,
  `status` INTEGER NOT NULL,
  `price` DOUBLE NOT NULL,
  `time` TIME NOT NULL,
  `date_last_change` TIMESTAMP NOT NULL
);
