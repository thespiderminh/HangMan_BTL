#pragma once

class Booster : public Texture
{
private:
    int x, y, i = 1;
    const int maxPosition = SCREEN_WIDTH - 100;
public:
    Uint32 appearTime = 0, dissappearTime = 0, tmp = 0;
    bool isOnTheScreen = false;

    Booster()
    {
        createBooster();
    }

    ~Booster()
    {
        free();
    }

    void createBooster()
    {
        loadTextureFromFile("Image/Booster.png");
        x = rand()%maxPosition + 50;
        y = rand()%31 * 10 + 180;
        appearTime = SDL_GetTicks();
        setRect(x, y, 30, 30);
        isOnTheScreen = true;
    }

    void moveBooster()
    {
        if(SDL_GetTicks() - appearTime >= 5000 && isOnTheScreen == true)
        {
            loadTextureFromFile();
            rect.x = -999;
            dissappearTime = SDL_GetTicks();
            isOnTheScreen = false;
            tmp = rand() % 5000 + 10000;
        }
        if(SDL_GetTicks() - dissappearTime >= tmp && isOnTheScreen == false)
        {
            createBooster();
        }
    }

    void renderBooster()
    {
        render();
    }
};
