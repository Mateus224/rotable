UPDATE `%1order_items` SET `order_id` = :order_id, `product_id` = :product_id, `amount` = :amount, `date_last_change` = now() WHERE `id` = %2;
