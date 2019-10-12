#ifndef BLOCKMANAGER_H
#define BLOCKMANAGER_H
#include <components/meshcomponent.h>
#include <components/texturecomponent.h>
#include <components/shadercomponent.h>
#include <components/renderedcomponent.h>
#include "placedblock.h"
#include "block.h"
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtx/hash.hpp>
#include <unordered_map>
#include <systems/texturesystem.h>
#include <systems/rendersystem.h>
#include <systems/meshsystem.h>
#include <systems/shadersystem.h>
#include <systems/system.h>



class BlockManager: public System{
    public:
        void Init();
        void Deinit();;
        bool Register(Component* component);
        bool Unregister(Component* component);
        void Update();
        std::string Name() { return "BlockManager"; }
        std::vector<std::string> Requires() { return {"MeshSystem","ShaderSystem"};}
        
        BlockType GetBlockType(std::string name);
        std::string GetBlockName(BlockType id);
        bool Place(PlacedBlock* block);
    private:
        MeshComponent* blockMesh;
        ShaderComponent* blockShader;
        std::map<BlockType, Block> blockRegister;
        std::map<std::string, BlockType> nameIDMap;

        std::unordered_map<glm::vec3,PlacedBlock> placedBlocks;
        std::map<ComponentID, RenderedComponent*> placedBlockRenderedComponent;

        bool Verify(PlacedBlock *block);
        bool VerifyBlockInRegister(BlockType id);
        bool VerifyBlockUniquePosition(glm::vec3 position);

        BlockType airType;

        TextureSystem* textureSystem;
        RenderSystem* renderSystem;
        MeshSystem* meshSystem;
        ShaderSystem* shaderSystem;
};

#endif //BLOCKMANAGER_H
