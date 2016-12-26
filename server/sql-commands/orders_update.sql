UPDATE `%1orders` SET `state` = :state, `waiter_state` = :waiter_state, `client_id` = :client_id, `date_last_change` = datetime('now') WHERE `id` = %2;
