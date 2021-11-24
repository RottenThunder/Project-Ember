#include "Player.h"

void Player::Init()
{
	PlayerVertexArray.reset(Ember::VertexArray::Create());

	PlayerVertexBuffer.reset(Ember::VertexBuffer::Create(grid.CharacterOriginWithTexCoords, sizeof(grid.CharacterOriginWithTexCoords)));

	PlayerVertexBuffer->SetLayout({
		{ Ember::ShaderDataType::Vec3, "a_Position", false },
		{ Ember::ShaderDataType::Vec2, "a_TexCoord", false }
		});

	PlayerVertexArray->AddVertexBuffer(PlayerVertexBuffer);

	uint32_t PlayerIndices[6] = { 3, 2, 0, 0, 1, 3 };
	PlayerIndexBuffer.reset(Ember::IndexBuffer::Create(PlayerIndices, sizeof(PlayerIndices) / sizeof(uint32_t)));

	PlayerVertexArray->SetIndexBuffer(PlayerIndexBuffer);

	std::string vertexSrcPlayer = R"(
			#version 330 core

			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec2 a_TexCoord;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			out vec2 v_TexCoord;

			void main()
			{
				v_TexCoord = a_TexCoord;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);	
			}
		)";

	std::string fragmentSrcPlayer = R"(
			#version 330 core

			layout(location = 0) out vec4 Colour;

			in vec2 v_TexCoord;

			uniform sampler2D u_Texture;

			void main()
			{
				Colour = texture(u_Texture, v_TexCoord);
			}
		)";

	PlayerTextureShader.reset(Ember::Shader::Create(vertexSrcPlayer, fragmentSrcPlayer));

	PlayerTexture = Ember::Texture2D::Create("assets/textures/Pokemon_Player_Front.png");

	std::dynamic_pointer_cast<Ember::OpenGLShader>(PlayerTextureShader)->Bind();
	std::dynamic_pointer_cast<Ember::OpenGLShader>(PlayerTextureShader)->UploadUniformInt("u_Texture", 0);

	//---------------------------------

	SetColliderValues();
}

void Player::UpdateTransform()
{
	PlayerTransform = glm::translate(glm::mat4(1.0f), PlayerPosition);
}

void Player::SetColliderValues()
{
	ColliderTopLeft.x = PlayerPosition.x - 0.5f;
	ColliderTopLeft.y = PlayerPosition.y + 0.5f;

	ColliderBottomLeft.x = PlayerPosition.x - 0.5f;
	ColliderBottomLeft.y = PlayerPosition.y - 0.5f;

	ColliderBottomRight.x = PlayerPosition.x + 0.5f;
	ColliderBottomRight.y = PlayerPosition.y - 0.5f;

	ColliderTopRight.x = PlayerPosition.x + 0.5f;
	ColliderTopRight.y = PlayerPosition.y + 0.5f;
}