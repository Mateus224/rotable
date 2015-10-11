UPDATE `%1order_items` SET `amount` = :amount, `state` = :state, `price` = :price, `time` = :time, `date_last_change` = date('now') WHERE `id` = %2;
