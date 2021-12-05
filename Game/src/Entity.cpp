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

	EntityTextureShader.reset(Ember::Shader::Create("assets/shaders/Texture.glsl"));

	EntityTexture = Ember::Texture2D::Create(textureFilePath);

	std::dynamic_pointer_cast<Ember::OpenGLShader>(EntityTextureShader)->Bind();
	std::dynamic_pointer_cast<Ember::OpenGLShader>(EntityTextureShader)->UploadUniformInt("u_Texture", 0);
}

void Entity::UpdateTransform()
{
	EntityTransform = glm::translate(glm::mat4(1.0f), EntityPosition);
}

void Entity::CalculateCollisions(const glm::vec3& ColliderCentre)
{
	glm::vec2 InternalMaxCoords = { EntityPosition.x + 0.5f, EntityPosition.y + 0.5f };
	glm::vec2 InternalMinCoords = { EntityPosition.x - 0.5f, EntityPosition.y - 0.5f };
	glm::vec2 ExternalMaxCoords = { ColliderCentre.x + 0.5f, ColliderCentre.y + 0.5f };
	glm::vec2 ExternalMinCoords = { ColliderCentre.x - 0.5f, ColliderCentre.y - 0.5f };


	if ((InternalMinCoords.x >= ExternalMinCoords.x && InternalMinCoords.x <= ExternalMaxCoords.x) && (InternalMinCoords.y >= ExternalMinCoords.y && InternalMinCoords.y <= ExternalMaxCoords.y)) //Bottom-Left Collider
	{
		CollidersActive.z++;
		if (ExternalMaxCoords.x >= (InternalMinCoords.x + 0.05f))
		{
			NumberOfCollisions.w++;
		}
		else
		{
			NumberOfCollisions.z++;
		}
	}


	if ((InternalMinCoords.x >= ExternalMinCoords.x && InternalMinCoords.x <= ExternalMaxCoords.x) && (InternalMaxCoords.y >= ExternalMinCoords.y && InternalMaxCoords.y <= ExternalMaxCoords.y)) //Top-Left Collider
	{
		CollidersActive.x++;
		if (ExternalMaxCoords.x >= (InternalMinCoords.x + 0.05f))
		{
			NumberOfCollisions.y++;
		}
		else
		{
			NumberOfCollisions.z++;
		}
	}


	if ((InternalMaxCoords.x >= ExternalMinCoords.x && InternalMaxCoords.x <= ExternalMaxCoords.x) && (InternalMinCoords.y >= ExternalMinCoords.y && InternalMinCoords.y <= ExternalMaxCoords.y)) //Bottom-Right Collider
	{
		CollidersActive.w++;
		if (ExternalMinCoords.x <= (InternalMaxCoords.x - 0.05f))
		{
			NumberOfCollisions.w++;
		}
		else
		{
			NumberOfCollisions.x++;
		}
	}


	if ((InternalMaxCoords.x >= ExternalMinCoords.x && InternalMaxCoords.x <= ExternalMaxCoords.x) && (InternalMaxCoords.y >= ExternalMinCoords.y && InternalMaxCoords.y <= ExternalMaxCoords.y)) //Top-Right Collider
	{
		CollidersActive.y++;
		if (ExternalMinCoords.x <= (InternalMaxCoords.x - 0.05f))
		{
			NumberOfCollisions.y++;
		}
		else
		{
			NumberOfCollisions.x++;
		}
	}
}

void Entity::HandleCollisions(bool& CanMovePositiveX, bool& CanMoveNegativeX, bool& CanMovePositiveY, bool& CanMoveNegativeY)
{
	if (NumberOfCollisions.x >= 1)
	{
		CanMovePositiveX = false;
		if (NumberOfCollisions.y >= 1 && CollidersActive.w == 0)
		{
			CanMovePositiveX = true;
		}
		if (NumberOfCollisions.w >= 1 && CollidersActive.y == 0)
		{
			CanMovePositiveX = true;
		}
	}
	else
	{
		CanMovePositiveX = true;
	}
	if (NumberOfCollisions.y >= 1)
	{
		CanMovePositiveY = false;
	}
	else
	{
		CanMovePositiveY = true;
	}
	if (NumberOfCollisions.z >= 1)
	{
		CanMoveNegativeX = false;
		if (NumberOfCollisions.y >= 1 && CollidersActive.z == 0)
		{
			CanMoveNegativeX = true;
		}
		if (NumberOfCollisions.w >= 1 && CollidersActive.x == 0)
		{
			CanMoveNegativeX = true;
		}
	}
	else
	{
		CanMoveNegativeX = true;
	}
	if (NumberOfCollisions.w >= 1)
	{
		CanMoveNegativeY = false;
	}
	else
	{
		CanMoveNegativeY = true;
	}

	if (NumberOfCollisions.x >= 1 && NumberOfCollisions.y >= 1 && NumberOfCollisions.z >= 1)
	{
		CanMovePositiveX = true;
		CanMoveNegativeX = true;
	}
	if (NumberOfCollisions.x >= 1 && NumberOfCollisions.z >= 1 && NumberOfCollisions.w >= 1)
	{
		CanMovePositiveX = true;
		CanMoveNegativeX = true;
	}

	NumberOfCollisions.x = 0;
	NumberOfCollisions.y = 0;
	NumberOfCollisions.z = 0;
	NumberOfCollisions.w = 0;

	CollidersActive.x = 0;
	CollidersActive.y = 0;
	CollidersActive.z = 0;
	CollidersActive.w = 0;
}