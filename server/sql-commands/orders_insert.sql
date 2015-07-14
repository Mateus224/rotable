INSERT INTO `%1orders` 
(`id`, `state`, `income_id`, `client_id`, `date_added`, `date_last_change`)
VALUES (%2, %3, %4, %5, date('now'), date('now'));
