INSERT INTO `%1orders` 
(`id`, `state`, `client_id`, `date_added`, `date_last_change`)
VALUES (%2, %3, %4, now(), now());
