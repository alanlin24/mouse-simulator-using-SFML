#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include<iostream>
#include<cstdlib>
#include<ctime>
#include <string>

using namespace std;
using namespace sf;

//Init game const
const double SCREEN_WIDTH = 800;
const double SCREEN_HEIGH = 600;
const int borderLeft = 140;
const int borderRight = 660;
const int mouseWidth = 69;
const int mouseHeight = 70;
string stringscore = "";
int score = 0;
int dissapear = 0;

double gameSpeed = 3;            


//Create Main Windows
RenderWindow app(VideoMode(SCREEN_WIDTH, SCREEN_HEIGH), "Mouse Simulator", sf::Style::Resize);

//Creat random Number for game loop
int getRandomNumber(int a, int b);

// Create gameover screen
int gameOver();
// Create Game Mode
int game2_1();
int game2_2();
int game2_3();
int game1_1();
int game1_2();
int game1_3();
// Choosing color
int color1();
int color2();
int main()
{
    score = 0;
    Texture gamestart;
    if (!gamestart.loadFromFile("pics/start1.png"))
        return EXIT_FAILURE;
    Sprite Gamestart(gamestart);
    //Gamestart.setPosition(0, 0);
    while (app.isOpen())
    {
        //Gamestart.setPosition(0, 0);
        Event event;
        while (app.pollEvent(event))
        {
            
            if (event.type == Event::Closed)
                app.close();
            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Num1)
                    color1();
                if (event.key.code == sf::Keyboard::Numpad1)
                    color1();
                if (event.key.code == sf::Keyboard::Num2)
                    color2();
                if (event.key.code == sf::Keyboard::Numpad2)
                    color2();
            }
            app.clear();
            app.draw(Gamestart);
            app.display();
        }
    }
}

