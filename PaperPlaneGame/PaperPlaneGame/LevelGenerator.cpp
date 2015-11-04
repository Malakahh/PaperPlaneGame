#include "LevelGenerator.h"

Game::LevelGenerator::LevelGenerator(Game::Camera& cam) : camera(cam)
{
	
}


Game::LevelGenerator::~LevelGenerator()
{
	while (!rows.empty())
	{
		delete rows.front();
		rows.pop();
	}
}

void Game::LevelGenerator::Update(int deltaTime)
{
	float dt = deltaTime / 1000.0;

	attemptDeleteFirstRow();

	//Move all rows up
	auto rowsContainer = rows._Get_container();
	for (auto rowIt = rowsContainer.cbegin(); rowIt != rowsContainer.cend(); ++rowIt)
	{
		auto row = *rowIt;
		for (auto it = row->cbegin(); it != row->cend(); ++it)
		{
			(*it)->position.x += rowMovementVector.x * dt;
			(*it)->position.y += rowMovementVector.y * dt;
			(*it)->position.z += rowMovementVector.z * dt;
		}
	}

	//Spawn sections
	if (rows.size() < SECTION_HEIGHT * 2)
	{
		Log::Message("Generating section...");

		if (spawnCleanSection)
		{
			generateSection(section_clean, SECTION_HEIGHT);
			spawnCleanSection = false;
		}
		else
		{
			auto roll = randomizer.getRandomIndex();
			generateSection(levels[currentLevel][roll], SECTION_HEIGHT);
		}
	}
}

void Game::LevelGenerator::generateRow(unsigned int rowDef)
{
	auto row = new std::vector<Game::WorldObject*>();
	float prevRowY = SECTION_HEIGHT / 2 + 1;
	if (!rows.empty())
	{
		auto prevRow = rows.back()->cbegin();
		prevRowY = (*prevRow)->position.y;
	}

	for (char i = 0; i < WALL_LENGTH; i++)
	{
		Game::WorldObject* wObj;

		bool isWall = (rowDef & 1 << i) > 0;
		if (isWall)
		{
			wObj = new Game::WallSegment;
		}
		else
		{
			wObj = new Game::BackgroundSegment;
		}

		row->push_back(wObj);

		//Size world object
		wObj->size.x = camera.getViewportWidth() / WALL_LENGTH;

		//Position world object
		float wallStart = -((WALL_LENGTH / 2.0f)*wObj->size.x);
		float centeredObjPosition = i * wObj->size.x + wObj->size.x / 2.0f;
		wObj->position = sf::Vector3f(
			wallStart + centeredObjPosition,
			prevRowY - wObj->size.y,
			-1);
	}

	this->rows.push(row);
}

void Game::LevelGenerator::generateSection(const unsigned int section[], int length)
{
	for (short i = 0; i < length; i++)
	{
		generateRow(section[i]);
	}
}

void Game::LevelGenerator::attemptDeleteFirstRow()
{
	if (rows.size() > 0 && !camera.shouldDrawWorldObject(*rows.front()->front()))
	{
		rows.pop();
	}
}

void Game::LevelGenerator::changeLevel()
{
	this->spawnCleanSection = true;
	this->currentLevel++;

	//TODO: update randomizer
}
