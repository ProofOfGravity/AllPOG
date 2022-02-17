// Windows platform layer.
#if POG_PLATFORM_WINDOWS
#define VK_USE_PLATFORM_WIN32_KHR

#include <windows.h>
#include "../core/logger.h"
//#include "vulkan/vulkan_win32.h"
#include "vulkan/vulkan.h"
#include "platform.h"

#include <stdlib.h>

typedef struct internal_state {
    HINSTANCE h_instance;
    HWND hwnd;
} internal_state;

static LRESULT CALLBACK win32_process_message(HWND hwnd, u32 msg, WPARAM w_param, LPARAM l_param);

b8 platform::platform_init(const char *application_name, i32 x, i32 y, i32 width, i32 height) {

    platform_state = malloc(sizeof(internal_state));
    auto state = (internal_state *)platform_state;

    state->h_instance = GetModuleHandleA(nullptr);

    // Setup and register window class.
    HICON icon = LoadIcon(state->h_instance, IDI_APPLICATION);
    WNDCLASSA wc;
    memset(&wc, 0, sizeof(wc));
    wc.style = CS_DBLCLKS;  // Get double-clicks
    wc.lpfnWndProc = win32_process_message;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = state->h_instance;
    wc.hIcon = icon;
    wc.hCursor = LoadCursor(nullptr, IDC_ARROW);  // NULL; // Manage the cursor manually
    wc.hbrBackground = nullptr;                   // Transparent
    wc.lpszClassName = "pog_window_class";

    if (!RegisterClassA(&wc)) {
        MessageBoxA(nullptr, "Window registration failed", "Error", MB_ICONEXCLAMATION | MB_OK);
        return FALSE;
    }

    // Create window
    u32 client_x = x;
    u32 client_y = y;
    u32 client_width = width;
    u32 client_height = height;

    u32 window_x = client_x;
    u32 window_y = client_y;
    u32 window_width = client_width;
    u32 window_height = client_height;

    u32 window_style = WS_OVERLAPPED | WS_SYSMENU | WS_CAPTION;
    u32 window_ex_style = WS_EX_APPWINDOW;

    window_style |= WS_MAXIMIZEBOX;
    window_style |= WS_MINIMIZEBOX;
    window_style |= WS_THICKFRAME;

    // Obtain the size of the border.
    RECT border_rect = {0, 0, 0, 0};
    AdjustWindowRectEx(&border_rect, window_style, 0, window_ex_style);

    // In this case, the border rectangle is negative.
    window_x += border_rect.left;
    window_y += border_rect.top;

    // Grow by the size of the OS border.
    window_width += border_rect.right - border_rect.left;
    window_height += border_rect.bottom - border_rect.top;

    HWND handle = CreateWindowExA(
        window_ex_style, "pog_window_class", application_name,
        window_style, (int)window_x, (int)window_y, (int)window_width,
        (int)window_height,nullptr, nullptr,
        state->h_instance, nullptr);

    if (handle == nullptr) {
        MessageBoxA(nullptr, "Window creation failed!", "Error!",
                    MB_ICONEXCLAMATION | MB_OK);

        POG_FATAL("Window creation failed!");
        return FALSE;
    } else {
        state->hwnd = handle;
    }

    // Show the window
    b32 should_activate = 1;  // TODO: if the window should not accept input, this should be false.
    i32 show_window_command_flags = should_activate ? SW_SHOW : SW_SHOWNOACTIVATE;
    // If initially minimized, use SW_MINIMIZE : SW_SHOWMINNOACTIVE;
    // If initially maximized, use SW_SHOWMAXIMIZED : SW_MAXIMIZE
    ShowWindow(state->hwnd, show_window_command_flags);

    // Clock setup
    LARGE_INTEGER frequency;
    QueryPerformanceFrequency(&frequency);
    clock_frequency = 1.0 / (f64)frequency.QuadPart;
    QueryPerformanceCounter(&start_time);

    return TRUE;
}

void platform::platform_shutdown() {
    // Simply cold-cast to the known type.
    auto state = (internal_state *)platform_state;

    if (state->hwnd) {
        DestroyWindow(state->hwnd);
        state->hwnd = nullptr;
    }
    free(state);
}

