#include "game.h"
#include "gameobject.h"
#include "gamecamera.h"

#include "blockmanager.h"
#include "block.h"

#include <string>
#include <cmath>
#include "math.h"

Game::Game(){
    const char *title = "Miner1.5";
    Engine = new Madd(1240, 698, title);
    GameObject* gameCamera = new GameCamera(Engine);
    Engine->AddObject(gameCamera);

    //Init Blocks
    BlockManager* Manager = new BlockManager(Engine);
    Manager->Register(new Block("Air", ""));
    Manager->Register(new Block("Stone", "stone.jpg"));
    Manager->Register(new Block("Lobby Stone", "lobby.jpg"));

    Engine->AddObject(Manager);

    LoadLobby(Manager);
}

Game::~Game(){
    delete Engine;
}

void Game::Run(){
    while(Engine->StayOpen()){
        Engine->Tick();
    }
}

std::vector<PlacedBlock> Game::Build(glm::vec3 startingCorner, glm::vec3 endingCorner, unsigned blockID) {

    int xDirection = copysign(1.0f, endingCorner.x - startingCorner.x);
    int yDirection = copysign(1.0f, endingCorner.y - startingCorner.y);
    int zDirection = copysign(1.0f, endingCorner.z - startingCorner.z);

    std::vector<PlacedBlock> roof = {};
    for (int x = startingCorner.x; x <= endingCorner.x; x += xDirection) {
        for (int z = startingCorner.z; z <= endingCorner.z; z += zDirection) {
            for (int y = startingCorner.y; y <= endingCorner.y; y += yDirection) {
                roof.push_back({blockID, glm::vec3((float)x, (float)y, (float)z)});
            }
        }
    }
    return roof;
}

void Game::LoadLobby(BlockManager* Manager) {
    unsigned airID = Manager->GetBlock("Air").id;
    unsigned stoneID = Manager->GetBlock("Stone").id;
    unsigned lobbyStoneID = Manager->GetBlock("Lobby Stone").id;

    // Roof
    Manager->Place(Build(glm::vec3(-5.0f, 2.0f, -5.0f), glm::vec3(5.0f, 2.0f, 5.0f), stoneID));

    // Floor with Lobby Center
    Manager->Place(Build(glm::vec3(-5.0f, 0.0f, -5.0f), glm::vec3(-2.0f, 0.0f, 5.0f), stoneID));

    Manager->Place(Build(glm::vec3(-1.0f, 0.0f, -5.0f), glm::vec3(1.0f, 0.0f, -2.0f), stoneID));
    Manager->Place(Build(glm::vec3(-1.0f, 0.0f, -1.0f), glm::vec3(1.0f, 0.0f, 1.0f), lobbyStoneID));
    Manager->Place(Build(glm::vec3(-1.0f, 0.0f, 2.0f), glm::vec3(1.0f, 0.0f, 5.0f), stoneID));


    Manager->Place(Build(glm::vec3(2.0f, 0.0f, -5.0f), glm::vec3(5.0f, 0.0f, 5.0f), stoneID));

    // Front Wall
    Manager->Place(Build(glm::vec3(-5.0f, 1.0f, -6.0f), glm::vec3(5.0f, 1.0f, -6.0f), stoneID));

    // Back Wall
    Manager->Place(Build(glm::vec3(-5.0f, 1.0f, 6.0f), glm::vec3(5.0f, 1.0f, 6.0f), stoneID));

    // Left Wall
    Manager->Place(Build(glm::vec3(-6.0f, 1.0f, -5.0f), glm::vec3(-6.0f, 1.0f, 5.0f), stoneID));

    // Right Wall
    Manager->Place(Build(glm::vec3(6.0f, 1.0f, -5.0f), glm::vec3(6.0f, 1.0f, 5.0f), stoneID));

    // Fill Room With Air
    Manager->Place(Build(glm::vec3(-5.0f, 1.0f, -5.0f), glm::vec3(5.0f, 1.0f, 5.0f), airID));
}
