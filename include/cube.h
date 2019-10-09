#ifndef CUBE_H
#define CUBE_H
#include <components/meshcomponent.h>
#include <vector>
#include <glm/glm.hpp>
class Madd;
class Cube{
    public:
        Cube(Madd* context);
        ~Cube();
        Madd* GetContext(){return context;};
        bool Render();
        bool Update();
        bool ReloadShaders();
    private:
        MeshComponent* cubeMesh;
        std::vector<glm::vec3> cubePositions;
        Madd* context;
};

#endif //CUBE_H