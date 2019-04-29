#include "Game.h"

Board *board;

//Players
Player *uno;
Player *dos;
Player *current;
Board::Decision des;
bool turn=true;
bool cmp;
Move *m=new Move();

sf::Clock clock_m;
sf::Time time_mf;

Game::Game(sf::RenderWindow *window)//:m_thread(&Game::SleepMoves,this) 
{
	m_window = window;

	m_windowWidth = m_window->getSize().x;
	m_windowHeight = m_window->getSize().y;

	m_font = new sf::Font();
}

Game::~Game()
{
	delete m_font;
	delete uno;
	delete dos;
}

void Game::Initialize(float musicVolume, int v_AI1, int v_AI2, int player1, int player2)
{
	initGameplay(player1,player2,v_AI1,v_AI2);

	if (!m_music.openFromFile("res/audio/game.wav"))
	{
		std::cerr << "[!] Cannot load resource: 'res/audio/game.wav'" << std::endl;
		std::cin.get();
		std::exit(1);
	}
	if (!m_font->loadFromFile("res/fonts/Cat.ttf"))
	{
		std::cerr << "[!] Cannot load file: \"" << "res/fonts/Cat.ttf" << "\". Exiting...\n";
		std::cin.get();
		exit(1);
	}

	m_music.setVolume(musicVolume);
	m_music.play();
	m_music.setLoop(true);

	fichaT.loadFromFile("res/img/CheckerSprites.png");
	fichaT.setSmooth(true);
	fichaS.setTexture(fichaT);
	fichaS.setTextureRect(sf::IntRect(0,0,80,80)); 
	fichaS.setScale(sf::Vector2f((float)m_window->getSize().x /8 / (float)fichaT.getSize().y, (float)m_window->getSize().y /8/ (float)fichaT.getSize().y));
}

bool Game::Run()
{
	m_exit = false;	
	while (!m_exit)
	{		
		processEvents();
		draw();
	}
	return enterMenu;
}

void Game::draw()
{
	///Clear the window
	m_window->clear();

	///Cell color of the table
	sf::Color colorCell;
	
	///Fill, draw and re draw the table
	for (int x = 0; x < 8; ++x)
	{
		for (int y = 0; y < 8; ++y)
		{
			if ((x + y) % 2)
			{
				colorCell = sf::Color::Cyan;
			}
			else
			{
				colorCell = sf::Color::White;
			}			

			///Draw each square 
			sf::RectangleShape cell_(sf::Vector2f(m_windowWidth / 8, m_windowHeight / 8));
			cell_.setFillColor(colorCell);
			cell_.setPosition(x * m_windowWidth / 8, y * m_windowHeight / 8);	

			
			
			m_window->draw(cell_);

			switch (board->getPiece(y,x))
			{
				case 0:
				break;
				case 1:
				fichaS.setTextureRect(sf::IntRect(0,0,80,80));
				fichaS.setPosition((x * m_windowWidth / 8), (y * m_windowHeight / 8));
				m_window->draw(fichaS);
				break;
				case 2:
				fichaS.setTextureRect(sf::IntRect(80*1,0,80,80));
				fichaS.setPosition((x * m_windowWidth / 8), (y * m_windowHeight / 8));
				m_window->draw(fichaS);
				break;
				case 3:
				fichaS.setTextureRect(sf::IntRect(80*2,0,80,80));
				fichaS.setPosition((x * m_windowWidth / 8), (y * m_windowHeight / 8));
				m_window->draw(fichaS);
				break;
				case 4:
				fichaS.setTextureRect(sf::IntRect(80*3,0,80,80));
				fichaS.setPosition((x * m_windowWidth / 8), (y * m_windowHeight / 8));
				m_window->draw(fichaS);
				break;
			}				
		}
	}
	//Selected cell
	if(m->start!=NULL){
				colorCell = sf::Color(255,255,255,128);
				sf::RectangleShape cell_(sf::Vector2f(m_windowWidth / 8, m_windowHeight / 8));
				cell_.setFillColor(colorCell);
				cell_.setPosition((m->start->y)* m_windowWidth / 8, (m->start->x)* m_windowHeight / 8);
				m_window->draw(cell_);
	}
	
	m_window->display();
}

