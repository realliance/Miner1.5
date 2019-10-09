#pragma once

#include <components/component.h>
#include <components/texturecomponent.h>
#include <sys/types.h>
#include <string>

struct Block : public Component{
    std::string name;
    TextureComponent* material;
};