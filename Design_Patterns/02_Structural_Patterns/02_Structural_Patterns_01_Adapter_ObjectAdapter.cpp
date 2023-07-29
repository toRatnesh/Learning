/********
Object Adapter
	The object adapter uses object composition to combine classes with different interfaces.
	The object adapter requires a little more effort to write, but it's more flexible. 
    
    The object adapter version of DBConnection will work equally well with subclasses of 
    SepecificDB. The client simply passes an instance of a SepecificDB subclass to the 
    DBConnection constructor.

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
    : public DBConnection {

    std::string     m_ip;
    uint32_t        m_port;

    SepecificDB & sdb;

    public:
        DBConnectionAdapter(SepecificDB & sdb) : sdb(sdb) { }
        virtual void initialize(std::string ip, uint32_t port) override { 
            std::cout << "Initializing DB\n";
            m_ip    = ip;
            m_port  = port;
        };        
        void connectDB() override {
            sdb.initDB(m_ip, m_port);
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
    SepecificDB sdb;
    DBConnectionAdapter db_adapter(sdb);
    db_adapter.initialize("127.0.0.1", 4568);

    MyApplication myapp(db_adapter);
    myapp.connectWithDB();

    return 0;
}

/********
    END OF FILE
************/

