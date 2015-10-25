UPDATE `%1order_items` SET `amount` = :amount, `status` = :state, `price` = :price, `time` = :time, `date_last_change` = datetime('now') WHERE `id` = :id;
