#include <vulkan/vulkan.h>
#include <stdint.h>

extern "C" {
    // RuneG1 Engine - Vulkan Initialization
    void initVulkan() {
        VkApplicationInfo appInfo{};
        appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
        appInfo.pApplicationName = "RuneG1_Engine";
        appInfo.applicationVersion = 1; 
        appInfo.apiVersion = VK_API_VERSION_1_0;

        VkInstanceCreateInfo createInfo{};
        createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
        createInfo.pApplicationInfo = &appInfo;
        
        VkInstance instance;
        vkCreateInstance(&createInfo, nullptr, &instance);
    }

    // Existing Player Data Symbols
    int32_t getHealth() { return 100; }
}
