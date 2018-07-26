#ifndef GAME_H
#define GAME_H
#include "madd.h"
#include "blockmanager.h"
#include "generator.h"

class Game{
    public:
        Game();
        ~Game();
        void Run();
    private:
        Madd* Engine;
        BlockManager* Manager;
        Generator* Gen;
        void LoadLobby();
        std::vector<PlacedBlock> Build(glm::vec3 startingCorner, glm::vec3 endingCorner, unsigned blockID);
};

#endif //GAME_H