int game2_1()
{
    //Init game music
    SoundBuffer gameSoundBuffer;
    gameSoundBuffer.loadFromFile("sound/game.wav");
    Sound GameSound;
    GameSound.setBuffer(gameSoundBuffer);

    Texture background, mouse1, mouse2, mouse3, obs1, obs2, obs3, obs4, cheese, apple, banana, gameover;
    //Init font
    Font myfont;
    myfont.loadFromFile("font/ab.ttf");

    //Load all images
    if (!background.loadFromFile("pics/background.png")) 
        return EXIT_FAILURE;
    if (!mouse1.loadFromFile("pics/mouse1.png")) 
        return EXIT_FAILURE;
    if (!mouse2.loadFromFile("pics/mouse2.png"))
        return EXIT_FAILURE;
    if (!mouse3.loadFromFile("pics/mouse3.png"))
        return EXIT_FAILURE;
    if (!obs1.loadFromFile("pics/obs1.png")) 
        return EXIT_FAILURE;
    if (!obs2.loadFromFile("pics/obs2.png")) 
        return EXIT_FAILURE;
    if (!obs3.loadFromFile("pics/obs3.png")) 
        return EXIT_FAILURE;
    if (!obs4.loadFromFile("pics/obs4.png")) 
        return EXIT_FAILURE;
    if (!cheese.loadFromFile("pics/cheese.png"))
        return EXIT_FAILURE;
    if (!apple.loadFromFile("pics/apple.png"))
        return EXIT_FAILURE;
    if (!banana.loadFromFile("pics/banana.png"))
        return EXIT_FAILURE;

    //Create sprite
    Sprite Background(background), Background1(background), Mouse(mouse1), Mouse2(mouse1),Obs1(obs1), 
        Obs2(obs2), Obs3(obs3), Obs4(obs4), Cheese(cheese), Apple(apple), Banana(banana), Gameover(gameover);

    double MouseX, MouseY, Mouse2X, Mouse2Y, Obs1X, Obs1Y, Obs2X, Obs2Y, 
        Obs3X, Obs3Y, Obs4X, Obs4Y, CheeseX, CheeseY, AppleX, AppleY, BananaX, BananaY;
    //Obs stands for obstacle
    //Set mouse1 and Obs position
    MouseX = SCREEN_WIDTH / 3;
    MouseY = SCREEN_HEIGH - mouseHeight;
    Mouse2X = 2 * (SCREEN_WIDTH / 3);
    Mouse2Y = SCREEN_HEIGH - mouseHeight;
    Obs1X = getRandomNumber(borderLeft, borderRight);
    Obs2X = getRandomNumber(borderLeft, borderRight);
    Obs3X = getRandomNumber(borderLeft, borderRight);
    Obs4X = getRandomNumber(borderLeft, borderRight);
    CheeseX = getRandomNumber(borderLeft, borderRight);
    AppleX = getRandomNumber(borderLeft, borderRight);
    BananaX = getRandomNumber(borderLeft, borderRight);
    Obs1Y = 0, Obs2Y = -100, Obs3Y = -200, Obs4Y = -300, CheeseY = -50, AppleY = -350, BananaY = -750;
    double BackgroundY1 = 0;
    double BackgroundY2 = -600;

    GameSound.play();
    GameSound.setLoop(true);

    
    //GAME LOOP
    while (app.isOpen())
    {
        //Init and count score
        stringscore = "SCORE:" + to_string(score);
        Text text(stringscore, myfont, 29);
        // set the text color
        text.setFillColor(sf::Color::Cyan);
        // set the text style
        text.setStyle(sf::Text::Bold);
        text.setPosition(5, 12);

        //Set mouse position
        Mouse.setPosition(MouseX, MouseY);
        Mouse2.setPosition(Mouse2X, Mouse2Y);
        Obs1.setPosition(Obs1X, Obs1Y);
        Obs2.setPosition(Obs2X, Obs2Y);
        Obs3.setPosition(Obs3X, Obs3Y);
        Obs4.setPosition(Obs4X, Obs4Y);
        Cheese.setPosition(CheeseX, CheeseY);
        Apple.setPosition(AppleX, AppleY);
        Banana.setPosition(BananaX, BananaY);

        //Create scrolling background
        Background.setPosition(0, BackgroundY1);
        Background1.setPosition(0, BackgroundY2);
        if (BackgroundY2 > 0)
        {
            BackgroundY1 = 0;
            BackgroundY2 = BackgroundY1 - 500;
        }
        //need to be same as gamespeed in order to look like as if the mouse is moving
        BackgroundY1 += gameSpeed;
        BackgroundY2 += gameSpeed;

        //Set objects LOOP
        if (Obs1Y > SCREEN_HEIGH)
        {
            Obs1Y = 0; 
            Obs1X = getRandomNumber(borderLeft, borderRight);
            score++;
        }
        else 
            Obs1Y = Obs1Y + gameSpeed;

        if (Obs2Y > SCREEN_HEIGH)
        {
            Obs2Y = 0; 
            Obs2X = getRandomNumber(borderLeft, borderRight); 
            score++;
        }
        else 
            Obs2Y = Obs2Y + gameSpeed;

        if (Obs3Y > SCREEN_HEIGH)
        {
            Obs3Y = 0; 
            Obs3X = getRandomNumber(borderLeft, borderRight); 
            score++;
        }
        else 
            Obs3Y = Obs3Y + gameSpeed; 

        if (Obs4Y > SCREEN_HEIGH)
        {
            Obs4Y = 0; 
            Obs4X = getRandomNumber(borderLeft, borderRight); 
            score++;
        }
        else 
            Obs4Y = Obs4Y + gameSpeed;

        if (CheeseY > SCREEN_HEIGH)
        {
            CheeseY = 0; 
            CheeseX = getRandomNumber(borderLeft, borderRight);
            if(dissapear == 1)
                dissapear = 0;
        }
        else 
            CheeseY = CheeseY + gameSpeed;

        if (AppleY > SCREEN_HEIGH)
        {
            AppleY = 0;
            AppleX = getRandomNumber(borderLeft, borderRight);
            if(dissapear == 2)
                dissapear = 0;
        }
        else
            AppleY = AppleY + gameSpeed;

        if (BananaY > SCREEN_HEIGH)
        {
            BananaY = 0;
            BananaX = getRandomNumber(borderLeft, borderRight);
            if(dissapear == 3)
                dissapear = 0;
        }
        else
            BananaY = BananaY + gameSpeed;

        //Game level
        if (score > 25 && score < 50)
            gameSpeed = 4;
        if (score > 50 && score < 75)
            gameSpeed = 5;
        if (score > 75 && score < 100)
            gameSpeed = 6;
        if (score > 100 && score < 150)
            gameSpeed = 7;
        if (score > 150 && score < 300)
            gameSpeed = 8;
        if (score > 300 && score < 500)
            gameSpeed = 9;
        if (score > 500 && score < 700)
            gameSpeed = 12.5;
        if (score > 700)
            gameSpeed = 20;

        //Create event to handle input from keyboard
        Event event;
        while (app.pollEvent(event))
        {
            if (event.type == Event::Closed)
                app.close();
            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Left)
                {
                    if (Mouse2X > borderLeft) 
                        Mouse2X = Mouse2X - 5;
                }
                if (event.key.code == sf::Keyboard::Right)
                {
                    if (Mouse2X < borderRight) 
                        Mouse2X = Mouse2X + 5;
                }
                if (event.key.code == sf::Keyboard::Up)
                {
                    if (Mouse2Y > 0) 
                        Mouse2Y = Mouse2Y - 5;
                }
                if (event.key.code == sf::Keyboard::Down)
                {
                    if (Mouse2Y < SCREEN_HEIGH - 70) 
                        Mouse2Y = Mouse2Y + 5;
                }
                if (event.key.code == sf::Keyboard::A)
                {
                    if (MouseX > borderLeft)
                        MouseX = MouseX - 5;
                }
                if (event.key.code == sf::Keyboard::D)
                {
                    if (MouseX < borderRight)
                        MouseX = MouseX + 5;
                }
                if (event.key.code == sf::Keyboard::W)
                {
                    if (MouseY > 0)
                        MouseY = MouseY - 5;
                }
                if (event.key.code == sf::Keyboard::S)
                {
                    if (MouseY < SCREEN_HEIGH - 70)
                        MouseY = MouseY + 5;
                }
            }
        }

        //Check if accident happen
        if (((MouseX >= (Obs1X - 35)) && (MouseX <= (Obs1X + 35))) && 
            ((MouseY >= (Obs1Y - 35)) && (MouseY <= (Obs1Y + 35))))
        //if (Mouse.getGlobalBounds().intersects(Obs1.getGlobalBounds()))
        {
            GameSound.stop(); 
            gameOver();
        }
        if (((Mouse2X >= (Obs1X - 35)) && (Mouse2X <= (Obs1X + 35))) && 
            ((Mouse2Y >= (Obs1Y - 35)) && (Mouse2Y <= (Obs1Y + 35))))
        //if (Mouse2.getGlobalBounds().intersects(Obs1.getGlobalBounds()))
        {
            GameSound.stop(); 
            gameOver();
        }
        if (((MouseX >= (Obs2X - 35)) && (MouseX <= (Obs2X + 35))) && 
            ((MouseY >= (Obs2Y - 35)) && (MouseY <= (Obs2Y + 35))))
        //if (Mouse.getGlobalBounds().intersects(Obs2.getGlobalBounds()))
        {
            GameSound.stop(); 
            gameOver();
        }
        if (((Mouse2X >= (Obs2X - 35)) && (Mouse2X <= (Obs2X + 35))) && 
            ((Mouse2Y >= (Obs2Y - 35)) && (Mouse2Y <= (Obs2Y + 35))))
        //if (Mouse2.getGlobalBounds().intersects(Obs2.getGlobalBounds()))
        {
            GameSound.stop(); 
            gameOver();
        }

        if (((MouseX >= (Obs3X - 35)) && (MouseX <= (Obs3X + 35))) && 
            ((MouseY >= (Obs3Y - 35)) && (MouseY <= (Obs3Y + 35))))
        //if (Mouse.getGlobalBounds().intersects(Obs3.getGlobalBounds()))
        {
            GameSound.stop(); 
            gameOver();
        }
        if (((Mouse2X >= (Obs3X - 35)) && (Mouse2X <= (Obs3X + 35))) && 
            ((Mouse2Y >= (Obs3Y - 35)) && (Mouse2Y <= (Obs3Y + 35))))
        //if (Mouse2.getGlobalBounds().intersects(Obs3.getGlobalBounds()))
        {
            GameSound.stop(); 
            gameOver();
        }

        if (((MouseX >= (Obs4X - 35)) && (MouseX <= (Obs4X + 35))) && 
            ((MouseY >= (Obs4Y - 35)) && (MouseY <= (Obs4Y + 35))))
        //if (Mouse.getGlobalBounds().intersects(Obs4.getGlobalBounds()))
        {
            GameSound.stop(); 
            gameOver();
        }
        if (((Mouse2X >= (Obs4X - 35)) && (Mouse2X <= (Obs4X + 35))) &&
            ((Mouse2Y >= (Obs4Y - 35)) && (Mouse2Y <= (Obs4Y + 35))))
        //if (Mouse2.getGlobalBounds().intersects(Obs4.getGlobalBounds()))
        {
            GameSound.stop(); 
            gameOver();
        }
        //Check if get reward
        if (((MouseX >= (CheeseX - 23)) && (MouseX <= (CheeseX + 23))) && 
            ((MouseY >= (CheeseY - 5)) && (MouseY <= (CheeseY + 5))))
        //if(Mouse.getGlobalBounds().intersects(Cheese.getGlobalBounds()))
        {
            dissapear = 1;
            score = score + 1;
        }
        if (((Mouse2X >= (CheeseX - 23)) && (Mouse2X <= (CheeseX + 23))) &&
            ((Mouse2Y >= (CheeseY - 5)) && (Mouse2Y <= (CheeseY + 5))))
        {
            dissapear = 1;
            score = score + 1;
        }

        if (((MouseX >= (AppleX - 23)) && (MouseX <= (AppleX + 23))) &&
            ((MouseY >= (AppleY - 5)) && (MouseY <= (AppleY + 5))))
        {
            dissapear = 2;
            score = score + 1;
        }
        if (((Mouse2X >= (AppleX - 23)) && (Mouse2X <= (AppleX + 23))) &&
            ((Mouse2Y >= (AppleY - 5)) && (Mouse2Y <= (AppleY + 5))))
        {
            dissapear = 2;
            score = score + 1;
        }

        if (((MouseX >= (BananaX - 23)) && (MouseX <= (BananaX + 23))) &&
            ((MouseY >= (BananaY - 5)) && (MouseY <= (BananaY + 5))))
        {
            dissapear = 3;
            gameSpeed += 0.05;
            score = score + 3;
        }
        if (((Mouse2X >= (BananaX - 23)) && (Mouse2X <= (BananaX + 23))) &&
            ((Mouse2Y >= (BananaY - 5)) && (Mouse2Y <= (BananaY + 5))))
        {
            dissapear = 3;
            gameSpeed += 0.05;
            score = score + 3;
        }


        //Clear and redraw position
        if (dissapear == 1)
        {
            //Cheese.setPosition(CheeseX, 2500);
            app.clear();
            app.draw(Background);
            app.draw(Background1);
            app.draw(Mouse);
            app.draw(Mouse2);
            app.draw(Obs1);
            app.draw(Obs2);
            app.draw(Obs3);
            app.draw(Obs4);
            app.draw(text);
           // app.draw(Cheese);
            app.draw(Apple);
            app.draw(Banana);
            app.display();
        }
        else if (dissapear == 2)
        {
            app.clear();
            app.draw(Background);
            app.draw(Background1);
            app.draw(Mouse);
            app.draw(Mouse2);
            app.draw(Obs1);
            app.draw(Obs2);
            app.draw(Obs3);
            app.draw(Obs4);
            app.draw(text);
            app.draw(Cheese);
            //app.draw(Apple);
            app.draw(Banana);
            app.display();
        }
        else if (dissapear == 3)
        {
            app.clear();
            app.draw(Background);
            app.draw(Background1);
            app.draw(Mouse);
            app.draw(Mouse2);
            app.draw(Obs1);
            app.draw(Obs2);
            app.draw(Obs3);
            app.draw(Obs4);
            app.draw(text);
            app.draw(Cheese);
            app.draw(Apple);
            //app.draw(Banana);
            app.display();
        }
        else
        {
            app.clear();
            app.draw(Background);
            app.draw(Background1);
            app.draw(Mouse);
            app.draw(Mouse2);
            app.draw(Obs1);
            app.draw(Obs2);
            app.draw(Obs3);
            app.draw(Obs4);
            app.draw(Cheese);
            app.draw(Apple);
            app.draw(Banana);
            app.draw(text);
            app.display();
        }
        
    }
    return EXIT_SUCCESS;
}
int game2_2()
{
    //Init game music
    SoundBuffer gameSoundBuffer;
    gameSoundBuffer.loadFromFile("sound/game.wav");
    Sound GameSound;
    GameSound.setBuffer(gameSoundBuffer);

    Texture background, mouse1, mouse2, mouse3, obs1, obs2, obs3, obs4, cheese, apple, banana, gameover;
    //Init font
    Font myfont;
    myfont.loadFromFile("font/ab.ttf");

    //Load all images
    if (!background.loadFromFile("pics/background.png"))
        return EXIT_FAILURE;
    if (!mouse1.loadFromFile("pics/mouse1.png"))
        return EXIT_FAILURE;
    if (!mouse2.loadFromFile("pics/mouse2.png"))
        return EXIT_FAILURE;
    if (!mouse3.loadFromFile("pics/mouse3.png"))
        return EXIT_FAILURE;
    if (!obs1.loadFromFile("pics/obs1.png"))
        return EXIT_FAILURE;
    if (!obs2.loadFromFile("pics/obs2.png"))
        return EXIT_FAILURE;
    if (!obs3.loadFromFile("pics/obs3.png"))
        return EXIT_FAILURE;
    if (!obs4.loadFromFile("pics/obs4.png"))
        return EXIT_FAILURE;
    if (!cheese.loadFromFile("pics/cheese.png"))
        return EXIT_FAILURE;
    if (!apple.loadFromFile("pics/apple.png"))
        return EXIT_FAILURE;
    if (!banana.loadFromFile("pics/banana.png"))
        return EXIT_FAILURE;

    //Create sprite
    Sprite Background(background), Background1(background), Mouse(mouse2), Mouse2(mouse2), Obs1(obs1),
        Obs2(obs2), Obs3(obs3), Obs4(obs4), Cheese(cheese), Apple(apple), Banana(banana), Gameover(gameover);

    double MouseX, MouseY, Mouse2X, Mouse2Y, Obs1X, Obs1Y, Obs2X, Obs2Y,
        Obs3X, Obs3Y, Obs4X, Obs4Y, CheeseX, CheeseY, AppleX, AppleY, BananaX, BananaY;
    //Obs stands for obstacle
    //Set mouse1 and Obs position
    MouseX = SCREEN_WIDTH / 3;
    MouseY = SCREEN_HEIGH - mouseHeight;
    Mouse2X = 2 * (SCREEN_WIDTH / 3);
    Mouse2Y = SCREEN_HEIGH - mouseHeight;
    Obs1X = getRandomNumber(borderLeft, borderRight);
    Obs2X = getRandomNumber(borderLeft, borderRight);
    Obs3X = getRandomNumber(borderLeft, borderRight);
    Obs4X = getRandomNumber(borderLeft, borderRight);
    CheeseX = getRandomNumber(borderLeft, borderRight);
    AppleX = getRandomNumber(borderLeft, borderRight);
    BananaX = getRandomNumber(borderLeft, borderRight);
    Obs1Y = 0, Obs2Y = -100, Obs3Y = -200, Obs4Y = -300, CheeseY = -50, AppleY = -350, BananaY = -750;
    double BackgroundY1 = 0;
    double BackgroundY2 = -600;

    GameSound.play();
    GameSound.setLoop(true);


    //GAME LOOP
    while (app.isOpen())
    {
        //Init and count score
        stringscore = "SCORE:" + to_string(score);
        Text text(stringscore, myfont, 29);
        // set the text color
        text.setFillColor(sf::Color::Cyan);
        // set the text style
        text.setStyle(sf::Text::Bold);
        text.setPosition(5, 12);

        //Set mouse position
        Mouse.setPosition(MouseX, MouseY);
        Mouse2.setPosition(Mouse2X, Mouse2Y);
        Obs1.setPosition(Obs1X, Obs1Y);
        Obs2.setPosition(Obs2X, Obs2Y);
        Obs3.setPosition(Obs3X, Obs3Y);
        Obs4.setPosition(Obs4X, Obs4Y);
        Cheese.setPosition(CheeseX, CheeseY);
        Apple.setPosition(AppleX, AppleY);
        Banana.setPosition(BananaX, BananaY);

        //Create scrolling background
        Background.setPosition(0, BackgroundY1);
        Background1.setPosition(0, BackgroundY2);
        if (BackgroundY2 > 0)
        {
            BackgroundY1 = 0;
            BackgroundY2 = BackgroundY1 - 500;
        }
        //need to be same as gamespeed in order to look like as if the mouse is moving
        BackgroundY1 += gameSpeed;
        BackgroundY2 += gameSpeed;

        //Set objects LOOP
        if (Obs1Y > SCREEN_HEIGH)
        {
            Obs1Y = 0;
            Obs1X = getRandomNumber(borderLeft, borderRight);
            score++;
        }
        else
            Obs1Y = Obs1Y + gameSpeed;

        if (Obs2Y > SCREEN_HEIGH)
        {
            Obs2Y = 0;
            Obs2X = getRandomNumber(borderLeft, borderRight);
            score++;
        }
        else
            Obs2Y = Obs2Y + gameSpeed;

        if (Obs3Y > SCREEN_HEIGH)
        {
            Obs3Y = 0;
            Obs3X = getRandomNumber(borderLeft, borderRight);
            score++;
        }
        else
            Obs3Y = Obs3Y + gameSpeed;

        if (Obs4Y > SCREEN_HEIGH)
        {
            Obs4Y = 0;
            Obs4X = getRandomNumber(borderLeft, borderRight);
            score++;
        }
        else
            Obs4Y = Obs4Y + gameSpeed;

        if (CheeseY > SCREEN_HEIGH)
        {
            CheeseY = 0;
            CheeseX = getRandomNumber(borderLeft, borderRight);
            if (dissapear == 1)
                dissapear = 0;
        }
        else
            CheeseY = CheeseY + gameSpeed;

        if (AppleY > SCREEN_HEIGH)
        {
            AppleY = 0;
            AppleX = getRandomNumber(borderLeft, borderRight);
            if (dissapear == 2)
                dissapear = 0;
        }
        else
            AppleY = AppleY + gameSpeed;

        if (BananaY > SCREEN_HEIGH)
        {
            BananaY = 0;
            BananaX = getRandomNumber(borderLeft, borderRight);
            if (dissapear == 3)
                dissapear = 0;
        }
        else
            BananaY = BananaY + gameSpeed;

        //Game level
        if (score > 25 && score < 50)
            gameSpeed = 4;
        if (score > 50 && score < 75)
            gameSpeed = 5;
        if (score > 75 && score < 100)
            gameSpeed = 6;
        if (score > 100 && score < 150)
            gameSpeed = 7;
        if (score > 150 && score < 300)
            gameSpeed = 8;
        if (score > 300 && score < 500)
            gameSpeed = 9;
        if (score > 500 && score < 700)
            gameSpeed = 12.5;
        if (score > 700)
            gameSpeed = 20;

        //Create event to handle input from keyboard
        Event event;
        while (app.pollEvent(event))
        {
            if (event.type == Event::Closed)
                app.close();
            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Left)
                {
                    if (Mouse2X > borderLeft)
                        Mouse2X = Mouse2X - 5;
                }
                if (event.key.code == sf::Keyboard::Right)
                {
                    if (Mouse2X < borderRight)
                        Mouse2X = Mouse2X + 5;
                }
                if (event.key.code == sf::Keyboard::Up)
                {
                    if (Mouse2Y > 0)
                        Mouse2Y = Mouse2Y - 5;
                }
                if (event.key.code == sf::Keyboard::Down)
                {
                    if (Mouse2Y < SCREEN_HEIGH - 70)
                        Mouse2Y = Mouse2Y + 5;
                }
                if (event.key.code == sf::Keyboard::A)
                {
                    if (MouseX > borderLeft)
                        MouseX = MouseX - 5;
                }
                if (event.key.code == sf::Keyboard::D)
                {
                    if (MouseX < borderRight)
                        MouseX = MouseX + 5;
                }
                if (event.key.code == sf::Keyboard::W)
                {
                    if (MouseY > 0)
                        MouseY = MouseY - 5;
                }
                if (event.key.code == sf::Keyboard::S)
                {
                    if (MouseY < SCREEN_HEIGH - 70)
                        MouseY = MouseY + 5;
                }
            }
        }

        //Check if accident happen
        if (((MouseX >= (Obs1X - 35)) && (MouseX <= (Obs1X + 35))) &&
            ((MouseY >= (Obs1Y - 35)) && (MouseY <= (Obs1Y + 35))))
            //if (Mouse.getGlobalBounds().intersects(Obs1.getGlobalBounds()))
        {
            GameSound.stop();
            gameOver();
        }
        if (((Mouse2X >= (Obs1X - 35)) && (Mouse2X <= (Obs1X + 35))) &&
            ((Mouse2Y >= (Obs1Y - 35)) && (Mouse2Y <= (Obs1Y + 35))))
            //if (Mouse2.getGlobalBounds().intersects(Obs1.getGlobalBounds()))
        {
            GameSound.stop();
            gameOver();
        }
        if (((MouseX >= (Obs2X - 35)) && (MouseX <= (Obs2X + 35))) &&
            ((MouseY >= (Obs2Y - 35)) && (MouseY <= (Obs2Y + 35))))
            //if (Mouse.getGlobalBounds().intersects(Obs2.getGlobalBounds()))
        {
            GameSound.stop();
            gameOver();
        }
        if (((Mouse2X >= (Obs2X - 35)) && (Mouse2X <= (Obs2X + 35))) &&
            ((Mouse2Y >= (Obs2Y - 35)) && (Mouse2Y <= (Obs2Y + 35))))
            //if (Mouse2.getGlobalBounds().intersects(Obs2.getGlobalBounds()))
        {
            GameSound.stop();
            gameOver();
        }

        if (((MouseX >= (Obs3X - 35)) && (MouseX <= (Obs3X + 35))) &&
            ((MouseY >= (Obs3Y - 35)) && (MouseY <= (Obs3Y + 35))))
            //if (Mouse.getGlobalBounds().intersects(Obs3.getGlobalBounds()))
        {
            GameSound.stop();
            gameOver();
        }
        if (((Mouse2X >= (Obs3X - 35)) && (Mouse2X <= (Obs3X + 35))) &&
            ((Mouse2Y >= (Obs3Y - 35)) && (Mouse2Y <= (Obs3Y + 35))))
            //if (Mouse2.getGlobalBounds().intersects(Obs3.getGlobalBounds()))
        {
            GameSound.stop();
            gameOver();
        }

        if (((MouseX >= (Obs4X - 35)) && (MouseX <= (Obs4X + 35))) &&
            ((MouseY >= (Obs4Y - 35)) && (MouseY <= (Obs4Y + 35))))
            //if (Mouse.getGlobalBounds().intersects(Obs4.getGlobalBounds()))
        {
            GameSound.stop();
            gameOver();
        }
        if (((Mouse2X >= (Obs4X - 35)) && (Mouse2X <= (Obs4X + 35))) &&
            ((Mouse2Y >= (Obs4Y - 35)) && (Mouse2Y <= (Obs4Y + 35))))
            //if (Mouse2.getGlobalBounds().intersects(Obs4.getGlobalBounds()))
        {
            GameSound.stop();
            gameOver();
        }
        //Check if get reward
        if (((MouseX >= (CheeseX - 23)) && (MouseX <= (CheeseX + 23))) &&
            ((MouseY >= (CheeseY - 5)) && (MouseY <= (CheeseY + 5))))
            //if(Mouse.getGlobalBounds().intersects(Cheese.getGlobalBounds()))
        {
            dissapear = 1;
            score = score + 1;
        }
        if (((Mouse2X >= (CheeseX - 23)) && (Mouse2X <= (CheeseX + 23))) &&
            ((Mouse2Y >= (CheeseY - 5)) && (Mouse2Y <= (CheeseY + 5))))
        {
            dissapear = 1;
            score = score + 1;
        }

        if (((MouseX >= (AppleX - 23)) && (MouseX <= (AppleX + 23))) &&
            ((MouseY >= (AppleY - 5)) && (MouseY <= (AppleY + 5))))
        {
            dissapear = 2;
            score = score + 1;
        }
        if (((Mouse2X >= (AppleX - 23)) && (Mouse2X <= (AppleX + 23))) &&
            ((Mouse2Y >= (AppleY - 5)) && (Mouse2Y <= (AppleY + 5))))
        {
            dissapear = 2;
            score = score + 1;
        }

        if (((MouseX >= (BananaX - 23)) && (MouseX <= (BananaX + 23))) &&
            ((MouseY >= (BananaY - 5)) && (MouseY <= (BananaY + 5))))
        {
            dissapear = 3;
            gameSpeed += 0.05;
            score = score + 3;
        }
        if (((Mouse2X >= (BananaX - 23)) && (Mouse2X <= (BananaX + 23))) &&
            ((Mouse2Y >= (BananaY - 5)) && (Mouse2Y <= (BananaY + 5))))
        {
            dissapear = 3;
            gameSpeed += 0.05;
            score = score + 3;
        }


        //Clear and redraw position
        if (dissapear == 1)
        {
            //Cheese.setPosition(CheeseX, 2500);
            app.clear();
            app.draw(Background);
            app.draw(Background1);
            app.draw(Mouse);
            app.draw(Mouse2);
            app.draw(Obs1);
            app.draw(Obs2);
            app.draw(Obs3);
            app.draw(Obs4);
            app.draw(text);
            // app.draw(Cheese);
            app.draw(Apple);
            app.draw(Banana);
            app.display();
        }
        else if (dissapear == 2)
        {
            app.clear();
            app.draw(Background);
            app.draw(Background1);
            app.draw(Mouse);
            app.draw(Mouse2);
            app.draw(Obs1);
            app.draw(Obs2);
            app.draw(Obs3);
            app.draw(Obs4);
            app.draw(text);
            app.draw(Cheese);
            //app.draw(Apple);
            app.draw(Banana);
            app.display();
        }
        else if (dissapear == 3)
        {
            app.clear();
            app.draw(Background);
            app.draw(Background1);
            app.draw(Mouse);
            app.draw(Mouse2);
            app.draw(Obs1);
            app.draw(Obs2);
            app.draw(Obs3);
            app.draw(Obs4);
            app.draw(text);
            app.draw(Cheese);
            app.draw(Apple);
            //app.draw(Banana);
            app.display();
        }
        else
        {
            app.clear();
            app.draw(Background);
            app.draw(Background1);
            app.draw(Mouse);
            app.draw(Mouse2);
            app.draw(Obs1);
            app.draw(Obs2);
            app.draw(Obs3);
            app.draw(Obs4);
            app.draw(Cheese);
            app.draw(Apple);
            app.draw(Banana);
            app.draw(text);
            app.display();
        }

    }
    return EXIT_SUCCESS;
}
int game2_3()
{
    //Init game music
    SoundBuffer gameSoundBuffer;
    gameSoundBuffer.loadFromFile("sound/game.wav");
    Sound GameSound;
    GameSound.setBuffer(gameSoundBuffer);

    Texture background, mouse1, mouse2, mouse3, obs1, obs2, obs3, obs4, cheese, apple, banana, gameover;
    //Init font
    Font myfont;
    myfont.loadFromFile("font/ab.ttf");

    //Load all images
    if (!background.loadFromFile("pics/background.png"))
        return EXIT_FAILURE;
    if (!mouse1.loadFromFile("pics/mouse1.png"))
        return EXIT_FAILURE;
    if (!mouse2.loadFromFile("pics/mouse2.png"))
        return EXIT_FAILURE;
    if (!mouse3.loadFromFile("pics/mouse3.png"))
        return EXIT_FAILURE;
    if (!obs1.loadFromFile("pics/obs1.png"))
        return EXIT_FAILURE;
    if (!obs2.loadFromFile("pics/obs2.png"))
        return EXIT_FAILURE;
    if (!obs3.loadFromFile("pics/obs3.png"))
        return EXIT_FAILURE;
    if (!obs4.loadFromFile("pics/obs4.png"))
        return EXIT_FAILURE;
    if (!cheese.loadFromFile("pics/cheese.png"))
        return EXIT_FAILURE;
    if (!apple.loadFromFile("pics/apple.png"))
        return EXIT_FAILURE;
    if (!banana.loadFromFile("pics/banana.png"))
        return EXIT_FAILURE;

    //Create sprite
    Sprite Background(background), Background1(background), Mouse(mouse3), Mouse2(mouse3), Obs1(obs1),
        Obs2(obs2), Obs3(obs3), Obs4(obs4), Cheese(cheese), Apple(apple), Banana(banana), Gameover(gameover);

    double MouseX, MouseY, Mouse2X, Mouse2Y, Obs1X, Obs1Y, Obs2X, Obs2Y,
        Obs3X, Obs3Y, Obs4X, Obs4Y, CheeseX, CheeseY, AppleX, AppleY, BananaX, BananaY;
    //Obs stands for obstacle
    //Set mouse1 and Obs position
    MouseX = SCREEN_WIDTH / 3;
    MouseY = SCREEN_HEIGH - mouseHeight;
    Mouse2X = 2 * (SCREEN_WIDTH / 3);
    Mouse2Y = SCREEN_HEIGH - mouseHeight;
    Obs1X = getRandomNumber(borderLeft, borderRight);
    Obs2X = getRandomNumber(borderLeft, borderRight);
    Obs3X = getRandomNumber(borderLeft, borderRight);
    Obs4X = getRandomNumber(borderLeft, borderRight);
    CheeseX = getRandomNumber(borderLeft, borderRight);
    AppleX = getRandomNumber(borderLeft, borderRight);
    BananaX = getRandomNumber(borderLeft, borderRight);
    Obs1Y = 0, Obs2Y = -100, Obs3Y = -200, Obs4Y = -300, CheeseY = -50, AppleY = -350, BananaY = -750;
    double BackgroundY1 = 0;
    double BackgroundY2 = -600;

    GameSound.play();
    GameSound.setLoop(true);


    //GAME LOOP
    while (app.isOpen())
    {
        //Init and count score
        stringscore = "SCORE:" + to_string(score);
        Text text(stringscore, myfont, 29);
        // set the text color
        text.setFillColor(sf::Color::Cyan);
        // set the text style
        text.setStyle(sf::Text::Bold);
        text.setPosition(5, 12);

        //Set mouse position
        Mouse.setPosition(MouseX, MouseY);
        Mouse2.setPosition(Mouse2X, Mouse2Y);
        Obs1.setPosition(Obs1X, Obs1Y);
        Obs2.setPosition(Obs2X, Obs2Y);
        Obs3.setPosition(Obs3X, Obs3Y);
        Obs4.setPosition(Obs4X, Obs4Y);
        Cheese.setPosition(CheeseX, CheeseY);
        Apple.setPosition(AppleX, AppleY);
        Banana.setPosition(BananaX, BananaY);

        //Create scrolling background
        Background.setPosition(0, BackgroundY1);
        Background1.setPosition(0, BackgroundY2);
        if (BackgroundY2 > 0)
        {
            BackgroundY1 = 0;
            BackgroundY2 = BackgroundY1 - 500;
        }
        //need to be same as gamespeed in order to look like as if the mouse is moving
        BackgroundY1 += gameSpeed;
        BackgroundY2 += gameSpeed;

        //Set objects LOOP
        if (Obs1Y > SCREEN_HEIGH)
        {
            Obs1Y = 0;
            Obs1X = getRandomNumber(borderLeft, borderRight);
            score++;
        }
        else
            Obs1Y = Obs1Y + gameSpeed;

        if (Obs2Y > SCREEN_HEIGH)
        {
            Obs2Y = 0;
            Obs2X = getRandomNumber(borderLeft, borderRight);
            score++;
        }
        else
            Obs2Y = Obs2Y + gameSpeed;

        if (Obs3Y > SCREEN_HEIGH)
        {
            Obs3Y = 0;
            Obs3X = getRandomNumber(borderLeft, borderRight);
            score++;
        }
        else
            Obs3Y = Obs3Y + gameSpeed;

        if (Obs4Y > SCREEN_HEIGH)
        {
            Obs4Y = 0;
            Obs4X = getRandomNumber(borderLeft, borderRight);
            score++;
        }
        else
            Obs4Y = Obs4Y + gameSpeed;

        if (CheeseY > SCREEN_HEIGH)
        {
            CheeseY = 0;
            CheeseX = getRandomNumber(borderLeft, borderRight);
            if (dissapear == 1)
                dissapear = 0;
        }
        else
            CheeseY = CheeseY + gameSpeed;

        if (AppleY > SCREEN_HEIGH)
        {
            AppleY = 0;
            AppleX = getRandomNumber(borderLeft, borderRight);
            if (dissapear == 2)
                dissapear = 0;
        }
        else
            AppleY = AppleY + gameSpeed;

        if (BananaY > SCREEN_HEIGH)
        {
            BananaY = 0;
            BananaX = getRandomNumber(borderLeft, borderRight);
            if (dissapear == 3)
                dissapear = 0;
        }
        else
            BananaY = BananaY + gameSpeed;

        //Game level
        if (score > 25 && score < 50)
            gameSpeed = 4;
        if (score > 50 && score < 75)
            gameSpeed = 5;
        if (score > 75 && score < 100)
            gameSpeed = 6;
        if (score > 100 && score < 150)
            gameSpeed = 7;
        if (score > 150 && score < 300)
            gameSpeed = 8;
        if (score > 300 && score < 500)
            gameSpeed = 9;
        if (score > 500 && score < 700)
            gameSpeed = 12.5;
        if (score > 700)
            gameSpeed = 20;

        //Create event to handle input from keyboard
        Event event;
        while (app.pollEvent(event))
        {
            if (event.type == Event::Closed)
                app.close();
            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Left)
                {
                    if (Mouse2X > borderLeft)
                        Mouse2X = Mouse2X - 5;
                }
                if (event.key.code == sf::Keyboard::Right)
                {
                    if (Mouse2X < borderRight)
                        Mouse2X = Mouse2X + 5;
                }
                if (event.key.code == sf::Keyboard::Up)
                {
                    if (Mouse2Y > 0)
                        Mouse2Y = Mouse2Y - 5;
                }
                if (event.key.code == sf::Keyboard::Down)
                {
                    if (Mouse2Y < SCREEN_HEIGH - 70)
                        Mouse2Y = Mouse2Y + 5;
                }
                if (event.key.code == sf::Keyboard::A)
                {
                    if (MouseX > borderLeft)
                        MouseX = MouseX - 5;
                }
                if (event.key.code == sf::Keyboard::D)
                {
                    if (MouseX < borderRight)
                        MouseX = MouseX + 5;
                }
                if (event.key.code == sf::Keyboard::W)
                {
                    if (MouseY > 0)
                        MouseY = MouseY - 5;
                }
                if (event.key.code == sf::Keyboard::S)
                {
                    if (MouseY < SCREEN_HEIGH - 70)
                        MouseY = MouseY + 5;
                }
            }
        }

        //Check if accident happen
        if (((MouseX >= (Obs1X - 35)) && (MouseX <= (Obs1X + 35))) &&
            ((MouseY >= (Obs1Y - 35)) && (MouseY <= (Obs1Y + 35))))
            //if (Mouse.getGlobalBounds().intersects(Obs1.getGlobalBounds()))
        {
            GameSound.stop();
            gameOver();
        }
        if (((Mouse2X >= (Obs1X - 35)) && (Mouse2X <= (Obs1X + 35))) &&
            ((Mouse2Y >= (Obs1Y - 35)) && (Mouse2Y <= (Obs1Y + 35))))
            //if (Mouse2.getGlobalBounds().intersects(Obs1.getGlobalBounds()))
        {
            GameSound.stop();
            gameOver();
        }
        if (((MouseX >= (Obs2X - 35)) && (MouseX <= (Obs2X + 35))) &&
            ((MouseY >= (Obs2Y - 35)) && (MouseY <= (Obs2Y + 35))))
            //if (Mouse.getGlobalBounds().intersects(Obs2.getGlobalBounds()))
        {
            GameSound.stop();
            gameOver();
        }
        if (((Mouse2X >= (Obs2X - 35)) && (Mouse2X <= (Obs2X + 35))) &&
            ((Mouse2Y >= (Obs2Y - 35)) && (Mouse2Y <= (Obs2Y + 35))))
            //if (Mouse2.getGlobalBounds().intersects(Obs2.getGlobalBounds()))
        {
            GameSound.stop();
            gameOver();
        }

        if (((MouseX >= (Obs3X - 35)) && (MouseX <= (Obs3X + 35))) &&
            ((MouseY >= (Obs3Y - 35)) && (MouseY <= (Obs3Y + 35))))
            //if (Mouse.getGlobalBounds().intersects(Obs3.getGlobalBounds()))
        {
            GameSound.stop();
            gameOver();
        }
        if (((Mouse2X >= (Obs3X - 35)) && (Mouse2X <= (Obs3X + 35))) &&
            ((Mouse2Y >= (Obs3Y - 35)) && (Mouse2Y <= (Obs3Y + 35))))
            //if (Mouse2.getGlobalBounds().intersects(Obs3.getGlobalBounds()))
        {
            GameSound.stop();
            gameOver();
        }

        if (((MouseX >= (Obs4X - 35)) && (MouseX <= (Obs4X + 35))) &&
            ((MouseY >= (Obs4Y - 35)) && (MouseY <= (Obs4Y + 35))))
            //if (Mouse.getGlobalBounds().intersects(Obs4.getGlobalBounds()))
        {
            GameSound.stop();
            gameOver();
        }
        if (((Mouse2X >= (Obs4X - 35)) && (Mouse2X <= (Obs4X + 35))) &&
            ((Mouse2Y >= (Obs4Y - 35)) && (Mouse2Y <= (Obs4Y + 35))))
            //if (Mouse2.getGlobalBounds().intersects(Obs4.getGlobalBounds()))
        {
            GameSound.stop();
            gameOver();
        }
        //Check if get reward
        if (((MouseX >= (CheeseX - 23)) && (MouseX <= (CheeseX + 23))) &&
            ((MouseY >= (CheeseY - 5)) && (MouseY <= (CheeseY + 5))))
            //if(Mouse.getGlobalBounds().intersects(Cheese.getGlobalBounds()))
        {
            dissapear = 1;
            score = score + 1;
        }
        if (((Mouse2X >= (CheeseX - 23)) && (Mouse2X <= (CheeseX + 23))) &&
            ((Mouse2Y >= (CheeseY - 5)) && (Mouse2Y <= (CheeseY + 5))))
        {
            dissapear = 1;
            score = score + 1;
        }

        if (((MouseX >= (AppleX - 23)) && (MouseX <= (AppleX + 23))) &&
            ((MouseY >= (AppleY - 5)) && (MouseY <= (AppleY + 5))))
        {
            dissapear = 2;
            score = score + 1;
        }
        if (((Mouse2X >= (AppleX - 23)) && (Mouse2X <= (AppleX + 23))) &&
            ((Mouse2Y >= (AppleY - 5)) && (Mouse2Y <= (AppleY + 5))))
        {
            dissapear = 2;
            score = score + 1;
        }

        if (((MouseX >= (BananaX - 23)) && (MouseX <= (BananaX + 23))) &&
            ((MouseY >= (BananaY - 5)) && (MouseY <= (BananaY + 5))))
        {
            dissapear = 3;
            gameSpeed += 0.05;
            score = score + 3;
        }
        if (((Mouse2X >= (BananaX - 23)) && (Mouse2X <= (BananaX + 23))) &&
            ((Mouse2Y >= (BananaY - 5)) && (Mouse2Y <= (BananaY + 5))))
        {
            dissapear = 3;
            gameSpeed += 0.05;
            score = score + 3;
        }


        //Clear and redraw position
        if (dissapear == 1)
        {
            //Cheese.setPosition(CheeseX, 2500);
            app.clear();
            app.draw(Background);
            app.draw(Background1);
            app.draw(Mouse);
            app.draw(Mouse2);
            app.draw(Obs1);
            app.draw(Obs2);
            app.draw(Obs3);
            app.draw(Obs4);
            app.draw(text);
            // app.draw(Cheese);
            app.draw(Apple);
            app.draw(Banana);
            app.display();
        }
        else if (dissapear == 2)
        {
            app.clear();
            app.draw(Background);
            app.draw(Background1);
            app.draw(Mouse);
            app.draw(Mouse2);
            app.draw(Obs1);
            app.draw(Obs2);
            app.draw(Obs3);
            app.draw(Obs4);
            app.draw(text);
            app.draw(Cheese);
            //app.draw(Apple);
            app.draw(Banana);
            app.display();
        }
        else if (dissapear == 3)
        {
            app.clear();
            app.draw(Background);
            app.draw(Background1);
            app.draw(Mouse);
            app.draw(Mouse2);
            app.draw(Obs1);
            app.draw(Obs2);
            app.draw(Obs3);
            app.draw(Obs4);
            app.draw(text);
            app.draw(Cheese);
            app.draw(Apple);
            //app.draw(Banana);
            app.display();
        }
        else
        {
            app.clear();
            app.draw(Background);
            app.draw(Background1);
            app.draw(Mouse);
            app.draw(Mouse2);
            app.draw(Obs1);
            app.draw(Obs2);
            app.draw(Obs3);
            app.draw(Obs4);
            app.draw(Cheese);
            app.draw(Apple);
            app.draw(Banana);
            app.draw(text);
            app.display();
        }

    }
    return EXIT_SUCCESS;
}
//Game over
int gameOver()
{
    Texture gameover, troll;
    if (!gameover.loadFromFile("pics/over.png")) 
        return EXIT_FAILURE;

    Sprite Gameover(gameover);
    SoundBuffer gameOver;
    gameOver.loadFromFile("sound/crash.wav");
    Sound GameOver;
    GameOver.setBuffer(gameOver);
    GameOver.play();
    while (app.isOpen())
    {
        Event event;
        while (app.pollEvent(event))
        {
            if (event.type == Event::Closed)
                app.close();
            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Enter)
                    main();
            }
        }
        Font myfont;
        myfont.loadFromFile("font/ab.ttf");
        stringscore = "YOUR SCORE:" + to_string(score);
        Text text(stringscore, myfont, 30);
        text.setPosition(250, 450);
        app.clear();
        app.draw(Gameover);
        app.draw(text);
        app.display();
    }

}

