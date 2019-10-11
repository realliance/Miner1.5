#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "blockmanager.h"
#include "placedblock.h"
#include "madd.h"

#include <string>
#include <unordered_map>

void BlockManager::Init(){
    blockMesh = new MeshComponent{};
    blockMesh->verts = {
        {-0.5f, -0.5f, -0.5f}, { 0.5f, -0.5f, -0.5f}, { 0.5f,  0.5f, -0.5f},
        { 0.5f,  0.5f, -0.5f}, {-0.5f,  0.5f, -0.5f}, {-0.5f, -0.5f, -0.5f},
        {-0.5f, -0.5f,  0.5f}, { 0.5f, -0.5f,  0.5f}, { 0.5f,  0.5f,  0.5f},
        { 0.5f,  0.5f,  0.5f}, {-0.5f,  0.5f,  0.5f}, {-0.5f, -0.5f,  0.5f},

        {-0.5f,  0.5f,  0.5f}, {-0.5f,  0.5f, -0.5f}, {-0.5f, -0.5f, -0.5f},
        {-0.5f, -0.5f, -0.5f}, {-0.5f, -0.5f,  0.5f}, {-0.5f,  0.5f,  0.5f},
        { 0.5f,  0.5f,  0.5f}, { 0.5f,  0.5f, -0.5f}, { 0.5f, -0.5f, -0.5f},
        { 0.5f, -0.5f, -0.5f}, { 0.5f, -0.5f,  0.5f}, { 0.5f,  0.5f,  0.5f},

        {-0.5f, -0.5f, -0.5f}, { 0.5f, -0.5f, -0.5f}, { 0.5f, -0.5f,  0.5f},
        { 0.5f, -0.5f,  0.5f}, {-0.5f, -0.5f,  0.5f}, {-0.5f, -0.5f, -0.5f},
        {-0.5f,  0.5f, -0.5f}, { 0.5f,  0.5f, -0.5f}, { 0.5f,  0.5f,  0.5f},
        { 0.5f,  0.5f,  0.5f}, {-0.5f,  0.5f,  0.5f}, {-0.5f,  0.5f, -0.5f}
    };
    blockMesh->texcoords = {
    {0.0f, 0.0f}, {1.0f, 0.0f}, {1.0f, 1.0f},
    {1.0f, 1.0f}, {0.0f, 1.0f}, {0.0f, 0.0f},
    {0.0f, 0.0f}, {1.0f, 0.0f}, {1.0f, 1.0f},
    {1.0f, 1.0f}, {0.0f, 1.0f}, {0.0f, 0.0f},

    {1.0f, 0.0f}, {1.0f, 1.0f}, {0.0f, 1.0f},
    {0.0f, 1.0f}, {0.0f, 0.0f}, {1.0f, 0.0f},
    {1.0f, 0.0f}, {1.0f, 1.0f}, {0.0f, 1.0f},
    {0.0f, 1.0f}, {0.0f, 0.0f}, {1.0f, 0.0f},

    {0.0f, 1.0f}, {1.0f, 1.0f}, {1.0f, 0.0f},
    {1.0f, 0.0f}, {0.0f, 0.0f}, {0.0f, 1.0f},
    {0.0f, 1.0f}, {1.0f, 1.0f}, {1.0f, 0.0f},
    {1.0f, 0.0f}, {0.0f, 0.0f}, {0.0f, 1.0f}
    };
    blockShader = new ShaderComponent{};
    blockShader->fragmentShaderPath = "default.fs";
    blockShader->vertexShaderPath = "default.vs";

    meshSystem = dynamic_cast<MeshSystem*>(Madd::GetInstance().GetSystem("MeshSystem"));
    renderSystem = dynamic_cast<RenderSystem*>(Madd::GetInstance().GetSystem("RenderSystem"));
    textureSystem = dynamic_cast<TextureSystem*>(Madd::GetInstance().GetSystem("TextureSystem"));
    shaderSystem = dynamic_cast<ShaderSystem*>(Madd::GetInstance().GetSystem("ShaderSystem"));

    meshSystem->Register(blockMesh);
    shaderSystem->Register(blockShader);

    Block air{};
    air.name = "Air";
    air.cID = Madd::GetInstance().GetNewComponentID();
    airType = air.cID;
    blockRegister[static_cast<blockType>(air.cID)] = air;
    nameIDMap[air.name] = static_cast<blockType>(air.cID);
}

void BlockManager::Deinit(){
    for(auto & [type, block] : blockRegister){
        // textureSystem->Unregister(block.material);
        delete block.material;
    }
    blockRegister.clear();
    nameIDMap.clear();
    for(auto & [pos, placedBlock] : placedBlocks){
        if(placedBlock.type != airType){
            renderSystem->Unregister(placedBlockRenderedComponent[placedBlock.cID]);
        }
    }
    placedBlocks.clear();
    placedBlockRenderedComponent.clear();
    airType = 0;
    delete blockMesh;
    delete blockShader;
}

bool BlockManager::Register(Component *b){
    Block* block = dynamic_cast<Block*>(b);
    block->cID = Madd::GetInstance().GetNewComponentID();
    textureSystem->Register(block->material);
    blockRegister[static_cast<blockType>(block->cID)] = *block;
    nameIDMap[block->name] = static_cast<blockType>(block->cID);
    return true;
}

bool BlockManager::Unregister(Component *b){
    Block* block = dynamic_cast<Block*>(b);
    textureSystem->Unregister(block->material);
    blockRegister.erase(block->cID);
    return true;
}
#include <glm/gtx/string_cast.hpp>
bool BlockManager::Place(PlacedBlock* block){
    if (Verify(block)) {
        block->cID = Madd::GetInstance().GetNewComponentID();
        if(block->type != airType){
            RenderedComponent* r = new RenderedComponent{};
            r->mesh = blockMesh;
            r->shade = glm::vec4(1.f);
            r->texture = blockRegister[block->type].material;
            r->shader = blockShader;
            r->model = glm::mat4(1.f);
            r->model = glm::translate(r->model,block->position);
            placedBlockRenderedComponent[block->cID] = r;
            renderSystem->Register(r);
        }
        placedBlocks[block->position] = *block;
        return true;
    }
    return false;
}

blockType BlockManager::GetBlockType(std::string name) {
    if(nameIDMap.contains(name)){
        return nameIDMap[name];
    }else{
        return static_cast<blockType>(-1);
    }
}

std::string BlockManager::GetBlockName(blockType id) {
    if(blockRegister.contains(id)){
        return blockRegister[id].name;
    }else{
        return "No Such Block";
    }
}

bool BlockManager::VerifyBlockInRegister(blockType id) {
    return blockRegister.contains(id);
}

bool BlockManager::VerifyBlockUniquePosition(glm::vec3 position) {
    return !placedBlocks.contains(position);
}

bool BlockManager::Verify(PlacedBlock* block) {
    return VerifyBlockInRegister(block->type) && VerifyBlockUniquePosition(block->position);
}


void BlockManager::Update(){
}
