#include <iostream>

class Creature {
  private:
    int id;
    std::string name;
    std::string species;
    std::string power;
    int level; // default 1
    
  public:
  Creature(int new_id, std::string new_name, std::string new_species, std::string new_power, int new_level = 1) 
  :id(new_id), name(new_name), species(new_species), power(new_power), level(new_level){}
    
    // Getter
    std::string getName();
    std::string getSpecies();
    std::string getPower();
    int getLevel();
    int getId();

    // Setter
    void setLevel(int new_level);
};