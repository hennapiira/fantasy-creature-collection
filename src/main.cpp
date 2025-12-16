#include "../include/controller.hpp"
#include "../include/db/dbConn.hpp"
#include "../include/utils.hpp"
#include <iostream>

std::string conn = loadDbConnectionString();
Database db(conn);

int main() {
    // Attempt to connect to the database
    if (!db.connect()) {
        std::cerr << "Failed to connect to the database.\n";
        return 1;
    }

    // Create tables if they do not exist
    db.createTables();

    // Start the application loop
    greet();
}