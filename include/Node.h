#ifndef NODE_H
#define NODE_H

#include "SFML/Graphics.hpp"

class Node
: public sf::Drawable
, public sf::Transformable
{
    public:
        Node(int x, int y, sf::Texture& texture, sf::Font& font1, bool passable);

        virtual ~Node();

        void update();
        void draw(sf::RenderTarget& target, sf::RenderStates states) const;

        void setPassable();
        bool getPassable() { return passable; }
        sf::FloatRect getBounds() const;
        void setStart() { start = true; }
        void setEnd() { ending = true; }
		bool getEnd() { return ending; }

		void setHeuristic(int heuristic);

        int getHeuristic() { return heuristic; }

        void setF(int moveCost);
        int getF() const { return fValue; }

		void setInList(bool inList) { inList = this->inList; }
		bool getInList() { return inList;  }

		void setClosed() { closed = true; }
		bool getClosed() { return closed; }

    private:

        void setFill();

    public:
        enum parentDirection
        {
            LEFT,
            RIGHT,
            UP,
            DOWN,
            UNSET
        };

        void setDirection(parentDirection direction);

        void setParent(Node* parent) { mParent = parent; }

    private:
        int nodeSize;

		bool inList;
		bool closed;

        bool start;
        bool ending;
        int pDir;

        sf::Sprite sArrow;

        sf::RectangleShape rect;
        sf::Vector2i pos;
        sf::Text h_text;
        sf::Text f_text;

        int heuristic;
        int movementCost;
		int gValue;
        int fValue;

        bool passable;

        Node* mParent;
};

#endif // NODE_H
