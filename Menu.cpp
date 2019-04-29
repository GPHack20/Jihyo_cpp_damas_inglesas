#include "Menu.h"
#include <iostream>

using namespace std;

///Set elements and values to the option "OPTIONS"
void Menu::Options()
{
	volume = m_volumeSlider->GetValue() * 100.f;//Get the volume vale from "volumeSlider"
	//**Conditions to set defauts values according a especial positions in the volume Slider
	if (m_volumeSlider->GetValue() == 0)
	{
		m_volumeSlider->SetValue(0.6f);
		volume = 60;
	}
	else if (volume < 10.f)
	{
		volume = 0;
	}
	else if(volume > 87.f)
	{
		volume = 100;
	}
	//**
	m_music.setVolume(volume);//Set the volume value in the music game 
	optionsText[3].setString(std::to_string(static_cast<int>(volume)) + '%');//Set numeric value volume

	v_AI1 = s_AI1->GetValue() * 9.f;//Get the AI1 value
	//**Conditions to set defauts values according a especial positions in the AI1 Slider
	if (s_AI1->GetValue() == 0)
	{
		s_AI1->SetValue(0.3f);
		v_AI1 = 3;
	}
	else if (v_AI1 < 0.6f)
	{
		v_AI1 = 2;
	}
	else if (v_AI1 >= 8.5f)
	{
		v_AI1 = 9;
	}
	//**
	v_AI1 = static_cast<int>(v_AI1)+1;//Set the value in the variable float
	optionsText[1].setString(std::to_string(static_cast<int>(v_AI1)) + "");//Set the depth in the array with labels 


	v_AI2 = s_AI2->GetValue() * 9.f;//Get the AI2 value
	//**Conditions to set defauts values according a especial positions in the AI1 Slider
	if (s_AI2->GetValue() <= 0)
	{
		s_AI2->SetValue(0.3f);
		v_AI2 = 3;
	}
	else if (v_AI2 < 0.6f)
	{
		v_AI2 = 2;
	}
	else if (v_AI2 >= 8.5f)
	{
		v_AI2 = 9;
	}
	//**
	v_AI2 = static_cast<int>(v_AI2)+1;//Set the value in the variable float
	optionsText[5].setString(std::to_string(static_cast<int>(v_AI2)) + "");//Set the depth in the array with labels 


}

