#ifndef BLOCKMANAGER_H
#define BLOCKMANAGER_H
#include "gameobject.h"
#include "renderedobject.h"
#include "placedblock.h"
#include "block.h"
#include <vector>
#include <glm/glm.hpp>
#include <unordered_map>

class Madd;
class BlockManager : public GameObject{
    public:
        BlockManager(Madd* context);
        ~BlockManager();
        Madd* GetContext(){return context;};
        unsigned Register(Block *block);
        bool Render();
        bool Update();
        bool ReloadShaders();
        Block GetBlock(std::string name);
        Block GetBlock(unsigned id);
        bool Place(PlacedBlock *block);
        bool Place(std::vector<PlacedBlock> blockVector);
    private:
        RenderedObject* cubeMesh;
        std::vector<PlacedBlock> placedBlocks;
        std::vector<Block> blocks;
        std::vector<float> vertices;
        Madd* context;
        bool Verify(PlacedBlock *block);
        bool VerifyBlockInRegister(int id);
        bool VerifyBlockUniquePosition(PlacedBlock *block);
        std::unordered_map<unsigned, int> textureMap;

};

#endif //BLOCKMANAGER_H
