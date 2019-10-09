#ifndef GAME_H
#define GAME_H
#include "madd.h"
#include "blockmanager.h"
#include "generator.h"
#include "gamecamera.h"

class Game{
    public:
        Game();
        ~Game();
        void Run();
    private:
        void LoadLobby();
        std::vector<PlacedBlock> Build(glm::vec3 startingCorner, glm::vec3 endingCorner, unsigned blockID);
        GameCamera* camera;
        BlockManager* Manager;
};

#endif //GAME_H
