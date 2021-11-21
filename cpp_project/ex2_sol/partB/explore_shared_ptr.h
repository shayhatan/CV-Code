//
// Created by USER on 09/11/2021.
//

#ifndef EX2_MTM_EXPLORE_SHARED_PTR_H
#define EX2_MTM_EXPLORE_SHARED_PTR_H


#include <iostream>

class Entity {

public:
    int i;
    Entity(int _i = 0) : i(_i) {
        std::cout << "Created Entity" << std::endl;
        std::cout << i << std::endl;
    }

    ~Entity() {
        std::cout << "Destroyed Entity" << std::endl;
    }

    void printEntity(){
        std::cout<<i;
    }
};


#endif //EX2_MTM_EXPLORE_SHARED_PTR_H
