CREATE TABLE IF NOT EXISTS `%1waiters_orders` (
  `id`			INTEGER PRIMARY KEY AUTOINCREMENT,
  `id_waiters`	INTEGER NOT NULL FOREIGN KEY,
  `id_orders`	INTEGER NOT NULL FOREIGN KEY	
);