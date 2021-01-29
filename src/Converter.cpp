#include "Converter.h"

Converter::Converter()
{

}

Converter::~Converter()
{

}
std::vector<vertex3D> Converter::convertToCalotte(std::vector<vertex2D> &vertices2D)
{

    vertices3D.clear();

    if (isSimple(vertices2D))
        return vertices3D;

    node *root = (node*) malloc(sizeof(node));
    root->vertex.atomName = vertices2D.at(0).element.atomName;
    root->first = nullptr;
    root->second = nullptr;
    root->third = nullptr;
    root->fourth = nullptr;
    root->parent = nullptr;
    root->bond = 0;
    root->index = 0;
    root->lastBond = 0;
    makeTree(root, vertices2D);
    sortTree(root);
    initCoordinates(root);
    clearTree(root);
    centrifyCoordinates();
    return vertices3D;
}
void Converter::makeTree(node*root, std::vector<vertex2D> &vertices2D)
{
    for (unsigned k=root->index+1; k<vertices2D.size(); k++)
    {
        if ((vertices2D.at(root->index).x == vertices2D.at(k).prevx) && (vertices2D.at(root->index).y == vertices2D.at(k).prevy))
        {
            node *daughter = (node*) malloc(sizeof(node));
            daughter->parent = root;
            daughter->first = nullptr;
            daughter->second = nullptr;
            daughter->third = nullptr;
            daughter->fourth = nullptr;
            daughter->index = k;
            daughter->vertex.atomName = vertices2D.at(k).element.atomName;
            daughter->bond = vertices2D.at(k).element.bond;
            daughter->lastBond = 0;
            switch (root->lastBond)
            {
            case 0:
                root->first = daughter;
                break;
            case 1:
                root->second = daughter;
                break;
            case 2:
                root->third = daughter;
                break;
            default:
                root->fourth = daughter;
                break;
            }

            root->lastBond++;
            if (getPossibleBonds(daughter->vertex.atomName)-daughter->bond > 0)
                makeTree(daughter, vertices2D);
        }
    }
    if (vertices2D.at(root->index).element.freebonds)
        for (int j = 0; j<vertices2D.at(root->index).element.freebonds; j++)
        {
            node *daughter = (node*) malloc(sizeof(node));
            daughter->parent = root;
            daughter->first = nullptr;
            daughter->second = nullptr;
            daughter->third = nullptr;
            daughter->fourth = nullptr;
            daughter->index = -1;
            daughter->vertex.atomName = hydrogen;
            daughter->bond = 1;
            daughter->lastBond = 0;
            switch (root->lastBond)
            {
            case 0:
                root->first = daughter;
                break;
            case 1:
                root->second = daughter;
                break;
            case 2:
                root->third = daughter;
                break;
            default:
                root->fourth = daughter;
                break;
            }

            root->lastBond++;
        }
}
void Converter::initCoordinates(node*root)
{
    root->vertex.point = {0, 0, 0};

    if (root->first->bond == 3)
    {
        root->first->vertex.point = {0, 0.8, 0};
        if (root->second != nullptr)
            root->second->vertex.point = {0, -0.8, 0};
    }
    else
        advancedSpin(root);

    if (root->first != nullptr)
        implementCoordinates(root->first);
    if (root->second != nullptr)
        implementCoordinates(root->second);
    if (root->third != nullptr)
        implementCoordinates(root->third);
    if (root->fourth != nullptr)
        implementCoordinates(root->fourth);

}
void Converter::implementCoordinates(node *root)
{
    if (root->lastBond == 0)
        return;

    if ((root->first->bond == 3) || ((root->first->bond == 2)&&(root->bond == 2)) || (root->bond == 3))
    {
        root->first->vertex.point.x = 2 * root->vertex.point.x - root->parent->vertex.point.x;
        root->first->vertex.point.y = 2 * root->vertex.point.y - root->parent->vertex.point.y;
        root->first->vertex.point.z = 2 * root->vertex.point.z - root->parent->vertex.point.z;
    }
    else
        advancedSpin(root);

    if (root->first != nullptr)
        implementCoordinates(root->first);
    if (root->second != nullptr)
        implementCoordinates(root->second);
    if (root->third != nullptr)
        implementCoordinates(root->third);

}

