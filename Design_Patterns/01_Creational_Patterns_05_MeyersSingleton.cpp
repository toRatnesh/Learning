/**************

References
	http://www.modernescpp.com/index.php/creational-patterns-singleton

******************/

#include <iostream>

class MeyersSingleton {
	int m_value;
	MeyersSingleton(const int v = 0) :	m_value(v) { }

	public:
    // delete copy (for C++11 and beyond this will also delete move)
    MeyersSingleton(const MeyersSingleton &) = delete;
    MeyersSingleton& operator=(const MeyersSingleton &) = delete;

	int get_value()		{ return m_value; }
	void set_value(const int v)	{ m_value = v; }

	static MeyersSingleton & instance() {
        static MeyersSingleton s_instance;
		return s_instance;
	}
};

void foo(void) {
	MeyersSingleton::instance().set_value(1);
	std::clog << __func__ << " singleton instance value is " << MeyersSingleton::instance().get_value() << '\n';
}

void bar(void) {
	MeyersSingleton::instance().set_value(2);
	std::clog << __func__ << " singleton instance value is " << MeyersSingleton::instance().get_value() << '\n';
}

int main() {
	std::clog << __func__ << " singleton instance value is " << MeyersSingleton::instance().get_value() << '\n';
	foo();
    std::clog << __func__ << " singleton instance value is " << MeyersSingleton::instance().get_value() << '\n';
	bar();
    std::clog << __func__ << " singleton instance value is " << MeyersSingleton::instance().get_value() << '\n';

    /*  COPY RESULTS IN COMPILATION ERROR because of deleted COPY constructor
    MeyersSingleton copyObj = *(MeyersSingleton::instance());
    copyObj.set_value(7);
    std::clog << __func__ << " singleton instance value is " << MeyersSingleton::instance().get_value() << '\n';
    std::clog << __func__ << " singleton instance value is " << copyObj.get_value() << '\n';
    */
    
	return 0;
}


/*******
	END OF FILE
***********/
