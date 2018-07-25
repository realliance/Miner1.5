#ifndef BLOCK_H
#define BLOCK_H
#include <string>

struct Block {
        Block(std::string n, std::string mP):name(n),materialPath(mP){}
        std::string name;
        std::string materialPath;
        int id;
};

#endif //BLOCK_H
