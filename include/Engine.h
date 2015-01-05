#ifndef ENGINE_H
#define ENGINE_H

#include "SFML/Graphics.hpp"
#include "node.h"
#include <memory>

class Engine
{
    public:
        Engine();
        ~Engine();

        void run();

    private:
        void gridMap();
        bool init();

        void processInput();
        void draw();
        void update();

        int calculateHeuritics(Node* nodeFrom, Node* nodeTarget);

    private:
        int gridSize;
        int tileSize;

        sf::RenderWindow window;
        sf::Font font;
        sf::Texture arrow;
        sf::Image img;

        std::vector<std::vector<Node> > mNodes;

        //Node* start;
        //Node* End;
};

#endif // ENGINE_H
