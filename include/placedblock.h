#ifndef PLACEDBLOCK_H
#define PLACEDBLOCK_H

#include <glm/glm.hpp>

struct PlacedBlock {
        PlacedBlock(unsigned id, glm::vec3 position):id(id),position(position){}
        unsigned id;
        glm::vec3 position;
};

#endif //PLACEDBLOCK_H
