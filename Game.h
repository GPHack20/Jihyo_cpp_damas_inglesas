#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <vector>
#include <SDL2/SDL.h>
#include "Engine.h"

class Game
{
private:
	/// Draws all stuff on scene
	void draw();

	/// Process all events
	void processEvents();

	/// Inits level and players (also after endGame)
	void initGameplay(int player1,int player2,int v_AI1, int v_AI2);


///Set pause 
void pause();
void GUI_LAST();

public:
	///Game Interfaze
	Game(sf::RenderWindow * window);
	///Destroy the game
	~Game();
	///Game initialize	
	void Initialize(float musicVolume, int v_AI1, int v_AI2, int player1, int player2);
	///Game running
	bool Run();	

private:
	///Dimension of the window
	unsigned m_windowWidth;
	unsigned m_windowHeight;
	///Boolean var - go to menu
	bool enterMenu;
	///Boolean var - exit
	bool m_exit;

	///Font to the game
	sf::Font* m_font;

	///Render the game interface
	sf::RenderWindow* m_window;

	///Boolean var - to end the game
	bool m_endOfGame;
	
	///Set new music to the game
	sf::Music m_music;
	sf::String playerWin;

	sf::Sprite fichaS;
    sf::Texture fichaT;
};
