#include "text.h"

void Text::draw(const int x, const int y)
{
    save();
    translate(x,y);
    QRect rect(position.x(), position.y(), width, height);
    drawText(rect, text);
    restore();
}
void Text::move(const int x, const int y)
{
    save();
    remove();
    translate(x,y);
    QRect rect(position.x(), position.y(), width, height);
    drawText(rect, text);
    restore();
}
double Text::perimeter()
{
    return 0;
}
double Text::area()
{
    return 0;
}
void Text::remove()
{
    QRect rect(position.x(), position.y(), width, height);
    eraseRect(rect);
}

void Text::setDimensions(int width, int height)
{
    this->width = width;
    this->height = height;
}

void Text::setTextString(QString textstring)
{
    this->text = textstring;
}

void Text::setAlignment(QString alignment)
{
    if(alignment == "AlignCenter")
    {
        this->alignment = Qt::AlignCenter;
    }
    else if(alignment == "AlignRight")
    {
        this->alignment = Qt::AlignRight;
    }
    else if(alignment == "AlignLeft")
    {
        this->alignment = Qt::AlignLeft;
    }
}
