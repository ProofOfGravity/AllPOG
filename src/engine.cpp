
#include "engine.h"

engine::engine(const char *application_name, i32 x, i32 y, i32 width, i32 height) {
    //initialize the platform
    //must be initialized prior to logger so we have a logger prompt
    plat.platform_init(application_name, x, y, width, height);

    //initialize logging
    initialize_logging(&plat);

    //initialize the renderer
    renderer.vulkan_initialize(application_name, plat);
}

void engine::run() {
    while(plat.platform_pump_messages());
}

void engine::cleanUp() {


    renderer.vulkan_cleanup();
}
