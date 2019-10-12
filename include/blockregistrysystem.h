#pragma once

#include <string>
#include <vector>
#include <map>
#include <systems/system.h>
#include <components/texturecomponent.h>
#include <systems/texturesystem.h>

#include "blocktype.h"
#include "block.h"

class BlockRegistrySystem : public System {
  public:
    void Init();
    void Deinit();
    bool Register(Component* component);
    bool Unregister(Component* component);
    void Update();
    std::string Name() { return "BlockRegistrySystem"; }
    std::vector<std::string> Requires() {return {};};

    BlockType GetBlockType(std::string name);
    std::string GetBlockName(BlockType id);
    Block* GetBlock(BlockType type);

    bool VerifyBlockInRegister(BlockType id);
  private:
    std::map<BlockType, Block> blockRegister;
    std::map<std::string, BlockType> nameIDMap;

    BlockType airType;

    TextureSystem* textureSystem;
};