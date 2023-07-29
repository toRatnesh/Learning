/*******
    This example is implementation of Iterator Design Pattern using Polymorphic Iterator with Proxy Pattern
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
    virtual T       get(size_t index) const = 0;
    virtual MyIteratorInterface<T> *    createIterator() const = 0;
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
    T      get(size_t index) const { return m_arr[index]; }
    virtual MyIteratorInterface<T> *    createIterator() const;
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
    T      get(size_t index) const { return m_arr[index]; }
    virtual MyIteratorInterface<T> *    createIterator() const;
};

// Iterator interface
template<typename T>
class MyIteratorInterface {
    public:
    virtual ~MyIteratorInterface() { }
    virtual void begin()        = 0;
    virtual void next()         = 0;
    virtual bool done() const   = 0;
    virtual T    cur_item() const  = 0;
};


// Iterator subclass implementations
template<typename T>
class MyListIterator : public MyIteratorInterface<T> {
    const MyList<T> * m_list;
    size_t          m_index;

    public:
    virtual ~MyListIterator() { }

    MyListIterator(const MyList<T> * list) 
        : m_list(list), m_index(0) { }

    virtual void begin()        { m_index = 0; };
    virtual void next()         { ++m_index; }
    virtual bool done() const   { return m_index >= m_list->size(); }
    virtual T    cur_item() const  {
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
    const SkipList<T> * m_list;
    size_t          m_index;

    public:
    virtual ~SkipListIterator() { }

    SkipListIterator(const SkipList<T> * list) 
        : m_list(list), m_index(0) { }

    virtual void begin()        { m_index = m_list->size(); };
    virtual void next()         { --m_index; }
    virtual bool done() const   { return m_index == 0; }
    virtual T    cur_item() const  {
        if(done()) {
            std::stringstream sstm ;
            sstm << "Index " << m_index << " is out of range";
            throw std::out_of_range(sstm.str());
        }
        return m_list->get(m_index - 1); 
    };        
};

template<typename T>
MyIteratorInterface<T> * MyList<T>::createIterator() const { 
    return new MyListIterator<T>(this);
}

template<typename T>
MyIteratorInterface<T> * SkipList<T>::createIterator() const { 
    return new SkipListIterator<T>(this);
}

// proxy for iterator pointer
template<typename T>
class IteratorPtr {
    MyIteratorInterface<T> * m_iptr;
    public:
    ~IteratorPtr() { delete m_iptr; m_iptr = nullptr; }
    IteratorPtr(MyIteratorInterface<T> * iptr) : m_iptr(iptr) { }

    // delete copy operations
    IteratorPtr(const IteratorPtr & ) = delete;
    IteratorPtr& operator=(const IteratorPtr &) = delete;

    MyIteratorInterface<T> * operator->()   { return m_iptr; }
    MyIteratorInterface<T> & operator*()    { return *m_iptr; } 
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

    std::cout << "=== Using Polymorphic Iterator with Proxy Pattern ===\n";
    {
        MyList<int> ilist(5, 3);    
        IteratorPtr<int> fwd_it = ilist.createIterator();
        printListInt(*fwd_it);
    }

    {
        SkipList<int> ilist(6, 7);    
        IteratorPtr<int> fwd_it = ilist.createIterator();
        printListInt(*fwd_it);
    }

    return 0;
}


/**********
    END OF FILE
****************/


