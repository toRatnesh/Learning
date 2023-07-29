/*******

Reference:
    https://sourcemaking.com/design_patterns/builder/java/2

    Builder implementation in C++

******/

#include <iostream>
#include <memory>
#include <string>

// "Product"
class Pizza {
   public:
    void setDough(const std::string& dough) { m_dough = dough; }
    void setSauce(const std::string& sauce) { m_sauce = sauce; }
    void setTopping(const std::string& topping) { m_topping = topping; }
    void open() const {
        std::clog << "Pizza with " << m_dough << " dough, " << m_sauce
             << " sauce and " << m_topping << " topping." << '\n';
    }

   private:
    std::string m_dough;
    std::string m_sauce;
    std::string m_topping;
};

// "Abstract Builder"
class PizzaBuilder {
   public:
    virtual ~PizzaBuilder(){};

    std::unique_ptr<Pizza> getPizza() { return std::move(m_pizza); }
    void createNewPizzaProduct() { m_pizza = std::make_unique<Pizza>(); }
    virtual void buildDough() = 0;
    virtual void buildSauce() = 0;
    virtual void buildTopping() = 0;

   protected:
    std::unique_ptr<Pizza> m_pizza;
};

// concrete builder
class HawaiianPizzaBuilder : public PizzaBuilder {
   public:
    virtual ~HawaiianPizzaBuilder(){};

    virtual void buildDough() { m_pizza->setDough("cross"); }
    virtual void buildSauce() { m_pizza->setSauce("mild"); }
    virtual void buildTopping() { m_pizza->setTopping("ham+pineapple"); }
};

// concrete builder
class SpicyPizzaBuilder : public PizzaBuilder {
   public:
    virtual ~SpicyPizzaBuilder(){};

    virtual void buildDough() { m_pizza->setDough("pan baked"); }
    virtual void buildSauce() { m_pizza->setSauce("hot"); }
    virtual void buildTopping() { m_pizza->setTopping("pepperoni+salami"); }
};

// Director
class Cook {
   public:
    void openPizza() { m_pizzaBuilder->getPizza()->open(); }
    void makePizza(PizzaBuilder* pb) {
        m_pizzaBuilder = pb;
        m_pizzaBuilder->createNewPizzaProduct();
        m_pizzaBuilder->buildDough();
        m_pizzaBuilder->buildSauce();
        m_pizzaBuilder->buildTopping();
    }

   private:
    PizzaBuilder* m_pizzaBuilder;
};

int main() {
    Cook cook;
    HawaiianPizzaBuilder hawaiianPizzaBuilder;
    SpicyPizzaBuilder spicyPizzaBuilder;

    cook.makePizza(&hawaiianPizzaBuilder);
    cook.openPizza();

    cook.makePizza(&spicyPizzaBuilder);
    cook.openPizza();
}


/********
	END OF FILE
********/

