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

        void calculatePath();
        void findNeighbors();
        void findNextNode();
		//bool F_sort(const Node& lNode, const Node& rNode) { return lNode.getF() > rNode.getF(); }
		void setHeuristics();
		void paintTrack();

    private:
        int gridSize;
        int tileSize;
        int moveCost;

        sf::RenderWindow window;
        sf::Font font;
        sf::Texture arrow;
        sf::Image img;

        std::vector<std::vector<Node> > mNodes;

        std::vector<Node*> openList;
        std::vector<Node*> closedList;
        Node* currentNode;

        //Node* start;
        //Node* End;
};

#endif // ENGINE_H
