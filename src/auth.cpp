#include <iostream>

#include "../include/auth.hpp"
#include "../include/utils.hpp"
#include "../include/db/dbMethods.hpp"

using namespace std;

// Global variables for current session
string username, password, hashed_password;
static int current_user_id = -1; // Tracks logged-in user
extern Database db; // Reference to global Database object

bool userRegister() {
    bool register_succeeded = false;

    while (!register_succeeded) {
        cout << "--------------------\n";
        cout << "REGISTER NEW USER\n";
        cout << "--------------------\n";

        // Ask for username
        cout << "Enter your username: ";
        cin >> username;

        // Validate input: only alphanumeric characters
        if (!validInput(username)) {
            cout << "\nInvalid characters in username. Try again.\n";
        }

        username = lowercase(username); // normalize to lowercase

        // Ask for password with hidden input
        cout << "Enter your password: ";
        password = hiddenInput();

        // Validate password input
        if (!validInput(password)) {
            cout << "\nInvalid characters in password. Try again.\n";
        }

        // Hash the password before storing in DB
        hashed_password = hashPassword(password);

        // Create DbMethods object to interact with database
        DbMethods dbMethods(&db);

        // Attempt to add user to database
        if (dbMethods.addUser(username, hashed_password)) {
            cout << "\nUser registered successfully!\n";
            register_succeeded = true;
            break;
        } else {
            // Failure (e.g., username already taken)
            cout << "\nRegistration failed. Username might be taken. Try again.\n";
        }
    }

    return register_succeeded;
}

bool userLogin() {
    bool login_succeeded = false;

    while (!login_succeeded) {
        cout << "--------------------\n";
        cout << "USER LOGIN\n";
        cout << "--------------------\n";

        // Ask for username
        cout << "Enter your username: ";
        cin >> username;
        username = lowercase(username);

        // Ask for password (hidden input)
        cout << "Enter your password: ";
        password = hiddenInput();

        // Hash the password before checking
        hashed_password = hashPassword(password);

        DbMethods dbMethods(&db);

        if (dbMethods.verifyLogin(username, hashed_password)) {
            current_user_id = dbMethods.getUserId(username); // Store user ID
            cout << "\nLogin successful!\n";
            login_succeeded = true;
        } else {
            cout << "\nLogin failed. Invalid username or password. Try again.\n";
        }
    }

    return login_succeeded;
}

// Getters

string getUsername() {
  return username;
}

int getOwnerId() {
    return current_user_id;
}
