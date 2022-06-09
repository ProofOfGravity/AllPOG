#pragma once

#include "../defines.h"
#include "vulkanAssets.h"
#include "../platform/platform.h"
#include "vulkanDeviceSelect.h"
#include <string>


class vulkanRenderer {

public:

    vulkanRenderer() = default;

    b8 vulkan_initialize(const std::string& appName, platform& platform);
    void vulkan_cleanup();


private:
    b8 vulkan_create_instance(const std::string& appName, platform& platform);
    b8 vulkan_get_surface(platform& platform);
    b8 vulkan_select_physical_device();


private:
    /*Cached variables*/
    vulkan_context context{};
    vulkan_queues queues{};


private:
    /*Helper classes*/
    vulkanDeviceSelect device_select{};
};



