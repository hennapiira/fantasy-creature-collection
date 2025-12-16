#include "dbConn.hpp"  
#include "../creature.hpp" 
#include <vector>       

class DbMethods {
private:
    Database* db;

public:
    // Constructor: sets the database pointer
    DbMethods(Database* database) : db(database) {}

    // Getter: retrieves the user ID by username
    int getUserId(const std::string& username);

    // Authentication methods
    bool addUser(const std::string& username, const std::string& password);
    bool verifyLogin(const std::string& username, const std::string& hashed_password);

    // Creature-related methods
    bool addCreature(int owner_id, std::string name, std::string species, std::string power, int level);
    std::vector<Creature> showAll(int owner_id); 
    bool updateLevel(int id, int level);        
    bool removeCreature(int id);                 
};
