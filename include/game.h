#ifndef GAME_H
#define GAME_H
#include "madd.h"
#include "blockmanager.h"

class Game{
    public:
        Game();
        ~Game();
        void Run();
    private:
        Madd* Engine;
        void LoadLobby(BlockManager* Manager);
        std::vector<PlacedBlock> Build(glm::vec3 startingCorner, glm::vec3 endingCorner, unsigned blockID);
};

#endif //GAME_H