///Constructor of the menu interface when the program start with width and height arguments
Menu::Menu(size_t width, size_t height):m_thread(&Menu::spriteAnimation,this)
{
	m_window = new sf::RenderWindow(); //Window that can serve as a target for 2D drawing - new Object
	m_windowWidth = width;//Set width as a property from argument
	m_windowHeight = height;////Set height as a property from argument
	m_window->create(sf::VideoMode(static_cast<int>(m_windowWidth), static_cast<int>(m_windowHeight)), "Jihyo | English drafts!", sf::Style::Close);//Create the Windows
	m_window->setFramerateLimit(60);// Limit the framerate to 60 frames per second (this step is optional)
	int bx=m_window->getSize().x/4;
	int by=m_window->getSize().y/8;
	//Fill and create new buttons to add in the main Windows
	m_buttonsPointers[0] = new Button(sf::Vector2f(m_window->getSize().x / 2 - bx, m_window->getSize().y / 2.5f), sf::Vector2i(bx*2, by), "res/img/pressButton.png", "res/img/unpressButton.png", "START");
	m_buttonsPointers[1] = new Button(sf::Vector2f(m_window->getSize().x / 2 - bx, m_window->getSize().y / 2.5f + by*1.1f), sf::Vector2i(bx*2, by), "res/img/pressButton.png", "res/img/unpressButton.png", "OPTIONS");
	m_buttonsPointers[2] = new Button(sf::Vector2f(m_window->getSize().x / 2 - bx, m_window->getSize().y / 2.5f + by*2.2f), sf::Vector2i(bx*2, by), "res/img/pressButton.png", "res/img/unpressButton.png", "CREDITS");
	m_buttonsPointers[3] = new Button(sf::Vector2f(m_window->getSize().x / 2 - bx, m_window->getSize().y / 2.5f + by*3.3f), sf::Vector2i(bx*2, by), "res/img/pressButton.png", "res/img/unpressButton.png", "EXIT");

	//Sliders {Play time and Volumen} as object
	s_AI1 = new Slider(Slider::horizontal, sf::Vector2f(m_windowWidth/1.35f, m_windowWidth/3), 100, 30, m_windowWidth/1.35f+10, 80, 20, 10, sf::Color(0, 148, 154), sf::Color(229, 229, 229), sf::Color(160, 160, 160), sf::Color(255, 255, 255), false);
	m_volumeSlider = new Slider(Slider::horizontal, sf::Vector2f(m_windowWidth/1.35f, m_windowWidth/3+by*1.1f), 100, 30, m_windowWidth/1.35f+10, 80, 20, 10, sf::Color(0, 148, 154), sf::Color(229, 229, 229), sf::Color(160, 160, 160), sf::Color(255, 255, 255), false);
	s_AI2 = new Slider(Slider::horizontal, sf::Vector2f(m_windowWidth/1.35f, m_windowWidth/3+by*2.2f), 100, 30, m_windowWidth/1.35f+10, 80, 20, 10, sf::Color(0, 148, 154), sf::Color(229, 229, 229), sf::Color(160, 160, 160), sf::Color(255, 255, 255), false);
	//**Set properties to labels in the option 'OPTIONS' 
	for (int i = 0; i < 6; ++i)
	{
		optionsText[i].setColor(sf::Color::Cyan);
		optionsText[i].setCharacterSize(20);
		optionsText[i].setFont(m_font);
		optionsText[i].setStyle(sf::Text::Bold);
	}
	optionsText[0].setString("AI 1 depth:");
	optionsText[1].setString("3");
	optionsText[2].setString("VOLUME LEVEL:");
	optionsText[3].setString("60%");
	optionsText[4].setString("AI 2 depth:");
	optionsText[5].setString("3");
	optionsText[0].setPosition(m_windowWidth/3-bx, m_windowWidth/3);
	optionsText[1].setPosition(m_windowWidth/1.8f, m_windowWidth/3);
	optionsText[2].setPosition(m_windowWidth/3-bx, m_windowWidth/3+by*1.1f);
	optionsText[3].setPosition(m_windowWidth/1.8f, m_windowWidth/3+by*1.1f);
	optionsText[4].setPosition(m_windowWidth/3-bx, m_windowWidth/3+by*2.2f);
	optionsText[5].setPosition(m_windowWidth/1.8f, m_windowWidth/3+by*2.2f);
	//**

	//Set default properties to the play time and volumen when start the game
	s_AI1->SetValue(0.4f);
	v_AI1 = 3;
	s_AI2->SetValue(0.4f);
	v_AI2 = 3;
	m_volumeSlider->SetValue(0.6f);
	volume = 5;

	//**Create sprites with textures for the main Window
	m_backgroundTexture.loadFromFile("res/img/menuBackground.png");
	m_backgroundTexture.setSmooth(true);
	m_backgroundSprite.setTexture(m_backgroundTexture);
	m_backgroundSprite.setScale(sf::Vector2f(m_window->getSize().x / 1080, m_window->getSize().y / 1365));
	m_backgroundSprite.setScale(sf::Vector2f((float)m_window->getSize().x / (float)m_backgroundTexture.getSize().x, (float)m_window->getSize().y / (float)m_backgroundTexture.getSize().y));

	m_logoTexture.loadFromFile("res/img/menuPiGames.png");
	m_logoTexture.setSmooth(true);
	m_logoSprite.setTexture(m_logoTexture);
	m_logoSprite.setScale(sf::Vector2f((float)m_window->getSize().x / (float)m_logoTexture.getSize().y / 8.f, (float)m_window->getSize().y / (float)m_logoTexture.getSize().y / 8.f));

	m_gameLogoTexture.loadFromFile("res/img/menuLogo.png");
	m_gameLogoTexture.setSmooth(true);
	m_gameLogoSprite.setTexture(m_gameLogoTexture);
	m_gameLogoSprite.setScale(sf::Vector2f((float)m_window->getSize().x / (float)m_gameLogoTexture.getSize().x, (float)m_window->getSize().y / (float)m_gameLogoTexture.getSize().y / 7.f));
	m_gameLogoSprite.setPosition(sf::Vector2f(m_window->getSize().x / 2.f - (m_gameLogoTexture.getSize().x * m_gameLogoSprite.getScale().x) / 2.f, m_window->getSize().y / 5.f - 30));
	//**

	//**Version
	m_font.loadFromFile("res/fonts/micross.ttf");
	m_gameVersion.setFont(m_font);
	m_gameVersion.setColor(sf::Color(32, 32, 32, 128));
	m_gameVersion.setString("Version 0.0.1");
	m_gameVersion.setScale(0.6f, 0.6f);
	m_gameVersion.setPosition(m_gameLogoSprite.getPosition().x + m_gameLogoTexture.getSize().x - 50, m_gameLogoSprite.getPosition().y + m_logoTexture.getSize().y);
	//**

	//Local bounding rectangle of the entity
	sf::FloatRect textRect = m_gameVersion.getLocalBounds();
	m_gameVersion.setPosition(m_gameLogoSprite.getPosition().x + m_gameLogoTexture.getSize().x * m_gameLogoSprite.getScale().x - textRect.width *0.8f, m_gameLogoSprite.getPosition().y + m_gameLogoTexture.getSize().y * m_gameLogoSprite.getScale().y);
	

	if (!m_music.openFromFile("res/audio/menu.wav"))
	{
		std::cerr << "[!] Cannot load resource: 'res/audio/menu.wav'" << std::endl;
		std::cin.get();
		std::exit(1);
	}

	//Music properties
	m_music.play();
	m_music.setLoop(true);
	m_music.setVolume(volume);

	m_credits = false;//Set false to see only the menu at the begging

	if (!m_creditsTexture.loadFromFile("res/img/credits.png"))
	{
		std::cerr << "[!] Cannot load resource: 'res/img/credits.png'" << std::endl;
		std::cin.get();
		std::exit(1);
	}
	m_creditsSprite.setTexture(m_creditsTexture);//Fill new sprite to fill all the windows with a photo of information 
	m_creditsSprite.setScale(sf::Vector2f(m_window->getSize().x / 1080, m_window->getSize().y / 1365));
	m_creditsSprite.setScale(sf::Vector2f((float)m_window->getSize().x / (float)m_creditsTexture.getSize().x, (float)m_window->getSize().y / (float)m_creditsTexture.getSize().y));

	if (!t_Jihyo.loadFromFile("res/img/Jihyo.png"))
	{
		std::cerr << "[!] Cannot load resource: 'res/img/Jihyo.png'" << std::endl;
		std::cin.get();
		std::exit(1);
	}
	t_Jihyo.setSmooth(true);
	s_Jihyo.setTexture(t_Jihyo);  
	//s_Jihyo.move(35.f,190.f);
	s_Jihyo.setPosition(35.f,m_windowHeight/2.3); //s_Jihyo.setPosition(35.f,190.f); 
	s_Jihyo.setTextureRect(sf::IntRect(0,0,300,300));  //s_Jihyo.setTextureRect(sf::IntRect(0,0,268,400)); 
	s_Jihyo.setScale(sf::Vector2f((float)m_window->getSize().x/(float)t_Jihyo.getSize().x,(float)m_window->getSize().y/(float)t_Jihyo.getSize().y));

	if (!t_splash.loadFromFile("res/img/splash.png"))
	{
		std::cerr << "[!] Cannot load resource: 'res/img/splash.png'" << std::endl;
		std::cin.get();
		std::exit(1);
	}
	t_splash.setSmooth(true);
	s_splash.setTexture(t_splash);  
	s_splash.setPosition(0,0);
	s_splash.setTextureRect(sf::IntRect(0,0,800,450));  
	s_splash.setScale(sf::Vector2f((float)m_windowWidth/800,(float)m_window->getSize().y/450));
	

	m_options = false;//Set false to see only the menu at the begging

	m_optionReturnButton = new Button(sf::Vector2f(25, m_windowHeight - 100), sf::Vector2i(bx*2, by), "res/img/pressButton.png", "res/img/unpressButton.png", "RETURN");

	b_player1 = new Button(sf::Vector2f((m_windowWidth/2-m_windowWidth/3)/2, 50), sf::Vector2i(m_windowWidth/3, by), "res/img/pressButton.png", "res/img/unpressButton.png", "PLAYER 1");
	b_player2 = new Button(sf::Vector2f(m_windowWidth/2+(m_windowWidth/2-m_windowWidth/3)/2, 50), sf::Vector2i(m_windowWidth/3, by), "res/img/pressButton.png", "res/img/unpressButton.png", "PLAYER 2");

	//**Player 1 text
	p_font.loadFromFile("res/fonts/micross.ttf");
	t_player1.setFont(p_font);
	t_player1.setColor(sf::Color(32, 32, 32, 128));
	t_player1.setString("HUMAN");
	t_player1.setScale(0.6f, 0.6f);
	t_player1.setPosition(b_player1->m_position.x+b_player1->m_size.x/4, b_player1->m_position.y+2);

	//**
	//**Player 2 text
	p_font.loadFromFile("res/fonts/micross.ttf");
	t_player2.setFont(p_font);
	t_player2.setColor(sf::Color(32, 32, 32, 128));
	t_player2.setString("HUMAN");
	t_player2.setScale(0.6f, 0.6f);
	t_player2.setPosition(b_player2->m_position.x+b_player2->m_size.x/4, b_player2->m_position.y+2);
	//**

}

