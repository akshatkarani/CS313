drop trigger calculate_rating ON reviews;

CREATE OR REPLACE FUNCTION calculate_rating_func() RETURNS trigger AS $$
    BEGIN
       
            update restaurant set rating=(select avg(user_rating) from reviews where restaurant_id = NEW.restaurant_id) where restaurant_id = NEW.restaurant_id ;
       
    RETURN NEW;
    END;

$$ LANGUAGE plpgsql;

CREATE TRIGGER calculate_rating AFTER INSERT OR UPDATE ON reviews
    FOR EACH ROW EXECUTE PROCEDURE calculate_rating_func();