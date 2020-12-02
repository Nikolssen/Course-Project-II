#ifndef STRUCTURES_H_INCLUDED
#define STRUCTURES_H_INCLUDED


#ifndef pi
#define pi 3.14159265358979323846
#endif // pi

enum elem {carbon, nitrogen, phosphorus, oxygen, sulfur, fluorine, chlorine, bromine, iodine, hydrogen};

typedef struct
{
    elem atomName;
    char freebonds;
    char bond;
} atom;

typedef struct
{
    float red;
    float green;
    float blue;
} colour;

typedef struct
{
    short int x;
    short int y;
    short int prevx;
    short int prevy;
    bool shortRear;
    bool shortFront;
    atom element;
} vertex2D;

typedef struct
{
    float x;
    float y;
    float z;
} Point;

typedef struct
{
    Point point;
    elem atomName;
} vertex3D;

typedef struct quaternaryTree
{
    struct quaternaryTree *first;
    struct quaternaryTree *second;
    struct quaternaryTree *third;
    struct quaternaryTree *fourth;
    struct quaternaryTree *parent;
    vertex3D vertex;
    short int index;
    char lastBond;
    char bond;
} node;
#endif // STRUCTURES_H_INCLUDED
