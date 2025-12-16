#include "../../include/db/dbMethods.hpp"
#include <pqxx/pqxx>
#include <iostream>

using namespace std;
using namespace pqxx;

// Getter 
int DbMethods::getUserId(const string& username) {
     // Start a transaction
    work tx(*db->getConnection());

    // Execute parameterized query to fetch user ID
    auto r = tx.exec_params(
        "SELECT id FROM users WHERE username = $1",
        username
    );

    if (r.empty()) return -1; // Return -1 if username not found
    return r[0][0].as<int>(); // Return user ID
}

// Auth methods
bool DbMethods::addUser(const string& username, const string& password) {
    if (!db || !db->getConnection()) return false;

    try {
        work tx(*db->getConnection());

        // Insert a new user with username and password
        tx.exec_params(
            "INSERT INTO users (username, password) VALUES ($1, $2)",
            username,
            password
        );
        tx.commit();
        return true;
    } catch (const exception &e) {
        cerr << "\nFailed to add user: " << e.what() << "\n";
        return false;
    }
}

bool DbMethods::verifyLogin(const string& username, const string& hashedPassword) {
    if (!db || !db->getConnection()) return false;

    try {
        work tx(*db->getConnection());

        // Fetch the stored hashed password for this username
        auto result = tx.exec_params("SELECT password FROM users WHERE username = $1", username);

        if (result.size() == 0) {
            return false; // username not found
        }

        string storedHash = result[0][0].as<string>();

        return storedHash == hashedPassword; // Check if password matches
    } catch (const exception& e) {
        cerr << "DB error: " << e.what() << "\n";
        return false;
    }
}


// Creature methods

bool DbMethods::addCreature(int owner_id, string name, string species, string power, int level) {
   if (!db || !db->getConnection()) return false;

    try {
        work tx(*db->getConnection());
        // Insert a new creature with owner ID and properties
        tx.exec_params(
            "INSERT INTO creatures (owner_id, name, species, power, level) VALUES ($1, $2, $3, $4, $5)",
            owner_id,
            name,
            species,
            power,
            level
        );
        tx.commit();
        return true;
    } catch (const exception &e) {
        cerr << "\nFailed to add creature: " << e.what() << "\n";
        return false;
    }
}

vector<Creature> DbMethods::showAll(int owner_id) {
    vector<Creature> creatures;

    if (!db || !db->getConnection()) return creatures;

    try {
        work tx(*db->getConnection());

        // Select all creatures belonging to a specific owner
        auto result = tx.exec_params(
            "SELECT id, name, species, power, level FROM creatures WHERE owner_id = $1",
            owner_id
        );

        // Convert database rows to Creature objects
        for (const auto& row : result) {
            Creature c(
                row["id"].as<int>(),
                row["name"].as<string>(),
                row["species"].as<string>(),
                row["power"].as<string>(),
                row["level"].as<int>()
            );

            creatures.push_back(c);
        }
    } catch (const exception &e) {
        cerr << "\nFailed to show creatures: " << e.what() << "\n";
    }

    return creatures;
}

bool DbMethods::updateLevel(int id, int level) {
  if (!db || !db->getConnection()) return false;

  try {
        work tx(*db->getConnection());

        // Update level of a specific creature by ID
        tx.exec_params(
            "UPDATE creatures SET level = $1 WHERE id = $2",
            level,
            id
        );

        tx.commit();
        return true;
    } catch (const exception &e) {
        cerr << "Failed to update creature level: " << e.what() << "\n";
        return false;
    }
}

bool DbMethods::removeCreature(int id) {
  if (!db || !db->getConnection()) return false;

  try {
        work tx(*db->getConnection());

         // Delete creature by ID
        tx.exec_params(
            "DELETE FROM creatures WHERE id = $1",
            id
        );

        tx.commit();
        return true;
    } catch (const exception &e) {
        cerr << "Failed to delete creature: " << e.what() << "\n";
        return false;
    }
}