int getRandomNumber(int a, int b)
{
    static bool first = true; 
    if (first) 
        srand(time(NULL)); first = false;
    int result = a + rand() % ((b + 1) - a);
    result = (result / 10) * 10;
    return result;
}

int game1_1()
{
    //Init game music
    SoundBuffer gameSoundBuffer;
    gameSoundBuffer.loadFromFile("sound/game.wav");
    Sound GameSound;
    GameSound.setBuffer(gameSoundBuffer);

    Texture background, mouse1, obs1, obs2, obs3, obs4, cheese, apple, banana, gameover;
    //Init font
    Font myfont;
    myfont.loadFromFile("font/ab.ttf");

    //Load all images
    if (!background.loadFromFile("pics/background.png"))
        return EXIT_FAILURE;
    if (!mouse1.loadFromFile("pics/mouse1.png"))
        return EXIT_FAILURE;
    if (!obs1.loadFromFile("pics/obs1.png"))
        return EXIT_FAILURE;
    if (!obs2.loadFromFile("pics/obs2.png"))
        return EXIT_FAILURE;
    if (!obs3.loadFromFile("pics/obs3.png"))
        return EXIT_FAILURE;
    if (!obs4.loadFromFile("pics/obs4.png"))
        return EXIT_FAILURE;
    if (!cheese.loadFromFile("pics/cheese.png"))
        return EXIT_FAILURE;
    if (!apple.loadFromFile("pics/apple.png"))
        return EXIT_FAILURE;
    if (!banana.loadFromFile("pics/banana.png"))
        return EXIT_FAILURE;

    //Create sprite
    Sprite Background(background), Background1(background), Mouse(mouse1), Obs1(obs1),
        Obs2(obs2), Obs3(obs3), Obs4(obs4), Cheese(cheese), Apple(apple), Banana(banana), Gameover(gameover);

    double MouseX, MouseY, Obs1X, Obs1Y, Obs2X, Obs2Y,
        Obs3X, Obs3Y, Obs4X, Obs4Y, CheeseX, CheeseY, AppleX, AppleY, BananaX, BananaY;
    //Obs stands for obstacle
    //Set mouse1 and Obs position
    MouseX = SCREEN_WIDTH / 2;
    MouseY = SCREEN_HEIGH - mouseHeight;
    Obs1X = getRandomNumber(borderLeft, borderRight);
    Obs2X = getRandomNumber(borderLeft, borderRight);
    Obs3X = getRandomNumber(borderLeft, borderRight);
    Obs4X = getRandomNumber(borderLeft, borderRight);
    CheeseX = getRandomNumber(borderLeft, borderRight);
    AppleX = getRandomNumber(borderLeft, borderRight);
    BananaX = getRandomNumber(borderLeft, borderRight);
    Obs1Y = 0, Obs2Y = -100, Obs3Y = -200, Obs4Y = -300, CheeseY = -50, AppleY = -350, BananaY = -750;
    double BackgroundY1 = 0;
    double BackgroundY2 = -600;

    GameSound.play();
    GameSound.setLoop(true);


    //GAME LOOP
    while (app.isOpen())
    {
        //Init and count score
        stringscore = "SCORE:" + to_string(score);
        Text text(stringscore, myfont, 29);
        // set the text color
        text.setFillColor(sf::Color::Cyan);
        // set the text style
        text.setStyle(sf::Text::Bold);
        text.setPosition(5, 12);

        //Set mouse amd obstacles position
        Mouse.setPosition(MouseX, MouseY);
        Obs1.setPosition(Obs1X, Obs1Y);
        Obs2.setPosition(Obs2X, Obs2Y);
        Obs3.setPosition(Obs3X, Obs3Y);
        Obs4.setPosition(Obs4X, Obs4Y);
        Cheese.setPosition(CheeseX, CheeseY);
        Apple.setPosition(AppleX, AppleY);
        Banana.setPosition(BananaX, BananaY);

        //Create scrolling background
        Background.setPosition(0, BackgroundY1);
        Background1.setPosition(0, BackgroundY2);
        if (BackgroundY2 > 0)
        {
            BackgroundY1 = 0;
            BackgroundY2 = BackgroundY1 - 590;
        }
        //need to be same as gamespeed in order to look like as if the mouse is moving
        BackgroundY1 += gameSpeed;
        BackgroundY2 += gameSpeed;

        //Set objects LOOP
        if (Obs1Y > SCREEN_HEIGH)
        {
            Obs1Y = 0;
            Obs1X = getRandomNumber(borderLeft, borderRight);
            score++;
        }
        else
            Obs1Y = Obs1Y + gameSpeed;

        if (Obs2Y > SCREEN_HEIGH)
        {
            Obs2Y = 0;
            Obs2X = getRandomNumber(borderLeft, borderRight);
            score++;
        }
        else
            Obs2Y = Obs2Y + gameSpeed;

        if (Obs3Y > SCREEN_HEIGH)
        {
            Obs3Y = 0;
            Obs3X = getRandomNumber(borderLeft, borderRight);
            score++;
        }
        else
            Obs3Y = Obs3Y + gameSpeed;

        if (Obs4Y > SCREEN_HEIGH)
        {
            Obs4Y = 0;
            Obs4X = getRandomNumber(borderLeft, borderRight);
            score++;
        }
        else
            Obs4Y = Obs4Y + gameSpeed;

        if (CheeseY > SCREEN_HEIGH)
        {
            CheeseY = 0;
            CheeseX = getRandomNumber(borderLeft, borderRight);
            if(dissapear == 1)
                dissapear = 0;
        }
        else
            CheeseY = CheeseY + gameSpeed;

        if (AppleY > SCREEN_HEIGH)
        {
            AppleY = 0;
            AppleX = getRandomNumber(borderLeft, borderRight);
            if(dissapear == 2)
                dissapear = 0;
        }
        else
            AppleY = AppleY + gameSpeed;

        if (BananaY > SCREEN_HEIGH)
        {
            BananaY = 0;
            BananaX = getRandomNumber(borderLeft, borderRight);
            if(dissapear == 3)
                dissapear = 0;
        }
        else
            BananaY = BananaY + gameSpeed;

        //Game level
        if (score > 25 && score < 50)
            gameSpeed = 4;
        if (score > 50 && score < 75)
            gameSpeed = 5;
        if (score > 75 && score < 100)
            gameSpeed = 6;
        if (score > 100 && score < 150)
            gameSpeed = 7;
        if (score > 150 && score < 300)
            gameSpeed = 8;
        if (score > 300 && score < 500)
            gameSpeed = 9;
        if (score > 500 && score < 700)
            gameSpeed = 12.5;
        if (score > 700)
            gameSpeed = 20;

        //Create event to handle input from keyboard
        Event event;
        while (app.pollEvent(event))
        {
            if (event.type == Event::Closed)
                app.close();
            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Left)
                {
                    if (MouseX > borderLeft)
                        MouseX = MouseX - 5;
                }
                if (event.key.code == sf::Keyboard::Right)
                {
                    if (MouseX < borderRight)
                        MouseX = MouseX + 5;
                }
                if (event.key.code == sf::Keyboard::Up)
                {
                    if (MouseY > 0)
                        MouseY = MouseY - 5;
                }
                if (event.key.code == sf::Keyboard::Down)
                {
                    if (MouseY < SCREEN_HEIGH - 70)
                        MouseY = MouseY + 5;
                }
            }
        }

        //Check if accident happen
        if (((MouseX >= (Obs1X - 35)) && (MouseX <= (Obs1X + 35))) &&
            ((MouseY >= (Obs1Y - 35)) && (MouseY <= (Obs1Y + 35))))
            //if (Mouse.getGlobalBounds().intersects(Obs1.getGlobalBounds()))
        {
            GameSound.stop();
            gameOver();
        }
        
        if (((MouseX >= (Obs2X - 35)) && (MouseX <= (Obs2X + 35))) &&
            ((MouseY >= (Obs2Y - 35)) && (MouseY <= (Obs2Y + 35))))
            //if (Mouse.getGlobalBounds().intersects(Obs2.getGlobalBounds()))
        {
            GameSound.stop();
            gameOver();
        }
        

        if (((MouseX >= (Obs3X - 35)) && (MouseX <= (Obs3X + 35))) &&
            ((MouseY >= (Obs3Y - 35)) && (MouseY <= (Obs3Y + 35))))
            //if (Mouse.getGlobalBounds().intersects(Obs3.getGlobalBounds()))
        {
            GameSound.stop();
            gameOver();
        }
        

        if (((MouseX >= (Obs4X - 35)) && (MouseX <= (Obs4X + 35))) &&
            ((MouseY >= (Obs4Y - 35)) && (MouseY <= (Obs4Y + 35))))
            //if (Mouse.getGlobalBounds().intersects(Obs4.getGlobalBounds()))
        {
            GameSound.stop();
            gameOver();
        }
      
        //Check if get reward
        if (((MouseX >= (CheeseX - 23)) && (MouseX <= (CheeseX + 23))) &&
            ((MouseY >= (CheeseY - 5)) && (MouseY <= (CheeseY + 5))))
            //if(Mouse.getGlobalBounds().intersects(Cheese.getGlobalBounds()))
        {
            dissapear = 1;
            score = score + 1;
        }
        

        if (((MouseX >= (AppleX - 23)) && (MouseX <= (AppleX + 23))) &&
            ((MouseY >= (AppleY - 5)) && (MouseY <= (AppleY + 5))))
        {
            dissapear = 2;
            score = score + 1;
        }
        

        if (((MouseX >= (BananaX - 23)) && (MouseX <= (BananaX + 23))) &&
            ((MouseY >= (BananaY - 5)) && (MouseY <= (BananaY + 5))))
        {
            dissapear = 3;
            gameSpeed += 0.05;

        }
        


        //Clear and redraw position
        if (dissapear == 1)
        {
            //Cheese.setPosition(CheeseX, 2500);
            app.clear();
            app.draw(Background);
            app.draw(Background1);
            app.draw(Mouse);
            app.draw(Obs1);
            app.draw(Obs2);
            app.draw(Obs3);
            app.draw(Obs4);
            app.draw(text);
            // app.draw(Cheese);
            app.draw(Apple);
            app.draw(Banana);
            app.display();
        }
        else if (dissapear == 2)
        {
            app.clear();
            app.draw(Background);
            app.draw(Background1);
            app.draw(Mouse);
            app.draw(Obs1);
            app.draw(Obs2);
            app.draw(Obs3);
            app.draw(Obs4);
            app.draw(text);
            app.draw(Cheese);
            //app.draw(Apple);
            app.draw(Banana);
            app.display();
        }
        else if (dissapear == 3)
        {
            app.clear();
            app.draw(Background);
            app.draw(Background1);
            app.draw(Mouse);
            app.draw(Obs1);
            app.draw(Obs2);
            app.draw(Obs3);
            app.draw(Obs4);
            app.draw(text);
            app.draw(Cheese);
            app.draw(Apple);
            //app.draw(Banana);
            app.display();
        }
        else
        {
            app.clear();
            app.draw(Background);
            app.draw(Background1);
            app.draw(Mouse);
            app.draw(Obs1);
            app.draw(Obs2);
            app.draw(Obs3);
            app.draw(Obs4);
            app.draw(Cheese);
            app.draw(Apple);
            app.draw(Banana);
            app.draw(text);
            app.display();
        }

    }
    return EXIT_SUCCESS;
}
int game1_2()
{
    //Init game music
    SoundBuffer gameSoundBuffer;
    gameSoundBuffer.loadFromFile("sound/game.wav");
    Sound GameSound;
    GameSound.setBuffer(gameSoundBuffer);

    Texture background, mouse1, mouse2, mouse3, obs1, obs2, obs3, obs4, cheese, apple, banana, gameover;
    //Init font
    Font myfont;
    myfont.loadFromFile("font/ab.ttf");

    //Load all images
    if (!background.loadFromFile("pics/background.png"))
        return EXIT_FAILURE;
    if (!mouse1.loadFromFile("pics/mouse1.png"))
        return EXIT_FAILURE;
    if (!mouse2.loadFromFile("pics/mouse2.png"))
        return EXIT_FAILURE;
    if (!mouse3.loadFromFile("pics/mouse3.png"))
        return EXIT_FAILURE;
    if (!obs1.loadFromFile("pics/obs1.png"))
        return EXIT_FAILURE;
    if (!obs2.loadFromFile("pics/obs2.png"))
        return EXIT_FAILURE;
    if (!obs3.loadFromFile("pics/obs3.png"))
        return EXIT_FAILURE;
    if (!obs4.loadFromFile("pics/obs4.png"))
        return EXIT_FAILURE;
    if (!cheese.loadFromFile("pics/cheese.png"))
        return EXIT_FAILURE;
    if (!apple.loadFromFile("pics/apple.png"))
        return EXIT_FAILURE;
    if (!banana.loadFromFile("pics/banana.png"))
        return EXIT_FAILURE;

    //Create sprite
    Sprite Background(background), Background1(background), Mouse(mouse2), Obs1(obs1),
        Obs2(obs2), Obs3(obs3), Obs4(obs4), Cheese(cheese), Apple(apple), Banana(banana), Gameover(gameover);

    double MouseX, MouseY, Obs1X, Obs1Y, Obs2X, Obs2Y,
        Obs3X, Obs3Y, Obs4X, Obs4Y, CheeseX, CheeseY, AppleX, AppleY, BananaX, BananaY;
    //Obs stands for obstacle
    //Set mouse1 and Obs position
    MouseX = SCREEN_WIDTH / 2;
    MouseY = SCREEN_HEIGH - mouseHeight;
    Obs1X = getRandomNumber(borderLeft, borderRight);
    Obs2X = getRandomNumber(borderLeft, borderRight);
    Obs3X = getRandomNumber(borderLeft, borderRight);
    Obs4X = getRandomNumber(borderLeft, borderRight);
    CheeseX = getRandomNumber(borderLeft, borderRight);
    AppleX = getRandomNumber(borderLeft, borderRight);
    BananaX = getRandomNumber(borderLeft, borderRight);
    Obs1Y = 0, Obs2Y = -100, Obs3Y = -200, Obs4Y = -300, CheeseY = -50, AppleY = -350, BananaY = -750;
    double BackgroundY1 = 0;
    double BackgroundY2 = -600;

    GameSound.play();
    GameSound.setLoop(true);


    //GAME LOOP
    while (app.isOpen())
    {
        //Init and count score
        stringscore = "SCORE:" + to_string(score);
        Text text(stringscore, myfont, 29);
        // set the text color
        text.setFillColor(sf::Color::Cyan);
        // set the text style
        text.setStyle(sf::Text::Bold);
        text.setPosition(5, 12);

        //Set mouse amd obstacles position
        Mouse.setPosition(MouseX, MouseY);
        Obs1.setPosition(Obs1X, Obs1Y);
        Obs2.setPosition(Obs2X, Obs2Y);
        Obs3.setPosition(Obs3X, Obs3Y);
        Obs4.setPosition(Obs4X, Obs4Y);
        Cheese.setPosition(CheeseX, CheeseY);
        Apple.setPosition(AppleX, AppleY);
        Banana.setPosition(BananaX, BananaY);

        //Create scrolling background
        Background.setPosition(0, BackgroundY1);
        Background1.setPosition(0, BackgroundY2);
        if (BackgroundY2 > 0)
        {
            BackgroundY1 = 0;
            BackgroundY2 = BackgroundY1 - 500;
        }
        //need to be same as gamespeed in order to look like as if the mouse is moving
        BackgroundY1 += gameSpeed;
        BackgroundY2 += gameSpeed;

        //Set objects LOOP
        if (Obs1Y > SCREEN_HEIGH)
        {
            Obs1Y = 0;
            Obs1X = getRandomNumber(borderLeft, borderRight);
            score++;
        }
        else
            Obs1Y = Obs1Y + gameSpeed;

        if (Obs2Y > SCREEN_HEIGH)
        {
            Obs2Y = 0;
            Obs2X = getRandomNumber(borderLeft, borderRight);
            score++;
        }
        else
            Obs2Y = Obs2Y + gameSpeed;

        if (Obs3Y > SCREEN_HEIGH)
        {
            Obs3Y = 0;
            Obs3X = getRandomNumber(borderLeft, borderRight);
            score++;
        }
        else
            Obs3Y = Obs3Y + gameSpeed;

        if (Obs4Y > SCREEN_HEIGH)
        {
            Obs4Y = 0;
            Obs4X = getRandomNumber(borderLeft, borderRight);
            score++;
        }
        else
            Obs4Y = Obs4Y + gameSpeed;

        if (CheeseY > SCREEN_HEIGH)
        {
            CheeseY = 0;
            CheeseX = getRandomNumber(borderLeft, borderRight);
            if (dissapear == 1)
                dissapear = 0;
        }
        else
            CheeseY = CheeseY + gameSpeed;

        if (AppleY > SCREEN_HEIGH)
        {
            AppleY = 0;
            AppleX = getRandomNumber(borderLeft, borderRight);
            if (dissapear == 2)
                dissapear = 0;
        }
        else
            AppleY = AppleY + gameSpeed;

        if (BananaY > SCREEN_HEIGH)
        {
            BananaY = 0;
            BananaX = getRandomNumber(borderLeft, borderRight);
            if (dissapear == 3)
                dissapear = 0;
        }
        else
            BananaY = BananaY + gameSpeed;

        //Game level
        if (score > 25 && score < 50)
            gameSpeed = 4;
        if (score > 50 && score < 75)
            gameSpeed = 5;
        if (score > 75 && score < 100)
            gameSpeed = 6;
        if (score > 100 && score < 150)
            gameSpeed = 7;
        if (score > 150 && score < 300)
            gameSpeed = 8;
        if (score > 300 && score < 500)
            gameSpeed = 9;
        if (score > 500 && score < 700)
            gameSpeed = 12.5;
        if (score > 700)
            gameSpeed = 20;

        //Create event to handle input from keyboard
        Event event;
        while (app.pollEvent(event))
        {
            if (event.type == Event::Closed)
                app.close();
            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Left)
                {
                    if (MouseX > borderLeft)
                        MouseX = MouseX - 5;
                }
                if (event.key.code == sf::Keyboard::Right)
                {
                    if (MouseX < borderRight)
                        MouseX = MouseX + 5;
                }
                if (event.key.code == sf::Keyboard::Up)
                {
                    if (MouseY > 0)
                        MouseY = MouseY - 5;
                }
                if (event.key.code == sf::Keyboard::Down)
                {
                    if (MouseY < SCREEN_HEIGH - 70)
                        MouseY = MouseY + 5;
                }
            }
        }

        //Check if accident happen
        if (((MouseX >= (Obs1X - 35)) && (MouseX <= (Obs1X + 35))) &&
            ((MouseY >= (Obs1Y - 35)) && (MouseY <= (Obs1Y + 35))))
            //if (Mouse.getGlobalBounds().intersects(Obs1.getGlobalBounds()))
        {
            GameSound.stop();
            gameOver();
        }

        if (((MouseX >= (Obs2X - 35)) && (MouseX <= (Obs2X + 35))) &&
            ((MouseY >= (Obs2Y - 35)) && (MouseY <= (Obs2Y + 35))))
            //if (Mouse.getGlobalBounds().intersects(Obs2.getGlobalBounds()))
        {
            GameSound.stop();
            gameOver();
        }


        if (((MouseX >= (Obs3X - 35)) && (MouseX <= (Obs3X + 35))) &&
            ((MouseY >= (Obs3Y - 35)) && (MouseY <= (Obs3Y + 35))))
            //if (Mouse.getGlobalBounds().intersects(Obs3.getGlobalBounds()))
        {
            GameSound.stop();
            gameOver();
        }


        if (((MouseX >= (Obs4X - 35)) && (MouseX <= (Obs4X + 35))) &&
            ((MouseY >= (Obs4Y - 35)) && (MouseY <= (Obs4Y + 35))))
            //if (Mouse.getGlobalBounds().intersects(Obs4.getGlobalBounds()))
        {
            GameSound.stop();
            gameOver();
        }

        //Check if get reward
        if (((MouseX >= (CheeseX - 23)) && (MouseX <= (CheeseX + 23))) &&
            ((MouseY >= (CheeseY - 5)) && (MouseY <= (CheeseY + 5))))
            //if(Mouse.getGlobalBounds().intersects(Cheese.getGlobalBounds()))
        {
            dissapear = 1;
            score = score + 1;
        }


        if (((MouseX >= (AppleX - 23)) && (MouseX <= (AppleX + 23))) &&
            ((MouseY >= (AppleY - 5)) && (MouseY <= (AppleY + 5))))
        {
            dissapear = 2;
            score = score + 1;
        }


        if (((MouseX >= (BananaX - 23)) && (MouseX <= (BananaX + 23))) &&
            ((MouseY >= (BananaY - 5)) && (MouseY <= (BananaY + 5))))
        {
            dissapear = 3;
            gameSpeed += 0.05;
        }



        //Clear and redraw position
        if (dissapear == 1)
        {
            //Cheese.setPosition(CheeseX, 2500);
            app.clear();
            app.draw(Background);
            app.draw(Background1);
            app.draw(Mouse);
            app.draw(Obs1);
            app.draw(Obs2);
            app.draw(Obs3);
            app.draw(Obs4);
            app.draw(text);
            // app.draw(Cheese);
            app.draw(Apple);
            app.draw(Banana);
            app.display();
        }
        else if (dissapear == 2)
        {
            app.clear();
            app.draw(Background);
            app.draw(Background1);
            app.draw(Mouse);
            app.draw(Obs1);
            app.draw(Obs2);
            app.draw(Obs3);
            app.draw(Obs4);
            app.draw(text);
            app.draw(Cheese);
            //app.draw(Apple);
            app.draw(Banana);
            app.display();
        }
        else if (dissapear == 3)
        {
            app.clear();
            app.draw(Background);
            app.draw(Background1);
            app.draw(Mouse);
            app.draw(Obs1);
            app.draw(Obs2);
            app.draw(Obs3);
            app.draw(Obs4);
            app.draw(text);
            app.draw(Cheese);
            app.draw(Apple);
            //app.draw(Banana);
            app.display();
        }
        else
        {
            app.clear();
            app.draw(Background);
            app.draw(Background1);
            app.draw(Mouse);
            app.draw(Obs1);
            app.draw(Obs2);
            app.draw(Obs3);
            app.draw(Obs4);
            app.draw(Cheese);
            app.draw(Apple);
            app.draw(Banana);
            app.draw(text);
            app.display();
        }

    }
    return EXIT_SUCCESS;
}
int game1_3()
{
    //Init game music
    SoundBuffer gameSoundBuffer;
    gameSoundBuffer.loadFromFile("sound/game.wav");
    Sound GameSound;
    GameSound.setBuffer(gameSoundBuffer);

    Texture background, mouse1, mouse2, mouse3, obs1, obs2, obs3, obs4, cheese, apple, banana, gameover;
    //Init font
    Font myfont;
    myfont.loadFromFile("font/ab.ttf");

    //Load all images
    if (!background.loadFromFile("pics/background.png"))
        return EXIT_FAILURE;
    if (!mouse1.loadFromFile("pics/mouse1.png"))
        return EXIT_FAILURE;
    if (!mouse2.loadFromFile("pics/mouse2.png"))
        return EXIT_FAILURE;
    if (!mouse3.loadFromFile("pics/mouse3.png"))
        return EXIT_FAILURE;
    if (!obs1.loadFromFile("pics/obs1.png"))
        return EXIT_FAILURE;
    if (!obs2.loadFromFile("pics/obs2.png"))
        return EXIT_FAILURE;
    if (!obs3.loadFromFile("pics/obs3.png"))
        return EXIT_FAILURE;
    if (!obs4.loadFromFile("pics/obs4.png"))
        return EXIT_FAILURE;
    if (!cheese.loadFromFile("pics/cheese.png"))
        return EXIT_FAILURE;
    if (!apple.loadFromFile("pics/apple.png"))
        return EXIT_FAILURE;
    if (!banana.loadFromFile("pics/banana.png"))
        return EXIT_FAILURE;

    //Create sprite
    Sprite Background(background), Background1(background), Mouse(mouse3), Obs1(obs1),
        Obs2(obs2), Obs3(obs3), Obs4(obs4), Cheese(cheese), Apple(apple), Banana(banana), Gameover(gameover);

    double MouseX, MouseY, Obs1X, Obs1Y, Obs2X, Obs2Y,
        Obs3X, Obs3Y, Obs4X, Obs4Y, CheeseX, CheeseY, AppleX, AppleY, BananaX, BananaY;
    //Obs stands for obstacle
    //Set mouse1 and Obs position
    MouseX = SCREEN_WIDTH / 2;
    MouseY = SCREEN_HEIGH - mouseHeight;
    Obs1X = getRandomNumber(borderLeft, borderRight);
    Obs2X = getRandomNumber(borderLeft, borderRight);
    Obs3X = getRandomNumber(borderLeft, borderRight);
    Obs4X = getRandomNumber(borderLeft, borderRight);
    CheeseX = getRandomNumber(borderLeft, borderRight);
    AppleX = getRandomNumber(borderLeft, borderRight);
    BananaX = getRandomNumber(borderLeft, borderRight);
    Obs1Y = 0, Obs2Y = -100, Obs3Y = -200, Obs4Y = -300, CheeseY = -50, AppleY = -350, BananaY = -750;
    double BackgroundY1 = 0;
    double BackgroundY2 = -600;

    GameSound.play();
    GameSound.setLoop(true);


    //GAME LOOP
    while (app.isOpen())
    {
        //Init and count score
        stringscore = "SCORE:" + to_string(score);
        Text text(stringscore, myfont, 29);
        // set the text color
        text.setFillColor(sf::Color::Cyan);
        // set the text style
        text.setStyle(sf::Text::Bold);
        text.setPosition(5, 12);

        //Set mouse amd obstacles position
        Mouse.setPosition(MouseX, MouseY);
        Obs1.setPosition(Obs1X, Obs1Y);
        Obs2.setPosition(Obs2X, Obs2Y);
        Obs3.setPosition(Obs3X, Obs3Y);
        Obs4.setPosition(Obs4X, Obs4Y);
        Cheese.setPosition(CheeseX, CheeseY);
        Apple.setPosition(AppleX, AppleY);
        Banana.setPosition(BananaX, BananaY);

        //Create scrolling background
        Background.setPosition(0, BackgroundY1);
        Background1.setPosition(0, BackgroundY2);
        if (BackgroundY2 > 0)
        {
            BackgroundY1 = 0;
            BackgroundY2 = BackgroundY1 - 500;
        }
        //need to be same as gamespeed in order to look like as if the mouse is moving
        BackgroundY1 += gameSpeed;
        BackgroundY2 += gameSpeed;

        //Set objects LOOP
        if (Obs1Y > SCREEN_HEIGH)
        {
            Obs1Y = 0;
            Obs1X = getRandomNumber(borderLeft, borderRight);
            score++;
        }
        else
            Obs1Y = Obs1Y + gameSpeed;

        if (Obs2Y > SCREEN_HEIGH)
        {
            Obs2Y = 0;
            Obs2X = getRandomNumber(borderLeft, borderRight);
            score++;
        }
        else
            Obs2Y = Obs2Y + gameSpeed;

        if (Obs3Y > SCREEN_HEIGH)
        {
            Obs3Y = 0;
            Obs3X = getRandomNumber(borderLeft, borderRight);
            score++;
        }
        else
            Obs3Y = Obs3Y + gameSpeed;

        if (Obs4Y > SCREEN_HEIGH)
        {
            Obs4Y = 0;
            Obs4X = getRandomNumber(borderLeft, borderRight);
            score++;
        }
        else
            Obs4Y = Obs4Y + gameSpeed;

        if (CheeseY > SCREEN_HEIGH)
        {
            CheeseY = 0;
            CheeseX = getRandomNumber(borderLeft, borderRight);
            if (dissapear == 1)
                dissapear = 0;
        }
        else
            CheeseY = CheeseY + gameSpeed;

        if (AppleY > SCREEN_HEIGH)
        {
            AppleY = 0;
            AppleX = getRandomNumber(borderLeft, borderRight);
            if (dissapear == 2)
                dissapear = 0;
        }
        else
            AppleY = AppleY + gameSpeed;

        if (BananaY > SCREEN_HEIGH)
        {
            BananaY = 0;
            BananaX = getRandomNumber(borderLeft, borderRight);
            if (dissapear == 3)
                dissapear = 0;
        }
        else
            BananaY = BananaY + gameSpeed;

        //Game level
        if (score > 25 && score < 50)
            gameSpeed = 4;
        if (score > 50 && score < 75)
            gameSpeed = 5;
        if (score > 75 && score < 100)
            gameSpeed = 6;
        if (score > 100 && score < 150)
            gameSpeed = 7;
        if (score > 150 && score < 300)
            gameSpeed = 8;
        if (score > 300 && score < 500)
            gameSpeed = 9;
        if (score > 500 && score < 700)
            gameSpeed = 12.5;
        if (score > 700)
            gameSpeed = 20;

        //Create event to handle input from keyboard
        Event event;
        while (app.pollEvent(event))
        {
            if (event.type == Event::Closed)
                app.close();
            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Left)
                {
                    if (MouseX > borderLeft)
                        MouseX = MouseX - 5;
                }
                if (event.key.code == sf::Keyboard::Right)
                {
                    if (MouseX < borderRight)
                        MouseX = MouseX + 5;
                }
                if (event.key.code == sf::Keyboard::Up)
                {
                    if (MouseY > 0)
                        MouseY = MouseY - 5;
                }
                if (event.key.code == sf::Keyboard::Down)
                {
                    if (MouseY < SCREEN_HEIGH - 70)
                        MouseY = MouseY + 5;
                }
            }
        }

        //Check if accident happen
        if (((MouseX >= (Obs1X - 35)) && (MouseX <= (Obs1X + 35))) &&
            ((MouseY >= (Obs1Y - 35)) && (MouseY <= (Obs1Y + 35))))
            //if (Mouse.getGlobalBounds().intersects(Obs1.getGlobalBounds()))
        {
            GameSound.stop();
            gameOver();
        }

        if (((MouseX >= (Obs2X - 35)) && (MouseX <= (Obs2X + 35))) &&
            ((MouseY >= (Obs2Y - 35)) && (MouseY <= (Obs2Y + 35))))
            //if (Mouse.getGlobalBounds().intersects(Obs2.getGlobalBounds()))
        {
            GameSound.stop();
            gameOver();
        }


        if (((MouseX >= (Obs3X - 35)) && (MouseX <= (Obs3X + 35))) &&
            ((MouseY >= (Obs3Y - 35)) && (MouseY <= (Obs3Y + 35))))
            //if (Mouse.getGlobalBounds().intersects(Obs3.getGlobalBounds()))
        {
            GameSound.stop();
            gameOver();
        }


        if (((MouseX >= (Obs4X - 35)) && (MouseX <= (Obs4X + 35))) &&
            ((MouseY >= (Obs4Y - 35)) && (MouseY <= (Obs4Y + 35))))
            //if (Mouse.getGlobalBounds().intersects(Obs4.getGlobalBounds()))
        {
            GameSound.stop();
            gameOver();
        }

        //Check if get reward
        if (((MouseX >= (CheeseX - 23)) && (MouseX <= (CheeseX + 23))) &&
            ((MouseY >= (CheeseY - 5)) && (MouseY <= (CheeseY + 5))))
            //if(Mouse.getGlobalBounds().intersects(Cheese.getGlobalBounds()))
        {
            dissapear = 1;
            score = score + 1;
        }


        if (((MouseX >= (AppleX - 23)) && (MouseX <= (AppleX + 23))) &&
            ((MouseY >= (AppleY - 5)) && (MouseY <= (AppleY + 5))))
        {
            dissapear = 2;
            score = score + 1;
        }


        if (((MouseX >= (BananaX - 23)) && (MouseX <= (BananaX + 23))) &&
            ((MouseY >= (BananaY - 5)) && (MouseY <= (BananaY + 5))))
        {
            dissapear = 3;
            gameSpeed += 0.05;
            score = score + 3;
        }



        //Clear and redraw position
        if (dissapear == 1)
        {
            //Cheese.setPosition(CheeseX, 2500);
            app.clear();
            app.draw(Background);
            app.draw(Background1);
            app.draw(Mouse);
            app.draw(Obs1);
            app.draw(Obs2);
            app.draw(Obs3);
            app.draw(Obs4);
            app.draw(text);
            // app.draw(Cheese);
            app.draw(Apple);
            app.draw(Banana);
            app.display();
        }
        else if (dissapear == 2)
        {
            app.clear();
            app.draw(Background);
            app.draw(Background1);
            app.draw(Mouse);
            app.draw(Obs1);
            app.draw(Obs2);
            app.draw(Obs3);
            app.draw(Obs4);
            app.draw(text);
            app.draw(Cheese);
            //app.draw(Apple);
            app.draw(Banana);
            app.display();
        }
        else if (dissapear == 3)
        {
            app.clear();
            app.draw(Background);
            app.draw(Background1);
            app.draw(Mouse);
            app.draw(Obs1);
            app.draw(Obs2);
            app.draw(Obs3);
            app.draw(Obs4);
            app.draw(text);
            app.draw(Cheese);
            app.draw(Apple);
            //app.draw(Banana);
            app.display();
        }
        else
        {
            app.clear();
            app.draw(Background);
            app.draw(Background1);
            app.draw(Mouse);
            app.draw(Obs1);
            app.draw(Obs2);
            app.draw(Obs3);
            app.draw(Obs4);
            app.draw(Cheese);
            app.draw(Apple);
            app.draw(Banana);
            app.draw(text);
            app.display();
        }

    }
    return EXIT_SUCCESS;
}

