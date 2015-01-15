#include "Engine.h"
#include "SFML/Graphics.hpp"
#include <stdlib.h>

Engine::Engine()
: currentNode(nullptr)
, moveCost(10)
{
    if(!init())
        throw("Init failed!");

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

    if(!arrow.loadFromImage(img))
    {
        printf("load of image failed\n");
        return false;
    }


    if(!font.loadFromFile("Roboto-Regular.ttf"))
    {
        printf("load of font failed\n");
        return false;
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
		Node temp(0,0, arrow, font, true );
		mNodes.at(i).resize(gridSize, temp);
	}

    bool passable = true;

    for (int i = 0; i < gridSize; i++)
    {
        for(int j = 0; j < gridSize; j++)
        {
            Node node(i, j, arrow, font, passable);
            mNodes[i][j] = node;
        }
    }

    mNodes[0][0].setStart();
    mNodes[9][9].setEnd();

    currentNode = &mNodes[0][0];

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

            if(event.mouseButton.button == sf::Mouse::Right)
            {
                calculatePath();
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

void Engine::calculatePath()
{
    closedList.push_back(currentNode);
    printf("calculating path");

    //Add neighbors to openList
    findNeighbors();

    findNextNode();

}

void Engine::findNeighbors()
{

    //Add neighbors to openList
    int posX = (int)currentNode->getPosition().x;
    int posY = (int)currentNode->getPosition().y;
    printf("x: %i, y: %i", posX, posY);

    if((posX+1) <= 9 && mNodes[posX+1][posY].getPassable() == true )
    {
        openList.push_back(&mNodes[posX+1][posY]);
        mNodes[(posX+1)][posY].setDirection(Node::RIGHT);
        mNodes[(posX+1)][posY].setParent(currentNode);
        mNodes[(posX+1)][posY].setF(moveCost);
            printf("right\n", posX+1);
    }

    if((posX-1) >= 0 && mNodes[posX-1][posY].getPassable() == true)
    {
        openList.push_back(&mNodes[posX-1][posY]);
        mNodes[posX-1][posY].setDirection(Node::LEFT);
        mNodes[posX-1][posY].setParent(currentNode);
        mNodes[posX-1][posY].setF(moveCost);
            printf("left\n");
    }

    if((posY+1) <= 9 && mNodes[posX][(posY+1)].getPassable() == true)
    {
        openList.push_back(&mNodes[posX][(posY+1)]);
        mNodes[posX][(posY+1)].setDirection(Node::DOWN);
        mNodes[posX][(posY+1)].setParent(currentNode);
        mNodes[posX][(posY+1)].setF(moveCost);
            printf("down\n");
    }

    if((posY-1) >= 0 && mNodes[posX][posY-1].getPassable() == true)
    {
        openList.push_back(&mNodes[posX][posY-1]);
        mNodes[posX][posY-1].setDirection(Node::UP);
        mNodes[posX][posY-1].setParent(currentNode);
        mNodes[posX][posY-1].setF(moveCost);
        printf("up\n");
    }
}

void Engine::findNextNode()
{

    for(auto& node : openList)
    {
        printf("node: %i, cNode: %i", node->getF(), currentNode->getF());

        if((node->getF()) <= currentNode->getF() || currentNode->getF() == 0)
        {
            currentNode = node;
            printf("switch");
        }

    }
}


