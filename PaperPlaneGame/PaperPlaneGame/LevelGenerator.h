#pragma once
#include "ControlObject.h"
#include "Camera.h"
#include "WorldObject.h"
#include "WallSegment.h"
#include "BackgroundSegment.h"
#include "WeightedRandomizer.h"
#include <queue>
#include <vector>

#define WALL_LENGTH			16
#define WALL_SIDE 			0b1000000000000001
#define WALL_CENTER_HOLE 	0b1111110000111111
#define WALL_LEFT_HOLE 		0b1000011111111111
#define WALL_RIGHT_HOLE 	0b1111111111100001
#define WALL_DOUBLE_HOLE 	0b1000011111100001

#define SECTION_HEIGHT		11
#define NUM_OF_SECTIONS		5

namespace Game
{
	class LevelGenerator : public ControlObject
	{
	public:
		LevelGenerator(Game::Camera& cam);
		~LevelGenerator();

		void Update(int deltaTime) override;
	private:
		Game::Camera camera;
		std::queue<std::vector<Game::WorldObject*>*> rows;

		const sf::Vector3f rowMovementVector = sf::Vector3f(0, 3, 0);

		#pragma region sections
		const unsigned int section_clean[SECTION_HEIGHT] = {
			WALL_SIDE,
			WALL_SIDE,
			WALL_SIDE,
			WALL_SIDE,
			WALL_SIDE,
			WALL_SIDE,
			WALL_SIDE,
			WALL_SIDE,
			WALL_SIDE,
			WALL_SIDE,
			WALL_SIDE,
		};

		const unsigned int section_center_hole[SECTION_HEIGHT] = {
			WALL_SIDE,
			WALL_SIDE,
			WALL_SIDE,
			WALL_SIDE,
			WALL_SIDE,
			WALL_SIDE,
			WALL_SIDE,
			WALL_SIDE,
			WALL_SIDE,
			WALL_SIDE,
			WALL_CENTER_HOLE,
		};

		const unsigned int section_right_hole[SECTION_HEIGHT] = {
			WALL_SIDE,
			WALL_SIDE,
			WALL_SIDE,
			WALL_SIDE,
			WALL_SIDE,
			WALL_SIDE,
			WALL_SIDE,
			WALL_SIDE,
			WALL_SIDE,
			WALL_SIDE,
			WALL_RIGHT_HOLE,
		};

		const unsigned int section_left_hole[SECTION_HEIGHT] = {
			WALL_SIDE,
			WALL_SIDE,
			WALL_SIDE,
			WALL_SIDE,
			WALL_SIDE,
			WALL_SIDE,
			WALL_SIDE,
			WALL_SIDE,
			WALL_SIDE,
			WALL_SIDE,
			WALL_LEFT_HOLE,
		};

		const unsigned int section_double_hole[SECTION_HEIGHT] = {
			WALL_SIDE,
			WALL_SIDE,
			WALL_SIDE,
			WALL_SIDE,
			WALL_SIDE,
			WALL_SIDE,
			WALL_SIDE,
			WALL_SIDE,
			WALL_SIDE,
			WALL_SIDE,
			WALL_DOUBLE_HOLE,
		};
		#pragma endregion

		#pragma region levels
		const unsigned int* levels[1][NUM_OF_SECTIONS] = {
			{
				section_clean,
				section_center_hole,
				section_right_hole,
				section_left_hole,
				section_double_hole
			}
		};

		const int levelWeights[1][NUM_OF_SECTIONS] = {
			{
				1,
				5,
				2,
				2,
				5
			}
		};
		#pragma endregion

		bool spawnCleanSection = true;
		int currentLevel = 0;
		Game::WeightedRandomizer randomizer = Game::WeightedRandomizer(levelWeights[currentLevel], NUM_OF_SECTIONS);


		void generateRow(unsigned int rowDef);
		void generateSection(const unsigned int section[], int length);
		void attemptDeleteFirstRow();
		void changeLevel();
	};
}