int color1()
{
    Texture choosecolor;
    if (!choosecolor.loadFromFile("pics/start2.png"))
        return EXIT_FAILURE;
    Sprite Choosecolor(choosecolor);
    Choosecolor.setPosition(0, 0);
    while (app.isOpen())
    {
        Choosecolor.setPosition(0, 0);
        Event event;
        while (app.pollEvent(event))
        {

            if (event.type == Event::Closed)
                app.close();
            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Num1)
                    game1_1();
                if (event.key.code == sf::Keyboard::Numpad1)
                    game1_1();
                if (event.key.code == sf::Keyboard::Num2)
                    game1_2();
                if (event.key.code == sf::Keyboard::Numpad2)
                    game1_2();
                if (event.key.code == sf::Keyboard::Num3)
                    game1_3();
                if (event.key.code == sf::Keyboard::Numpad3)
                    game1_3();
            }
            app.clear();
            app.draw(Choosecolor);
            app.display();
        }
    }
}
int color2()
{
    Texture choosecolor;
    if (!choosecolor.loadFromFile("pics/start2.png"))
        return EXIT_FAILURE;
    Sprite Choosecolor(choosecolor);
    Choosecolor.setPosition(0, 0);
    while (app.isOpen())
    {
        Choosecolor.setPosition(0, 0);
        Event event;
        while (app.pollEvent(event))
        {

            if (event.type == Event::Closed)
                app.close();
            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Num1)
                    game2_1();
                if (event.key.code == sf::Keyboard::Numpad1)
                    game2_1();
                if (event.key.code == sf::Keyboard::Num2)
                    game2_2();
                if (event.key.code == sf::Keyboard::Numpad2)
                    game2_2();
                if (event.key.code == sf::Keyboard::Num3)
                    game2_3();
                if (event.key.code == sf::Keyboard::Numpad3)
                    game2_3();
            }
            app.clear();
            app.draw(Choosecolor);
            app.display();
        }
    }
}
