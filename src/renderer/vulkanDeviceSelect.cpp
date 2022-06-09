#include "vulkanDeviceSelect.h"
#include "../core/logger.h"
#include "vulkanAssets.h"
#include <map>


typedef struct vulkan_physical_device_requirements {
    b8 graphics;
    b8 present;
    b8 compute;
    b8 transfer;
    const char** device_extension_names;
    b8 sampler_anisotropy;
    b8 discrete_gpu;
} vulkan_physical_device_requirements;

b8 vulkanDeviceSelect::vulkan_choose_physical_device(
        vulkan_context& context, vulkan_queues& queues) {

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

    std::map<u32, VkPhysicalDevice> device_scores{};

    for (const auto& device : physicalDevices){
        VkPhysicalDeviceProperties properties{};
        vkGetPhysicalDeviceProperties(device, &properties);
        VkPhysicalDeviceFeatures features{};
        vkGetPhysicalDeviceFeatures(device, &features);
        VkPhysicalDeviceMemoryProperties memory{};
        vkGetPhysicalDeviceMemoryProperties(device, &memory);

        u32 temp_score{};

        if(!features.geometryShader){
            POG_FATAL("Must have geometry shader");
            return false;
        }

        bool has_discrete_physical_device = false;
        if(properties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU){
            temp_score += 100;
            has_discrete_physical_device = true;
        }

        if(!has_discrete_physical_device && device_requirements.discrete_gpu){
            POG_FATAL("No physical device found and one was required");
        }

        if(device_requirements.sampler_anisotropy && features.samplerAnisotropy){
            temp_score += 10;
        }

        POG_INFO("driver name is: %s", properties.deviceName);



    }

    return true;

}
