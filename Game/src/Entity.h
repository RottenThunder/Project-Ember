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

class Entity
{
private:
	Grid grid;
public:
	bool ColliderActiveTR = false;
	bool ColliderActiveBR = false;
	bool ColliderActiveTL = false;
	bool ColliderActiveBL = false;
	Ember::Ref<Ember::VertexArray> EntityVertexArray;
	Ember::Ref<Ember::VertexBuffer> EntityVertexBuffer;
	Ember::Ref<Ember::IndexBuffer> EntityIndexBuffer;
	Ember::Ref<Ember::Shader> EntityTextureShader;
	Ember::Ref<Ember::Texture2D> EntityTexture;
	glm::mat4 EntityTransform;
	glm::vec3 EntityPosition = { 0.0f, 0.0f, 0.0f };

	void Init(bool createCharacter, const std::string& textureFilePath);
	void UpdateTransform();
	void HandleCollisions(bool& CanMovePositiveX, bool& CanMoveNegativeX, bool& CanMovePositiveY, bool& CanMoveNegativeY, const glm::vec3& ColliderCentre);
};