#pragma once
#include "defines.h"
#include "platform/platform.h"
#include "renderer/vulkanRenderer.h"

class POG_API engine {
public:

    engine(const char* application_name,
           i32 x,
           i32 y,
           i32 width,
           i32 height);

    void run();
    void cleanUp();





private:
    platform plat{};
    vulkanRenderer renderer{};




};


