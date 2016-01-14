CREATE TRIGGER IF NOT EXISTS `%1update_orderitem_status_add` UPDATE OF status ON `%1order_items` 
WHEN new.status =  1 
BEGIN
    WHEN old.status != 1
    BEGIN
	UPDATE `%1daily_incomes` SET income = income + new.price WHERE id = (select income_id from `%1orders` where id = new.id);
    END;
END;
