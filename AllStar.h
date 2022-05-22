#pragma once

class AllStars : public Star
{
private:

public:
    int number;
    Star one, two, three, four, five, six, seven, eight, nine, ten;
    Star allStars[10] = {one, two, three, four, five, six, seven, eight, nine, ten};

    AllStars()
    {

    }

    AllStars(int a)
    {
        number = a;
    }

    ~AllStars()
    {
        free();
    }

    void moveAllStar()
    {
        for(int i = 0; i < number; i++)
        {
            allStars[i].moveStar();
        }
    }

    void renderAllStar()
    {
        for(int i = 0; i < number; i++)
        {
            allStars[i].renderStar();
        }
    }

    int getNumber()
    {
        return number;
    }
};
