#ifndef CONVERTER_H
#define CONVERTER_H

#include "structures.h"
#include <vector>
#include <math.h>
#include <stdlib.h>


class Converter
{
public:
    Converter();
    ~Converter();
    std::vector<vertex3D> convertToCalotte(std::vector<vertex2D> &vertices2D);


private:
    void tethrahedron(elem vertex);
    void triangle(elem vertex);
    void linear(elem vertex);
    bool isSimple(std::vector<vertex2D> &vertices2D);
    Point spin(Point &root, float phi, float theta);
    char getPossibleBonds(elem activeElement);
    void makeTree(node*root, std::vector<vertex2D> &vertices2D);
    void sortTree(node*root);
    void initCoordinates(node* root);
    void implementCoordinates(node* root);
    void clearTree(node*root);
    void centrifyCoordinates();
    void advancedSpin(node* root);

    std::vector<vertex3D> vertices3D;
};

#endif // CONVERTER_H
