#include "empch.h"
#include "ImGuiLayer.h"

#include "imgui.h"
#include "Ember/Platform/OpenGL/ImGuiOpenGLRenderer.h"
#include "GLFW/glfw3.h"
#include "glad/glad.h"

#include "Ember/Core/Application.h"
#include "Ember/Core/KeyCodes.h"

namespace Ember
{
	ImGuiLayer::ImGuiLayer()
		: Layer("ImGui Layer")
	{

	}

	ImGuiLayer::~ImGuiLayer()
	{

	}

	void ImGuiLayer::OnAttach()
	{
		ImGui::CreateContext();
		ImGui::StyleColorsDark();

		ImGuiIO& io = ImGui::GetIO();
		io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
		io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;

		io.KeyMap[ImGuiKey_Tab] = EM_KEY_TAB;
		io.KeyMap[ImGuiKey_LeftArrow] = EM_KEY_LEFT_ARROW;
		io.KeyMap[ImGuiKey_RightArrow] = EM_KEY_RIGHT_ARROW;
		io.KeyMap[ImGuiKey_UpArrow] = EM_KEY_UP_ARROW;
		io.KeyMap[ImGuiKey_DownArrow] = EM_KEY_DOWN_ARROW;
		io.KeyMap[ImGuiKey_PageUp] = EM_KEY_PAGE_UP;
		io.KeyMap[ImGuiKey_PageDown] = EM_KEY_PAGE_DOWN;
		io.KeyMap[ImGuiKey_Home] = EM_KEY_HOME;
		io.KeyMap[ImGuiKey_End] = EM_KEY_END;
		io.KeyMap[ImGuiKey_Insert] = EM_KEY_INSERT;
		io.KeyMap[ImGuiKey_Delete] = EM_KEY_DELETE;
		io.KeyMap[ImGuiKey_Backspace] = EM_KEY_BACKSPACE;
		io.KeyMap[ImGuiKey_Space] = EM_KEY_SPACE;
		io.KeyMap[ImGuiKey_Enter] = EM_KEY_ENTER;
		io.KeyMap[ImGuiKey_Escape] = EM_KEY_ESCAPE;
		io.KeyMap[ImGuiKey_A] = EM_KEY_A;
		io.KeyMap[ImGuiKey_C] = EM_KEY_C;
		io.KeyMap[ImGuiKey_V] = EM_KEY_V;
		io.KeyMap[ImGuiKey_X] = EM_KEY_X;
		io.KeyMap[ImGuiKey_Y] = EM_KEY_Y;
		io.KeyMap[ImGuiKey_Z] = EM_KEY_Z;

		ImGui_ImplOpenGL3_Init("#version 410");
	}

	void ImGuiLayer::OnDetach()
	{

	}

	void ImGuiLayer::OnUpdate(DeltaTime DT)
	{
		ImGuiIO& io = ImGui::GetIO();
		Application& app = Application::Get();
		io.DisplaySize = ImVec2(app.GetWindow().GetWidth(), app.GetWindow().GetHeight());

		float time = (float)glfwGetTime();
		io.DeltaTime = Time > 0.0f ? (time - Time) : (1.0f / 60.0f);
		Time = time;

		ImGui_ImplOpenGL3_NewFrame();
		ImGui::NewFrame();

		static bool show = true;
		ImGui::ShowDemoWindow(&show);

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}

	void ImGuiLayer::OnEvent(Event& event)
	{
		EventDispatcher dispatcher(event);
		dispatcher.Dispatch<MouseButtonPressedEvent>(EM_BIND_EVENT_FUNC(ImGuiLayer::OnMouseButtonPressedEvent));
		dispatcher.Dispatch<MouseButtonReleasedEvent>(EM_BIND_EVENT_FUNC(ImGuiLayer::OnMouseButtonReleasedEvent));
		dispatcher.Dispatch<MouseMovedEvent>(EM_BIND_EVENT_FUNC(ImGuiLayer::OnMouseMovedEvent));
		dispatcher.Dispatch<MouseScrolledEvent>(EM_BIND_EVENT_FUNC(ImGuiLayer::OnMouseScrolledEvent));
		dispatcher.Dispatch<KeyPressedEvent>(EM_BIND_EVENT_FUNC(ImGuiLayer::OnKeyPressedEvent));
		dispatcher.Dispatch<KeyReleasedEvent>(EM_BIND_EVENT_FUNC(ImGuiLayer::OnKeyReleasedEvent));
		dispatcher.Dispatch<KeyTypedEvent>(EM_BIND_EVENT_FUNC(ImGuiLayer::OnKeyTypedEvent));
		dispatcher.Dispatch<WindowResizeEvent>(EM_BIND_EVENT_FUNC(ImGuiLayer::OnWindowResizedEvent));
	}

	bool ImGuiLayer::OnMouseButtonPressedEvent(MouseButtonPressedEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.MouseDown[e.GetMouseButton()] = true;

		return false;
	}

	bool ImGuiLayer::OnMouseButtonReleasedEvent(MouseButtonReleasedEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.MouseDown[e.GetMouseButton()] = false;

		return false;
	}

	bool ImGuiLayer::OnMouseMovedEvent(MouseMovedEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.MousePos = ImVec2(e.GetX(), e.GetY());

		return false;
	}

	bool ImGuiLayer::OnMouseScrolledEvent(MouseScrolledEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.MouseWheelH += e.GetXOffset();
		io.MouseWheel += e.GetYOffset();

		return false;
	}

	bool ImGuiLayer::OnKeyPressedEvent(KeyPressedEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.KeysDown[e.GetKeyCode()] = true;

		io.KeyCtrl = io.KeysDown[EM_KEY_LEFT_CONTROL] || io.KeysDown[EM_KEY_RIGHT_CONTROL];
		io.KeyShift = io.KeysDown[EM_KEY_LEFT_SHIFT] || io.KeysDown[EM_KEY_RIGHT_SHIFT];
		io.KeyAlt = io.KeysDown[EM_KEY_LEFT_ALT] || io.KeysDown[EM_KEY_RIGHT_ALT];
		io.KeySuper = io.KeysDown[EM_KEY_LEFT_SUPER] || io.KeysDown[EM_KEY_RIGHT_SUPER];

		return false;
	}

	bool ImGuiLayer::OnKeyReleasedEvent(KeyReleasedEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.KeysDown[e.GetKeyCode()] = false;

		return false;
	}

	bool ImGuiLayer::OnKeyTypedEvent(KeyTypedEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		uint16_t keycode = e.GetKeyCode();
		if (keycode > 0 && keycode < 0x10000)
			io.AddInputCharacter(keycode);

		return false;
	}

	bool ImGuiLayer::OnWindowResizedEvent(WindowResizeEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.DisplaySize = ImVec2(e.GetWidth(), e.GetHeight());
		io.DisplayFramebufferScale = ImVec2(1.0f, 1.0f);
		glViewport(0, 0, e.GetWidth(), e.GetHeight());

		return false;
	}
}