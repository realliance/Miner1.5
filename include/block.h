#ifndef BLOCK_H
#define BLOCK_H
#include <string>

struct Block {
        Block(std::string n, std::string mP, bool ren):name(n),materialPath(mP),rendered(ren){}
        std::string name;
        std::string materialPath;
        bool rendered;
        int id;
};

#endif //BLOCK_H
