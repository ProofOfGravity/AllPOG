#pragma once
#include "../defines.h"
#include "vulkan/vulkan.h"
#include "vulkanAssets.h"
#include "../platform/platform.h"
#include <string>

class vulkanRenderer {

public:

    vulkanRenderer() = default;

    b8 vulkan_initialize(std::string appName);
    void vulkan_cleanup();



private:
    b8 vulkan_create_instance(std::string appName);
    b8 vulkan_choose_physical_device();

};



