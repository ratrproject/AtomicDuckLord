#include "TitleScreen.h"

Screen::TitleScreen::TitleScreen(void)
{
}


Screen::TitleScreen::~TitleScreen(void)
{
}



void Screen::TitleScreen::LoadScreen(){
	//make all entities for this screen and then put them into the entity manager
	Entity::getEntityManager().clear();
	Map::getMap().spawnEntities();
}

void Screen::TitleScreen::UnloadScreen()
{	
	//Entity::getEntityManager().clear();
}

void Screen::TitleScreen::Update(){
	
	//Entity::getEntityManager().update();

	if(System::getWindow().getKeyboard().anyKeyHit())
		{
			GameScreen* gameScreen;
			gameScreen = new GameScreen();	
			ScreenManager::getInstance().LoadScreen(gameScreen);//switch to the Game Screen
		}
	
}

void Screen::TitleScreen::Draw(System::Window &window){
		Map::getMap().draw(System::getWindow());
		
		Entity::getEntityManager().draw(window);
	
	// Draw the string
	window.drawText(Map::getMap().getPixelWidth()/2 - 260, 240, "Press A Key", 48, "PressStart2P.ttf");
}