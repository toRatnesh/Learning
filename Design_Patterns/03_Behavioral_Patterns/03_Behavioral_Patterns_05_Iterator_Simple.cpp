/*******
    This example is implementation of Iterator Design Pattern
**************/

#include <iostream>
#include <stdexcept>
#include <sstream>

template<typename T>
class MyList {
    T           m_arr[100];
    size_t      m_size;
    public:
    MyList(size_t list_size, T val) : m_size(list_size)  {
        for(size_t i = 0; i < list_size; ++i) {
            m_arr[i] = val;
        }
    }
    size_t  size() const { return m_size; }
    T      get(size_t index) const { return m_arr[index]; }
};



// Iterator interface
template<typename T>
class MyIteratorInterface {
    public:
    virtual ~MyIteratorInterface() {}
    virtual void begin()        = 0;
    virtual void next()         = 0;
    virtual bool done() const   = 0;
    virtual T    cur_item() const  = 0;
};


// Iterator subclass implementations
template<typename T>
class MyListIterator : public MyIteratorInterface<T> {
    const MyList<T> & m_list;
    size_t          m_index;
    public:
    virtual ~MyListIterator() { }
    MyListIterator(const MyList<T> & list) 
        : m_list(list), m_index(0) { }
    virtual void begin()        { m_index = 0; };
    virtual void next()         { ++m_index; }
    virtual bool done() const   { return m_index >= m_list.size(); }
    virtual T    cur_item() const  {
        if(done()) {
            std::stringstream sstm ;
            sstm << "Index " << m_index << " is out of range";
            throw std::out_of_range(sstm.str());
        }
        return m_list.get(m_index); 
    };        
};

template<typename T>
class MyReverseListIterator : public MyIteratorInterface<T> {
    const MyList<T> & m_list;
    size_t          m_index;
    public:
    virtual ~MyReverseListIterator() { }
    MyReverseListIterator(const MyList<T> & list) 
        : m_list(list), m_index(0) { }
    virtual void begin()        { m_index = m_list.size(); };
    virtual void next()         { --m_index; }
    virtual bool done() const   { return m_index == 0; }
    virtual T    cur_item() const  {
        if(done()) {
            std::stringstream sstm ;
            sstm << "Index " << m_index << " is out of range";
            throw std::out_of_range(sstm.str());
        }        
        return m_list.get(m_index-1); 
    };        
};

// Using the iterators
void printListInt(MyIteratorInterface<int> & it_list) {
    for(it_list.begin(); ! it_list.done(); it_list.next()) {
        std::cout << it_list.cur_item() << ' ';
    }
    std::cout << '\n';
}


int main() {

    MyList<int> ilist(5, 4);

    MyListIterator<int>  fwd_it(ilist);
    printListInt(fwd_it);

    MyReverseListIterator<int>  rev_it(ilist);
    printListInt(rev_it);

    return 0;
}


/**********
    END OF FILE
****************/


