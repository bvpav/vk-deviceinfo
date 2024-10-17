/**
 * This program is free software: you can redistribute it and/or modify it under
 * the terms of the GNU General Public License as published by the Free Software Foundation,
 * either version 3 of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along with this program.
 * If not, see <https://www.gnu.org/licenses/>.
 */

#include <iostream>
#include <vector>

#include <vulkan/vulkan.h>

int main()
{
    VkInstance instance;
    VkInstanceCreateInfo create_info{ .sType=VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO };
    if (vkCreateInstance(&create_info, nullptr, &instance) != VK_SUCCESS)
    {
        std::cerr << "failed to create Vulkan instance\n";
        return 1;
    }

    uint32_t device_count{0};
    vkEnumeratePhysicalDevices(instance, &device_count, nullptr);
    if (!device_count)
    {
        std::cerr << "no GPUs with Vulkan support found\n";
        return 1;
    }

    std::vector<VkPhysicalDevice> devices(device_count);
    vkEnumeratePhysicalDevices(instance, &device_count, devices.data());
    for (const auto &device : devices)
    {
        VkPhysicalDeviceProperties device_properties;
        vkGetPhysicalDeviceProperties(device, &device_properties);

        std::cout << "Device: " << device_properties.deviceName << '\n';

        uint32_t extension_count{0};
        vkEnumerateDeviceExtensionProperties(device, nullptr, &extension_count, nullptr);

        std::vector<VkExtensionProperties> extensions(extension_count);
        vkEnumerateDeviceExtensionProperties(device, nullptr, &extension_count, extensions.data());

        std::cout << "Supported Extensions: \n";
        for (const auto &extension : extensions)
            std::cout << "    " << extension.extensionName << '\n';

        std::cout << '\n';
    }

    vkDestroyInstance(instance, nullptr);
}