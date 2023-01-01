
/*************

Reference:
    Book: Head First: Design Patterns
    
Abstract Factory Pattern Code Sample

***************/

#include <iostream>
#include <string>
#include <memory>

class Cheese {
		std::string name;
	public:
		~Cheese() { }
		Cheese(std::string name) : name(name) { }
		virtual std::string getName() { return name; }
};


class NyStyleCheese : public Cheese {
	public:
		~NyStyleCheese() { }
		NyStyleCheese() : Cheese("New York Cheese") { }
};

class ChicagoStyleCheese : public Cheese {
	public:
		~ChicagoStyleCheese() { }
		ChicagoStyleCheese() : Cheese("Chicago Style Cheese") { }
};

class Sauce {
		std::string name;
	public:
		~Sauce() { }
		Sauce(std::string name) : name(name) { }
		virtual std::string getName()	{ return name; }
};

class NyStyleSauce : public Sauce {
	public:
		~NyStyleSauce() { }
		NyStyleSauce() : Sauce("New York Style Sauce") { }
};

class ChicagoStyleSauce : public Sauce {
	public:
		~ChicagoStyleSauce() { }
		ChicagoStyleSauce() : Sauce("Chicago Style Sauce") { }
};

class PizzaIngredientFactory {
	public:
		virtual std::unique_ptr<Cheese> createCheese()  = 0;
		virtual std::unique_ptr<Sauce> createSauce()    = 0;
};

class NyPizzaIngredientFactory : public PizzaIngredientFactory {
	public:
		std::unique_ptr<Cheese> createCheese()  { return std::make_unique<NyStyleCheese>(); }
		std::unique_ptr<Sauce> createSauce()    { return std::make_unique<NyStyleSauce>();  }
};

class ChicagoPizzaIngredientFactory : public PizzaIngredientFactory {
	public:
		std::unique_ptr<Cheese> createCheese()  { return std::make_unique<ChicagoStyleCheese>();    }
		std::unique_ptr<Sauce> createSauce()    { return std::make_unique<ChicagoStyleSauce>();	    }
};

class Pizza {
    std::string	name;

    public:
        std::unique_ptr<Cheese> cheese  = nullptr;
        std::unique_ptr<Sauce>  sauce   = nullptr;
        
        Pizza(std::string name) : name(name) {  }
        virtual ~Pizza()    {  }
        
		virtual void prepare()  = 0;
		
        virtual void bake()     { std::puts("baking pizza"); }
        virtual void cut()      { std::puts("cutting pizza"); }
        virtual void box()      { std::puts("boxing pizza"); }
		virtual void setName(std::string name)	{ this->name = name; }
        virtual std::string getName()   { return name; }
};

class CheesePizza : public Pizza {
	std::shared_ptr<PizzaIngredientFactory> m_ingd_factory = nullptr;
    public:
    CheesePizza(std::shared_ptr<PizzaIngredientFactory> ingd_factory) : Pizza("Cheese Pizza"), m_ingd_factory(ingd_factory) {    }
    virtual ~CheesePizza()   {   }
	
    virtual void prepare()  { 
		std::puts("preparing ");

		cheese = m_ingd_factory->createCheese();
		sauce = m_ingd_factory->createSauce();

		std::puts("mixing ");
		std::puts(cheese->getName(). c_str());
		std::puts(sauce->getName(). c_str());
		std::puts(getName().c_str()); 
	}
    virtual void bake()     { std::puts("baking pizza"); }
    virtual void cut()      { std::puts("cutting pizza"); }
    virtual void box()      { std::puts("boxing"); }
};

class NonvegPizza : public Pizza {

	std::shared_ptr<PizzaIngredientFactory> m_ingd_factory = nullptr;
    public:
    NonvegPizza(std::shared_ptr<PizzaIngredientFactory> ingd_factory) : Pizza("Non veg Pizza"), m_ingd_factory(ingd_factory) {    }
    virtual ~NonvegPizza()   {   }
	
    virtual void prepare()  { 
		std::puts("preparing ");
		cheese = m_ingd_factory->createCheese();
		sauce = m_ingd_factory->createSauce();
		std::puts("mixing ");
		std::puts(cheese->getName(). c_str());
		std::puts(sauce->getName(). c_str());
		std::puts(getName().c_str()); 
	}
    virtual void bake()     { std::puts("baking pizza"); }
    virtual void cut()      { std::puts("cutting pizza"); }
    virtual void box()      { std::puts("boxing"); }
};

class PizzaStore {
    public:
    virtual std::unique_ptr<Pizza> createPizza(std::string type) = 0;  // abstract factory method
    virtual ~PizzaStore()   {   }

    std::unique_ptr<Pizza> orderPizza(std::string type) {

        std::unique_ptr<Pizza> pizza = createPizza(type);
        
        pizza->prepare();
        pizza->bake();
        pizza->cut();
        pizza->box();

        return pizza;
    }
};

class NyPizzaStore : public PizzaStore {

	std::shared_ptr<PizzaIngredientFactory> ingd_factory = std::make_shared<NyPizzaIngredientFactory>();

    std::unique_ptr<Pizza> pizza = nullptr;

    std::unique_ptr<Pizza> createPizza(std::string type) {
        if(type.compare("cheese")) {
            pizza = std::make_unique<CheesePizza>(ingd_factory);
			pizza->setName("New York Style Cheese Pizza");
        }
        else if(type.compare("nonveg")) {
            pizza = std::make_unique<NonvegPizza>(ingd_factory);
			pizza->setName("New York Style Nonveg Pizza");
        }
        
        return std::move(pizza);
    }  
};

class ChicagoPizzaStore : public PizzaStore {
	std::shared_ptr<PizzaIngredientFactory> ingd_factory = std::make_shared<ChicagoPizzaIngredientFactory>();
	
	std::unique_ptr<Pizza> pizza = nullptr;

    std::unique_ptr<Pizza> createPizza(std::string type) {
        if(type.compare("cheese")) {
            pizza = std::make_unique<CheesePizza>(ingd_factory);
			pizza->setName("Chicago Style Cheese Pizza");
        }
        else if(type.compare("nonveg")) {
            pizza = std::make_unique<NonvegPizza>(ingd_factory);
			pizza->setName("Chicago Style Nonveg Pizza");
        }
        
        return std::move(pizza);
    }  
};

int main() {
    {
        std::unique_ptr<PizzaStore> ny_pizza_store = std::make_unique<NyPizzaStore>();
        std::unique_ptr<Pizza> nonveg_pizza = ny_pizza_store->orderPizza("nonveg");
        std::puts(nonveg_pizza->getName().c_str());
    }
    std::puts("");
    {
        std::unique_ptr<PizzaStore> ny_pizza_store = std::make_unique<NyPizzaStore>();
        std::unique_ptr<Pizza> cheese_pizza = ny_pizza_store->orderPizza("cheese");
        std::puts(cheese_pizza->getName().c_str());
    }


    std::puts("");
    {
        std::unique_ptr<PizzaStore> chicago_pizza_store = std::make_unique<ChicagoPizzaStore>();
        std::unique_ptr<Pizza> cheese_pizza = chicago_pizza_store->orderPizza("cheese");
        std::puts(cheese_pizza->getName().c_str());
    //}
    std::puts("");
    //{
        //std::unique_ptr<PizzaStore> chicago_pizza_store = std::make_unique<ChicagoPizzaStore>();
        std::unique_ptr<Pizza> nonveg_pizza = chicago_pizza_store->orderPizza("cheese");
        std::puts(nonveg_pizza->getName().c_str());
    }


    return 0;
}

/**********
    END OF FILE
***********/
