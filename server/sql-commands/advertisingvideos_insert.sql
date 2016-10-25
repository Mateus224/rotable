INSERT INTO `%1categories` 
(`id`, `name`, `icon`, `date_added`, `date_last_change`, `sequence`)
VALUES (%2, %3, %4, datetime('now'), datetime('now'), %5);
