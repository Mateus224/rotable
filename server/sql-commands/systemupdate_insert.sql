INSERT INTO `%1systemupdate` 
(`id`, `current_version`, `date_current_version`, `available_version`, `date_available_version`)
VALUES (%2, %3, datetime('%4'), %5, datetime('now'));
