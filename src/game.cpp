#include "game.h"
#include "gamecamera.h"

#include "block.h"
#include "blockregistrysystem.h"
#include "blockplacesystem.h"

#include "generator.h"

#include <string>
#include <cmath>
#include "math.h"

#include "systems.h"

Game::Game(){
    Madd::GetInstance().Init();
  
    Madd::GetInstance().Register({
        new GlfwSystem,&RenderSystem::GetInstance(),new TextureSystem,
        new ShaderSystem, new MeshSystem, &MouseEventSystem::GetInstance(),
        &KeyboardEventSystem::GetInstance(), new CameraSystem, 
        new FreeCamSystem, new BlockRegistrySystem, new BlockPlaceSystem, new Generator
    });

    Madd::GetInstance().InitSystems();


    camera = new GameCamera{};
    window = new WindowComponent{};
    window->height = 698;
    window->width = 1240;
    window->title = "Miner1.5";
    window->cameras.push_back(&camera->camera.camera);
    Madd::GetInstance().GetSystem("GlfwSystem")->Register(window);

    //Init Blocks
    blockRegistry = dynamic_cast<BlockRegistrySystem*>(Madd::GetInstance().GetSystem("BlockRegistrySystem"));
    blockPlace = dynamic_cast<BlockPlaceSystem*>(Madd::GetInstance().GetSystem("BlockPlaceSystem"));
    Generator* Gen = dynamic_cast<Generator*>(Madd::GetInstance().GetSystem("Generator"));

    // {Name, filepath in assets, weight of spawning}
    std::vector<std::tuple<std::string, std::string, int>> blocks = {
        {"Stone",           "stone.jpg",           20},
        {"Iron",            "ironore.jpg",          8},
        {"Copper",          "copperore.jpg",        8},
        {"Tin",             "tinore.jpg",           8},
        {"Gold",            "goldore.jpg",          5},
        {"Amethyst",        "amethystore.jpg",      5},
        {"Quartz",          "quartzore.jpg",        5},
        {"Meteoric Iron",   "meteorironore.jpg",    4},
        {"Uranium",         "uraniumore.jpg",       3}
    };
    {
        Block b{};
        b.name = "Lobby Stone";
        b.material = new TextureComponent{};
        b.material->filename = "lobbystone.jpg";
        blockRegistry->Register(&b);
    }
    for(auto const & [name, texture, weight] : blocks){
        Block b{};
        b.name = name;
        b.material = new TextureComponent{};
        b.material->filename = texture;
        blockRegistry->Register(&b);
        BlockDistribution d{};
        d.type = blockRegistry->GetBlockType(b.name);
        d.weight = weight;
        Gen->Register(&d);
    }

    LoadLobby();
}

Game::~Game(){
    Madd::GetInstance().Deinit();
    delete camera;
}

void Game::Run(){
    Madd::GetInstance().Run();
}

std::vector<PlacedBlock> Game::Build(glm::vec3 startingCorner, glm::vec3 endingCorner, BlockType blockID) {

    int xDirection = copysign(1.0f, endingCorner.x - startingCorner.x);
    int yDirection = copysign(1.0f, endingCorner.y - startingCorner.y);
    int zDirection = copysign(1.0f, endingCorner.z - startingCorner.z);

    std::vector<PlacedBlock> roof = {};
    for (int x = startingCorner.x; x <= endingCorner.x; x += xDirection) {
        for (int z = startingCorner.z; z <= endingCorner.z; z += zDirection) {
            for (int y = startingCorner.y; y <= endingCorner.y; y += yDirection) {
                PlacedBlock p{};
                p.position = glm::vec3((float)x, (float)y, (float)z);
                p.type = blockID;
                roof.push_back(p);
            }
        }
    }
    return roof;
}

void Game::LoadLobby() {
    BlockType airID = blockRegistry->GetBlockType("Air");
    BlockType stoneID = blockRegistry->GetBlockType("Stone");
    BlockType lobbyStoneID = blockRegistry->GetBlockType("Lobby Stone");

    // Roof
    for(auto & block : Build(glm::vec3(-5.0f, 2.0f, -5.0f), glm::vec3(5.0f, 2.0f, 5.0f), stoneID)){
        blockPlace->Place(&block);
    }

    // Floor with Lobby Center
    for(auto & block : Build(glm::vec3(-5.0f, 0.0f, -5.0f), glm::vec3(-2.0f, 0.0f, 5.0f), stoneID)){
        blockPlace->Place(&block);
    }

    for(auto & block : Build(glm::vec3(-1.0f, 0.0f, -5.0f), glm::vec3(1.0f, 0.0f, -2.0f), stoneID)){
        blockPlace->Place(&block);
    }
    for(auto & block : Build(glm::vec3(-1.0f, 0.0f, -1.0f), glm::vec3(1.0f, 0.0f, 1.0f), lobbyStoneID)){
        blockPlace->Place(&block);
    }
    for(auto & block : Build(glm::vec3(-1.0f, 0.0f, 2.0f), glm::vec3(1.0f, 0.0f, 5.0f), stoneID)){
        blockPlace->Place(&block);
    }


    for(auto & block : Build(glm::vec3(2.0f, 0.0f, -5.0f), glm::vec3(5.0f, 0.0f, 5.0f), stoneID)){
        blockPlace->Place(&block);
    }

    // Front Wall
    for(auto & block : Build(glm::vec3(-5.0f, 1.0f, -6.0f), glm::vec3(5.0f, 1.0f, -6.0f), stoneID)){
        blockPlace->Place(&block);
    }

    // Back Wall
    for(auto & block : Build(glm::vec3(-5.0f, 1.0f, 6.0f), glm::vec3(5.0f, 1.0f, 6.0f), stoneID)){
        blockPlace->Place(&block);
    }

    // Left Wall
    for(auto & block : Build(glm::vec3(-6.0f, 1.0f, -5.0f), glm::vec3(-6.0f, 1.0f, 5.0f), stoneID)){
        blockPlace->Place(&block);
    }

    // Right Wall
    for(auto & block : Build(glm::vec3(6.0f, 1.0f, -5.0f), glm::vec3(6.0f, 1.0f, 5.0f), stoneID)){
        blockPlace->Place(&block);
    }

    // Fill Room With Air
    for(auto & block : Build(glm::vec3(-5.0f, 1.0f, -5.0f), glm::vec3(5.0f, 1.0f, 5.0f), airID)){
        blockPlace->Place(&block);
    }
}
