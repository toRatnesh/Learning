/*********

    Composite pattern

    In this example safety is preferred over transparency

    child management is defined in Composite class
    Leaf and Composite have different interfaces

    To avoid call to child operation by Leaf class two methods could be used:
        1. A method getComposite() is added to Component it defautls returns nullptr while 
            for Composite class it returns this pointer to indicate Composite class object
        2. dynamic_cast to Composite * (dynamic_cast<Composite *>(obj)) 
            returns nullptr for Leaf class and 
            a pointer value for Composite class object

    This way safety is preferred over transparency. 

**************/

#include <iostream>
#include <vector>

class Composite;

class Component {
    public:
        virtual ~Component() {}
        virtual void        display()           = 0;
        virtual Composite*  getComposite()      { return nullptr; }
};

class Composite : public Component {
        std::vector<Component *> m_cmp_con;
        public:
        virtual ~Composite() {}
        virtual void display() override   {
            for(auto & elem : m_cmp_con) 
                elem->display();
        }
        virtual Composite*  getComposite() { return this;}        

        // child operations inside Composite only for safety
        virtual void add(Component * cmp) { 
            m_cmp_con.push_back(cmp);
            return ;
        }        
        virtual Component*  child(int idx) { return m_cmp_con[idx]; };
        
};

class Leaf : public Component {
    int m_id;
    public:
    Leaf(int id) : m_id(id) { }
    virtual void display() override {
        std::cout << "Leaf - " << m_id << " execution\n";
    }
};

int main() {
    Component * lp_component = nullptr;

    Composite * lp_composite_1 = new Composite;
    Composite * lp_composite_2 = new Composite;
    Leaf        * lp_leaf_1   = new Leaf(1);
    Leaf        * lp_leaf_2   = new Leaf(2);
    Leaf        * lp_leaf_3   = new Leaf(3);

    Composite * temp_comp = nullptr;

    lp_component = lp_composite_1;
    if(temp_comp = lp_component->getComposite(); nullptr != temp_comp) {
        temp_comp->add(lp_leaf_1);
        temp_comp->add(lp_composite_2);
    }
    std::cout << "=== Display composite - 1 ===\n";
    lp_component->display();

    // following will not add
    lp_component = lp_leaf_2;
    if(temp_comp = lp_component->getComposite(); nullptr != temp_comp) {
        temp_comp->add(lp_leaf_3);
    }

    lp_component = lp_composite_1->child(1);
    if(temp_comp = lp_component->getComposite(); nullptr != temp_comp) {
        temp_comp->add(lp_leaf_2);
        temp_comp->add(lp_leaf_3);
    }
    std::cout << "=== Display composite - 1's child ===\n";
    lp_component->display();

    std::cout << '\n';
    lp_component = lp_composite_1;
    std::cout << "=== Display complete structure ===\n";
    lp_component->display();

    std::cout << '\n';
    std::cout << "=== Using dynamic_cast<Composite *> to check whether object is a Composite or not ===\n";
    {
        Composite * temp_comp = dynamic_cast<Composite *>(lp_composite_1);
        if(nullptr == temp_comp) {
            std::cout << "dynamic_cast<Composite *>(lp_composite_1) returns nullptr\n";
        } else {
            std::cout << "dynamic_cast<Composite *>(lp_composite_1) returns a pointer value\n";
        }
    }

    {
        Composite * temp_comp = dynamic_cast<Composite *>(lp_leaf_3);
        if(nullptr == temp_comp) {
            std::cout << "dynamic_cast<Composite *>(lp_leaf_3) returns nullptr\n";
        } else {
            std::cout << "dynamic_cast<Composite *>(lp_leaf_3) returns a pointer value\n";
        }
    }

    delete lp_composite_1;   lp_composite_1 = nullptr;
    delete lp_composite_2;   lp_composite_2 = nullptr;

    delete lp_leaf_1; lp_leaf_1 = nullptr;
    delete lp_leaf_2; lp_leaf_2 = nullptr;
    delete lp_leaf_3; lp_leaf_3 = nullptr;

    return 0;
}

/*********


Output:

=== Display composite - 1 ===
Leaf - 1 execution
=== Display composite - 1's child ===
Leaf - 2 execution
Leaf - 3 execution

=== Display complete structure ===
Leaf - 1 execution
Leaf - 2 execution
Leaf - 3 execution

=== Using dynamic_cast<Composite *> to check whether object is a Composite or not ===
dynamic_cast<Composite *>(lp_composite_1) returns a pointer value
dynamic_cast<Composite *>(lp_leaf_3) returns nullptr


***********
    END OF FILE
**************/

