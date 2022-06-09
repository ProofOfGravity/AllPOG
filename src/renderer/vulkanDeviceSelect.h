#pragma once
#include "../defines.h"


struct vulkan_context;
struct vulkan_queues;

class vulkanDeviceSelect {

public:

    vulkanDeviceSelect() = default;

    b8 vulkan_choose_physical_device(vulkan_context& context, vulkan_queues& queues);

};



