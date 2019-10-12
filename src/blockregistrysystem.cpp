#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "blockregistrysystem.h"
#include "blocktype.h"
#include "madd.h"
#include <iostream>
#include <string>

void BlockRegistrySystem::Init(){
  textureSystem = dynamic_cast<TextureSystem*>(Madd::GetInstance().GetSystem("TextureSystem"));

  Block air{};
  air.name = "Air";
  air.cID = Madd::GetInstance().GetNewComponentID();
  airType = air.cID;
  blockRegister[static_cast<BlockType>(air.cID)] = air;
  nameIDMap[air.name] = static_cast<BlockType>(air.cID);
  std::cout << static_cast<BlockType>(air.cID) << std::endl;
}

void BlockRegistrySystem::Deinit(){
  for(auto & [type, block] : blockRegister){
    // textureSystem->Unregister(block.material);
    delete block.material;
  }
  blockRegister.clear();
  nameIDMap.clear();
  airType = 0;
}

bool BlockRegistrySystem::Register(Component *b){
  Block* block = dynamic_cast<Block*>(b);
  block->cID = Madd::GetInstance().GetNewComponentID();
  textureSystem->Register(block->material);
  blockRegister[static_cast<BlockType>(block->cID)] = *block;
  nameIDMap[block->name] = static_cast<BlockType>(block->cID);
  return true;
}

bool BlockRegistrySystem::Unregister(Component *b){
  Block* block = dynamic_cast<Block*>(b);
  textureSystem->Unregister(block->material);
  blockRegister.erase(block->cID);
  return true;
}

BlockType BlockRegistrySystem::GetBlockType(std::string name) {
    if(nameIDMap.contains(name)){
        return nameIDMap[name];
    }else{
        return static_cast<BlockType>(-1);
    }
}

std::string BlockRegistrySystem::GetBlockName(BlockType id) {
    if(blockRegister.contains(id)){
        return blockRegister[id].name;
    }else{
        return "No Such Block";
    }
}

Block* BlockRegistrySystem::GetBlock(BlockType type) {
  if (!VerifyBlockInRegister(type))
    return nullptr;
  return &blockRegister[type];
}

bool BlockRegistrySystem::VerifyBlockInRegister(BlockType id) {
    return blockRegister.contains(id);
}


void BlockRegistrySystem::Update(){
}
