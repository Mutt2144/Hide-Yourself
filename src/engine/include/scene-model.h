#pragma once

#include <iostream>

#include "engine.h"

class SceneModel {
public:
    std::string name;
    ENGINE engine;

    SceneModel(std::string name, ENGINE& engine) : name(name), engine(engine) {}
};
