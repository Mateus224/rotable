UPDATE `%1configs` SET `value` = "0.0.6" WHERE `name` = "2";;
CREATE TABLE IF NOT EXISTS `%1advertisingvideos` (
  `id` INTEGER PRIMARY KEY AUTOINCREMENT,
  `frequency` INTEGER NOT NULL,
  `play` INTEGER NOT NULL DEFAULT 0,
  `played` INTEGER NOT NULL,
  `media_id` INTEGER NOT NULL,
  `duration` INTEGER NOT NULL
);;
