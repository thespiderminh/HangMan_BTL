#pragma once

class Saw : public Texture
{
private:
    int sawDirection, x;
    int degree = 0;
    bool inTheScreen = false;
    const int y = 542;
    Uint32 loadingTime, tmp;
public:
    Saw()
    {
        loadTextureFromFile("Image/Saw.png");
        createSaw();
    }

    ~Saw()
    {
        free();
    }

    void createSaw()
    {
        sawDirection = rand() % 2;

        (sawDirection == 0) ? x = -100 : x = SCREEN_WIDTH;

        setRect(x, y, 100, 100);

        velocity = 3;

        inTheScreen = true;
    }

    void moveSaw()
    {
        (sawDirection == 0) ? rect.x += velocity : rect.x -= velocity;

        if((rect.x < -100 || rect.x > SCREEN_WIDTH) && inTheScreen == true)
        {
            inTheScreen = false;
            loadingTime = SDL_GetTicks();
            tmp = rand()% 1000 + 2000;
        }

        if(inTheScreen == false && SDL_GetTicks() - loadingTime >= tmp)
        {
            inTheScreen = true;
            createSaw();
        }
    }

    void renderSaw()
    {
        if(inTheScreen == true)
        {
            render(degree, NULL, SDL_FLIP_NONE);
            degree += 7;
        }
     }

};
