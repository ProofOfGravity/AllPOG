#include "vulkanDeviceSelect.h"
#include "../core/logger.h"


typedef struct vulkan_physical_device_requirements {
    b8 graphics;
    b8 present;
    b8 compute;
    b8 transfer;
    // darray
    const char** device_extension_names;
    b8 sampler_anisotropy;
    b8 discrete_gpu;
} vulkan_physical_device_requirements;

typedef struct vulkan_physical_device_queue_family_info {
    u32 graphics_family_index;
    u32 present_family_index;
    u32 compute_family_index;
    u32 transfer_family_index;
} vulkan_physical_device_queue_family_info;


b8 vulkanDeviceSelect::vulkan_choose_physical_device(vulkan_context& context) {

    //the desired requirements
    //TODO: make this configurable
    vulkan_physical_device_requirements device_requirements{};
    device_requirements.compute = true;
    device_requirements.discrete_gpu = true;
    device_requirements.graphics = true;
    device_requirements.present = true;
    device_requirements.sampler_anisotropy = true;
    device_requirements.transfer = true;

    //first, enumerate over devices to obtain list
    POG_DEBUG("Enumerating Physical Devices.");
    u32 count{};
    vkEnumeratePhysicalDevices(context.instance, &count, nullptr);
    if(count == 0){
        POG_FATAL("Could not find ANY physical device_select.");
        return false;
    }
    std::vector<VkPhysicalDevice> physicalDevices(count);
    vkEnumeratePhysicalDevices(context.instance, &count, physicalDevices.data());

    for (auto& device : physicalDevices){
        VkPhysicalDeviceProperties properties{};
        vkGetPhysicalDeviceProperties(device, &properties);
        VkPhysicalDeviceFeatures features{};
        vkGetPhysicalDeviceFeatures(device, &features);
        VkPhysicalDeviceMemoryProperties memory{};
        vkGetPhysicalDeviceMemoryProperties(device, &memory);

        context.physical_device = device;

    }

    return true;

}
