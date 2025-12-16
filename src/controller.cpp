#include <iostream>
#include <vector>

#include "../include/controller.hpp"
#include "../include/utils.hpp"
#include "../include/auth.hpp"
#include "../include/db/dbMethods.hpp"

using namespace std;

extern Database db; // Reference to the global database object

// Initial greeting and menu
void greet() {
    int select = 0;

    while(true) {
      cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
      cout << "WELCOME TO THE FANTASY CREATURE COLLECTION\n";
      cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n";
      cout << "SELECT 1 if you want to register new user\n";
      cout << "SELECT 2 if you already have a user\n\n";
      cin >> select;

      if (select == 1) {
        // Call registration function
        if(userRegister()) { 
          catalog();
        } 
        break;
      } else if (select == 2) {
        // Call login function
        if(userLogin()) {
          catalog();
        }
        break;
      } else {
        cout << "\n";
        cout << "Invalid selection, please try again.\n\n";
      }
    }
}

void catalog() {
  DbMethods dbMethods(&db); // Database methods object
  int owner_id = getOwnerId(); // Current logged-in user ID
  vector<Creature> creatures;  // Local cache of user's creatures

  string upper_username = uppercase(getUsername());
  int selection_input, id;
  string name, species, power;
  
  while(true) {
  cout << "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
  cout << "PLEASE SELECT ONE OF ABOVE, " << upper_username;
  cout << "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n";

  cout << "1 ADD NEW CREATURE\n";
  cout << "2 SHOW MY CREATURES\n";
  cout << "3 MODIFY CREATURE'S LEVEL\n";
  cout << "4 REMOVE CREATURE\n";
  cout << "5 LOGOUT\n";
  cin >> selection_input;

  switch (selection_input)
    {
    // Add new creature
    case 1:
      cout << "Name: ";
      cin >> name;
      cout << "Species: ";
      cin >> species;
      cout << "Power: ";
      cin >> power;

     owner_id = getOwnerId();

      if (dbMethods.addCreature(owner_id, name, species, power, 1)) {
          cout << "Creature added successfully.\n";
      } else {
          cout << "Failed to add creature.\n";
      } 
      break;
      
    // Show all creatures
    case 2:
      creatures = dbMethods.showAll(owner_id);
      if(creatures.empty()) {
          cout << "\nNo creatures in catalog.\n";
      } else {
        cout << "Here is your creatures:\n";
        for(size_t i = 0; i < creatures.size(); ++i) {
            cout << i+1 << ". "
            << creatures[i].getName() << " | "
            << creatures[i].getSpecies() << " | "
            << creatures[i].getPower() << " | LEVEL: "
            << creatures[i].getLevel() << " | ID: "
            << creatures[i].getId() << "\n";
        }
      }
      break;

    // Modify creature level 
    case 3: {
        cout << "Creatures ID: ";
        cin >> id;

        bool found = false;

        for (auto &c : creatures) {
            if (c.getId() == id) {
                found = true;
                cout << "SELECT 1 TO RAISE LEVEL OR 2 TO LOWER LEVEL\n";
                cin >> selection_input;

                int level = c.getLevel();
                if (selection_input == 1) level++;
                else if (selection_input == 2 && level > 1) level--;
                else {
                    cout << "\nInvalid selection.\n";
                    break;
                }

                // Update database and local cache
                if (dbMethods.updateLevel(id, level)) {
                    c.setLevel(level); 
                    cout << "\nLevel updated successfully. Level is now " << c.getLevel() << "\n";
                } else {
                    cout << "\nFailed to update level in database.\n";
                }

                break;
            }
        }

        if (!found) {
            cout << "Creature not found.\n";
        }
        break;
    }

    // Remove creature
    case 4: {
      cout << "Creature ID: ";
      cin >> id;

      bool found = false;

      for (auto it = creatures.begin(); it != creatures.end(); ++it) {
          if (it->getId() == id) {
              found = true;
              if (dbMethods.removeCreature(id)) {
                  cout << "Creature removed.\n";
                  creatures.erase(it); // Remove from local cache
              } else {
                  cout << "\nFailed to remove creature.\n";
              }
              break; // exit loop after removing/finding
          }
      }

      if (!found) {
          cout << "Creature not found.\n";
      }
      break;
    }

    // Logout
    case 5:
      return;

    // Invalid input
    default:
      cout << "\nInvalid selection. Try again.\n";
    }}
} 