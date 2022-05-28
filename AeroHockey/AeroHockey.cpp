#include <SFML/Graphics.hpp>
#include "AeroHockey.h"
#include <iostream>
#include <math.h>

using namespace std;
using namespace sf;

int screenWidth = 2000;
int screenHeight = 1000;

int racketRadius = 50.f;
int ballRadius = 25.f;

float x = 1;
float y = 1;

int racketSpeed = 3.f;
int ballSpeed = 3.f;

CircleShape playerOneRacket;
CircleShape playerTwoRacket;
CircleShape ball;

bool IsColliding(CircleShape ball, CircleShape racket)
{
    return pow(ball.getPosition().x - racket.getPosition().x, 2) + pow(ball.getPosition().y - racket.getPosition().y, 2) <= pow(ballRadius + racketRadius, 2);
}

void SetCircleObject(CircleShape &circle, int radius, Color color, int x, int y) 
{
    circle.setRadius(radius);
    circle.setOrigin(radius, radius);
    circle.setFillColor(color);
    circle.setPosition(x, y);
}

void RacketControl()
{
    Keyboard dir;

    int x1 = 0;
    int y1 = 0;

    int x2 = 0;
    int y2 = 0;
    if (Keyboard::isKeyPressed(dir.W) && playerOneRacket.getPosition().y - playerOneRacket.getRadius() > 0)
    {
        y1 = -1 * racketSpeed;
    }
    if (Keyboard::isKeyPressed(dir.A) && playerOneRacket.getPosition().x - playerOneRacket.getRadius() > 0)
    {
        x1 = -1 * racketSpeed;
    }
    if (Keyboard::isKeyPressed(dir.S) && playerOneRacket.getPosition().y + playerOneRacket.getRadius() < screenHeight)
    {
        y1 = racketSpeed;
    }
    if (Keyboard::isKeyPressed(dir.D) && playerOneRacket.getPosition().x + playerOneRacket.getRadius() < screenWidth)
    {
        x1 = racketSpeed;
    }
    if(!Keyboard::isKeyPressed(dir.W) && Keyboard::isKeyPressed(dir.A) && Keyboard::isKeyPressed(dir.S) && Keyboard::isKeyPressed(dir.D))
    {
        x1 = 0;
        y1 = 0;
    }

    if (Keyboard::isKeyPressed(dir.Up) && playerTwoRacket.getPosition().y - playerTwoRacket.getRadius() > 0)
    {
        y2 = -1 * racketSpeed;
    }
    if (Keyboard::isKeyPressed(dir.Left) && playerTwoRacket.getPosition().x - playerTwoRacket.getRadius() > 0)
    {
        x2 = -1 * racketSpeed;
    }
    if (Keyboard::isKeyPressed(dir.Down) && playerTwoRacket.getPosition().y + playerTwoRacket.getRadius() < screenHeight)
    {
        y2 = racketSpeed;
    }
    if (Keyboard::isKeyPressed(dir.Right) && playerTwoRacket.getPosition().x + playerTwoRacket.getRadius() < screenWidth)
    {
        x2 = racketSpeed;
    }
    if (!Keyboard::isKeyPressed(dir.Up) && Keyboard::isKeyPressed(dir.Left) && Keyboard::isKeyPressed(dir.Down) && Keyboard::isKeyPressed(dir.Right))
    {
        x2 = 0;
        y2 = 0;
    }

    playerOneRacket.move(x1, y1);
    playerTwoRacket.move(x2, y2);
}

void CollisionWithRacket(CircleShape ball, CircleShape racket, float &x, float &y)
{
    Vector2f ballPos = ball.getPosition();

    if (IsColliding(ball, racket))
    {
        x = (ballPos.x - racket.getPosition().x) / (ball.getRadius() + racket.getRadius());
        y = (ballPos.y - racket.getPosition().y) / (ball.getRadius() + racket.getRadius());
        ballSpeed *= 1.1;
    }
}

void BallMovement()
{
    Vector2f ballPos = ball.getPosition();

    CollisionWithRacket(ball, playerOneRacket, x, y);
    CollisionWithRacket(ball, playerTwoRacket, x, y);

    if (ballPos.x + ball.getRadius() >= screenWidth || ballPos.x - ball.getRadius() <= 0)
    {
        x *= -1;
    }
    if (ballPos.y + ball.getRadius() >= screenHeight || ballPos.y - ball.getRadius() <= 0)
    {
        y *= -1;
    }

    ball.move(ballSpeed * x, ballSpeed * y);
}

int main()
{
    RenderWindow window(VideoMode(screenWidth, screenHeight), "Aerohockey");

    SetCircleObject(playerOneRacket, racketRadius, Color::Blue, 50, 500);
    SetCircleObject(playerTwoRacket, racketRadius, Color::Red, 1950, 500);
    SetCircleObject(ball, ballRadius, Color::Green, 1000, 500);

    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(playerOneRacket);
        window.draw(playerTwoRacket);
        window.draw(ball);
        RacketControl();
        BallMovement();
        window.display();
    }

    return 0;
}