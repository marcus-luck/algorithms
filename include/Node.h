#ifndef NODE_H
#define NODE_H

#include "SFML/Graphics.hpp"

class Node
: public sf::Drawable
, public sf::Transformable
{
    public:
        Node(int x, int y, sf::Texture *texture, bool passable);

        virtual ~Node();

        void update();
        void draw(sf::RenderTarget& target, sf::RenderStates states) const;

        void setPassable();
        sf::FloatRect getBounds() const;
        void setStart() { start = true; }
        void setEnd() { ending = true; }

    private:

        void setFill();

    private:
        int nodeSize;

        bool start;
        bool ending;

        sf::Sprite sArrow;

        sf::RectangleShape rect;
        sf::IntRect pos;
        int heuritic;
        int movementCost;
        int fValue;

        bool passable;

        Node* mParent;
};

#endif // NODE_H
