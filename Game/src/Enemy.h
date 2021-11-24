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

class Enemy
{
private:
	Grid grid;
public:
	Ember::Ref<Ember::VertexArray> EnemyVertexArray;
	Ember::Ref<Ember::VertexBuffer> EnemyVertexBuffer;
	Ember::Ref<Ember::IndexBuffer> EnemyIndexBuffer;
	Ember::Ref<Ember::Shader> EnemyTextureShader;
	Ember::Ref<Ember::Texture2D> EnemyTexture;
	glm::mat4 EnemyTransform;
	glm::vec3 EnemyPosition = { 0.0f, 0.0f, 0.0f };
	glm::vec2 MaxColliderPosition = { 0.5f, 0.5f }; //Top-Right of Collider
	glm::vec2 MinColliderPosition = { -0.5f, -0.5f }; //Bottom-Left of Collider
	bool Colliding;

	void Init();
	void UpdateTransform();
	void SetColliderValues();
};