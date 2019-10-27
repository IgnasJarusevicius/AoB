#pragma once
#include "Rectangle.h"

class ProgressBar {
public:
    ProgressBar(float x, float y, float w, float h);
    ~ProgressBar() = default;
    void SetValue(float val);
    void SetPosition(float x, float y);
    void Enable(bool en = true);
    void SetColor(glm::vec3 col);
private:
    Rectangle outer;
    Rectangle inner;

};



