#include "game.h"
#include "gameobject.h"
#include "gamecamera.h"

#include "blockmanager.h"
#include "block.h"

#include <string>

Game::Game(){
    const char *title = "test";
    Engine = new Madd(800, 600, title);
    GameObject* gameCamera = new GameCamera(Engine);
    Engine->AddObject(gameCamera);

    //Init Blocks
    BlockManager* Manager = new BlockManager(Engine);
    Manager->Register(new Block("Air", ""));
    Manager->Register(new Block("Stone", "stone.jpg"));
    Manager->Register(new Block("Lobby Stone", "lobby.jpg"));

    Manager->Place(new PlacedBlock(Manager->GetBlock("Lobby Stone").id, glm::vec3( 1.0f,  0.0f,  0.0f)));

    Engine->AddObject(Manager);
}

Game::~Game(){
    delete Engine;
}

void Game::Run(){
    while(Engine->StayOpen()){
        Engine->Tick();
    }
}
