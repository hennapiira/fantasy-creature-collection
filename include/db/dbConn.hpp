#pragma once
#include <pqxx/pqxx> // lib for PostgreSQL database operations
#include <memory>



class Database {
    private:
        std::string connection_str; 
        std::unique_ptr<pqxx::connection> conn; // Smart pointer to manage the PostgreSQL connection

    public:
        Database(const std::string& conn_str)
        : connection_str(conn_str), conn(nullptr) {}

        // Establish DB connection
        bool connect();

        // Create tables in the database
        void createTables();

        // Getter for the raw connection pointer
        pqxx::connection* getConnection();
};

