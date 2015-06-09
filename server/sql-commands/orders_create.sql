CREATE TABLE IF NOT EXISTS `%1orders` (
  `id` INTEGER PRIMARY KEY AUTOINCREMENT,
  `state` INTEGER,
  `client_id` INTEGER,
  `income_id` INTEGER,
  `date_added` TIMESTAMP NOT NULL,
  `date_last_change` TIMESTAMP NOT NULL
);
