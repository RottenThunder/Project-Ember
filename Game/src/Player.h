#pragma once
//Ember
// //---For Creating An Application--------------------
#include "Ember/Core/Application.h"
//--------------------------------------------------

//---For Creating an Orthographic Camera------------
#include "Ember/Renderer/OrthographicCamera.h"
//--------------------------------------------------

//---For Calculating Delta Time---------------------
#include "Ember/Core/DeltaTime.h"
//--------------------------------------------------

//---For Polling Input------------------------------
#include "Ember/Core/Input.h"
//--------------------------------------------------

//---To Reference to a Certain Key Code-------------
#include "Ember/Core/KeyCodes.h"
//--------------------------------------------------

//---To Reference to a Certain Mouse Button---------
#include "Ember/Core/MouseButtonCodes.h"
//--------------------------------------------------

//---For Creating Layers----------------------------
#include "Ember/Core/Layer.h"
//--------------------------------------------------


//--------------------------------------------------



//---DEBUG------------------------------------------


//---For Logging Support----------------------------
#include "Ember/Debug/Log.h"
//--------------------------------------------------


//--------------------------------------------------



//---RENDERER---------------------------------------


//---For Rendering----------------------------------
#include "Ember/Renderer/Renderer.h"
//--------------------------------------------------

//---For Executing Rendering-Related Commands-------
#include "Ember/Renderer/RenderCommand.h"
//--------------------------------------------------

//---For Creating Vertex Arrays---------------------
#include "Ember/Renderer/VertexArray.h"
//--------------------------------------------------

//---For Creating Vertex and Index Buffers----------
#include "Ember/Renderer/Buffer.h"
//--------------------------------------------------

//---For Creating Shaders---------------------------
#include "Ember/Renderer/Shader.h"
//--------------------------------------------------

//---For Creating Textures--------------------------
#include "Ember/Renderer/Texture.h"
//--------------------------------------------------


//--------------------------------------------------



//---IMGUI------------------------------------------


//---For Making an ImGui Layer----------------------
#include "Ember/ImGui/ImGuiLayer.h"
//--------------------------------------------------


//--------------------------------------------------
//
#include "Ember/Platform/OpenGL/OpenGLShader.h"
#include "Grid.h"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include <glm/glm.hpp>

class Player
{
private:
	Grid grid;
public:
	Ember::Ref<Ember::VertexArray> PlayerVertexArray;
	Ember::Ref<Ember::VertexBuffer> PlayerVertexBuffer;
	Ember::Ref<Ember::IndexBuffer> PlayerIndexBuffer;
	Ember::Ref<Ember::Shader> PlayerTextureShader;
	Ember::Ref<Ember::Texture2D> PlayerTexture;
	glm::mat4 PlayerTransform;
	glm::vec3 PlayerPosition = { 0.0f, 0.0f, 0.0f };
	float_t PlayerSpeed = 2.0f;
	glm::vec2 ColliderTopRight = { 0.5f, 0.5f };
	glm::vec2 ColliderTopLeft = { -0.5f, 0.5f };
	glm::vec2 ColliderBottomRight = { 0.5f, -0.5f };
	glm::vec2 ColliderBottomLeft = { -0.5f, -0.5f };
	float_t ColliderCoords[8] =
	{
		-0.5f, -0.5f, //Bottom-Left
		0.5f, -0.5f, //Bottom-Right
		-0.5f, 0.5f, //Top-Left
		0.5f, 0.5f //Top-Right
	};
	bool TopRightColliding = false;;
	bool TopLeftColliding = false;
	bool BottomRightColliding = false;
	bool BottomLeftColliding = false;

	void Init();
	void UpdateTransform();
	void SetColliderValues();
};