//
// Created by matsl on 2/4/2022.
//

#include "engine.h"

engine::engine(const char *application_name, i32 x, i32 y, i32 width, i32 height) {
    //initialize the platform
    plat.platform_init(application_name, x, y, width, height);

    //initialize the renderer
    renderer.vulkan_initialize("balls");
}

void engine::run() {
    while(platform::platform_pump_messages());
}

void engine::cleanUp() {


    renderer.vulkan_cleanup();
}
