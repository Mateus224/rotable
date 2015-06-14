INSERT INTO `%1clients` 
(`id`, `name`, `type`, `date_added`, `date_last_change`)
VALUES (%2, %3, %4, date('now'), date('now'));
