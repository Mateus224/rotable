CREATE TABLE IF NOT EXISTS `%1daily_incomes` (
  `id` INTEGER PRIMARY KEY AUTOINCREMENT,
  `income` REAL NOT NULL,
  `date` DATE NOT NULL,
);