void Game::processEvents()
{
	if (m_exit)
	{
		return; // if exiting: skip event processing!
	}
	
	sf::Event event;
	sf::Vector2f mouse = sf::Vector2f(sf::Mouse::getPosition(*m_window).x, sf::Mouse::getPosition(*m_window).y);//Get position x and y of the mouse

	while (m_window->pollEvent(event))
	{
		
		if (event.type == sf::Event::Closed)
		{
			m_exit = true;
			enterMenu = false;
			break;
		}


		if (!m_endOfGame)
		{
			
			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
			{
				pause();
				m_music.play();
			}
			cmp=false;		
			if((current->name=="Stupid AI 1")||(current->name=="Stupid AI 2")){	//Generar cualquier evento para mover			
				if(clock_m.getElapsedTime().asMilliseconds()>=sf::milliseconds(50).asMilliseconds()){
				cout<<current->name<<endl;
				des=current->makeMove(board);				
				cmp=true;
				clock_m.restart();
				}
			}
			//Insertar AI here					
			else if(((current->name=="AI 1")||(current->name=="AI 2")))  {	
				
				if(uno->name=="AI 1"&&dos->name=="AI 2"){
					if((event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space)){
						if(clock_m.getElapsedTime().asMilliseconds()>=sf::milliseconds(50).asMilliseconds()){
						cout<<current->name<<endl;
						des=current->makeAImove(board,current->side);				
						cmp=true;
						clock_m.restart();
						}
					}
				}
				else{
					if(clock_m.getElapsedTime().asMilliseconds()>=sf::milliseconds(50).asMilliseconds()){
						cout<<current->name<<endl;
						des=current->makeAImove(board,current->side);				
						cmp=true;
						clock_m.restart();
					}
				}
				
				// if((uno->name!="AI 1")&&(dos->name!="AI 2"))
				// {
				// if(clock_m.getElapsedTime().asMilliseconds()>=sf::milliseconds(50).asMilliseconds()){
				// cout<<current->name<<endl;
				// des=current->makeAImove(board,current->side);				
				// cmp=true;
				// clock_m.restart();
				// }
				// }
				
			}
			/////
			else
			{
			if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left&&turn){
				cout<<uno->name<<endl;
				const int xx=mouse.x/(m_windowWidth/8);
				const int yy=mouse.y/(m_windowHeight/8);
				if(m->getStart()==NULL){
					m->setStart(yy,xx);	
					cout<<m->getStart()->x<<" - "<<m->getStart()->y;
					cout<<" Seleccionado"<<endl;	
									
				}else{					
					cout<<yy<<" - "<<xx;
					cout<<" A mover"<<endl;	
					m=new Move(m->getStart()->x,m->getStart()->y,yy,xx);
					//cout<<"Tabla:"<<board->getPiece(xx,yy)<<endl;
					des=current->makeMove(m,board);
					//cout<<"Tabla:"<<board->getPiece(5,2)<<endl;
					//cout<<"Des:"<<des<<endl;
					m->start=NULL;
					m->end=NULL;
					cmp=true;
				}
						
			}
			if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left&&!turn){
				cout<<dos->name<<endl;
				const int xx=mouse.x/(m_windowWidth/8);
				const int yy=mouse.y/(m_windowHeight/8);
				if(m->getStart()==NULL){
					m->setStart(yy,xx);	
					cout<<m->getStart()->x<<" - "<<m->getStart()->y;
					cout<<" Seleccionado"<<endl;	
									
				}else{					
					cout<<yy<<" - "<<xx;
					cout<<" A mover"<<endl;	
					m=new Move(m->getStart()->x,m->getStart()->y,yy,xx);
					//cout<<"Tabla:"<<board->getPiece(xx,yy)<<endl;
					des=current->makeMove(m,board);
					//cout<<"Tabla:"<<board->getPiece(5,2)<<endl;
					//cout<<"Des:"<<des<<endl;
					m->start=NULL;
					m->end=NULL;
					cmp=true;
				}	
			}
			}
			if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Right){
				//Something to rightclick
			}
			if(cmp){
			if(des==Board::Decision::FAILED_INVALID_DESTINATION||des==Board::Decision::FAILED_MOVING_INVALID_PIECE){
				cout<<"Move Failed!"<<endl;
			}
			else if(des==Board::Decision::COMPLETED){
				if(board->getNumBlackPieces()==0){
					playerWin=dos->name+" win with "+to_string(board->getNumWhitePieces())+" pieces left";
					GUI_LAST();
				}
				if(board->getNumWhitePieces()==0){
					playerWin=uno->name+" win with "+to_string(board->getNumBlackPieces())+" pieces left";
					GUI_LAST();
				}
				if(turn)
					current=dos;
				else
					current=uno;
				turn=!turn;				
			}
			else if(des==Board::Decision::ADDITIONAL_MOVE){
				cout<<"Additional Move"<<endl;
			}		
			vector<Move*>all=board->getAllValidMoves(current->side);
			cout<<"TOTAL POSSIBLE MOVES=>"<<all.size()<<endl;	
			if(all.size()==0||des==Board::Decision::GAME_ENDED){
				if(current->side == 1)
                    {
                        playerWin=dos->name+" win with "+to_string(board->getNumWhitePieces())+" pieces left";
						GUI_LAST();

                    }
                    else {
                        playerWin=uno->name+" win with "+to_string(board->getNumBlackPieces())+" pieces left";
						GUI_LAST();
                    }
                    break;
			}
			}
		}
	}
}

