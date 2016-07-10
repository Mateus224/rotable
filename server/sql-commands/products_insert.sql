INSERT INTO `%1products`
(`id`, `name`, `price`, `info`, `category_id`, `icon`, `amount`, `date_added`, `date_last_change`, `sequence`)
VALUES (%2, %3, %4, %5, %6, %7, %8, datetime('now'), datetime('now'), %9);
