UPDATE `%1products` SET `name` = :name, `price` = :price,
`info` = :info, `category_id` = :category_id, `amount` = :amount, `icon` = :icon , `sequence` = :sequence, `date_last_change` = datetime('now')
WHERE `id` = %2;
