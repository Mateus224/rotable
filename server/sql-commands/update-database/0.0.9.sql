UPDATE `%1configs` SET `value` = "0.0.9" WHERE `name` = "2";;
CREATE TABLE IF NOT EXISTS `%1advertisingconfigs` (
  `id` INTEGER PRIMARY KEY AUTOINCREMENT,
  `frequency` INTEGER NOT NULL
);;