void Converter::sortTree(node*root)
{
    switch(root->lastBond)
    {
    case 2:
        if (root->first->bond < root->second->bond)
        {
            node* temp = root->second;
            root->second = root->first;
            root->first = temp;
        }
        break;
    case 3:
        if (root->second->bond > root->first->bond)
        {
            node* temp = root->second;
            root->second = root->first;
            root->first = temp;
        }
        else if(root->third->bond > root->second->bond)
        {
            node* temp = root->third;
            root->third = root->second;
            root->second = temp;
        }
        break;

    }
    if (root->first != nullptr)
        sortTree(root->first);
    if (root->second != nullptr)
        sortTree(root->second);
    if (root->third != nullptr)
        sortTree(root->third);
    if (root->fourth != nullptr)
        sortTree(root->fourth);
}
void Converter::clearTree(node* root)
{
    if (root->first != nullptr)
        clearTree(root->first);
    if (root->second != nullptr)
        clearTree(root->second);
    if (root->third != nullptr)
        clearTree(root->third);
    if (root->fourth != nullptr)
        clearTree(root->fourth);
    vertices3D.push_back(root->vertex);
    free(root);
}
Point Converter::spin(Point &root, float phi, float theta)
{

    Point result;
    float r = 0.8;
    result.z = r * cos(theta) * sin(phi);
    result.x = r * sin(theta) * sin(phi);
    result.y = r * cos(phi);
    return result;
}