b8 platform::platform_pump_messages() {
    MSG message;
    while (PeekMessageA(&message, nullptr, 0,
                        0, PM_REMOVE)) {
        TranslateMessage(&message);
        DispatchMessageA(&message);
        if(message.message == WM_QUIT){
            return FALSE;
        }
    }
    return TRUE;
}

void* platform::platform_allocate(u64 size, b8 aligned) {
    return malloc(size);
}

void platform::platform_free(void* block, b8 aligned) {
    free(block);
}

void* platform::platform_zero_memory(void* block, u64 size) {
    return memset(block, 0, size);
}

void* platform::platform_copy_memory(void* dest, const void *source, u64 size) {
    return memcpy(dest, source, size);
}

void* platform::platform_set_memory(void* dest, i32 value, u64 size) {
    return memset(dest, value, size);
}

void platform::platform_console_write(const char* message, u8 colour) {
    HANDLE console_handle = GetStdHandle(STD_OUTPUT_HANDLE);
    // FATAL,ERROR,WARN,INFO,DEBUG,TRACE
    static u8 levels[6] = {64, 4, 6, 2, 1, 8};
    SetConsoleTextAttribute(console_handle, levels[colour]);
    OutputDebugStringA(message);
    u64 length = strlen(message);
    LPDWORD number_written = nullptr;
    WriteConsoleA(GetStdHandle(STD_OUTPUT_HANDLE), message,
                  (DWORD)length, number_written, nullptr);
}

void platform::platform_console_write_error(const char *message, u8 colour) {
    HANDLE console_handle = GetStdHandle(STD_ERROR_HANDLE);
    // FATAL,ERROR,WARN,INFO,DEBUG,TRACE
    static u8 levels[6] = {64, 4, 6, 2, 1, 8};
    SetConsoleTextAttribute(console_handle, levels[colour]);
    OutputDebugStringA(message);
    u64 length = strlen(message);
    LPDWORD number_written = nullptr;
    WriteConsoleA(GetStdHandle(STD_ERROR_HANDLE), message,
                  (DWORD)length, number_written, nullptr);
}

f64 platform::platform_get_absolute_time() {
    LARGE_INTEGER now_time;
    QueryPerformanceCounter(&now_time);
    return (f64)now_time.QuadPart * clock_frequency;
}

void platform::platform_sleep(u64 ms) {
    Sleep(ms);
}

LRESULT CALLBACK win32_process_message(HWND hwnd, u32 msg, WPARAM w_param, LPARAM l_param) {
    switch (msg) {
        case WM_ERASEBKGND:
            // Notify the OS that erasing will be handled by the engine to prevent flicker.
            return 1;
        case WM_CLOSE:
            PostQuitMessage(0);
            DestroyWindow(hwnd);
            return 0;
        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;
        case WM_SIZE: {
            // Get the updated size.
            // RECT r;
            // GetClientRect(hwnd, &r);
            // u32 width = r.right - r.left;
            // u32 height = r.bottom - r.top;

            // TODO: Fire an event for window resize.
        }
        //case WM_KEYDOWN:
        //case WM_SYSKEYDOWN:
        //case WM_KEYUP:
        //case WM_SYSKEYUP:
        //case WM_MOUSEMOVE:
        //case WM_MOUSEWHEEL:
        //case WM_LBUTTONDOWN:
        //case WM_MBUTTONDOWN:
        //case WM_RBUTTONDOWN:
        //case WM_LBUTTONUP:
        //case WM_MBUTTONUP:
        //case WM_RBUTTONUP:
        default:
            return DefWindowProcA(hwnd, msg, w_param, l_param);
    }

}

void platform::get_platform_extensions(std::vector<const char *> &out_vec) {
    out_vec.push_back(VK_KHR_WIN32_SURFACE_EXTENSION_NAME);
}

b8 platform::get_platform_surface(vulkan_context& context) {

    VkWin32SurfaceCreateInfoKHR surfaceCreateInfo{};
    surfaceCreateInfo.sType = {VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR};

    auto state = (internal_state *)platform_state;
    if(state){
        surfaceCreateInfo.hwnd = state->hwnd;
        surfaceCreateInfo.hinstance = GetModuleHandle(nullptr);
    }

    vkCreateWin32SurfaceKHR(context.instance, &surfaceCreateInfo, context.custom_allocator, &context.surface);

    return true;
}

#endif  // POG_PLATFORM_WINDOWS