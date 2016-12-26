INSERT INTO `%1orders` 
(`id`, `state`, `income_id`, `client_id`, `date_added`, `date_last_change`, `waiter_state`)
VALUES (%2, %3, %4, %5, datetime('now'), datetime('now'), 0);