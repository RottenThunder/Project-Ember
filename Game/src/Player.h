#pragma once
#include "Entity.h"

enum class PlayerFace : uint8_t
{
	Down = 0, Left, Up, Right
};

class Player : public Entity
{
private:
	float_t InventorySlotPosX = -8.25f;
	float_t InventorySlotPosY = 3.75f;
public:
	glm::vec3 TransformedPosition = { 0.0f, 0.0f, 0.0f };
	float_t Speed = 2.0f;
	PlayerFace Face = PlayerFace::Down;

	std::unordered_map<uint16_t, std::string> ItemDataBase =
	{
		{0x0000, "assets/textures/UI/Coin.png"},
		{0x0001, "assets/textures/UI/Torch.png"},
		{0x0002, "assets/textures/UI/Potion.png"},
		{0x0003, "assets/textures/UI/Sword.png"},
		{0x0004, "assets/textures/UI/Axe.png"},
		{0x0005, "assets/textures/UI/Bow.png"}
	};

	std::vector<Ember::Ref<Ember::Texture2D>> Inventory;
	std::vector<glm::vec3> InventorySlotPositions;
	void AddToInventory(uint16_t itemCode, uint8_t quantity);
	void DeleteFromInventory(uint16_t itemCode, uint8_t quantity);
};