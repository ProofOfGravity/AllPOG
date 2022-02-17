#pragma once

#include "../defines.h"
#include "vulkanAssets.h"
#include "../platform/platform.h"
#include <string>

class vulkanRenderer {

public:

    vulkanRenderer() = default;

    b8 vulkan_initialize(std::string appName, platform& platform);
    void vulkan_cleanup();



private:
    b8 vulkan_create_instance(std::string appName, platform& platform);
    b8 vulkan_choose_physical_device(platform& platform);


private:
    vulkan_context context{};
};



