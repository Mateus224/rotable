UPDATE `%1clients` SET `name` = :name, `type` = :type, `date_last_change` = datetime('now') WHERE `id` = %2;
