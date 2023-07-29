/*********

    Composite pattern
    
    In this example transparency is preferred over safety

    Child management interface is present in Component class
    Line and Composite have same interfaces

**************/

#include <iostream>
#include <vector>

class Component {
    public:
        virtual ~Component() {}
        virtual void        display()           = 0;
        virtual void        add(Component * ) { return ; }
        virtual Component*  child(int ) { return nullptr; }
};

class Composite : public Component {
        std::vector<Component *> m_cmp_con;
        public:
        virtual ~Composite() {}
        
        virtual void display() override   {
            for(auto & elem : m_cmp_con) 
                elem->display();
        }

        virtual void add(Component * cmp) { 
            m_cmp_con.push_back(cmp);
            return ;
        }
        virtual Component*  child(int idx) { return m_cmp_con[idx]; };
        
};

class Line : public Component {
    int m_id;
    public:
    Line(int id) : m_id(id) { }
    virtual void display() override {
        std::cout << "Line - " << m_id << '\n';
    }
};

class Circle : public Component {
    int m_id;
    public:
    Circle(int id) : m_id(id) { }
    virtual void display() override {
        std::cout << "Circle - " << m_id << '\n';
    }
};

int main() {
    /*
                    Comosite-1
                    /       \
                Line-1      Composite-2
                            /        \
                        Line-2      Circle-1
    
    */
    Component * lp_component = nullptr;

    Composite   * lp_composite_1    = new Composite;
    Composite   * lp_composite_2    = new Composite;

    Line        * lp_line_1         = new Line(1);
    Line        * lp_line_2         = new Line(2);

    Circle      * lp_crcl_1         = new Circle(1);

    lp_component = lp_composite_1;
    if(nullptr != lp_component) {
        lp_component->add(lp_line_1);
        lp_component->add(lp_composite_2);
    }
    std::cout << "=== Display composite - 1 ===\n";
    lp_component->display();


    // following will not add
    lp_component = lp_line_2;
    if(nullptr != lp_component) {
        lp_component->add(lp_crcl_1);
    }

    lp_component = lp_composite_1->child(1);
    if(nullptr != lp_component) {
        lp_component->add(lp_line_2);
        lp_component->add(lp_crcl_1);
    }

    std::cout << "=== Display composite - 1's child ===\n";
    lp_component->display();

    std::cout << '\n';
    lp_component = lp_composite_1;
    std::cout << "=== Display complete structure ===\n";
    lp_component->display();

    delete lp_composite_1;   lp_composite_1 = nullptr;
    delete lp_composite_2;   lp_composite_2 = nullptr;

    delete lp_line_1; lp_line_1 = nullptr;
    delete lp_line_2; lp_line_2 = nullptr;
    delete lp_crcl_1; lp_crcl_1 = nullptr;

    return 0;
}

/*********

Output:

=== Display composite - 1 ===
Line - 1
=== Display composite - 1's child ===
Line - 2
Circle - 1

=== Display complete structure ===
Line - 1
Line - 2
Circle - 1


***************
    END OF FILE
**************/

