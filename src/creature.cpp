#include <iostream>
#include <string>

#include "../include/creature.hpp"

// Getter
std::string Creature::getName() {
    return name;
}

std::string Creature::getSpecies() {
    return species;
}
    
std::string Creature::getPower(){
    return power;
}

int Creature::getLevel(){
    return level;
}

int Creature::getId(){
    return id;
}

// Setter
void Creature::setLevel(int new_level){
  level = new_level;
}
