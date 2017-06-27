//
// Created by marc on 21/06/17.
//

#pragma once

#ifdef DEBUG
# define ENABLE_VALIDATION_LAYERS 1
#else
# define ENABLE_VALIDATION_LAYERS 0
#endif

#include <vulkan/vulkan.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <set>
#include <array>

#include "utils.h"

class VulkanInstance
{
private:
	VkInstance						m_instance;
	VkDebugReportCallbackEXT		m_callback;
	VkSurfaceKHR					m_surface;

	VkPhysicalDevice				m_physicalDevice;
	VkDevice						m_device;

	VkQueue							m_graphicsQueue;
	VkQueue							m_presentQueue;

	VkSwapchainKHR					m_swapChain;
	std::vector<VkImage>			m_swapChainImages;
	VkFormat						m_swapChainImageFormat;
	VkExtent2D						m_swapChainExtent;
	std::vector<VkImageView> 		m_swapChainImageViews;
	std::vector<VkFramebuffer>		m_swapChainFramebuffers;

	VkCommandPool 					m_commandPool;
	std::vector<VkCommandBuffer> 	m_commandBuffers;

	VkRenderPass					m_renderPass;
	VkPipeline						m_graphicsPipeline;
	VkPipelineLayout				m_pipelineLayout;

	VkSemaphore						m_imageAvailableSemaphore;
	VkSemaphore						m_renderFinishedSemaphore;

	std::vector<const char *>		m_validationLayers;
	std::vector<const char *> 		m_deviceExtensions;

	VkBuffer						m_vertexBuffer;
	VkDeviceMemory					m_vertexBufferMemory;

	typedef struct	_Vertex
	{
		glm::vec2 pos;
		glm::vec3 color;

		static VkVertexInputBindingDescription getBindingDescription()
		{
			VkVertexInputBindingDescription bindingDescription = {};

			bindingDescription.binding = 0;
			bindingDescription.stride = sizeof(struct _Vertex);
			bindingDescription.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;
			return bindingDescription;
		}
		static std::array<VkVertexInputAttributeDescription, 2> getAttributeDescriptions()
		{
			std::array<VkVertexInputAttributeDescription, 2> attributeDescriptions = {};

			/*
				float: VK_FORMAT_R32_SFLOAT
				vec2: VK_FORMAT_R32G32_SFLOAT
				vec3: VK_FORMAT_R32G32B32_SFLOAT
				vec4: VK_FORMAT_R32G32B32A32_SFLOAT
				ivec2: VK_FORMAT_R32G32_SINT
				uvec4: VK_FORMAT_R32G32B32A32_UINT
				double: VK_FORMAT_R64_SFLOAT
			*/
			attributeDescriptions[0].binding = 0;
			attributeDescriptions[0].location = 0;
			attributeDescriptions[0].format = VK_FORMAT_R32G32_SFLOAT;
			attributeDescriptions[0].offset = offsetof(Vertex, pos);

			attributeDescriptions[1].binding = 0;
			attributeDescriptions[1].location = 1;
			attributeDescriptions[1].format = VK_FORMAT_R32G32B32_SFLOAT;
			attributeDescriptions[1].offset = offsetof(Vertex, color);
			return attributeDescriptions;
		}
	}				Vertex;

	const std::vector<Vertex> m_vertices = {
		{{0.0f, -0.5f}, {1.0f, 0.0f, 0.0f}},
		{{0.5f, 0.5f}, {0.0f, 1.0f, 0.0f}},
		{{-0.5f, 0.5f}, {0.0f, 0.0f, 1.0f}}
	};

public:
	VulkanInstance(std::vector<const char *> layers, std::vector<const char *> extensions);
	~VulkanInstance();

	void initDebugCallbacks();
	void initWindowSurface(GLFWwindow *window);
	void initPhysicalDevices();
	void createLogicalDevices(float priority);
	void createSwapChain(uint32_t width, uint32_t height);
	void createImageViews();
	void createGraphicsPipeline();
	void createRenderPass();
	void createFramebuffers();
	void createCommandPool();
	void createBuffer(VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VkBuffer& buffer, VkDeviceMemory& bufferMemory);
	void createVertexBuffer();
	void createCommandBuffers();
	void createSemaphores();
	void drawFrame();

	void recreateSwapChain(uint32_t width, uint32_t height);
	void cleanupSwapChain();

	inline VkInstance getInstance() { return (m_instance); }
	inline VkSurfaceKHR getSurface() { return (m_surface); }
	inline VkPhysicalDevice getPhysicalDevice() { return (m_physicalDevice); }
	inline VkDevice getDevice() { return (m_device); }
	inline VkQueue getGraphicsQueue() { return (m_graphicsQueue); }
	inline VkCommandPool getCommandPool() { return (m_commandPool); }

	inline std::vector<const char *> getValidationLayers() const { return (m_validationLayers); }
	inline std::vector<const char *> getDeviceExtensions() { return (m_deviceExtensions); }
};
