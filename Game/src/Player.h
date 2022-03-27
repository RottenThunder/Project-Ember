#pragma once
#include "Entity.h"

enum class PlayerFace : uint8_t
{
	Down = 0, Left, Up, Right
};

class MiscPlayerData
{
public:
	static std::unordered_map<uint16_t, std::string> CardTextureDatabase;
	static std::unordered_map<uint16_t, std::string> CardNameDatabase;
	static std::unordered_map<uint16_t, uint8_t> CardTierDatabase;
};

class CardInfo
{
private:
	std::string Name;
	uint8_t Tier;
	uint16_t Effect;
public:
	std::string GetName() const { return Name; }
	uint8_t GetTier() const { return Tier; }
	uint16_t GetEffect() const { return Effect; }

	void SetName(std::string name) { Name = name; }
	void SetTier(uint8_t tier) { Tier = tier; }
	void SetEffect(uint16_t effect) { Effect = effect; }
};

class Player : public Entity
{
public:
	glm::vec3 TransformedPosition = { 0.0f, 0.0f, 0.0f };
	float_t Speed = 2.0f;
	float_t AttackPower = 3.0f;
	PlayerFace Face = PlayerFace::Down;

	std::vector<Ember::Ref<Ember::Texture2D>> CurrentCards;
	std::vector<CardInfo> CurrentCardsInfo;
	std::vector<float_t> CardPos;
	void AddToCurrentCards(uint16_t cardCode);
	void RemoveFromCurrentCards(uint16_t cardIndex);
};