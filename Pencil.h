#pragma once

using namespace start;

class Pencil : public Texture
{
private:
    int x, y, bodyLength, type;
    Uint32 disappearTime, tmp;
public:
    bool inTheScreen = false;
    Texture Head, Body, Eraser;
    int velo, minSpeed = 1;

    Pencil()
    {
        createPencil();
    }

    ~Pencil()
    {
        free();
        Head.free();
        Body.free();
        Eraser.free();
    }

    void createOne(int _x, int _y, int _bodyLength, int _type)
    {
        x = _x; y = _y; bodyLength = _bodyLength; type = _type;

        Head.loadTextureFromFile("Image/Pencil" + to_string(type) + "Head.png");
        Body.loadTextureFromFile("Image/Pencil" + to_string(type) + "Body.png");
        Eraser.loadTextureFromFile("Image/Pencil" + to_string(type) + "Eraser.png");

        Head.setRect(x, y, 71, 35);
        Body.setRect(x + Head.rect.w, y, bodyLength, 35);
        Eraser.setRect(x + Head.rect.w + bodyLength, y, 54, 35);
    }

    void createPencil()
    {
        bodyLength = rand() % 200 + 100;

        if (rand()%2 == 0)
        {
            x = - bodyLength - 71 - 54;
            velo = rand()%3 + minSpeed;
        }
        else
        {
            x = SCREEN_WIDTH;
            velo = -(rand()%3 + minSpeed);
        }

        y = rand()%31 * 10 + 190;

        inTheScreen = true;

        type = rand()%12+1;

        Head.loadTextureFromFile("Image/Pencil" + to_string(type) + "Head.png");
        Body.loadTextureFromFile("Image/Pencil" + to_string(type) + "Body.png");
        Eraser.loadTextureFromFile("Image/Pencil" + to_string(type) + "Eraser.png");

        Head.setRect(x, y, 71, 35);
        Body.setRect(x + Head.rect.w, y, bodyLength, 35);
        Eraser.setRect(x + Head.rect.w + bodyLength, y, 54, 35);

    }

    void movePencil()
    {
        Head.rect.x += velo;
        Body.rect.x += velo;
        Eraser.rect.x += velo;

        if(inTheScreen == true && (Eraser.rect.x + Eraser.rect.w < -10 || Head.rect.x > SCREEN_WIDTH + 10))
        {
            inTheScreen = false;
            disappearTime = SDL_GetTicks();
            tmp = rand() % 2000 + 100;
        }

        if(inTheScreen == false && SDL_GetTicks() - disappearTime >= tmp)
        {
            createPencil();
        }
    }

    void renderPencil()
    {
        if(inTheScreen == true)
        {
            Head.render();
            Body.render();
            Eraser.render();
        }
    }

    void destroy()
    {
        Head.rect.x = -99;
        Body.rect.x = -99;
        Eraser.rect.x = -99;
    }
};
