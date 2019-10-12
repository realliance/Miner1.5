#include "block.h"
#include "blockplacesystem.h"
#include "placedblock.h"

#include "generator.h"

#include <vector>
#include <random>
#include <time.h>
#include <iostream>

void Generator::Init() {
    Manager = dynamic_cast<BlockPlaceSystem*>(Madd::GetInstance().GetSystem("BlockPlaceSystem"));;
    eng = std::mt19937(rd() * time(NULL));
}

void Generator::Deinit(){
    SumOfRegistered = 0;
    registeredBlocks.clear();
}

bool Generator::Register(Component* component) {
    BlockDistribution* b = dynamic_cast<BlockDistribution*>(component);
    b->cID = Madd::GetInstance().GetNewComponentID();
    registeredBlocks[b->cID] = *b;
    SumOfRegistered += b->weight;
    return true;
}

bool Generator::Unregister(Component* component) {
    if(registeredBlocks.contains(component->cID)){
        SumOfRegistered -= registeredBlocks[component->cID].weight;
        registeredBlocks.erase(component->cID);
        return true;
    }
    return false;
}

BlockType Generator::GetRandomRegisteredBlockID() {
    std::uniform_real_distribution<float> dist(1, SumOfRegistered);
    int randomWeight = (int)std::round(dist(eng));
    for(auto & [cID, distrib] : registeredBlocks){
        randomWeight -= distrib.weight;
        if(randomWeight <= 0){
            return distrib.type;
        }
    }
    return static_cast<BlockType>(-1);
}

void Generator::GenerateAfterMined(glm::vec3 positionMined) {
    std::vector<glm::vec3> positions = {
        {1.0f, 0.0f, 0.0f}, {-1.0f, 0.0f, 0.0f}, {0.0f, 1.0f, 0.0f},
        {0.0f, -1.0f, 0.0f}, {0.0f, 0.0f, 1.0f}, {1.0f, 0.0f, -1.0f}
    };
    for(glm::vec3 & offset : positions){
        PlacedBlock b{};
        b.position = positionMined+offset;
        b.type = GetRandomRegisteredBlockID();
        Manager->Place(&b);
    }
}

void Generator::Update(){

}
