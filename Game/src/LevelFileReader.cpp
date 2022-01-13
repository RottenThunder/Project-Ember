#include "LevelFileReader.h"

std::vector<Entity> LevelFileReader::Read(const std::string& levelFile, int32_t xOffset, int32_t yOffset)
{
	std::vector<Entity> currentMap;

	file.open(levelFile, std::ios::in | std::ios::binary);

	if (file.is_open())
	{
		std::string currentLine;
		int32_t width, height;

		std::getline(file, currentLine);
		width = std::stoi(currentLine.substr(4, 2));

		std::getline(file, currentLine);
		height = std::stoi(currentLine.substr(4, 2));

		for (int32_t row = 0; row < height; row++)
		{
			std::getline(file, currentLine);

			for (int32_t pos = 0; pos < width; pos++)
			{
				std::unordered_map<std::string, std::string>::const_iterator temp = TileDataBase.find(currentLine.substr(pos * 4, 2));

				Entity e;
				e.Position = { pos + xOffset, -row + yOffset, -0.1f };
				e.Texture = Ember::Texture2D::Create(temp->second);
				if (currentLine.substr((pos * 4) + 2, 1) == "1")
				{
					e.IsCollidable = true;
				}

				currentMap.push_back(e);
			}
		}
	}

	file.close();

	return currentMap;
}