#pragma once

#include "../defines.h"
#include "vector"
#include "../renderer/vulkanAssets.h"
#include "windows.h"


class POG_API platform{

public:

    platform() = default;

    b8 platform_init(const char* application_name,
                     i32 x,
                     i32 y,
                     i32 width,
                     i32 height);

    void platform_shutdown();

    b8 platform_pump_messages();

    void* platform_allocate(u64 size, b8 aligned);
    void platform_free(void* block, b8 aligned);
    void* platform_zero_memory(void* block, u64 size);
    void* platform_copy_memory(void* dest, const void* source, u64 size);
    void* platform_set_memory(void* dest, i32 value, u64 size);

    void platform_console_write(const char* message, u8 color);
    void platform_console_write_error(const char* message, u8 color);

    f64 platform_get_absolute_time();

    // sleep on the thread for the provided ms; this blocks the main thread
    // should only be used for giving time back to the OS for unused update power
    // therefore it is not exported
    void platform_sleep(u64 ms);

    //fetch platform specific extensions for vulkan
    void get_platform_extensions(std::vector<const char*> &out_vec);

    //get platform specific surface
    b8 get_platform_surface(vulkan_context& context);


private:
    void* platform_state{};

    // Clock
    f64 clock_frequency{};
    LARGE_INTEGER start_time{};
};

