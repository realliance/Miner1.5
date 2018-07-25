#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "blockmanager.h"
#include "placedblock.h"
#include "madd.h"
#include "eventhandler.h"

#include <string>

BlockManager::BlockManager(Madd* context):context(context){
    std::vector<float> vertices = {
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
    };

    placedBlocks = {};

    blocks = {};

    cubeMesh = new RenderedObject(this);
    cubeMesh->RenderInit(vertices,"default.vs","default.fs","stone.jpg");
}

BlockManager::~BlockManager(){
    delete cubeMesh;
}

unsigned BlockManager::Register(Block *block) {
  int id = blocks.size();
  block->id = id;
  blocks.push_back(*block);
  return id;
}

Block BlockManager::GetBlock(std::string name) {
    for (unsigned i = 0; i < blocks.size(); i++) {
        if (blocks[i].name.compare(name) == 0) {
            return blocks[i];
        }
    }
    throw "No Block Found with given name!";
}

Block BlockManager::GetBlock(unsigned id) {
    for (unsigned i = 0; i < blocks.size(); i++) {
        if (i == id) {
            return blocks[i];
        }
    }
    throw "No Block Found with given id!";
}

bool BlockManager::VerifyBlockInRegister(int id) {
    try {
        GetBlock(id);
        return true;
    } catch (const char* msg) {
        return false;
    }
}

bool BlockManager::VerifyBlockUniquePosition(PlacedBlock* block) {
    for (unsigned i = 0; i < placedBlocks.size(); i++) {
        if (glm::all(glm::equal(placedBlocks[i].position, block->position))) {
            return false;
        }
    }
    return true;
}

bool BlockManager::Verify(PlacedBlock* block) {
    return VerifyBlockInRegister(block->id) && VerifyBlockUniquePosition(block);
}

bool BlockManager::Place(PlacedBlock *block) {
    if (VerifyBlockInRegister(block->id)) {
        placedBlocks.push_back(*block);
        return true;
    } else {
        return false;
    }
}

bool BlockManager::Place(std::vector<PlacedBlock> blockVector) {
    for(auto const block : blockVector) {
        if (VerifyBlockInRegister(block.id)) {
            placedBlocks.push_back(block);
        } else {
            return false;
        }
    }
    return true;
}

// Madd Functions

bool BlockManager::Render() {
    int i = 0;
    for(auto const block : placedBlocks) {
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, block.position);
        cubeMesh->SetTransformation(model);
        if(!cubeMesh->Render())
            return false;
        i++;
    }
    return true;
}

bool BlockManager::ReloadShaders(){
    return cubeMesh->LoadShader();
}

bool BlockManager::Update(){
    //glm::mat4 trans = cubeMesh->GetTransformation();
    //cubeMesh->SetTransformation(glm::rotate(trans, glm::clamp(context->GetTime(), -1.f, 1.f)/100.f, glm::vec3(1.0, -1.0, 1.0)));
    return true;
}
