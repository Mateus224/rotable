UPDATE `%1categories` SET `name` = :name, `icon` = :icon, `date_last_change` = now() WHERE `id` = %2;
