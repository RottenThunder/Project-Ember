#include "Enemy.h"

void Enemy::Init()
{
	EnemyVertexArray.reset(Ember::VertexArray::Create());

	EnemyVertexBuffer.reset(Ember::VertexBuffer::Create(grid.CharacterOriginWithTexCoords, sizeof(grid.CharacterOriginWithTexCoords)));

	EnemyVertexBuffer->SetLayout({
		{ Ember::ShaderDataType::Vec3, "a_Position", false },
		{ Ember::ShaderDataType::Vec2, "a_TexCoord", false }
		});

	EnemyVertexArray->AddVertexBuffer(EnemyVertexBuffer);

	uint32_t EnemyIndices[6] = { 3, 2, 0, 0, 1, 3 };
	EnemyIndexBuffer.reset(Ember::IndexBuffer::Create(EnemyIndices, sizeof(EnemyIndices) / sizeof(uint32_t)));

	EnemyVertexArray->SetIndexBuffer(EnemyIndexBuffer);

	std::string vertexSrcEnemy = R"(
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

	std::string fragmentSrcEnemy = R"(
			#version 330 core

			layout(location = 0) out vec4 Colour;

			in vec2 v_TexCoord;

			uniform sampler2D u_Texture;

			void main()
			{
				Colour = texture(u_Texture, v_TexCoord);
			}
		)";

	EnemyTextureShader.reset(Ember::Shader::Create(vertexSrcEnemy, fragmentSrcEnemy));

	EnemyTexture = Ember::Texture2D::Create("assets/textures/Pokemon_NPC_Front.png");

	std::dynamic_pointer_cast<Ember::OpenGLShader>(EnemyTextureShader)->Bind();
	std::dynamic_pointer_cast<Ember::OpenGLShader>(EnemyTextureShader)->UploadUniformInt("u_Texture", 0);

	//---------------------------------

	SetColliderValues();
}

void Enemy::UpdateTransform()
{
	EnemyTransform = glm::translate(glm::mat4(1.0f), EnemyPosition);
}

void Enemy::SetColliderValues()
{
	MinColliderPosition.x = EnemyPosition.x - 0.5f;
	MinColliderPosition.y = EnemyPosition.y - 0.5f;

	MaxColliderPosition.x = EnemyPosition.x + 0.5f;
	MaxColliderPosition.y = EnemyPosition.y + 0.5f;
}