//
// game.cpp
// 

// Engine includes.
#include "GameManager.h"
#include "LogManager.h"
#include "Pause.h"
#include "ResourceManager.h"
#include "WorldManager.h"
 
// Game includes.
#include "GameStart.h"
#include "Star.h"
#include "Hero.h"
#include "Enemy.h"
#include "Wall.h"

// Function prototypes.
void loadResources(void);
void populateWorld(void);
 
int main(int argc, char *argv[]) {
  LogManager &log_manager = LogManager::getInstance();
  WorldManager &world_manager = WorldManager::getInstance();
  world_manager.startUp();
  // Start up game manager.
  GameManager &game_manager = GameManager::getInstance();
  if (game_manager.startUp())  {
    log_manager.writeLog("Error starting game manager!");
    game_manager.shutDown();
    return 0;
  }

  // Set flush of logfile during development (when done, make false).
  log_manager.setFlush(true);

  // Show splash screen.
  splash();

  // Load game resources.
  loadResources();

  // Populate game world with some objects.
  populateWorld();
 
  // Enable player to pause game (press F10).
  new Pause;

  // Run game (this blocks until game loop is over).
  game_manager.run();
 
  // Shut everything down.
  game_manager.shutDown();
}
 
// Load resources (sprites, here).
void loadResources(void) {
  ResourceManager &resource_manager = ResourceManager::getInstance();
  resource_manager.loadSprite("sprites/enemy-spr.txt", "enemy");
  resource_manager.loadSprite("sprites/hero-spr.txt", "hero");
  resource_manager.loadSprite("sprites/invincibility-spr.txt", "invincibility");
  resource_manager.loadSprite("sprites/wall-spr.txt", "wall");
  resource_manager.loadSprite("sprites/crouch-spr.txt", "duck");
}
 
// Populate world with some objects.
void populateWorld(void) {
 
	new Hero;
	//new Enemy;
	new Wall;
	
  // Create GameStart object.
	new GameStart();
}