//Films to watch: Scorpion, Person of interest, Halt and catch fire

void Game::initGameplay(int player1,int player2,int v_AI1, int v_AI2)
{
	v_AI1=v_AI1==2?3:v_AI1;
	v_AI2=v_AI2==2?3:v_AI2;
	m_endOfGame = false;
	board=new Board();
	//Players
	switch (player1)
	{
	case 1:
		uno=new Player("Player 1",1); //BLACK
		break;	
	case 2:
		uno=new Player("AI 1",1,v_AI1);
		break;
	case 3:
		uno=new Player("Stupid AI 1",1);
		break;
	}
	switch (player2)
	{
	case 1:
		dos=new Player("Player 2",2);  //WHITE
		break;	
	case 2:
		dos=new Player("AI 2", 2,v_AI2);
		break;
	case 3:
		dos=new Player("Stupid AI 2",2);
		break;
	}	
 	current=uno;
	//int var=SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "Missing file","File is missing. Please reinstall the program.",NULL);
}

void Game::pause(){
	sf::Image scrn = m_window->capture();
	sf::Texture scrnTexture;
	scrnTexture.create(m_windowWidth, m_windowHeight);
	scrnTexture.update(scrn);
	sf::Sprite scrnSprite(scrnTexture);
	sf::RectangleShape filter(sf::Vector2f(m_windowWidth, m_windowHeight));
	filter.setFillColor(sf::Color(255, 255, 255, 155));
	
	sf::Text pauseText("ESCAPE to continue!\n\nBACKSPACE to exit!", *m_font, 25);
	sf::FloatRect textRect = pauseText.getLocalBounds();
	pauseText.setColor(sf::Color::Red);
	pauseText.setOrigin(textRect.left + textRect.width/2.0f,
               			textRect.top  + textRect.height/2.0f);
	pauseText.setPosition(sf::Vector2f(m_windowWidth/2.0f,m_windowHeight/2.0f));
	bool m_pause=true;
	m_music.pause();
	sf::Event events;

	while (m_pause && !m_endOfGame && !m_exit)
	{
		while (m_window->pollEvent(events)){
			if (events.type == sf::Event::KeyPressed && events.key.code == sf::Keyboard::Escape){
				m_pause = false;
			}
			if (events.type == sf::Event::KeyPressed && events.key.code == sf::Keyboard::BackSpace){
				m_pause = false;
				m_exit=true;
				m_endOfGame=true;
				enterMenu=true;				
			}	
		}
		if (events.type == sf::Event::Closed)
			m_exit = true;

		m_window->clear();
		m_window->draw(scrnSprite);
		m_window->draw(filter);
		m_window->draw(pauseText);
		m_window->display();
	}
}


void Game::GUI_LAST(){
	sf::Image scrn = m_window->capture();
	sf::Texture scrnTexture;
	scrnTexture.create(m_windowWidth, m_windowHeight);
	scrnTexture.update(scrn);
	sf::Sprite scrnSprite(scrnTexture);
	sf::RectangleShape filter(sf::Vector2f(m_windowWidth, m_windowHeight));
	filter.setFillColor(sf::Color(255, 255, 255, 155));

	sf::Text pauseText(playerWin+"\n\nPress ESCAPE!", *m_font, 25);
	pauseText.setColor(sf::Color::Red);
	pauseText.setPosition(m_windowWidth / 2 - pauseText.getGlobalBounds().width / 2, m_windowHeight / 2);
	bool m_pause=true;
	sf::Event events;

	while (m_pause && !m_endOfGame && !m_exit)
	{
		while (m_window->pollEvent(events))
			if (events.type == sf::Event::KeyPressed && events.key.code == sf::Keyboard::Escape){
				m_pause = false;
				m_exit=true;
				m_endOfGame=true;
				enterMenu=true;				
			}				
		if (events.type == sf::Event::Closed)
			m_exit = true;

		m_window->clear();
		m_window->draw(scrnSprite);
		m_window->draw(filter);
		m_window->draw(pauseText);
		m_window->display();
	}
}