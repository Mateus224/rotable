UPDATE `%1products` SET `name` = :name, `price` = :price,
`info` = :info, `category_id` = :category_id, `amount` = :amount, `icon` = :icon , `date_last_change` = now()
WHERE `id` = %2;