#ifndef GENERATOR_H
#define GENERATOR_H
#include "block.h"
#include "blockmanager.h"

#include <random>
#include <vector>
#include <systems/system.h>
#include "blockdistribution.h"
#include "madd.h"

class Generator: public System {
    public:
        void Init();
        void Deinit();
        bool Register(Component* component);
        bool Unregister(Component* component);
        void Update();
        std::string Name() { return "Generator"; }
        void GenerateAfterMined(glm::vec3 positionMined);
    private:
        std::random_device rd;
        std::mt19937 eng;
        BlockManager* Manager;
        std::map<ComponentID, BlockDistribution> registeredBlocks;
        blockType GetRandomRegisteredBlockID();
        size_t SumOfRegistered;
};

#endif //GENERATOR_H
