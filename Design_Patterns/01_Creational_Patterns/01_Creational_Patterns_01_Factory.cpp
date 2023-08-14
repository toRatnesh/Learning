/*************

Reference:
    Book: Head First: Design Patterns
    
Factory Pattern Code Sample

***************/

#include <iostream>
#include <string>

class Pizza {
    std::string name;
    public:
        Pizza(std::string name) : name(name) {  }
        virtual ~Pizza()    {  }
        virtual void prepare()  { std::puts("preparing pizza"); }
        virtual void bake()     { std::puts("baking pizza"); }
        virtual void cut()      { std::puts("cutting pizza"); }
        virtual void box()      { std::puts("boxing pizza"); }
        virtual std::string getName()   { return name; }
};

class NyStyleCheesePizza : public Pizza {
    public:
    NyStyleCheesePizza() : Pizza("New York Style Cheese Pizza") {    }
    virtual ~NyStyleCheesePizza()   {   }
    virtual void prepare()  { std::puts("preparing "); std::puts(getName().c_str()); }
    virtual void bake()     { std::puts("baking pizza"); }
    virtual void cut()      { std::puts("cutting pizza"); }
    virtual void box()      { std::puts("boxing with new york based advertisement"); }
};

class NyStyleNonvegPizza : public Pizza {
    public:
    NyStyleNonvegPizza() : Pizza("New York Style Nonveg Pizza") {    }
    virtual ~NyStyleNonvegPizza()   {   }
    virtual void prepare()  { std::puts("preparing "); std::puts(getName().c_str()); }
    virtual void bake()     { std::puts("baking pizza"); }
    virtual void cut()      { std::puts("cutting pizza"); }
    virtual void box()      { std::puts("boxing with new york based advertisement"); }
};

class ChicagoStyleCheesePizza : public Pizza {
    public:
    ChicagoStyleCheesePizza() : Pizza("Chicago Style Cheese Pizza") {    }
    virtual ~ChicagoStyleCheesePizza()  {   }
    virtual void prepare()  { std::puts("preparing "); std::puts(getName().c_str()); }
    virtual void bake()     { std::puts("baking pizza"); }
    virtual void cut()      { std::puts("cutting pizza"); }
    virtual void box()      { std::puts("boxing with new york based advertisement"); }
};

class ChicagoStyleNonvegPizza : public Pizza {
    public:
    ChicagoStyleNonvegPizza() : Pizza("Chicago Style Nonveg Pizza") {    }
    virtual ~ChicagoStyleNonvegPizza()  {   }
    virtual void prepare()  { std::puts("preparing "); std::puts(getName().c_str()); }
    virtual void bake()     { std::puts("baking pizza"); }
    virtual void cut()      { std::puts("cutting pizza"); }
    virtual void box()      { std::puts("boxing with new york based advertisement"); }
};

class PizzaStore {
    public:
    virtual Pizza * createPizza(std::string type) = 0;  // abstract factory method
    virtual ~PizzaStore()   {   }

    Pizza * orderPizza(std::string type) {
        Pizza * pizza = nullptr;
        pizza = createPizza(type);

        pizza->prepare();
        pizza->bake();
        pizza->cut();
        pizza->box();

        return pizza;
    }
};

class NyPizzaStore : public PizzaStore {
    Pizza * createPizza(std::string type) {
        if(! type.compare("cheese")) {
            return new NyStyleCheesePizza();
        }
        else if(! type.compare("nonveg")) {
            return new NyStyleNonvegPizza();
        }
        
        return nullptr;
    }  
};

class ChicagoPizzaStore : public PizzaStore {
    Pizza * createPizza(std::string type) {
        if(! type.compare("cheese")) {
            return new ChicagoStyleCheesePizza();
        }
        else if(! type.compare("nonveg")) {
            return new ChicagoStyleNonvegPizza();
        }
        
        return nullptr;
    }  
};

int main() {
    {
        PizzaStore * ny_pizza_store = new NyPizzaStore{};
        Pizza * nonveg_pizza = ny_pizza_store->orderPizza("nonveg");
        std::puts(nonveg_pizza->getName().c_str());
        delete nonveg_pizza;
        delete ny_pizza_store;
    }
    std::puts("");
    {
        PizzaStore * ny_pizza_store = new NyPizzaStore{};
        Pizza * cheese_pizza = ny_pizza_store->orderPizza("cheese");
        std::puts(cheese_pizza->getName().c_str());
        delete cheese_pizza;
        delete ny_pizza_store;
    }
    std::puts("");
    {
        PizzaStore * chicago_pizza_store = new ChicagoPizzaStore{};
        Pizza * cheese_pizza = chicago_pizza_store->orderPizza("cheese");
        std::puts(cheese_pizza->getName().c_str());
        delete cheese_pizza;
        delete chicago_pizza_store;
    }
    std::puts("");
    {
        PizzaStore * chicago_pizza_store = new ChicagoPizzaStore{};
        Pizza * nonveg_pizza = chicago_pizza_store->orderPizza("nonveg");
        std::puts(nonveg_pizza->getName().c_str());
        delete nonveg_pizza;
        delete chicago_pizza_store;
    }

    return 0;
}

/**********
    END OF FILE
***********/

