INSERT INTO `%1products` 
(`id`, `name`, `price`, `info`, `category_id`, `icon`, `amount`, `date_added`, `date_last_change`) 
VALUES (%2, %3, %4, %5, %6, %7, %8, now(), now());
