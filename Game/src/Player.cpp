#include "Player.h"

std::unordered_map<uint16_t, std::string> MiscPlayerData::CardTextureDatabase =
{
	{0x0000, "???"},
	{0x0001, "assets/textures/Cards/T1_Speed_Potion.png"},
	{0x0002, "assets/textures/Cards/T2_Speed_Potion.png"},
	{0x0003, "assets/textures/Cards/T3_Speed_Potion.png"},
	{0x0004, "assets/textures/Cards/T1_Attack_Potion.png"},
	{0x0005, "assets/textures/Cards/T2_Attack_Potion.png"},
	{0x0006, "assets/textures/Cards/T3_Attack_Potion.png"}
};

std::unordered_map<uint16_t, std::string> MiscPlayerData::CardNameDatabase =
{
	{0x0000, "???"},
	{0x0001, "Speed Potion"},
	{0x0002, "Speed Potion"},
	{0x0003, "Speed Potion"},
	{0x0004, "Attack Potion"},
	{0x0005, "Attack Potion"},
	{0x0006, "Attack Potion"}
};

std::unordered_map<uint16_t, uint8_t> MiscPlayerData::CardTierDatabase =
{
	{0x0000, 0x00},
	{0x0001, 0x01},
	{0x0002, 0x02},
	{0x0003, 0x03},
	{0x0004, 0x01},
	{0x0005, 0x02},
	{0x0006, 0x03}
};

void Player::AddToCurrentCards(uint16_t cardCode)
{
	if (CurrentCards.size() == 5)
	{
		return;
	}

	auto TextureFilePath = MiscPlayerData::CardTextureDatabase.find(cardCode);
	CurrentCards.push_back(Ember::Texture2D::Create(TextureFilePath->second));
	CardInfo newCardInfo;
	newCardInfo.SetName(MiscPlayerData::CardNameDatabase.find(cardCode)->second);
	newCardInfo.SetTier(MiscPlayerData::CardTierDatabase.find(cardCode)->second);
	newCardInfo.SetEffect(cardCode);
	CurrentCardsInfo.push_back(newCardInfo);

	CardPos.clear();

	if (CurrentCards.size() % 2 == 0)
	{
		float_t begin = (CurrentCards.size() / 2) * CurrentCards.size();
		begin *= -1.0f;
		begin += CurrentCards.size() / 2;

		for (uint16_t i = 0; i < CurrentCards.size(); i++)
		{
			CardPos.push_back(begin + (i * CurrentCards.size()));
		}
		return;
	}
	else
	{
		float_t MiddleCard = (CurrentCards.size() + 1) / 2;
		float_t begin = (MiddleCard - CurrentCards.size()) * CurrentCards.size();

		for (uint16_t i = 0; i < CurrentCards.size(); i++)
		{
			CardPos.push_back(begin + (i * CurrentCards.size()));
		}
	}
}

void Player::RemoveFromCurrentCards(uint16_t cardIndex)
{
	CurrentCards.erase(CurrentCards.begin() + cardIndex);
	CurrentCardsInfo.erase(CurrentCardsInfo.begin() + cardIndex);

	CardPos.clear();

	if (CurrentCards.size() % 2 == 0)
	{
		float_t begin = (CurrentCards.size() / 2) * CurrentCards.size();
		begin *= -1.0f;
		begin += CurrentCards.size() / 2;

		for (uint16_t i = 0; i < CurrentCards.size(); i++)
		{
			CardPos.push_back(begin + (i * CurrentCards.size()));
		}
		return;
	}
	else
	{
		float_t MiddleCard = (CurrentCards.size() + 1) / 2;
		float_t begin = (MiddleCard - CurrentCards.size()) * CurrentCards.size();

		for (uint16_t i = 0; i < CurrentCards.size(); i++)
		{
			CardPos.push_back(begin + (i * CurrentCards.size()));
		}
	}
}