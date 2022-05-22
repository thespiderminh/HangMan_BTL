#pragma once

#include "Chunk.h"

using namespace start;

class Texture
{
private:
    SDL_Texture *texture;
    int height = 0;
public:
    int base = 523, direction = 0, velocity = 0;
    double jumpSpeed = 0;
    Chunk jumpSound, jumpSound2;
    bool isFalling = false, isJumping = false, isJumping2 = false, isStandingOnPencil = false, isPressingLeft = false, isPressingRight = false;

    SDL_Rect rect;

    Texture()
    {
        texture = NULL;
        jumpSound.loadSoundFromFile("Music/Jump.mp3");
        jumpSound2.loadSoundFromFile("Music/Jump2.mp3");
    }

    ~Texture()
    {
        free();
    }

    void free()
    {
        if( texture != NULL )
        {
            SDL_DestroyTexture( texture );
            texture = NULL;
        }
    }
    Texture(string path)
    {
        texture = loadTexture(renderer, path.c_str());
        jumpSound.loadSoundFromFile("Music/Jump.mp3");
        jumpSound2.loadSoundFromFile("Music/Jump2.mp3");
    }

    void loadTextureFromFile()
    {
        texture = NULL;
    }

    void loadTextureFromFile(string path)
    {
        texture = loadTexture(renderer, path.c_str());
    }

    void render(int x, int y, int w, int h)
    {
        rect = {x, y, w, h};
        SDL_RenderCopy(renderer, texture, NULL, &rect);
    }

    void render()
    {
        SDL_RenderCopy(renderer, texture, NULL, &rect);
    }

    void render(int x, int y, int w, int h, double angle, SDL_Point* center, SDL_RendererFlip flip)
    {
        rect = {x, y, w, h};
        SDL_RenderCopyEx( renderer, texture, NULL, &rect, angle, center, flip );
    }

    void render(double angle, SDL_Point* center, SDL_RendererFlip flip)
    {
        SDL_RenderCopyEx( renderer, texture, NULL, &rect, angle, center, flip );
    }

    void render(SDL_Rect* clip)
    {
        SDL_RenderCopy(renderer, texture, clip, &rect);
    }

    void setRect(int x, int y, int w, int h)
    {
        rect = {x, y, w, h};
    }

    void render(Uint8 r)
    {
        SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
        SDL_SetTextureAlphaMod(texture, r);
        SDL_RenderCopy(renderer, texture, NULL, &rect);
    }

    void handleEventButNotMove()
    {
        if(event.type == SDL_KEYDOWN && event.key.repeat == 0)
        {
            switch(event.key.keysym.sym)
            {
            case SDLK_RIGHT:
                isPressingRight = true;
                break;
            case SDLK_LEFT:
                isPressingLeft = true;
                break;
            default:
                break;
            }
        }

        else if(event.type == SDL_KEYUP && event.key.repeat == 0)
        {
            switch(event.key.keysym.sym)
            {
            case SDLK_RIGHT:
                isPressingRight = false;
                break;
            case SDLK_LEFT:
                isPressingLeft = false;
                break;
            default:
                break;
            }
        }
    }

    void handleEvent(SDL_Event &event, int &frame, SDL_Rect* currentClip, Uint32 &oldTick)
    {
        if(event.type == SDL_KEYDOWN && event.key.repeat == 0)
        {
            switch(event.key.keysym.sym)
            {
            case SDLK_RIGHT:
                velocity += RUN_SPEED;  isPressingRight = true;
                break;
            case SDLK_LEFT:
                velocity -= RUN_SPEED; isPressingLeft = true;
                break;
            case SDLK_UP:
                if(isJumping2 == false)
                {
                    if(isJumping == false)
                    {
                        isJumping = true;
                        jumpSound.playonce();
                    }
                    else
                    {
                        isJumping2 = true;
                        jumpSound2.playonce();
                    }
                    jumpSpeed = MAX_JUMP_SPEED;
                    isStandingOnPencil = false;
                }
                break;
            default:
                break;
            }
        }
        else if(event.type == SDL_KEYUP && event.key.repeat == 0)
        {
            frame = 0;
            currentClip = &Move[0];
            switch(event.key.keysym.sym)
            {
            case SDLK_RIGHT:
                velocity -= RUN_SPEED; isPressingRight = false;
                break;
            case SDLK_LEFT:
                velocity += RUN_SPEED; isPressingLeft = false;
                break;
            default:
                break;
            }
        }
    }

    void stickMove(int &frame, SDL_Rect* *currentClip)
    {
        rect.x += velocity;

        if(velocity > 0) direction = 1;
        else if(velocity < 0) direction = -1;

        if(rect.x < 0) rect.x = 0;
        else if((rect.x + rect.w) > SCREEN_WIDTH) rect.x = SCREEN_WIDTH - rect.w;

        if(direction == 1)
        {
            if(isJumping == false)
            {
                loadTextureFromFile("Image/MoveRight.png");
            }
            else if(isJumping == true)
            {
                frame = 0;
                loadTextureFromFile("Image/JumpRight.png");
            }
        }
        else if(direction == -1)
        {
            if(isJumping == false)
            {
                loadTextureFromFile("Image/MoveLeft.png");
            }
            else if(isJumping == true)
            {
                frame = 0;
                loadTextureFromFile("Image/JumpLeft.png");
            }
        }

        if(velocity != 0 && isJumping == false) frame++;

        if(frame/5 == 5) frame = 0;

        *currentClip = &Move[frame/5];

        if(isJumping == true)
        {
            rect.y -= jumpSpeed;
            jumpSpeed -= ACCELARATION;

            if(jumpSpeed < 0) isFalling = true;
            else if(jumpSpeed > 0) isFalling = false;

            if(rect.y >= base)
            {
                jumpSpeed = 0;
                rect.y = base;
                isJumping = false;
                isJumping2 = false;
                isFalling = false;
            }
            if(rect.y <= 0)
            {
                jumpSpeed = -1;
                rect.y = 0;
            }
        }
    }
};
