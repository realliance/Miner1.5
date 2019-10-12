#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "blockplacesystem.h"
#include "placedblock.h"
#include "madd.h"

#include <string>
#include <unordered_map>

#include "blockregistrysystem.h"

void BlockPlaceSystem::Init(){
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
    shaderSystem = dynamic_cast<ShaderSystem*>(Madd::GetInstance().GetSystem("ShaderSystem"));

    meshSystem->Register(blockMesh);
    shaderSystem->Register(blockShader);

    airType = dynamic_cast<BlockRegistrySystem*>(Madd::GetInstance().GetSystem("BlockRegistrySystem"))->GetBlockType("Air");
    std::cout << airType << std::endl;
}

void BlockPlaceSystem::Deinit(){
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

bool BlockPlaceSystem::Register(Component *b){ return true; }
bool BlockPlaceSystem::Unregister(Component *b){ return true; }

bool BlockPlaceSystem::Place(PlacedBlock* block){
    if (Verify(block)) {
        block->cID = Madd::GetInstance().GetNewComponentID();
        if(block->type != airType){
            RenderedComponent* r = new RenderedComponent{};
            r->mesh = blockMesh;
            r->shade = glm::vec4(1.f);
            r->texture = dynamic_cast<BlockRegistrySystem*>(Madd::GetInstance().GetSystem("BlockRegistrySystem"))->GetBlock(block->type)->material;
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

bool BlockPlaceSystem::VerifyBlockUniquePosition(glm::vec3 position) {
    return !placedBlocks.contains(position);
}

bool BlockPlaceSystem::Verify(PlacedBlock* block) {
    return dynamic_cast<BlockRegistrySystem*>(Madd::GetInstance().GetSystem("BlockRegistrySystem"))->VerifyBlockInRegister(block->type) && VerifyBlockUniquePosition(block->position);
}


void BlockPlaceSystem::Update(){
}
