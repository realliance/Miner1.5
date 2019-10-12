#pragma once

#include <components/meshcomponent.h>
#include <components/shadercomponent.h>
#include <components/renderedcomponent.h>
#include "placedblock.h"
#include "block.h"
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtx/hash.hpp>
#include <unordered_map>
#include <systems/rendersystem.h>
#include <systems/meshsystem.h>
#include <systems/shadersystem.h>
#include <systems/system.h>

class BlockPlaceSystem : public System {
public:
  void Init();
  void Deinit();
  bool Register(Component* component);
  bool Unregister(Component* component);
  void Update();
  std::string Name() { return "BlockPlaceSystem"; }
  std::vector<std::string> Requires() { return {"MeshSystem","ShaderSystem","BlockRegistrySystem"};}

  bool Place(PlacedBlock* block);
private:
  MeshComponent* blockMesh;
  ShaderComponent* blockShader;

  std::unordered_map<glm::vec3,PlacedBlock> placedBlocks;
  std::map<ComponentID, RenderedComponent*> placedBlockRenderedComponent;

  BlockType airType;

  bool Verify(PlacedBlock *block);
  bool VerifyBlockUniquePosition(glm::vec3 position);

  RenderSystem* renderSystem;
  MeshSystem* meshSystem;
  ShaderSystem* shaderSystem;
};