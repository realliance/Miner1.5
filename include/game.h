#ifndef GAME_H
#define GAME_H
#include "madd.h"
#include "blockregistrysystem.h"
#include "blockplacesystem.h"
#include "generator.h"
#include "gamecamera.h"

class Game{
    public:
        Game();
        ~Game();
        void Run();
    private:
        void LoadLobby();
        std::vector<PlacedBlock> Build(glm::vec3 startingCorner, glm::vec3 endingCorner, BlockType blockID);
        GameCamera* camera;
        BlockRegistrySystem* blockRegistry;
        BlockPlaceSystem* blockPlace;
        WindowComponent* window;
};

#endif //GAME_H