///Destroyer of the main window menu
Menu::~Menu()
{

}

///Loop with the execution of the program.
void Menu::Run()
{
	m_exit = false;
	while (!m_exit)
	{
		Draw();
		ProcessEvents();
		if(execute==false){//Show spash
			h=2250;a=4000;	
			x1=800;y1=450;
			m_thread.launch();			
			s_splash.setTextureRect(sf::IntRect(x,y,800,450)); 
		}
		if (m_options)
			Options();
		if(m_credits){//Show animation credits
			h=1500;a=600;	
			x1=300;y1=300;   //x1=268;y1=400;
			m_thread.launch();
			s_Jihyo.setTextureRect(sf::IntRect(x,y,300,300)); 					
		}
	}
}

void Menu::spriteAnimation(){
	sf::sleep(sf::seconds(0.05f));
	if(x<=a){
      x=x+x1;
    }else{
      y=y+y1;
      x=0;
    } 
	if(y>=h&&x>=a){
		x=0;y=0;execute=true;
	}			
}

void Menu::Draw()
{
	//**Run splash
	if(execute==false){		
		m_window->draw(s_splash);
		m_window->display();
		return;
	}
	if (execute==true&&m_credits==false){
		x=0;y=0;
	}
	//**

	m_window->clear(sf::Color::White);//Clear elements of the windows
	m_window->draw(m_backgroundSprite);//Set the background sprite as background
	
	if (m_credits)//if m_credits is true show an image with credits - Menu option
	{
		m_window->draw(m_creditsSprite);
		m_window->draw(s_Jihyo);
		m_window->display();//Show
		return;
	}

	if (m_options)//if m_options is true show elements of option 'OPTIONS' - Menu option
	{
		m_window->draw(*b_player1->GetSpritePointer());
		m_window->draw(*b_player1->GetTextPointer());
		m_window->draw(*b_player2->GetSpritePointer());
		m_window->draw(*b_player2->GetTextPointer());

		m_window->draw(t_player1);
		m_window->draw(t_player2);
		
		m_window->draw(*m_optionReturnButton->GetSpritePointer());
		m_window->draw(*m_optionReturnButton->GetTextPointer());
		//Draw sliders 
		m_window->draw(*s_AI1);
		m_window->draw(*s_AI2);
		m_window->draw(*m_volumeSlider);
		for (int i = 0; i < 6; ++i)//Draw labels
		{
			m_window->draw(optionsText[i]);
		}
		m_window->display();//Show
		return;
	}
	
	//**Draw the main Windows
	m_window->draw(m_backgroundSprite);
	m_window->draw(m_logoSprite);

	m_window->draw(m_gameLogoSprite);

	m_window->draw(m_gameVersion);

	m_window->draw(*m_buttonsPointers[0]->GetSpritePointer());
	m_window->draw(*m_buttonsPointers[0]->GetTextPointer());

	m_window->draw(*m_buttonsPointers[1]->GetSpritePointer());
	m_window->draw(*m_buttonsPointers[1]->GetTextPointer());

	m_window->draw(*m_buttonsPointers[2]->GetSpritePointer());
	m_window->draw(*m_buttonsPointers[2]->GetTextPointer());

	m_window->draw(*m_buttonsPointers[3]->GetSpritePointer());
	m_window->draw(*m_buttonsPointers[3]->GetTextPointer());
	//**

	m_window->display();
}

