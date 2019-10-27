#include "ProgressBar.h"

ProgressBar::ProgressBar(float x, float y, float w, float h) :
    outer(x, y, w, h),
    inner(x+1, y+1, w-2, h-2)
{
    outer.SetColor(glm::vec3(0.0f, 0.0f, 0.0f));
    inner.SetColor(glm::vec3(1.0f, 0.0f, 0.0f));
}

void ProgressBar::SetValue(float val)
{
    if (val > 1.0f) val = 1.0f;
    else if (val < 0.0f) val = 0.0f;
    inner.SetScale(val, 1.0f);
}

void ProgressBar::SetPosition(float x, float y)
{
    inner.SetPosition(x+1, y+1, -y);
    outer.SetPosition(x, y, -y);
}

void ProgressBar::SetColor(glm::vec3 col)
{
    inner.SetColor(col);
}

void ProgressBar::Enable(bool en)
{
    inner.Enable(en);
    outer.Enable(en);
}



