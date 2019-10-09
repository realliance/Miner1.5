#pragma once

#include <components/component.h>
#include "block.h"
#include <sys/types.h>

struct BlockDistribution : public Component{
  blockType type;
  int weight;
};

