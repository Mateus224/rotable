UPDATE `%1clients` SET `name` = :name, `mac_address` = :mac_address, `type` = :type, `date_last_change` = now() WHERE `id` = %2;
