#pragma once

int Startype[20] = {1,1,1,1,1,1,1,1,1,1,1,1,1,2,2,2,2,2,3,3};
Uint32 timeOnScreen[4] = {0, 8000, 5000, 2000};

class Star : public Texture
{
private:
    int x, y, i = 1;
    const int maxPosition = SCREEN_WIDTH - 100;
public:
    int type;
    Uint32 appearTime = 0, dissappearTime = 0, tmp = 0;
    bool isOnTheScreen = false;

    Star()
    {
        createStar();
    }

    ~Star()
    {
        free();
    }

    void createStar()
    {
        type = Startype[rand() % 20];
        x = rand()%maxPosition + 50;
        y = rand()%450 + 100;
        loadTextureFromFile("Image/Star" + to_string(type) + ".png");
        appearTime = SDL_GetTicks();
        setRect(x, y, 30, 30);
        isOnTheScreen = true;
    }

    void moveStar()
    {
        if(SDL_GetTicks() - appearTime >= timeOnScreen[type] && isOnTheScreen == true)
        {
            loadTextureFromFile();
            rect.x = -999;
            dissappearTime = SDL_GetTicks();
            isOnTheScreen = false;
            tmp = rand() % 3000 + 1000;
        }
        if(SDL_GetTicks() - dissappearTime >= tmp && isOnTheScreen == false)
        {
            createStar();
        }
    }

    void renderStar()
    {
        if(isOnTheScreen == true)
        {
            render();
        }
    }
};
