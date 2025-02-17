#ifndef PLAYER_H
#define PLAYER_H
#include <Entity.hpp>
#include <vector>



// Stats, inventory, actions
// Not a singleton to account for multiple players (network)
class Player : public Entity {
    public:
        Player();
        Player(const Player&);
        ~Player();
        void GenerateEntity();
        std::string ToString();
        
    private:
        std::vector<Entity*> inventory;
        short stats[4];

};
#endif