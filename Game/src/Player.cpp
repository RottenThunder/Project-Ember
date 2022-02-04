#include "Player.h"

void Player::AddToInventory(uint16_t itemCode, uint8_t quantity)
{
	auto textureFilePath = ItemDataBase.find(itemCode);
	for (uint8_t i = 0; i < quantity; i++)
	{
		Inventory.push_back(Ember::Texture2D::Create(textureFilePath->second));
		InventorySlotPosX += 1.5f;
		if (InventorySlotPosX == 8.25f)
		{
			InventorySlotPosX = -6.75f;
			InventorySlotPosY -= 1.5f;
		}
		InventorySlotPositions.push_back({ InventorySlotPosX, InventorySlotPosY, 0.3f });
	}
}

void Player::DeleteFromInventory(uint16_t itemCode, uint8_t quantity)
{
	for (uint8_t i = 0; i < quantity; i++)
	{
		//Delete from Inventory
	}
}