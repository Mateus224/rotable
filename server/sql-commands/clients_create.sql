CREATE TABLE IF NOT EXISTS `%1clients` (
  `id` INTEGER PRIMARY KEY AUTOINCREMENT,
  `name` VARCHAR(512) NOT NULL,
  `type` INTEGER,
  `date_added` TIMESTAMP NOT NULL,
  `date_last_change` TIMESTAMP NOT NULL
);