void Converter::advancedSpin(node* root)
{

    const float r = 0.8;
    if (root->parent == nullptr)
    {
        switch (root->lastBond)
        {
        case 4:
            root->fourth->vertex.point.x = root->vertex.point.x + r * sin(0) * sin(0);
            root->fourth->vertex.point.y = root->vertex.point.y + r * cos(0);
            root->fourth->vertex.point.z = root->vertex.point.z + r * cos(0) * sin(0);
        case 3:
            root->third->vertex.point.x = root->vertex.point.x + r * sin(0) * sin(2.0944);
            root->third->vertex.point.y = root->vertex.point.y + r * cos(2.0944);
            root->third->vertex.point.z = root->vertex.point.z + r * cos(0) * sin(2.0944);
        case 2:
            root->second->vertex.point.x = root->vertex.point.x + r * sin(4.18879) * sin(2.0944);
            root->second->vertex.point.y = root->vertex.point.y + r * cos(2.0944);
            root->second->vertex.point.z = root->vertex.point.z + r * cos(4.18879) * sin(2.0944);
        case 1:
            root->first->vertex.point.x = root->vertex.point.x + r * sin(2.0944) * sin(2.0944);
            root->first->vertex.point.y = root->vertex.point.y + r * cos(2.0944);
            root->first->vertex.point.z = root->vertex.point.z + r * cos(2.0944) * sin(2.0944);
            break;
        }
    }
    else
    {

        if ((round(root->vertex.point.x *100) == round(root->parent->vertex.point.x * 100))&& (round(root->vertex.point.z *100) == round(root->parent->vertex.point.z * 100)))
        {
            if (root->vertex.point.y>root->parent->vertex.point.y)
            {
                if (root->third != nullptr)
                {
                    root->third->vertex.point.x = root->vertex.point.x + r * sin(3.14159) * sin(1.0472);
                    root->third->vertex.point.y = root->vertex.point.y + r * cos(1.0472);
                    root->third->vertex.point.z = root->vertex.point.z + r * cos(3.14159) * sin(1.0472);
                }


                if (root->second != nullptr)
                {
                    root->second->vertex.point.x = root->vertex.point.x + r * sin(-1.0472) * sin(1.0472);
                    root->second->vertex.point.y = root->vertex.point.y + r * cos(1.0472);
                    root->second->vertex.point.z = root->vertex.point.z + r * cos(-1.0472) * sin(1.0472);
                }

                if (root->first != nullptr)
                {
                    root->first->vertex.point.x = root->vertex.point.x + r * sin(1.0472) * sin(1.0472);
                    root->first->vertex.point.y = root->vertex.point.y + r * cos(1.0472);
                    root->first->vertex.point.z = root->vertex.point.z + r * cos(1.0472) * sin(1.0472);
                }
                return;
            }
            else
            {
                if (root->third != nullptr)
                {
                    root->third->vertex.point.x = root->vertex.point.x + r * sin(0) * sin(2.0944);
                    root->third->vertex.point.y = root->vertex.point.y + r * cos(2.0944);
                    root->third->vertex.point.z = root->vertex.point.z + r * cos(0) * sin(2.0944);
                }
                if (root->second != nullptr)
                {
                    root->second->vertex.point.x = root->vertex.point.x + r * sin(4.18879) * sin(2.0944);
                    root->second->vertex.point.y = root->vertex.point.y + r * cos(2.0944);
                    root->second->vertex.point.z = root->vertex.point.z + r * cos(4.18879) * sin(2.0944);
                }

                if (root->first != nullptr)
                {
                    root->first->vertex.point.x = root->vertex.point.x + r * sin(2.0944) * sin(2.0944);
                    root->first->vertex.point.y = root->vertex.point.y + r * cos(2.0944);
                    root->first->vertex.point.z = root->vertex.point.z + r * cos(2.0944) * sin(2.0944);
                }
                return;
            }
        }
        else
        {
            if ((root->vertex.point.x < root->parent->vertex.point.x) && (root->vertex.point.y < root->parent->vertex.point.y) && (root->vertex.point.z < root->parent->vertex.point.z))
            {
                if (root->third != nullptr)
                {
                    root->third->vertex.point.x = root->vertex.point.x + r * sin(0) * sin(3.14159);
                    root->third->vertex.point.y = root->vertex.point.y + r * cos(3.14159);
                    root->third->vertex.point.z = root->vertex.point.z + r * cos(0) * sin(3.14159);
                }
                if (root->second != nullptr)
                {
                    root->second->vertex.point.x = root->vertex.point.x + r * sin(3.14159) * sin(1.0472);
                    root->second->vertex.point.y = root->vertex.point.y + r * cos(1.0472);
                    root->second->vertex.point.z = root->vertex.point.z + r * cos(3.14159) * sin(1.0472);
                }

                if (root->first != nullptr)
                {

                    root->first->vertex.point.x = root->vertex.point.x + r * sin(-1.0472) * sin(1.0472);
                    root->first->vertex.point.y = root->vertex.point.y + r * cos(1.0472);
                    root->first->vertex.point.z = root->vertex.point.z + r * cos(-1.0472) * sin(1.0472);
                }
                return;
            }

            if ((root->vertex.point.x > root->parent->vertex.point.x) && (root->vertex.point.y < root->parent->vertex.point.y) && (root->vertex.point.z < root->parent->vertex.point.z))
            {
                if (root->third != nullptr)
                {
                    root->third->vertex.point.x = root->vertex.point.x + r * sin(0) * sin(3.14159);
                    root->third->vertex.point.y = root->vertex.point.y + r * cos(3.14159);
                    root->third->vertex.point.z = root->vertex.point.z + r * cos(0) * sin(3.14159);
                }

                if (root->second != nullptr)
                {
                    root->second->vertex.point.x = root->vertex.point.x + r * sin(3.14159) * sin(1.0472);
                    root->second->vertex.point.y = root->vertex.point.y + r * cos(1.0472);
                    root->second->vertex.point.z = root->vertex.point.z + r * cos(3.14159) * sin(1.0472);
                }
                if (root->first != nullptr)
                {

                    root->first->vertex.point.x = root->vertex.point.x + r * sin(1.0472) * sin(1.0472);
                    root->first->vertex.point.y = root->vertex.point.y + r * cos(1.0472);
                    root->first->vertex.point.z = root->vertex.point.z + r * cos(1.0472) * sin(1.0472);
                }
                return;
            }

            if ((root->vertex.point.x < root->parent->vertex.point.x) && (root->vertex.point.y > root->parent->vertex.point.y) && (root->vertex.point.z > root->parent->vertex.point.z))
            {
                if (root->third != nullptr)
                {
                    root->third->vertex.point.x = root->vertex.point.x + r * sin(0) * sin(0);
                    root->third->vertex.point.y = root->vertex.point.y + r * cos(0);
                    root->third->vertex.point.z = root->vertex.point.z + r * cos(0) * sin(0);
                }

                if (root->second != nullptr)
                {
                    root->second->vertex.point.x = root->vertex.point.x + r * sin(0) * sin(2.0944);
                    root->second->vertex.point.y = root->vertex.point.y + r * cos(2.0944);
                    root->second->vertex.point.z = root->vertex.point.z + r * cos(0) * sin(2.0944);
                }
                if (root->first != nullptr)
                {

                    root->first->vertex.point.x = root->vertex.point.x + r * sin(4.18879) * sin(2.0944);
                    root->first->vertex.point.y = root->vertex.point.y + r * cos(2.0944);
                    root->first->vertex.point.z = root->vertex.point.z + r * cos(4.18879) * sin(2.0944);
                }
                return;

            }
            if ((root->vertex.point.x > root->parent->vertex.point.x) && (root->vertex.point.y > root->parent->vertex.point.y) && (root->vertex.point.z > root->parent->vertex.point.z))
            {
                if (root->third != nullptr)
                {
                    root->third->vertex.point.x = root->vertex.point.x + r * sin(0) * sin(0);
                    root->third->vertex.point.y = root->vertex.point.y + r * cos(0);
                    root->third->vertex.point.z = root->vertex.point.z + r * cos(0) * sin(0);
                }

                if (root->second != nullptr)
                {
                    root->second->vertex.point.x = root->vertex.point.x + r * sin(0) * sin(2.0944);
                    root->second->vertex.point.y = root->vertex.point.y + r * cos(2.0944);
                    root->second->vertex.point.z = root->vertex.point.z + r * cos(0) * sin(2.0944);
                }
                if (root->first != nullptr)
                {

                    root->first->vertex.point.x = root->vertex.point.x + r * sin(2.0944) * sin(2.0944);
                    root->first->vertex.point.y = root->vertex.point.y + r * cos(2.0944);
                    root->first->vertex.point.z = root->vertex.point.z + r * cos(2.0944) * sin(2.0944);
                }
                return;
            }

            if ((round(root->vertex.point.x *100) == round(root->parent->vertex.point.x * 100)) && (root->vertex.point.y < root->parent->vertex.point.y) && (root->vertex.point.z > root->parent->vertex.point.z))
            {
                if (root->third != nullptr)
                {
                    root->third->vertex.point.x = root->vertex.point.x + r * sin(0) * sin(3.14159);
                    root->third->vertex.point.y = root->vertex.point.y + r * cos(3.14159);
                    root->third->vertex.point.z = root->vertex.point.z + r * cos(0) * sin(3.14159);
                }

                if (root->second != nullptr)
                {
                    root->second->vertex.point.x = root->vertex.point.x + r * sin(1.0472) * sin(1.0472);
                    root->second->vertex.point.y = root->vertex.point.y + r * cos(1.0472);
                    root->second->vertex.point.z = root->vertex.point.z + r * cos(1.0472) * sin(1.0472);
                }
                if (root->first != nullptr)
                {
                    root->first->vertex.point.x = root->vertex.point.x + r * sin(-1.0472) * sin(1.0472);
                    root->first->vertex.point.y = root->vertex.point.y + r * cos(1.0472);
                    root->first->vertex.point.z = root->vertex.point.z + r * cos(-1.0472) * sin(1.0472);
                }
                return;

            }

            if ((round(root->vertex.point.x *100) == round(root->parent->vertex.point.x * 100)) && (root->vertex.point.y > root->parent->vertex.point.y) && (root->vertex.point.z < root->parent->vertex.point.z))
            {
                if (root->third != nullptr)
                {
                    root->third->vertex.point.x = root->vertex.point.x + r * sin(0) * sin(0);
                    root->third->vertex.point.y = root->vertex.point.y + r * cos(0);
                    root->third->vertex.point.z = root->vertex.point.z + r * cos(0) * sin(0);
                }
                if (root->second != nullptr)
                {
                    root->second->vertex.point.x = root->vertex.point.x + r * sin(4.18879) * sin(2.0944);
                    root->second->vertex.point.y = root->vertex.point.y + r * cos(2.0944);
                    root->second->vertex.point.z = root->vertex.point.z + r * cos(4.18879) * sin(2.0944);
                }

                if (root->first != nullptr)
                {
                    root->first->vertex.point.x = root->vertex.point.x + r * sin(2.0944) * sin(2.0944);
                    root->first->vertex.point.y = root->vertex.point.y + r * cos(2.0944);
                    root->first->vertex.point.z = root->vertex.point.z + r * cos(2.0944) * sin(2.0944);
                }
                return;

            }

            if ((round(root->vertex.point.x *100) == round(root->parent->vertex.point.x * 100)) && (root->vertex.point.y < root->parent->vertex.point.y) && (root->vertex.point.z < root->parent->vertex.point.z))
            {
                if (root->third != nullptr)
                {
                    root->third->vertex.point.x = root->vertex.point.x + r * sin(0) * sin(3.14159);
                    root->third->vertex.point.y = root->vertex.point.y + r * cos(3.14159);
                    root->third->vertex.point.z = root->vertex.point.z + r * cos(0) * sin(3.14159);
                }

                if (root->second != nullptr)
                {
                    root->second->vertex.point.x = root->vertex.point.x + r * sin(2.0944) * sin(1.0472);
                    root->second->vertex.point.y = root->vertex.point.y + r * cos(1.0472);
                    root->second->vertex.point.z = root->vertex.point.z + r * cos(2.0944) * sin(1.0472);
                }

                if (root->first != nullptr)
                {
                    root->first->vertex.point.x = root->vertex.point.x + r * sin(4.18879) * sin(1.0472);
                    root->first->vertex.point.y = root->vertex.point.y + r * cos(1.0472);
                    root->first->vertex.point.z = root->vertex.point.z + r * cos(4.18879) * sin(1.0472);
                }
                return;
            }

            if ((round(root->vertex.point.x *100) == round(root->parent->vertex.point.x * 100)) && (root->vertex.point.y > root->parent->vertex.point.y) && (root->vertex.point.z > root->parent->vertex.point.z))
            {
                if (root->third != nullptr)
                {
                    root->third->vertex.point.x = root->vertex.point.x + r * sin(0) * sin(0);
                    root->third->vertex.point.y = root->vertex.point.y + r * cos(0);
                    root->third->vertex.point.z = root->vertex.point.z + r * cos(0) * sin(0);
                }

                if (root->second != nullptr)
                {
                    root->second->vertex.point.x = root->vertex.point.x + r * sin(1.0472) * sin(1.0472);
                    root->second->vertex.point.y = root->vertex.point.y + r * cos(1.0472);
                    root->second->vertex.point.z = root->vertex.point.z + r * cos(1.0472) * sin(1.0472);
                }

                if (root->first != nullptr)
                {
                    root->first->vertex.point.x = root->vertex.point.x + r * sin(-1.0472) * sin(1.0472);
                    root->first->vertex.point.y = root->vertex.point.y + r * cos(1.0472);
                    root->first->vertex.point.z = root->vertex.point.z + r * cos(-1.0472) * sin(1.0472);
                }
                return;
            }




            if ((root->vertex.point.x < root->parent->vertex.point.x) && (root->vertex.point.y > root->parent->vertex.point.y) && (root->vertex.point.z < root->parent->vertex.point.z))
            {
                if (root->third != nullptr)
                {
                    root->third->vertex.point.x = root->vertex.point.x + r * sin(0) * sin(0);
                    root->third->vertex.point.y = root->vertex.point.y + r * cos(0);
                    root->third->vertex.point.z = root->vertex.point.z + r * cos(0) * sin(0);
                }

                if (root->second != nullptr)
                {
                    root->second->vertex.point.x = root->vertex.point.x + r * sin(3.14159) * sin(2.0944);
                    root->second->vertex.point.y = root->vertex.point.y + r * cos(2.0944);
                    root->second->vertex.point.z = root->vertex.point.z + r * cos(3.14159) * sin(2.0944);
                }

                if (root->first != nullptr)
                {
                    root->first->vertex.point.x = root->vertex.point.x + r * sin(-1.0472) * sin(2.0944);
                    root->first->vertex.point.y = root->vertex.point.y + r * cos(2.0944);
                    root->first->vertex.point.z = root->vertex.point.z + r * cos(-1.0472) * sin(2.0944);
                }

                return;
            }
            if ((root->vertex.point.x > root->parent->vertex.point.x) && (root->vertex.point.y > root->parent->vertex.point.y) && (root->vertex.point.z < root->parent->vertex.point.z))
            {
                if (root->third != nullptr)
                {
                    root->third->vertex.point.x = root->vertex.point.x + r * sin(0) * sin(0);
                    root->third->vertex.point.y = root->vertex.point.y + r * cos(0);
                    root->third->vertex.point.z = root->vertex.point.z + r * cos(0) * sin(0);
                }

                if (root->second != nullptr)
                {
                    root->second->vertex.point.x = root->vertex.point.x + r * sin(3.14159) * sin(2.0944);
                    root->second->vertex.point.y = root->vertex.point.y + r * cos(2.0944);
                    root->second->vertex.point.z = root->vertex.point.z + r * cos(3.14159) * sin(2.0944);
                }

                if (root->first != nullptr)
                {
                    root->first->vertex.point.x = root->vertex.point.x + r * sin(1.0472) * sin(2.0944);
                    root->first->vertex.point.y = root->vertex.point.y + r * cos(2.0944);
                    root->first->vertex.point.z = root->vertex.point.z + r * cos(1.0472) * sin(2.0944);
                }

                return;
            }

            if ((root->vertex.point.x < root->parent->vertex.point.x) && (root->vertex.point.y < root->parent->vertex.point.y) && (root->vertex.point.z > root->parent->vertex.point.z))
            {
                if (root->third != nullptr)
                {
                    root->third->vertex.point.x = root->vertex.point.x + r * sin(0) * sin(3.14159);
                    root->third->vertex.point.y = root->vertex.point.y + r * cos(3.14159);
                    root->third->vertex.point.z = root->vertex.point.z + r * cos(0) * sin(3.14159);
                }

                if (root->second != nullptr)
                {
                    root->second->vertex.point.x = root->vertex.point.x + r * sin(4.18879) * sin(1.0472);
                    root->second->vertex.point.y = root->vertex.point.y + r * cos(1.0472);
                    root->second->vertex.point.z = root->vertex.point.z + r * cos(4.18879) * sin(1.0472);
                }
                if (root->first != nullptr)
                {
                    root->first->vertex.point.x = root->vertex.point.x + r * sin(0) * sin(1.0472);
                    root->first->vertex.point.y = root->vertex.point.y + r * cos(1.0472);
                    root->first->vertex.point.z = root->vertex.point.z + r * cos(0) * sin(1.0472);
                }
                return;
            }

            if ((root->vertex.point.x > root->parent->vertex.point.x) && (root->vertex.point.y < root->parent->vertex.point.y) && (root->vertex.point.z > root->parent->vertex.point.z))
            {
                if (root->third != nullptr)
                {
                    root->third->vertex.point.x = root->vertex.point.x + r * sin(0) * sin(3.14159);
                    root->third->vertex.point.y = root->vertex.point.y + r * cos(3.14159);
                    root->third->vertex.point.z = root->vertex.point.z + r * cos(0) * sin(3.14159);
                }

                if (root->second != nullptr)
                {
                    root->second->vertex.point.x = root->vertex.point.x + r * sin(2.0944) * sin(1.0472);
                    root->second->vertex.point.y = root->vertex.point.y + r * cos(1.0472);
                    root->second->vertex.point.z = root->vertex.point.z + r * cos(2.0944) * sin(1.0472);
                }

                if (root->first != nullptr)
                {
                    root->first->vertex.point.x = root->vertex.point.x + r * sin(0) * sin(1.0472);
                    root->first->vertex.point.y = root->vertex.point.y + r * cos(1.0472);
                    root->first->vertex.point.z = root->vertex.point.z + r * cos(0) * sin(1.0472);
                }
                return;
            }
        }

    }

}

