#pragma once
#include "../defines.h"
#include "vulkan/vulkan.h"


typedef struct vulkan_context{

    VkInstance instance{};
    VkPhysicalDevice physicalDevice{};

    VkSurfaceKHR surface{};


    //TODO: Create custom allocator
    //currently, this is set to nullptr, given there is no allocator right now,
    // so it can be filled in later
    VkAllocationCallbacks* custom_allocator{nullptr};


#if defined(_DEBUG)
    /** @brief The debug messenger, if active.. */
    VkDebugUtilsMessengerEXT debug_messenger{};
#endif

} vulkan_context;








/* --------------------------------------------------*/
//This section is for building a macro to print debug//
//information about VkResult and tell you what it is //
/*---------------------------------------------------*/
static const char* vulkanCheckResult(VkResult result)
{
    switch((int) result)
    {
#define RESULT_CASE(x) case x: return #x
        RESULT_CASE(VK_SUCCESS);
        RESULT_CASE(VK_NOT_READY);
        RESULT_CASE(VK_TIMEOUT);
        RESULT_CASE(VK_EVENT_SET);
        RESULT_CASE(VK_EVENT_RESET);
        RESULT_CASE(VK_INCOMPLETE);
        RESULT_CASE(VK_ERROR_OUT_OF_HOST_MEMORY);
        RESULT_CASE(VK_ERROR_OUT_OF_DEVICE_MEMORY);
        RESULT_CASE(VK_ERROR_INITIALIZATION_FAILED);
        RESULT_CASE(VK_ERROR_DEVICE_LOST);
        RESULT_CASE(VK_ERROR_MEMORY_MAP_FAILED);
        RESULT_CASE(VK_ERROR_LAYER_NOT_PRESENT);
        RESULT_CASE(VK_ERROR_EXTENSION_NOT_PRESENT);
        RESULT_CASE(VK_ERROR_FEATURE_NOT_PRESENT);
        RESULT_CASE(VK_ERROR_INCOMPATIBLE_DRIVER);
        RESULT_CASE(VK_ERROR_TOO_MANY_OBJECTS);
        RESULT_CASE(VK_ERROR_FORMAT_NOT_SUPPORTED);
        RESULT_CASE(VK_ERROR_FRAGMENTED_POOL);
        RESULT_CASE(VK_ERROR_SURFACE_LOST_KHR);
        RESULT_CASE(VK_ERROR_NATIVE_WINDOW_IN_USE_KHR);
        RESULT_CASE(VK_SUBOPTIMAL_KHR);
        RESULT_CASE(VK_ERROR_OUT_OF_DATE_KHR);
        RESULT_CASE(VK_ERROR_INCOMPATIBLE_DISPLAY_KHR);
        RESULT_CASE(VK_ERROR_VALIDATION_FAILED_EXT);
        RESULT_CASE(VK_ERROR_OUT_OF_POOL_MEMORY_KHR);
        RESULT_CASE(VK_ERROR_INVALID_SHADER_NV);
#undef RESULT_CASE
        default: break;
    }
    return (result < 0) ? "VK_ERROR_<Unknown>" : "VK_<Unknown>";
}
//Macro that defines this function more compactly and prints
//out result automatically to debug
#define VK_CHECK(arg) {POG_DEBUG(vulkanCheckResult(arg))}



