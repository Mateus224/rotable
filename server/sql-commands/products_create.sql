CREATE TABLE IF NOT EXISTS `%1products` (
  `id` INTEGER PRIMARY KEY AUTOINCREMENT,
  `name` VARCHAR(512) NOT NULL,
  `price` INTEGER NOT NULL,
  `info` text NOT NULL,
  `category_id` INTEGER NOT NULL,
  `icon` VARCHAR(128) NOT NULL,
  `amount` VARCHAR(512) NOT NULL,
  `date_added` TIMESTAMP NOT NULL,
  `date_last_change` TIMESTAMP NOT NULL
);
