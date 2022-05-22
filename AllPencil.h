#pragma once

class AllPencils : public Pencil
{
private:

public:
    int number;
    Pencil one, two, three, four, five, six, seven, eight, nine, ten;
    Pencil allPencils[10] = {one, two, three, four, five, six, seven, eight, nine, ten};

    AllPencils()
    {
    }

    AllPencils(int a)
    {
        number = a;
    }

    ~AllPencils()
    {
        free();
    }

    void moveAllPencil()
    {
        for(int i = 0; i < number; i++)
        {
            allPencils[i].movePencil();
        }
    }

    void renderAllPencil()
    {
        for(int i = 0; i < number; i++)
        {
            allPencils[i].renderPencil();
        }
    }

    int getNumber(){
        return number;
    }
};
