#pragma once

#include "components/component.h"
#include <glm/glm.hpp>

#include "blocktype.h"

struct PlacedBlock: public Component {
    glm::vec3 position;
    BlockType type;
};
