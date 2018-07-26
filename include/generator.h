#ifndef GENERATOR_H
#define GENERATOR_H
#include "block.h"
#include "blockmanager.h"

#include <random>
#include <vector>

class Generator {
    public:
        Generator(BlockManager* ma);
        void RegisterBlock(unsigned blockID, int weight);
        void GenerateAfterMined(glm::vec3 positionMined);
    private:
        std::random_device rd;
        std::mt19937 eng;
        Madd* Engine;
        BlockManager* Manager;
        std::vector<std::pair<unsigned, int>> registeredBlocks;
        unsigned GetRandomRegisteredBlockID();
        int SumOfRegistered();
};

#endif //GENERATOR_H
