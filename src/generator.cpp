#include "block.h"
#include "blockmanager.h"
#include "placedblock.h"

#include "generator.h"

#include <vector>
#include <random>
#include <time.h>
#include <iostream>

Generator::Generator(BlockManager* man) {
    Manager = man;
    eng = std::mt19937(rd() * time(NULL));
}

void Generator::RegisterBlock(unsigned blockID, int weight) {
    registeredBlocks.push_back(std::make_pair(blockID, weight));
}

int Generator::SumOfRegistered() {
    int i = 0;
    for(auto const blockPair : registeredBlocks) {
        i += std::get<1>(blockPair);
    }
    return i;
}

unsigned Generator::GetRandomRegisteredBlockID() {
    std::uniform_real_distribution<double> dist(1, SumOfRegistered());
    int randomWeight = (int)std::round(dist(eng));
    std::pair<unsigned, int> chosenPair;
    for(auto const blockPair : registeredBlocks) {
        std::cout << randomWeight << " > ";
        randomWeight -= std::get<1>(blockPair);
        if (randomWeight <= 0) {
            chosenPair = blockPair;
            break;
        }
    }
    std::cout << randomWeight << '\n';
    return std::get<0>(chosenPair);
}

void Generator::GenerateAfterMined(glm::vec3 positionMined) {
    Manager->Place(new PlacedBlock( GetRandomRegisteredBlockID(), positionMined + glm::vec3(1.0f, 0.0f, 0.0f) ));
    Manager->Place(new PlacedBlock( GetRandomRegisteredBlockID(), positionMined + glm::vec3(-1.0f, 0.0f, 0.0f) ));

    Manager->Place(new PlacedBlock( GetRandomRegisteredBlockID(), positionMined + glm::vec3(0.0f, 1.0f, 0.0f) ));
    Manager->Place(new PlacedBlock( GetRandomRegisteredBlockID(), positionMined + glm::vec3(0.0f, -1.0f, 0.0f) ));

    Manager->Place(new PlacedBlock( GetRandomRegisteredBlockID(), positionMined + glm::vec3(0.0f, 0.0f, 1.0f) ));
    Manager->Place(new PlacedBlock( GetRandomRegisteredBlockID(), positionMined + glm::vec3(0.0f, 0.0f, -1.0f) ));
}
