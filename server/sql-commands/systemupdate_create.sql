CREATE TABLE IF NOT EXISTS `%1systemupdate` (
  `id` INTEGER PRIMARY KEY AUTOINCREMENT,
  `current_version` REAL NOT NULL,
  `date_current_version` TIMESTAMP NOT NULL,
  `available_version` REAL NOT NULL,
  `date_available_version` TIMESTAMP NOT NULL
);