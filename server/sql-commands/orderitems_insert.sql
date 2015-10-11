INSERT INTO `%1order_items` 
(`id`, `order_id`, `product_id`, `amount`, `status`, `price`, `time`, `date_last_change`)
VALUES (%2, %3, %4, %5, %6, %7, %8, date('now'));