void Menu::ProcessEvents()//
{
	sf::Event event;//Control events 
	sf::Vector2f mouse = sf::Vector2f(sf::Mouse::getPosition(*m_window).x, sf::Mouse::getPosition(*m_window).y);//Get position x and y of the mouse
	while (m_window->pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			m_exit = true;
			break;
		}
		if (m_options)
		{
			//**Update the value of Sliders according the positions and events of the mouse
			s_AI2->Update(sf::Mouse::getPosition(*m_window), &event);
			s_AI1->Update(sf::Mouse::getPosition(*m_window), &event);
			m_volumeSlider->Update(sf::Mouse::getPosition(*m_window), &event);
			//**
			if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left && !m_credits)
			{
				m_optionReturnButton->Update(sf::Mouse::getPosition(*m_window), false);//Check and uncheck return button
				if (m_optionReturnButton->GetSpritePointer()->getGlobalBounds().contains(mouse))//Verify if select that button
					m_options = false;
				
				b_player1->Update(sf::Mouse::getPosition(*m_window), false);//Check and uncheck player1 button
				if (b_player1->GetSpritePointer()->getGlobalBounds().contains(mouse))//Verify if select that button
				{
					player1=player1+1;
					if(player1>3)
						player1=1;
					switch (player1)
					{
					case 1:
						t_player1.setString("HUMAN");
						player1=1;
						break;
					case 2:
						t_player1.setString("AI");
						player1=2;
						break;	
					case 3:
						t_player1.setString("STUPID AI");
						player1=3;
						break;					
					}
				}
					
					b_player2->Update(sf::Mouse::getPosition(*m_window), false);//Check and uncheck player2 button
				if (b_player2->GetSpritePointer()->getGlobalBounds().contains(mouse))//Verify if select that button
				{
					player2=player2+1;
					if(player2>3)
						player2=1;
					switch (player2)
					{
					case 1:
						t_player2.setString("HUMAN");
						player2=1;
						break;
					case 2:
						t_player2.setString("AI");
						player2=2;
						break;	
					case 3:
						t_player2.setString("STUPID AI");
						player2=3;
						break;					
					}

				}
			}
		}
		//**Events to buttons of the menu 
		else if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left && !m_credits)
		{
			m_buttonsPointers[0]->Update(sf::Mouse::getPosition(*m_window), false);
			m_buttonsPointers[1]->Update(sf::Mouse::getPosition(*m_window), false);
			m_buttonsPointers[2]->Update(sf::Mouse::getPosition(*m_window), false);
			m_buttonsPointers[3]->Update(sf::Mouse::getPosition(*m_window), false);
			
			if (m_buttonsPointers[0]->GetSpritePointer()->getGlobalBounds().contains(mouse))//Start new game
			{
				m_music.stop();	//Stos last music 			
				m_game = new Game(m_window);//Start new game
				m_game->Initialize(volume, v_AI1,v_AI2,player1,player2);
				m_exit = !m_game->Run();
				m_music.play();
				delete m_game;				
				return;
			}
			else   
			{
				if (m_buttonsPointers[1]->GetSpritePointer()->getGlobalBounds().contains(mouse))//Select Options
				{
					m_options = true;
				}
				if (m_buttonsPointers[2]->GetSpritePointer()->getGlobalBounds().contains(mouse))//Select Credits
					m_credits = true;

				if (m_buttonsPointers[3]->GetSpritePointer()->getGlobalBounds().contains(mouse))//Select Exit
					m_exit = true;
			}
		}
		//**
		//**Check buttons
		if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left && !m_credits)
		{
			if (m_options)
			{
				m_optionReturnButton->Update(sf::Mouse::getPosition(*m_window), true);
				b_player1->Update(sf::Mouse::getPosition(*m_window), true);
				b_player2->Update(sf::Mouse::getPosition(*m_window), true);
				break;
			}

			m_buttonsPointers[0]->Update(sf::Mouse::getPosition(*m_window), true);
			m_buttonsPointers[1]->Update(sf::Mouse::getPosition(*m_window), true);
			m_buttonsPointers[2]->Update(sf::Mouse::getPosition(*m_window), true);
			m_buttonsPointers[3]->Update(sf::Mouse::getPosition(*m_window), true);
		}
		//**
		if (m_credits)//Exit from the credits with any key
			if (event.type == sf::Event::KeyPressed)
				m_credits = false;

		if (execute==false)//Skip from the splash with any key
			if (event.type == sf::Event::KeyPressed)
				execute = true;

		if (m_options)//Exit from options with Escape
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
				m_options = false;
	}
}