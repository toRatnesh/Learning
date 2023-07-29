/*******
    This example is implementation of Iterator Design Pattern With Internal Iterator
**************/

#include <iostream>
#include <stdexcept>
#include <sstream>

template<typename T>
class MyIteratorInterface;

template<typename T>
class AbstractList {
    public:
    virtual ~AbstractList() { }
    virtual size_t  size() const    = 0;
    virtual T&       get(size_t index)  = 0;
    virtual MyIteratorInterface<T> *    createIterator()  = 0;
};

template<typename T>
class MyList : public AbstractList<T> {
    T           m_arr[100];
    size_t      m_size;
    public:

    virtual ~MyList() { }

    MyList(size_t list_size, T val) : m_size(list_size) { 
        for(size_t i = 0; i < list_size; ++i) {
            m_arr[i] = val;
        }
    }
    size_t  size() const { return m_size; }
    T&      get(size_t index)  { return m_arr[index]; }
    virtual MyIteratorInterface<T> *    createIterator();
};

template<typename T>
class SkipList : public AbstractList<T> {
    T           m_arr[100];
    size_t      m_size;
    public:

    virtual ~SkipList() { }

    SkipList(size_t list_size, T val) : m_size(list_size) { 
        for(size_t i = 0; i < list_size; ++i) {
            m_arr[i] = val++;
        }
    }
    size_t  size() const { return m_size; }
    T&      get(size_t index)  { return m_arr[index]; }
    virtual MyIteratorInterface<T> *    createIterator();
};

// Iterator interface
template<typename T>
class MyIteratorInterface {
    public:
    virtual ~MyIteratorInterface() { }
    virtual void begin()        = 0;
    virtual void next()         = 0;
    virtual bool done() const   = 0;
    virtual T&    cur_item()   = 0;
};


// Iterator subclass implementations
template<typename T>
class MyListIterator : public MyIteratorInterface<T> {
    MyList<T> * m_list;
    size_t          m_index;

    public:
    virtual ~MyListIterator() { }

    MyListIterator(MyList<T> * list) 
        : m_list(list), m_index(0) { }

    virtual void begin()        { m_index = 0; };
    virtual void next()         { ++m_index; }
    virtual bool done() const   { return m_index >= m_list->size(); }
    virtual T&    cur_item()   {
        if(done()) {
            std::stringstream sstm ;
            sstm << "Index " << m_index << " is out of range";
            throw std::out_of_range(sstm.str());
        }
        return m_list->get(m_index); 
    };        
};


// Iterator subclass implementations
template<typename T>
class SkipListIterator : public MyIteratorInterface<T> {
    SkipList<T> * m_list;
    size_t          m_index;

    public:
    virtual ~SkipListIterator() { }

    SkipListIterator(SkipList<T> * list) 
        : m_list(list), m_index(0) { }

    virtual void begin()        { m_index = m_list->size(); };
    virtual void next()         { --m_index; }
    virtual bool done() const   { return m_index == 0; }
    virtual T&    cur_item()  {
        if(done()) {
            std::stringstream sstm ;
            sstm << "Index " << m_index << " is out of range";
            throw std::out_of_range(sstm.str());
        }
        return m_list->get(m_index - 1); 
    };        
};

template<typename T>
MyIteratorInterface<T> * MyList<T>::createIterator()  { 
    return new MyListIterator<T>(this);
}

template<typename T>
MyIteratorInterface<T> * SkipList<T>::createIterator()  { 
    return new SkipListIterator<T>(this);
}


// internal iterator (internally uses an external iterator)
template<typename T>
class InternalItertor {
    MyListIterator<T>   m_list_iter;

    protected:
    virtual bool processItem(T & elem)  = 0;
    
    public:
    virtual ~InternalItertor() { }
    InternalItertor(MyList<T> * list) : m_list_iter(list) { }
    
    bool traverse() {
        bool res = false;
        for(m_list_iter.begin(); ! m_list_iter.done(); m_list_iter.next()) {
            res = processItem(m_list_iter.cur_item());
            if(false == res) {
                break;
            }
        }
        return res;
    }
};


class MultiplyBy : public InternalItertor<int> {
    int                 m_multiplier;
    protected:
    virtual bool processItem(int & elem) {
        elem = elem * m_multiplier;
        return true;
    }
    public:
    virtual ~MultiplyBy() { }
    MultiplyBy(MyList<int> * list, int multiplier) 
        : InternalItertor<int>(list), m_multiplier(multiplier) { }
};

class DisplayList : public InternalItertor<int> {
    protected:
    virtual bool processItem(int & elem) {
        std::cout << elem << ' ';
        return true;
    }
    public:
    virtual ~DisplayList() { }
    DisplayList(MyList<int> * list) 
        : InternalItertor<int>(list) { }
};

// Using the iterators
void printListInt(MyIteratorInterface<int> & it_list) {
    for(it_list.begin(); ! it_list.done(); it_list.next()) {
        std::cout << it_list.cur_item() << ' ';
    }
    std::cout << '\n';
}

int main() {
    std::cout << "=== Using Polymorphic Iterator ===\n";
    {
        MyList<int> ilist(5, 3);    
        MyIteratorInterface<int>  * fwd_it = ilist.createIterator();
        printListInt(*fwd_it);    
        delete fwd_it; fwd_it = nullptr;
    }

    {
        SkipList<int> ilist(6, 7);    
        MyIteratorInterface<int>  * fwd_it = ilist.createIterator();
        printListInt(*fwd_it);    
        delete fwd_it; fwd_it = nullptr;
    }

    std::cout << "=== Using Internal Iterator ===\n";
    {
        MyList<int> ilist(5, 3);
        MultiplyBy list_mul(&ilist, 3);
        DisplayList disp_list(&ilist);
        disp_list.traverse();   std::cout << '\n';
        list_mul.traverse();
        disp_list.traverse();   std::cout << '\n';
    }

    return 0;
}


/**********
    END OF FILE
****************/


