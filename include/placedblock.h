#pragma once

#include "components/component.h"
#include <sys/types.h>
#include <glm/glm.hpp>
typedef size_t blockType;
struct PlacedBlock: public Component {
    glm::vec3 position;
    blockType type;
};