void Converter::tethrahedron(elem vertex)

{

    bool top = false;
    float degree;

    switch(vertex)
    {
    case carbon:

        top = true;
        degree = 1.9111355;  //109.5
        break;

    case phosphorus:
        degree = 1.623156; //93.5
        break;
    case nitrogen:
    default:
        degree = 1.8675023; //107.8
        break;

    }
    Point root, _1, _2, _3, _4;
    if (top)
    {
        root = {0, 0, 0};
        _1 = spin(root, 0, 0);
        _2 = spin(root, degree, 2.0944);
        _3 = spin(root, degree, 4.18879);
        _4 = spin(root, degree, 0);
    }
    else
    {
        root = {0, 0, 0};
        degree = cos(degree/2);
        degree = pi - acos(sqrt(1-4/3*degree*degree));
        _1 = spin(root, degree, 2.0944);
        _2 = spin(root, degree, 4.18879);
        _3 = spin(root, degree, 0);
    }
    vertex3D _point = {root, vertex};
    vertices3D.push_back(_point);
    _point.point =_1;
    _point.atomName = hydrogen;
    vertices3D.push_back(_point);
    _point.point = _2;
    vertices3D.push_back(_point);
    _point.point = _3;
    vertices3D.push_back(_point);
    if (top)
    {
        _point.point = _4;
        vertices3D.push_back(_point);
    }

}
void Converter::centrifyCoordinates()
{
    float x, y, z;
    x = y = z = 0;
    for (unsigned int i = 0; i<vertices3D.size(); i++)
    {
        x+=vertices3D[i].point.x;
        y+=vertices3D[i].point.y;
        z+=vertices3D[i].point.z;
    }
    x /= vertices3D.size();
    y /= vertices3D.size();
    z /= vertices3D.size();

    for (unsigned int i = 0; i<vertices3D.size(); i++)
    {
        vertices3D[i].point.x -= x;
        vertices3D[i].point.y -= y;
        vertices3D[i].point.z -= z;
    }
}
void Converter::triangle(elem vertex)
{
    float degree;
    switch(vertex)
    {
    case sulfur:
        degree = 1.605703;
        break;
    default:
        degree = 1.81514242;
    }
    vertex3D root = {{0, 0, 0}, vertex};
    vertices3D.push_back(root);
    float r = 0.8;
    Point _1;
    _1.y = - r * cos(degree/2);
    _1.z = 0;
    _1.x = r * sin(degree/2);

    root.point = _1;
    root.atomName = hydrogen;
    vertices3D.push_back(root);
    Point _2;
    _2 = _1;
    _2.x = - _2.x;
    root.point = _2;
    vertices3D.push_back(root);
}

void Converter::linear(elem vertex)
{
    vertex3D _1 = {{-0.4, 0, 0}, vertex};
    vertices3D.push_back(_1);
    vertex3D _2 = {{0.4, 0, 0}, hydrogen};
    vertices3D.push_back(_2);
}

bool Converter::isSimple(std::vector<vertex2D> &vertices2D)
{

    if (vertices2D.size() ==1)
    {

        switch(vertices2D[0].element.atomName)
        {
        case carbon:
        case phosphorus:
        case nitrogen:
            tethrahedron(vertices2D[0].element.atomName);
            break;
        case sulfur:
        case oxygen:
            triangle(vertices2D[0].element.atomName);
            break;
        default:
            linear(vertices2D[0].element.atomName);

        }
        return true;
    }
    return false;

}
int Converter::getPossibleBonds(elem activeElement)
{
    switch (activeElement)
    {
    case carbon:
        return 4;
    case nitrogen:
    case phosphorus:
        return 3;
    case oxygen:
    case sulfur:
        return 2;
    default:
        return 1;
    }
}
