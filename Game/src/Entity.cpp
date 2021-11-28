#include "Entity.h"

void Entity::Init(bool createCharacter, const std::string& textureFilePath)
{
	EntityVertexArray.reset(Ember::VertexArray::Create());

	if (createCharacter)
	{
		EntityVertexBuffer.reset(Ember::VertexBuffer::Create(grid.CharacterOriginWithTexCoords, sizeof(grid.CharacterOriginWithTexCoords)));
	}
	if (!createCharacter)
	{
		EntityVertexBuffer.reset(Ember::VertexBuffer::Create(grid.ObjectOriginWithTexCoords, sizeof(grid.ObjectOriginWithTexCoords)));
	}

	EntityVertexBuffer->SetLayout({
		{ Ember::ShaderDataType::Vec3, "a_Position", false },
		{ Ember::ShaderDataType::Vec2, "a_TexCoord", false }
		});

	EntityVertexArray->AddVertexBuffer(EntityVertexBuffer);

	uint32_t EntityIndices[6] = { 3, 2, 0, 0, 1, 3 };
	EntityIndexBuffer.reset(Ember::IndexBuffer::Create(EntityIndices, sizeof(EntityIndices) / sizeof(uint32_t)));

	EntityVertexArray->SetIndexBuffer(EntityIndexBuffer);

	std::string vertexSrcEntity = R"(
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

	std::string fragmentSrcEntity = R"(
			#version 330 core

			layout(location = 0) out vec4 Colour;

			in vec2 v_TexCoord;

			uniform sampler2D u_Texture;

			void main()
			{
				Colour = texture(u_Texture, v_TexCoord);
			}
		)";

	EntityTextureShader.reset(Ember::Shader::Create(vertexSrcEntity, fragmentSrcEntity));

	EntityTexture = Ember::Texture2D::Create(textureFilePath);

	std::dynamic_pointer_cast<Ember::OpenGLShader>(EntityTextureShader)->Bind();
	std::dynamic_pointer_cast<Ember::OpenGLShader>(EntityTextureShader)->UploadUniformInt("u_Texture", 0);
}

void Entity::UpdateTransform()
{
	EntityTransform = glm::translate(glm::mat4(1.0f), EntityPosition);
}

void Entity::HandleCollisions(bool& CanMovePositiveX, bool& CanMoveNegativeX, bool& CanMovePositiveY, bool& CanMoveNegativeY, const glm::vec3& ColliderCentre)
{
	glm::vec2 InternalMaxCoords = { EntityPosition.x + 0.5f, EntityPosition.y + 0.5f };
	glm::vec2 InternalMinCoords = { EntityPosition.x - 0.5f, EntityPosition.y - 0.5f };
	glm::vec2 ExternalMaxCoords = { ColliderCentre.x + 0.5f, ColliderCentre.y + 0.5f };
	glm::vec2 ExternalMinCoords = { ColliderCentre.x - 0.5f, ColliderCentre.y - 0.5f };

	if (CanMoveNegativeY && CanMoveNegativeX)
	{
		if ((InternalMinCoords.x >= ExternalMinCoords.x && InternalMinCoords.x <= ExternalMaxCoords.x) && (InternalMinCoords.y >= ExternalMinCoords.y && InternalMinCoords.y <= ExternalMaxCoords.y)) //Bottom-Left Collider
		{
			ColliderActiveBL = true;
			if (ExternalMaxCoords.x >= (InternalMinCoords.x + 0.05f))
			{
				CanMoveNegativeY = false;
			}
			else
			{
				CanMoveNegativeX = false;
			}
		}
	}

	if (CanMovePositiveY && CanMoveNegativeX)
	{
		if ((InternalMinCoords.x >= ExternalMinCoords.x && InternalMinCoords.x <= ExternalMaxCoords.x) && (InternalMaxCoords.y >= ExternalMinCoords.y && InternalMaxCoords.y <= ExternalMaxCoords.y)) //Top-Left Collider
		{
			ColliderActiveTL = true;
			if (ExternalMaxCoords.x >= (InternalMinCoords.x + 0.05f))
			{
				CanMovePositiveY = false;
			}
			else
			{
				CanMoveNegativeX = false;
			}
		}
	}

	if (CanMoveNegativeY && CanMovePositiveX)
	{
		if ((InternalMaxCoords.x >= ExternalMinCoords.x && InternalMaxCoords.x <= ExternalMaxCoords.x) && (InternalMinCoords.y >= ExternalMinCoords.y && InternalMinCoords.y <= ExternalMaxCoords.y)) //Bottom-Right Collider
		{
			ColliderActiveBR = true;
			if (ExternalMinCoords.x <= (InternalMaxCoords.x - 0.05f))
			{
				CanMoveNegativeY = false;
			}
			else
			{
				CanMovePositiveX = false;
			}
		}
	}

	if (CanMovePositiveY && CanMovePositiveX)
	{
		if ((InternalMaxCoords.x >= ExternalMinCoords.x && InternalMaxCoords.x <= ExternalMaxCoords.x) && (InternalMaxCoords.y >= ExternalMinCoords.y && InternalMaxCoords.y <= ExternalMaxCoords.y)) //Top-Right Collider
		{
			ColliderActiveTR = true;
			if (ExternalMinCoords.x <= (InternalMaxCoords.x - 0.05f))
			{
				CanMovePositiveY = false;
			}
			else
			{
				CanMovePositiveX = false;
			}
		}
	}


	if (!(CanMovePositiveY) && !(CanMoveNegativeX))
	{
		CanMoveNegativeX = true;
	}
	if (!(CanMoveNegativeY) && !(CanMoveNegativeX))
	{
		CanMoveNegativeX = true;
	}
}