#include <iostream>
#include <pqxx/pqxx>

#include "../../include/db/dbConn.hpp"

using namespace std;
using namespace pqxx;

// Database connection handling

bool Database::connect() {
    try {
        // Create a new connection using the connection string
        conn = make_unique<connection>(connection_str);
        return conn->is_open(); // Return true if connection is successfully opened
    } catch (const exception &e) {
        cerr << "Error connecting to DB: " << e.what() << "\n";
        return false; // Return false if connection fails
    }
}

// Return raw pointer to the connection
connection* Database::getConnection() {
    return conn.get();
}

void Database::createTables() {
    if (!conn || !conn->is_open()) return; // Ensure connection is valid

    work tx(*conn); // Start a transaction

    // Create 'users' table if it doesn't exist
    tx.exec(
        "CREATE TABLE IF NOT EXISTS users ("
        "id SERIAL PRIMARY KEY, "
        "username VARCHAR(50) UNIQUE NOT NULL, "
        "password VARCHAR(50) NOT NULL);"
    );

    // Create 'creatures' table if it doesn't exist
    tx.exec(
        "CREATE TABLE IF NOT EXISTS creatures ("
        "id SERIAL PRIMARY KEY, "
        "owner_id INT REFERENCES users(id), "
        "name VARCHAR(50), "
        "species VARCHAR(50), "
        "power VARCHAR(50), "
        "level INT DEFAULT 1);"
    );

    tx.commit();
}
