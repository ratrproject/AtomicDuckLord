#include "GameScreen.h"
#include "../Entity/Duck.h"


Screen::GameScreen::GameScreen(void)
{
}


Screen::GameScreen::~GameScreen(void)
{
}



void Screen::GameScreen::LoadScreen(){
	Entity::Duck* duck = new Entity::Duck(Map::getMap().getPixelWidth()/2 - 19, 160, 38,40);
	Entity::getEntityManager().add(duck);
}

void Screen::GameScreen::UnloadScreen()
{
	//Entity::getEntityManager().clear();
}

void Screen::GameScreen::Update()
{
	Entity::getEntityManager().update();
}

void Screen::GameScreen::Draw(System::Window& window)
{

	Map::getMap().draw(System::getWindow());
	Entity::getEntityManager().draw(window);
	
	
}