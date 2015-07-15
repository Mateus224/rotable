CREATE TABLE IF NOT EXISTS `%1order_items` (
  `id` INTEGER PRIMARY KEY AUTOINCREMENT,
  `order_id` INTEGER,
  `product_id` INTEGER,
  `amount` INTEGER
);
