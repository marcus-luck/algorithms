#include "Engine.h"
#include "SFML/Graphics.hpp"
#include <stdlib.h>
#include <algorithm>

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

	mNodes[0][0].setInList(true);
	mNodes[0][0].setClosed();
	openList.push_back(&mNodes[0][0]);
    currentNode = &mNodes[0][0];

	setHeuristics();

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

            if(event.mouseButton.button == sf::Mouse::Right && currentNode->getEnd() != true)
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

    return (abs(from->getPosition().x - target->getPosition().x)
    + abs(from->getPosition().y - target->getPosition().y))*10;
}

void Engine::calculatePath()
{
	//sort open list
	std::sort(openList.begin(), openList.end(), [](const Node* lhs, const Node* rhs)
	{
		return lhs->getF() > rhs->getF();
	});

	//pick node with lowest f value from openlist
	currentNode = openList.back();
	openList.pop_back();

	//move node from openlist to closed list
    closedList.push_back(currentNode);
	currentNode->setClosed();
	currentNode->setInList(true);

	//check if target is reached
	if (currentNode->getEnd() == true)
	{
		paintTrack();
	}

    printf("calculating path\n");

    //Add neighbors to openList
    findNeighbors();

   // findNextNode();

	
	
	//find neighbours
	//add neigbours to openlist
	//set parent of neighbours to currentnode
	//calculate f & g value for neighbors
	//
	

}

void Engine::findNeighbors()
{

    //Add neighbors to openList
    int posX = (int)currentNode->getPosition().x;
    int posY = (int)currentNode->getPosition().y;
    printf("---- x: %i, y: %i ----\n", posX, posY);

	int dx[4] = { 0, 1, -1, 0 };
	int dy[4] = { 1, 0, 0, -1 };

	for (int i = 0; i < 4; i++)
	{


		if (posX + dx[i] <= 9 &&
			posX + dx[i] >= 0 &&
			posY + dy[i] <= 9 &&
			posY + dy[i] >= 0)
		{
			printf("  -- x: %i, y: %i ----\n", posX + dx[i], posY + dy[i]);
			if (mNodes[posX + dx[i]][posY + dy[i]].getInList() != true)
			{
				printf("     node not in open list\n");
			}

			if (mNodes[posX + dx[i]][posY + dy[i]].getPassable() == true &&
				mNodes[posX + dx[i]][posY + dy[i]].getInList() != true &&
				mNodes[posX + dx[i]][posY + dy[i]].getClosed() != true)
			{

				openList.push_back(&mNodes[posX + dx[i]][posY + dy[i]]);
				mNodes[posX + dx[i]][posY + dy[i]].setParent(currentNode);
				mNodes[posX + dx[i]][posY + dy[i]].setF(moveCost);
				mNodes[posX + dx[i]][posY + dy[i]].setInList(true);

				switch (i)
				{
				case 0:
					mNodes[posX + dx[i]][posY + dy[i]].setDirection(Node::DOWN);
					break;

				case 1:
					mNodes[posX + dx[i]][posY + dy[i]].setDirection(Node::RIGHT);
					break;

				case 2:
					mNodes[posX + dx[i]][posY + dy[i]].setDirection(Node::LEFT);
					break;

				case 3:
					mNodes[posX + dx[i]][posY + dy[i]].setDirection(Node::UP);
					break;
				}
			}
		}
	}

}

void Engine::findNextNode()
{
	//very expensive...

    for(auto& node : openList)
    {
        printf("node: %i, cNode: %i\n", node->getF(), currentNode->getF());

        if((node->getF()) <= currentNode->getF() || currentNode->getF() == 0)
        {
            currentNode = node;
            printf("switch\n");
        }

    }

	//move node from openList
}

void Engine::setHeuristics()
{
	for (int i = 0; i < gridSize; i++)
	{
		for (int j = 0; j < gridSize; j++)
		{

			mNodes[i][j].setHeuristic(calculateHeuritics(&mNodes[i][j], &mNodes[9][9]));
		}
	}
}

void Engine::paintTrack()
{
	printf("END reached!!");
}
