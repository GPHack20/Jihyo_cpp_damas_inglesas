#pragma once//macro protection
#include <SFML/Graphics.hpp>//Graphics library
#include "Button.h"//Create-Control buttons
#include "Game.h"//Game Interface
#include "Slider.h"//Slider object in the options
///Create the menu interface when the program start
class Menu
{
private:
    ///Set the configurations in the option 'OPTIONS'
    void Options();

    //Player options: 1=human 2=AI 3=RandomMoves
    int player1=1;
    int player2=1;

public:
    ///Costructor the menu interface when the program start
    Menu(size_t with, size_t height);
    ///Destructor the menu interface when the program start
    ~Menu();
    ///Loop with the execution of the program
    void Run();

private:
    ///Game interface
    Game* m_game;
    ///Draw the menu interface
    void Draw();
    ///COntrol events
    void ProcessEvents();
    ///Buttons of the main Windows
    Button* m_buttonsPointers[4];
    ///Button return in the option 'OPTIONS'
    Button* m_optionReturnButton;

    sf::Font p_font;
    Button* b_player1;
    Button* b_player2;
    sf::Text t_player1;
    sf::Text t_player2;

    ///Slider - AI 1 difficulty
    Slider* s_AI1;
    ///Slider - AI 2 difficulty
    Slider* s_AI2;
    ///Slider - Volume
    Slider* m_volumeSlider;
    ///System volume
    float volume;
    ///AI 1 difficulty
    int v_AI1;
    ///AI 2 difficulty
    int v_AI2;
    ///Label array with text in the option 'Option' {A1,numeric valueA1,Volume,numeric value volume,A2,numeric valueA2}
    sf::Text optionsText[6];
    ///Background texture
    sf::Texture m_backgroundTexture;
    ///Background sprite
    sf::Sprite m_backgroundSprite;
    ///Logo of program name texture
    sf::Texture m_logoTexture;
    ///Logo of program name sprite
    sf::Sprite m_logoSprite;
    ///Logo of program texture
    sf::Texture m_gameLogoTexture;
    ///Logo of program sprite
    sf::Sprite m_gameLogoSprite;
    ///Version font
    sf::Font m_font;
    ///Version text
    sf::Text m_gameVersion;
    ///Window that can serve as a target for 2D drawing - As a pointer to access and change from anywhere
    sf::RenderWindow* m_window;
    ///Verify the program status EXIT
    bool m_exit;
    ///Height - Windows
    size_t m_windowHeight;
    ///Width - Windows
    size_t m_windowWidth;
    ///Object music in the game
    sf::Music m_music;
    ///Set status of credits to visualize
    bool m_credits;
    ///Sprite to fill all the window - Sprite
    sf::Sprite m_creditsSprite;
     ///Sprite to fill all the window - Texture
    sf::Texture m_creditsTexture;
    
    ///Animation - Credits
    sf::Texture t_Jihyo;
    sf::Sprite s_Jihyo;
    sf::Thread m_thread;

    void spriteAnimation();
    int x=0,y=0;
    int x1,y1,h,a;
    
    ///Splash
    bool execute=false;
    sf::Texture t_splash;
    sf::Sprite s_splash;  
    
    ///Set status of options to visualize
    bool m_options;    
};