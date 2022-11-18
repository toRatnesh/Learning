#include <iostream>

class ClassicSingleton {
	int m_value;
	static ClassicSingleton *s_instance;
	ClassicSingleton(const int v = 0) :	m_value(v) { }

    // DECLARE COPY CONSTRUCTOR PRIVATE AND DO NOT DEFINE IT TO PREVENT COPY (for C++11 and beyond this will also delete move)
    ClassicSingleton(const ClassicSingleton &);
    ClassicSingleton& operator=(const ClassicSingleton &);

	public:
	int get_value()		{ return m_value; }
	void set_value(int v)	{ m_value = v; }

	static ClassicSingleton* instance() {
		if (!s_instance)
			s_instance = new ClassicSingleton;
		return s_instance;
	}
};

// initialize static instance
ClassicSingleton *ClassicSingleton::s_instance = 0;

void foo(void) {
	ClassicSingleton::instance()->set_value(1);
	std::clog << __func__ << " singleton instance value is " << ClassicSingleton::instance()->get_value() << '\n';
}

void bar(void) {
	ClassicSingleton::instance()->set_value(2);
	std::clog << __func__ << " singleton instance value is " << ClassicSingleton::instance()->get_value() << '\n';
}

int main() {
	std::clog << __func__ << " singleton instance value is " << ClassicSingleton::instance()->get_value() << '\n';
	foo();
    std::clog << __func__ << " singleton instance value is " << ClassicSingleton::instance()->get_value() << '\n';
	bar();
    std::clog << __func__ << " singleton instance value is " << ClassicSingleton::instance()->get_value() << '\n';

    /*  COPY RESULTS IN COMPILATION ERROR because of UNDEFINED PRIVATE COPY AND NOT DEFINED
    ClassicSingleton copyObj = *(ClassicSingleton::instance());
    copyObj.set_value(7);
    std::clog << __func__ << " singleton instance value is " << ClassicSingleton::instance()->get_value() << '\n';
    std::clog << __func__ << " singleton instance value is " << copyObj.get_value() << '\n';
    */
	return 0;
}

