#include <pch.h>
#include "Application.h"

#include <iostream>



int main()
{
    auto app = std::make_unique<Application>("LearnOpenGL");

    app->Loop();

    return 0;
}