#include "Engine.h"
#include "SFML/Graphics.hpp"
#include <stdlib.h>

Engine::Engine()
{
    if(!init())
        throw("Init failed!");
    auto a=42;
}

Engine::~Engine()
{
    //dtor
    //delete arrow;
}

bool Engine::init()
{

    gridSize = 10;
    tileSize = 64;

    window.create(sf::VideoMode(640, 800), "My window");

    if(!img.loadFromFile("arrow.png"))
    {
        printf("load of file failed");
        return false;
    }


    //printf("inter %i\n", img.getSize().x);

    if(!arrow.loadFromImage(img))
    {
        printf("load of image failed\n");
        return false;
    }


    if(!font.loadFromFile("Roboto-Regular.ttf"))
    {
        printf("load of font failed\n");
    }


    return true;
}

void Engine::run()
{
    gridMap();
    printf("Starting\n");
    while(window.isOpen())
    {

        processInput();

        update();

        draw();

    }
}

void Engine::gridMap()
{

    mNodes.resize(gridSize);

	for(int i=0; i < gridSize; i++)
	{
		//fills the map with empty spaces.
		Node temp(0,0, nullptr, nullptr, true );
		mNodes.at(i).resize(gridSize, temp);
	}

    bool passable = true;

    for (int i = 0; i < gridSize; i++)
    {
        for(int j = 0; j < gridSize; j++)
        {
            Node node(i, j, &arrow, &font, passable);
            mNodes[i][j] = node;
        }
    }

    mNodes[0][0].setStart();
    mNodes[9][9].setEnd();

    for (int i = 0; i < gridSize; i++)
    {
        for(int j = 0; j < gridSize; j++)
        {

            mNodes[i][j].setHeuristic(calculateHeuritics(&mNodes[i][j], &mNodes[9][9]));
        }
    }
}

void Engine::processInput()
{
    sf::Event event;

    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            window.close();
        }

        if(event.type == sf::Event::MouseButtonPressed)
        {

            sf::Vector2f position = window.mapPixelToCoords(sf::Mouse::getPosition(window));
            int posX = (int)(position.x/64);
            int posY = (int)(position.y/64);

            if(event.mouseButton.button == sf::Mouse::Left)
            {
                mNodes[posX][posY].setPassable();
            }
        }
    }

}

void Engine::draw()
{
	window.clear();
    for (int i = 0; i < gridSize; i++)
    {
        for(int j = 0; j < gridSize; j++)
        {
            window.draw(mNodes[i][j]);
        }
    }

    window.display();
}

void Engine::update()
{
    for (int i = 0; i < gridSize; i++)
    {
        for(int j = 0; j < gridSize; j++)
        {
            mNodes[i][j].update();
        }
    }

}

int Engine::calculateHeuritics(Node* from, Node* target)
{

    return abs(from->getPosition().x - target->getPosition().x)
    + abs(from->getPosition().y - target->getPosition().y);
}


