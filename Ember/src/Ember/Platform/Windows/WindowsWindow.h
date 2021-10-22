#pragma once
#include "Ember/Core/Window.h"
#include <GLFW/glfw3.h>

namespace Ember
{
#ifdef EM_PLATFORM_WINDOWS

	class WindowsWindow : public Window
	{
	private:
		struct WindowData
		{
			std::string Title;
			uint16_t Width;
			uint16_t Height;
			EventCallbackFunc EventCallback;
			bool VSync;
		};

		GLFWwindow* window;
		WindowData windowData;

		virtual void Init(const WindowProperties& props);
		virtual void Terminate();
	public:
		WindowsWindow(const WindowProperties& props);
		virtual ~WindowsWindow();

		inline uint16_t GetWidth() const override { return windowData.Width; }
		inline uint16_t GetHeight() const override { return windowData.Height; }

		inline void SetEventCallback(const EventCallbackFunc& callback) override { windowData.EventCallback = callback; }
		void SetVSync(bool enable) override;
		bool IsVSync() const override;

		void OnUpdate() override;
	};

#endif // EM_PLATFORM_WINDOWS
}