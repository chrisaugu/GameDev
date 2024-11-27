#include <iostream>
#include <stdio.h>

#include "Player.h"

Player::Player()
{
    //ctor
    std::cout << "Player born" << std::endl;
}

Player::~Player()
{
    //dtor
    std::cout << "Player died" << std::endl;
}
