/********
Class Adapter
	A class adapter uses multiple inheritance to adapt interfaces. 
	Use one inheritance branch to inherit the interface and another branch to inherit the implementation. 
	In C++, inherit the interface publicly and inherit the implementation privately.

************/

#include <iostream>
#include <string>
#include <cstdint>

class SepecificDB {
    public:
        void initDB(std::string ip, uint32_t port) {
            std::cout   << "Specific DB initializing with " 
                        << ip << ":" << port << '\n';
        }
};

class DBConnection {
    public:
        virtual void initialize(std::string, uint32_t)   = 0;
        virtual void connectDB() { }
};

class DBConnectionAdapter
    : public DBConnection, private SepecificDB {

    std::string      m_ip;
    uint32_t        m_port;
    public:
        virtual void initialize(std::string ip, uint32_t port) override { 
            std::cout << "Initializing DB\n";
            m_ip    = ip;
            m_port  = port;
        };
        void connectDB() override {
            initDB(m_ip, m_port);
        }
};

class MyApplication {
    DBConnection & db;
    public:
    MyApplication(DBConnection & db) : db(db) {}

    void connectWithDB() {
        db.connectDB();
    }
};

int main() {
    DBConnectionAdapter db_adapter;
    db_adapter.initialize("127.0.0.1", 4568);

    MyApplication myapp(db_adapter);
    myapp.connectWithDB();

    return 0;
}

/********
    END OF FILE
************/

