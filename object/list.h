#pragma once
//------------------------------------------------------------------------------

class Path {
public:
    Path();
    ~Path();

    class Item {
    public:
        Item* next;
        float x, y;
        int dir;
        bool att;
    } *first;

    void Add(float, float);
    void Remove();
    int count;
};