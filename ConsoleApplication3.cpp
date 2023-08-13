#include <SFML/Graphics.hpp>
#include <time.h>
#include <iostream>
using namespace sf;

int main()
{
    srand(time(0));
    int fps;
    //std::cin >> fps;
    RenderWindow app(VideoMode(520, 450), "Arkanoid!");
    app.setFramerateLimit(20);

    Texture t1, t2, t3, t4, t5, t6, t7, t8, t9;
    t1.loadFromFile("images/blue.png");
    t2.loadFromFile("images/wood.jpg");
    t3.loadFromFile("images/ball.png");
    t4.loadFromFile("images/plat.png");
    t5.loadFromFile("images/dark.png");
    t6.loadFromFile("images/green.png");
    t7.loadFromFile("images/white.png");
    t8.loadFromFile("images/red.png");
    t9.loadFromFile("images/over.png");

    Sprite sBackground(t2), sBall(t3), sPaddle(t4),sOver(t9);
    sPaddle.setPosition(300, 390);

    Sprite block[1000];

    bool over = false;

    int n = 0;
    for (int i = 1; i <= 10; i++)
        for (int j = 1; j <= 10; j++)
        {
            block[n].setTexture(t1);
            block[n].setPosition(i * 43, j * 20);
            n++;
        }

    float dx = 6, dy = 5;
    float x = 300, y = 300;

    while (app.isOpen())
    {
        Event e;
        while (app.pollEvent(e))
        {
            if (e.type == Event::Closed)
                app.close();
        }

        x += dx;
        for (int i = 0; i < n; i++)
            if (FloatRect(x + 3, y + 3, 6, 6).intersects(block[i].getGlobalBounds()))
            {
                block[i].setPosition(-100, 0); dx = -dx;
            }

        y += dy;
        if (y > 450)
        {
            over = true;
        }

        for (int i = 0; i < n; i++)
            if (FloatRect(x + 3, y + 3, 6, 6).intersects(block[i].getGlobalBounds()))
            {
                block[i].setPosition(-100, 0); dy = -dy;
            }

        if (x < 0 || x>520)  dx = -dx;
        if (y < 0 || y>450)  dy = -dy;

        if (Keyboard::isKeyPressed(Keyboard::Right))
        {
            sPaddle.move(10,0);
        }
        if (Keyboard::isKeyPressed(Keyboard::Left))
        {
            sPaddle.move(-10, 0);
        }
        if (FloatRect(x, y, 12, 12).intersects(sPaddle.getGlobalBounds())) dy = -(rand() % 5 + 2);


        sBall.setPosition(x, y);
        app.clear();
        app.draw(sBackground);
        if (over)
        {
            app.draw(sOver);
            std::cout << "restart:   yes/no" << std::endl;
            std::string pOver;
            std::cin >> pOver;
            if (pOver == "yes")
            {
                over = false;
            }
            else
            {
                return 0;
            }
        }
        else
        {
        app.draw(sBackground);
        app.draw(sBall);
        app.draw(sPaddle);
        for (int i = 0; i < n; i++)
        {
            app.draw(block[i]);
        }
        }


        app.display();
    }
}