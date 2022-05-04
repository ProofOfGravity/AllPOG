#pragma once
#include "../defines.h"
#include "vulkanAssets.h"

class vulkanDeviceSelect {


public:
    vulkanDeviceSelect() = default;

    b8 vulkan_choose_physical_device(vulkan_context& context);

};



