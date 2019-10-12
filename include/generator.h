#ifndef GENERATOR_H
#define GENERATOR_H
#include "block.h"
#include "blockplacesystem.h"

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
        std::vector<std::string> Requires() {return {};}
        void GenerateAfterMined(glm::vec3 positionMined);
    private:
        std::random_device rd;
        std::mt19937 eng;
        BlockPlaceSystem* Manager;
        std::map<ComponentID, BlockDistribution> registeredBlocks;
        BlockType GetRandomRegisteredBlockID();
        size_t SumOfRegistered;
};

#endif //GENERATOR_H
