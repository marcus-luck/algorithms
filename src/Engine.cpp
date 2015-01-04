#include "Engine.h"
#include "SFML/Graphics.hpp"

Engine::Engine()
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

    window.create(sf::VideoMode(640, 640), "My window");

    if(!img.loadFromFile("arrow.png"))
    {
        printf("load of file failed");
        return false;
    }

    printf("proceeding to load from image\n");

    //printf("inter %i\n", img.getSize().x);

    if(!arrow->loadFromImage(img))
    {
        printf("load of image failed\n");
        return false;
    }
    else
    {
        printf("image loading complete\n");
    }

    printf("Init successful\n");

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
        printf("0\n");
		Node temp(0,0, arrow, true );
		printf("1\n");
		mNodes.at(i).resize(gridSize, temp);
	}
    printf("2\n");
    bool passable = true;

    for (int i = 0; i < gridSize; i++)
    {
        for(int j = 0; j < gridSize; j++)
        {
            Node node(i, j, arrow, passable);
            mNodes[i][j] = node;
        }
    }

    mNodes[0][0].setStart();
    mNodes[9][9].setEnd();


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

            //printf("posX: %i, posY: %i, x: %i, y: %i\n", (int)position.x, (int)position.y , posX, posY);

            if(event.mouseButton.button == sf::Mouse::Left)
            {
                mNodes[posX][posY].setPassable();
            }
        }
    }

}

void Engine::draw()
{
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


