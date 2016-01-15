CREATE TRIGGER IF NOT EXISTS `%1update_orderitem_status_remove` UPDATE OF status ON `%1order_items` 
WHEN old.status = 1 AND old.status <> 1
BEGIN
    UPDATE `%1daily_incomes` SET income = income - new.price WHERE id = (select income_id from `%1orders` where id = new.id);
END;
