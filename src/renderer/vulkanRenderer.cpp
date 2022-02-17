#include "vulkanRenderer.h"
#define VK_USE_PLATFORM_WIN32_KHR
#include <vulkan/vulkan.h>
#include "../core/logger.h"



//forward declare debug callback, which is implemented at end
VKAPI_ATTR VkBool32 VKAPI_CALL vk_debug_callback(
        VkDebugUtilsMessageSeverityFlagBitsEXT message_severity,
VkDebugUtilsMessageTypeFlagsEXT message_types,
const VkDebugUtilsMessengerCallbackDataEXT* callback_data,
void* user_data);


b8 vulkanRenderer::vulkan_initialize(std::string appName, platform& platform) {

    POG_CHECK(vulkan_create_instance(appName, platform), "Failed to create instance");
    POG_CHECK(vulkan_choose_physical_device(platform), "failed to choose physical device");

    return true;
}

b8 vulkanRenderer::vulkan_create_instance(std::string appName, platform& platform) {
    VkApplicationInfo appInfo{};
    appInfo.sType = {VK_STRUCTURE_TYPE_APPLICATION_INFO};
    appInfo.apiVersion = VK_API_VERSION_1_2;
    appInfo.pApplicationName = appName.c_str();
    appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
    appInfo.pEngineName = "POG Engine";
    appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);


    //create needed extensions
    std::vector<const char*> extensions{};
    //generic surface extension
    extensions.push_back(VK_KHR_SURFACE_EXTENSION_NAME);
    //get platform specific extensions
    platform.get_platform_extensions(extensions);

    //for debug builds, add debug extension
    //this is currently added manually to cmake file
#if defined(_DEBUG)
    extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
#endif

    //print out needed extensions for debugging purposes
    for (auto& e : extensions) {
        POG_DEBUG(e);
    }

    VkInstanceCreateInfo createInfo{};
    createInfo.sType = {VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO};
    createInfo.pApplicationInfo = &appInfo;
    createInfo.enabledExtensionCount = (uint32_t)extensions.size();
    createInfo.ppEnabledExtensionNames = extensions.data();

    std::vector<const char*> required_validation_layers{};

    //if in debug build, add validation layers and ensure they exist
#if defined(_DEBUG)
    required_validation_layers.push_back({"VK_LAYER_KHRONOS_validation"});

    u32 available_layer_count{0};
    vkEnumerateInstanceLayerProperties(&available_layer_count, nullptr);
    std::vector<VkLayerProperties> available_layers(available_layer_count);
    vkEnumerateInstanceLayerProperties(&available_layer_count, available_layers.data());

    for(auto i = 0; i < required_validation_layers.size(); i++){
        POG_INFO("Searching for layer: %s", required_validation_layers[i]);
        b8 found{false};
        for(auto j = 0; j < available_layer_count; j++){
            if(strcmp(required_validation_layers[i], available_layers[j].layerName) == 0){
                found = true;
                POG_INFO("Layer found");
                break;
            }
        }

        if(!found){
            POG_FATAL("Could not find required layer: %s", required_validation_layers[i]);
            return false;
        }
    }
    POG_INFO("All required validation layers found");
#endif

    createInfo.enabledLayerCount = required_validation_layers.size();
    createInfo.ppEnabledLayerNames = required_validation_layers.data();

    //if in debug build, build the create info for the debugger
    //this will be used in the createInstance function as pNext
#if defined(_DEBUG)
    POG_DEBUG("Creating Vulkan debugger...");
    u32 log_severity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT |
                       VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT |
                       VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT;//  |
       // VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT;

    VkDebugUtilsMessengerCreateInfoEXT debug_create_info = {VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT};
    debug_create_info.messageSeverity = log_severity;
    debug_create_info.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT
                                    | VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT;
    debug_create_info.pfnUserCallback = vk_debug_callback;
    createInfo.pNext = (VkDebugUtilsMessengerCreateInfoEXT*) &debug_create_info;
#endif

    //finally, create the instance
    POG_DEBUG("Creating Instance");
    VK_CHECK(vkCreateInstance(&createInfo, context.custom_allocator, &context.instance));
    POG_DEBUG("Instance created successfully");

    // if in debug, need to get instance specific debug create function
#if defined(_DEBUG)
    auto func = (PFN_vkCreateDebugUtilsMessengerEXT)vkGetInstanceProcAddr(context.instance,
                                                                          "vkCreateDebugUtilsMessengerEXT");
    func(context.instance, &debug_create_info, nullptr, &context.debug_messenger);
    POG_DEBUG("Vulkan debugger created.");
#endif

    //if have made it to end of method without error already found
    //then instance has been created successfully and return true
    return true;
}

void vulkanRenderer::vulkan_cleanup() {

    //if debug enabled, then cleanup debugger
#if defined(_DEBUG)
    auto func = (PFN_vkDestroyDebugUtilsMessengerEXT) vkGetInstanceProcAddr(context.instance, "vkDestroyDebugUtilsMessengerEXT");
    if (func != nullptr) {
        func(context.instance, context.debug_messenger, context.custom_allocator);
    }
#endif

    vkDestroySurfaceKHR(context.instance, context.surface, context.custom_allocator);
    vkDestroyInstance(context.instance, context.custom_allocator);

}

b8 vulkanRenderer::vulkan_choose_physical_device(platform& platform) {

    //first, enumerate over devices to obtain list
    POG_DEBUG("Enumerating Physical Devices.");
    u32 count{};
    vkEnumeratePhysicalDevices(context.instance, &count, nullptr);
    if(count == 0){
        POG_FATAL("Could not find ANY physical device.");
        return false;
    }
    std::vector<VkPhysicalDevice> physicalDevices(count);
    vkEnumeratePhysicalDevices(context.instance, &count, physicalDevices.data());

    for (auto& device : physicalDevices){
        VkPhysicalDeviceProperties properties{};
        vkGetPhysicalDeviceProperties(device, &properties);
        VkPhysicalDeviceFeatures features{};
        vkGetPhysicalDeviceFeatures(device, &features);


    }

    POG_DEBUG("Creating surface");
    //creates this surface in vulkanAssets static struct "context.surface"

    platform.get_platform_surface(context);



    return true;

}


//the debug callback function, utilizing POG_LOG
VKAPI_ATTR VkBool32 VKAPI_CALL vk_debug_callback(
        VkDebugUtilsMessageSeverityFlagBitsEXT message_severity,
VkDebugUtilsMessageTypeFlagsEXT message_types,
const VkDebugUtilsMessengerCallbackDataEXT* callback_data,
void* user_data) {
switch (message_severity) {
default:
case VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT:
    POG_ERROR(callback_data->pMessage);
    break;
case VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT:
    POG_WARN(callback_data->pMessage);
    break;
case VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT:
    POG_INFO(callback_data->pMessage);
    break;
case VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT:
    POG_TRACE(callback_data->pMessage);
    break;
}
return VK_FALSE;
}
