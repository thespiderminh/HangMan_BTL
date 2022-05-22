#pragma once

bool quit = false, again = false, _again = false;

bool checkAnswer(char ch)
{
    for(int i = 0; i < correctAnswers.size(); i++)
    {
        if(ch == correctAnswers[i]) return false;
    }
    correctAnswers.push_back(ch);
    return true;

}

void startgame(Image* title, Image* start, Image* screen, Chunk* Button, Chunk* Click)
{
    Texture _title("Image/Title.png");
    _title.rect = {1100, 100, 477, 267};

    while (_title.rect.x > 240)
    {
        while (SDL_PollEvent(&event) != 0)
        {
            if (event.type == SDL_QUIT)
            {
                quitSDL(gWindow, renderer);
                return;
            }
        }
        _title.rect.x -= 3;
        SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(renderer);

        _title.render();

        SDL_RenderPresent(renderer);
    }
    screen->display(0, 0);
    title->display(240, 100);
    start->display(330, 550);
    SDL_UpdateWindowSurface(gWindow);

    bool checkCollision = 0, oldCollision = 0;
    while (!quit)
    {
        while (SDL_PollEvent(&event) != 0)
        {
            if (event.type == SDL_QUIT)
            {
                quitSDL(gWindow, renderer);
                return;
            }
            else if (event.type == SDL_MOUSEMOTION)
            {
                oldCollision = checkCollision;
                if ((event.motion.x > start->rect.x && event.motion.x < (start->rect.x + start->rect.w)) && (event.motion.y > start->rect.y && event.motion.y < (start->rect.y + start->rect.h)))
                    checkCollision = 1;
                else
                    checkCollision = 0;
                if(oldCollision != checkCollision)
                    Button->playonce();
                if (checkCollision == 0)
                    start->loadImage("Image/PlayButton1.png");
                else
                    start->loadImage("Image/PlayButton2.png");
                start->display(330, 550);
                SDL_UpdateWindowSurface(gWindow);
            }
            if (checkCollision == 1 && event.type == SDL_MOUSEBUTTONDOWN)
            {
                Click->playonce();
                return;
            }
        }
    }
}

void part1(Image* screen, Image* rule, Image* wrong, Image* hangman, Image* word, Image* a, Image* n, Image* g, Image* m, Image* h, Chunk* Correct, Chunk* Incorrect, Image* gameOverScreen)
{
    int wrongGuess = 0, rightGuess = 0;
    while (!quit)
    {
        screen->display(0, 0);
        rule->display(0, 0);
        wrong->display(500, 200);
        hangman->display(100, 230);
        word->display(50, 750);
        a->display(180, 670);
        n->display(280, 670);
        g->display(380, 670);
        m->display(480, 680);
        h->display(70, 680);
        SDL_UpdateWindowSurface(gWindow);

        while (SDL_PollEvent(&event) != 0)
        {
            if (event.type == SDL_QUIT)
            {
                quitSDL(gWindow, renderer);
                return;
            }
            else if (event.type == SDL_KEYDOWN && rightGuess <= 3 && event.key.repeat == 0)
            {
                switch (event.key.keysym.sym)
                {
                case SDLK_a:
                    if(checkAnswer('a'))
                    {
                        rightGuess++;
                        a->loadImage("Image/a.png");
                        Correct->playonce();
                    }
                    break;
                case SDLK_h:
                    if(checkAnswer('h'))
                    {
                        rightGuess++;
                        h->loadImage("Image/h.png");
                        Correct->playonce();
                    }
                    break;
                case SDLK_n:
                    if(checkAnswer('n'))
                    {
                        rightGuess++;
                        n->loadImage("Image/n.png");
                        Correct->playonce();
                    }
                    break;
                case SDLK_g:
                    if(checkAnswer('g'))
                    {
                        rightGuess++;
                        g->loadImage("Image/g.png");
                        Correct->playonce();
                    }
                    break;
                case SDLK_m:
                    if(checkAnswer('m'))
                    {
                        rightGuess++;
                        m->loadImage("Image/m.png");
                        Correct->playonce();
                    }
                    break;
                default:
                    wrongGuess++;
                    Incorrect->playonce();
                    break;
                }
            }
            else if (event.type == SDL_KEYDOWN && rightGuess > 3 && event.key.repeat == 0)
            {
                wrongGuess++;
                Incorrect->playonce();
            }
            if (wrongGuess == 1)
            {
                hangman->loadImage("Image/Hangman1.png");
                wrong->loadImage("Image/Wrong1.png");
            }
            else if (wrongGuess == 2)
            {
                hangman->loadImage("Image/Hangman2.png");
                wrong->loadImage("Image/Wrong2.png");
            }
            else if (wrongGuess == 3)
            {
                hangman->loadImage("Image/Hangman3.png");
                wrong->loadImage("Image/Wrong3.png");
            }
            else if (wrongGuess == 4)
            {
                hangman->loadImage("Image/Hangman4.png");
                wrong->loadImage("Image/Wrong4.png");
            }
            else if (wrongGuess == 5)
            {
                hangman->loadImage("Image/Hangman5.png");
                wrong->loadImage("Image/Wrong5.png");
            }
            else if (wrongGuess == 6)
            {
                hangman->loadImage("Image/Hangman6.png");
                wrong->loadImage("Image/Wrong6.png");
            }

            if (wrongGuess == 6)
            {
                SDL_Delay(200);
                if (rightGuess <= 3)
                {
                    while (!quit)
                    {
                        gameOverScreen->display(0, 0);
                        SDL_UpdateWindowSurface(gWindow);
                        while (SDL_PollEvent(&event) != 0)
                        {
                            if (event.type == SDL_QUIT)
                            {
                                quitSDL(gWindow, renderer);
                                return;
                            }
                            else if (event.type == SDL_KEYDOWN)
                            {
                                if (event.key.keysym.sym == SDLK_r)
                                {
                                    again = true;
                                    return;
                                }
                                if (event.key.keysym.sym == SDLK_ESCAPE)
                                {
                                    gameOverScreen->loadImage("Image/Gameover2.png");
                                }
                            }
                        }
                    }
                }
                else
                {
                    return;
                }
            }
        }
    }
}

void animation(Texture* Screen, Texture* Stickman)
{
    int y = 316;
    Texture  Gallow("Image/Hangman.png"), Hand("Image/Hand.png");
//    while (y < 340)
//    {
//        while (SDL_PollEvent(&event) != 0)
//        {
//            if (event.type == SDL_QUIT)
//            {
//                quitSDL(gWindow, renderer);
//                return;
//            }
//            Stickman->handleEventButNotMove();
//        }
//        y += 1;
//        SDL_RenderClear(renderer);
        Screen->render(0, 0, 1600, 1200);
//        Gallow.render(100, 230, 376, 376);
//        Stickman->render(302, y, 139, 257);
//        SDL_RenderPresent(renderer);
//
//    }

    int stick[] = {2, 3, 2, 1, 4, 5, 4, 7, 8, 9, 10, 11, 12, 13, 14};
    int i = -1;

//    while (i<14)
//    {
//        while (SDL_PollEvent(&event) != 0)
//        {
//            if (event.type == SDL_QUIT)
//            {
//                quitSDL(gWindow, renderer);
//                return;
//            }
//            Stickman->handleEventButNotMove();
//        }
//        i++;
//        SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
//        SDL_RenderClear(renderer);
//        Screen->render();
//        Gallow.render();
//        Stickman->loadTextureFromFile("Image/Stickman" + to_string(stick[i]) + ".png");
//        Stickman->render();
//        SDL_RenderPresent(renderer);
//        if (stick[i] == 2)
//            SDL_Delay(50);
//        else if (stick[i] == 3)
//            SDL_Delay(200);
//        else if (i == 3)
//            SDL_Delay(1500);
//        else if (i == 4)
//            SDL_Delay(1500);
//        else if (i == 5)
//            SDL_Delay(1500);
//        else if (i == 6)
//            SDL_Delay(800);
//        else if (i == 7)
//            SDL_Delay(100);
//        else if (i == 8)
//            SDL_Delay(30);
//        else if (i == 9)
//            SDL_Delay(30);
//        else if (i == 10)
//            SDL_Delay(30);
//        else if (i == 11)
//            SDL_Delay(30);
//        else if (i == 12)
//            SDL_Delay(30);
//        else if (i == 13)
//            SDL_Delay(30);
//        else if (i == 14)
//            SDL_Delay(30);
//    }

    Hand.render(304, 459, 61, 42);

//    while(Hand.rect.x > 192)
//    {
//        while (SDL_PollEvent(&event) != 0)
//        {
//            if (event.type == SDL_QUIT)
//            {
//                quitSDL(gWindow, renderer);
//                return;
//            }
//            Stickman->handleEventButNotMove();
//        }
//        Hand.rect.x-= 5;
//        Hand.render();
//        SDL_RenderPresent(renderer);
//    }

    Hand.loadTextureFromFile("Image/Hand1.png");
    Texture Gallow1("Image/Gallow1.png"), Gallow2("Image/Gallow2.png");
    Gallow1.setRect(100, 230, 376, 376);
    Gallow2.setRect(100, 230, 376, 376);
    double degrees = 0;
    SDL_Point center = {157, 25};
    Uint8 r = 255;

//    while(Gallow2.rect.x > -400)
//    {
//        while (SDL_PollEvent(&event) != 0)
//        {
//            if (event.type == SDL_QUIT)
//            {
//                quitSDL(gWindow, renderer);
//                return;
//            }
//            Stickman->handleEventButNotMove();
//        }
//        degrees -= 5;
//        Gallow2.rect.x -= 3;
//        Gallow2.rect.y -= 1;
//
//        SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
//        SDL_RenderClear(renderer);
//
//        Screen->render();
//        Stickman->render();
//        Hand.render(192, 459, 173, 42);
//        Gallow2.render(degrees, &center, SDL_FLIP_NONE);
//        Gallow1.render(r);
//
//        SDL_RenderPresent(renderer);
//    }

//    while(r > 2)
//    {
//        while (SDL_PollEvent(&event) != 0)
//        {
//            if (event.type == SDL_QUIT)
//            {
//                quitSDL(gWindow, renderer);
//                return;
//            }
//            Stickman->handleEventButNotMove();
//        }
//        r--;
//        SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
//        SDL_RenderClear(renderer);
//
//        Screen->render();
//        Stickman->render();
//        Hand.render(192, 459, 173, 42);
//        Gallow2.render(degrees, &center, SDL_FLIP_NONE);
//        Gallow1.render(r);
//
//        SDL_RenderPresent(renderer);
//    }

//    while(i > 3)
//    {
//        while (SDL_PollEvent(&event) != 0)
//        {
//            if (event.type == SDL_QUIT)
//            {
//                quitSDL(gWindow, renderer);
//                return;
//            }
//            Stickman->handleEventButNotMove();
//        }
//        i--;
//        SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
//        SDL_RenderClear(renderer);
//        Screen->render();
//        Stickman->loadTextureFromFile("Image/Stickman" + to_string(stick[i]) + ".png");
//        Stickman->render();
//        SDL_RenderPresent(renderer);
//        if (i == 8)
//            SDL_Delay(30);
//        else if (i == 9)
//            SDL_Delay(30);
//        else if (i == 10)
//            SDL_Delay(30);
//        else if (i == 11)
//            SDL_Delay(30);
//        else if (i == 12)
//            SDL_Delay(30);
//        else if (i == 13)
//            SDL_Delay(30);
//        else if (i == 14)
//            SDL_Delay(30);
//    }
//    SDL_Delay(1000);

//    for(i = 0; i <= 30; i++)
//    {
//        while (SDL_PollEvent(&event) != 0)
//        {
//            if (event.type == SDL_QUIT)
//            {
//                quitSDL(gWindow, renderer);
//                return;
//            }
//            Stickman->handleEventButNotMove();
//        }
//        if(i%2==0)
//        {
//            Stickman->rect.w -= 10;
//            Stickman->rect.h -= 20;
//            Stickman->rect.x += 5;
//            Stickman->rect.y += 19;
//        }
//        else
//        {
//            Stickman->rect.w += 4;
//            Stickman->rect.h += 8;
//            Stickman->rect.x -= 2;
//            Stickman->rect.y -= 8;
//        }
//        Screen->render();
//        Stickman->render();
//        SDL_RenderPresent(renderer);
//        SDL_Delay(50);
//    }

    Texture Boom("Image/Boom.png");
    Screen->render();
    Boom.render(285, 480, 150, 150);
    SDL_RenderPresent(renderer);
    SDL_Delay(500);

    Stickman->setRect(349, 523, 38, 69);
    Screen->render();
    Stickman->render();
    SDL_RenderPresent(renderer);
}

void checkPencil(Pencil &a, Texture &b, int i, int &_type, bool &isDead)
{
    if(b.isFalling == true)
    {
        if((b.rect.x < a.Body.rect.x + a.Body.rect.w) && (b.rect.x + b.rect.w > a.Body.rect.x - 20))
        {
            if( ((b.rect.y + b.rect.h) >= a.Body.rect.y + 2) && ((b.rect.y + b.rect.h) <= a.Body.rect.y + 17) )
            {
                b.rect.y = a.Body.rect.y - b.rect.h + 2;
                b.jumpSpeed = 0;
                b.isFalling = false;
                b.isJumping = false;
                b.isJumping2 = false;
                b.isStandingOnPencil = true;
                _type = i;
            }
        }
    }

    if(b.isStandingOnPencil == true && _type == i)
    {
        if(((b.rect.x > a.Body.rect.x + a.Body.rect.w) || (b.rect.x + b.rect.w < a.Body.rect.x - 30)))
        {
            b.jumpSpeed = -0.1;
            b.isJumping = true;
            b.isJumping2 = false;
            b.isStandingOnPencil = false;
            _type = -1;
        }
    }

    if((b.rect.x < a.Body.rect.x + a.Body.rect.w) && (b.rect.x + b.rect.w > a.Body.rect.x - 30))
    {
        if(b.rect.y < (a.Body.rect.y + a.Body.rect.h - 2) && b.rect.y > (a.Body.rect.y + a.Body.rect.h - 17))
        {
            b.rect.y = (a.Body.rect.y + a.Body.rect.h - 2);
            b.jumpSpeed = -0.1;
            b.isFalling = true;
        }
    }

    if((b.rect.x < a.Eraser.rect.x + a.Eraser.rect.w - 10) && (b.rect.x + b.rect.w > a.Eraser.rect.x + 10))
    {
        if(b.rect.y < a.Eraser.rect.y + a.Eraser.rect.h - 3 && b.rect.y + b.rect.h > a.Eraser.rect.y + 3)
        {
            isDead = true;
        }
    }

    if((b.rect.x < a.Head.rect.x + a.Head.rect.w - 30) && (b.rect.x + b.rect.w > a.Head.rect.x + 5))
    {
        if(b.rect.y < a.Head.rect.y + a.Head.rect.h + (b.rect.x + b.rect.w/2 - a.Head.rect.x - a.Head.rect.w) / 4 && b.rect.y + b.rect.h > a.Head.rect.y - (b.rect.x - a.Head.rect.x - a.Head.rect.w) / 4)
        {
            isDead = true;
        }
    }
}

void checkAllPencil(AllPencils &a, Texture &b, int &_type, bool &isDead)
{
    for(int i = 0; i < a.getNumber(); i++)
    {
        checkPencil(a.allPencils[i], b, i, _type, isDead);

        if(b.isStandingOnPencil == true && _type == i)
        {
            b.rect.x += a.allPencils[i].velo;
        }
    }
}

void instruction(Uint32 &oldTick, Uint32 &instructor1, Texture &Stickman, int &frame, SDL_Rect* currentClip, Texture &Screen, int &_type, bool &isDead, int &difficulty, Texture &pauseButton, Texture &playButton, Chunk &Button, Chunk &Click)
{
    Text Instructor("Press  LEFT  and  RIGHT  to move,  UP  to jump", 50);
    Text _InstructorText1, _InstructorText2, Star1, Star2, Star5, CountedTime, easy, normal, difficult;
    Pencil Easy, Normal, Difficult;
    Texture _Instructor, _Instructor2;
    Uint32 standingTime = 999999;
    int isMove = 0, countedTime = 3;
    bool isPaused = false, checkCollision = 0, oldCollision = 0;
    easy.loadTextureFromText("EASY", 50);
    normal.loadTextureFromText("NORMAL", 50);
    difficult.loadTextureFromText("DIFFICULT", 50);
    Easy.createOne(20, 400, 100, 4);
    Normal.createOne(360, 400, 100, 12);
    Difficult.createOne(700, 400, 100, 8);

    Stickman.velocity = 0;

    if(Stickman.isPressingLeft == true)
    {
        Stickman.velocity -= RUN_SPEED;
    }

    if(Stickman.isPressingRight == true)
    {
        Stickman.velocity += RUN_SPEED;
    }

    while (!quit)
    {
        oldTick = SDL_GetTicks();
        while (SDL_PollEvent(&event) != 0)
        {
            if (event.type == SDL_QUIT)
            {
                quit = true;
                quitSDL(gWindow, renderer);
                return;
            }

            if(event.type == SDL_MOUSEMOTION)
            {
                oldCollision = checkCollision;
                if(event.motion.x >= SCREEN_WIDTH - 50 && event.motion.y >= SCREEN_HEIGHT - 50)
                {
                    pauseButton.setRect(SCREEN_WIDTH - 45, SCREEN_HEIGHT - 45, 40, 40);
                    checkCollision = true;
                }
                else
                {
                    pauseButton.setRect(SCREEN_WIDTH - 50, SCREEN_HEIGHT - 50, 50, 50);
                    checkCollision = false;
                }
                if(oldCollision != checkCollision)
                {
                    Button.playonce();
                }
            }

            if(event.type == SDL_MOUSEBUTTONDOWN)
            {
                if(pauseButton.rect.w == 40)
                {
                    isPaused = true;
                    Click.playonce();
                    checkCollision = false;
                    oldCollision = false;
                    while(isPaused)
                    {
                        while (SDL_PollEvent(&event) != 0)
                        {
                            if (event.type == SDL_QUIT)
                            {
                                quit = true;
                                quitSDL(gWindow, renderer);
                                return;
                            }
                            if(event.type == SDL_MOUSEMOTION)
                            {
                                oldCollision = checkCollision;
                                if(event.motion.x >= SCREEN_WIDTH / 2 - 150 && event.motion.y >= SCREEN_HEIGHT / 2 - 150 && event.motion.x <= SCREEN_WIDTH / 2 + 150 && event.motion.y <= SCREEN_HEIGHT / 2 + 150)
                                {
                                    playButton.setRect(SCREEN_WIDTH / 2 - 120, SCREEN_HEIGHT / 2 - 120, 240, 240);
                                    checkCollision = true;
                                }
                                else
                                {
                                    playButton.setRect(SCREEN_WIDTH / 2 - 150, SCREEN_HEIGHT / 2 - 150, 300, 300);
                                    checkCollision = false;
                                }
                                if(oldCollision != checkCollision)
                                {
                                    Button.playonce();
                                }
                            }
                            if(event.type == SDL_MOUSEBUTTONDOWN && playButton.rect.w == 240)
                            {
                                isPaused = false;
                                break;
                                playButton.setRect(SCREEN_WIDTH / 2 - 150, SCREEN_HEIGHT / 2 - 150, 300, 300);
                            }
                        }
                        if(isPaused == false)
                        {
                            checkCollision = false;
                            oldCollision = false;
                            Click.playonce();
                            break;
                        }
                        playButton.render();

                        SDL_RenderPresent(renderer);
                    }
                }
                pauseButton.setRect(SCREEN_WIDTH - 50, SCREEN_HEIGHT - 50, 50, 50);
            }

            if(event.type == SDL_KEYDOWN && isMove == 0 && (event.key.keysym.sym == SDLK_UP || event.key.keysym.sym == SDLK_RIGHT || event.key.keysym.sym == SDLK_LEFT))
            {
                Instructor.loadTextureFromText();
                isMove = 1;
            }
            Stickman.handleEvent(event, frame, currentClip, oldTick);
        }


        if(isMove == 1)
        {
            checkPencil(Easy, Stickman, 1, _type, isDead);
            checkPencil(Normal, Stickman, 2, _type, isDead);
            checkPencil(Difficult, Stickman, 3, _type, isDead);
            if(Stickman.isStandingOnPencil == true)
            {
                CountedTime.loadTextureFromText(to_string(countedTime), 70);
                if(standingTime == 999999)
                {
                    standingTime = SDL_GetTicks();
                }

                if(SDL_GetTicks() - standingTime >= 1000)
                {
                    standingTime = SDL_GetTicks();
                    countedTime--;
                }
                if(countedTime == 0)
                {
                    difficulty = _type;
                    isMove++;
                    Stickman.jumpSpeed = -0.1;
                    Stickman.isJumping = true;
                    Stickman.isJumping2 = false;
                    Stickman.isStandingOnPencil = false;
                    instructor1 = SDL_GetTicks() - 4000;
                    if(_again == true)
                    {
                        quit = true;
                    }
                }
            }
            else if(Stickman.isStandingOnPencil == false)
            {
                CountedTime.loadTextureFromText("Please   choose   difficulty", 70);
                standingTime = 999999;
                countedTime = 3;
            }
        }

        if((SDL_GetTicks() - instructor1) >= 4000 && isMove == 2)
        {
            Instructor.loadTextureFromText("You can jump on pencils", 50);
            _Instructor.loadTextureFromFile("Image/Instruction.png");
            _InstructorText1.loadTextureFromText("DANGEROUS", 30);
            _InstructorText2.loadTextureFromText("SAFE", 30);
            instructor1 = SDL_GetTicks();
            isMove++;
        }
        else if((SDL_GetTicks() - instructor1) >= 4000 && isMove == 3)
        {
            Instructor.loadTextureFromText("Avoid being erased or being destroyed", 50);
            instructor1 = SDL_GetTicks();
            isMove++;
        }
        else if((SDL_GetTicks() - instructor1) >= 4000 && isMove == 4)
        {
            Instructor.loadTextureFromText("Eat stars to get scores", 50);
            instructor1 = SDL_GetTicks();
            _Instructor2.loadTextureFromFile("Image/Instruction2.png");
            Star1.loadTextureFromText(" 1 Score", 30);
            Star2.loadTextureFromText(" 2 Scores", 30);
            Star5.loadTextureFromText(" 5 Scores", 30);
            isMove++;
        }
        else if((SDL_GetTicks() - instructor1) >= 4000 && isMove == 5)
        {
            Instructor.loadTextureFromText("Get's go", 150);
            instructor1 = SDL_GetTicks();
            isMove++;
        }
        else if((SDL_GetTicks() - instructor1) >= 4000 && isMove == 6)
        {
            quit = true;
        }

        Stickman.stickMove(frame, &currentClip);

        SDL_SetRenderDrawColor( renderer, 0xFF, 0xFF, 0xFF, 0xFF );
        SDL_RenderClear( renderer );

        Screen.render();
        Instructor.textRender(50, 50);

        if(isMove == 3 || isMove == 4)
        {
            _Instructor.render(200, 220, 580, 125);
            _InstructorText1.textRender(100, 190);
            _InstructorText1.textRender(700, 190);
            _InstructorText2.textRender(410, 190);
        }
        else if(isMove == 5)
        {
            _Instructor2.render(200, 120, 56, 180);
            Star1.textRender(270, 130);
            Star2.textRender(270, 195);
            Star5.textRender(270, 260);
        }
        else if(isMove == 1)
        {
            CountedTime.textRender(SCREEN_WIDTH / 2 - CountedTime.textSize.w / 2, 250);
            Easy.renderPencil();
            Normal.renderPencil();
            Difficult.renderPencil();
            easy.textRender(70, 470);
            normal.textRender(410, 470);
            difficult.textRender(750, 470);
        }

        pauseButton.render();
        Stickman.render(currentClip);

        SDL_RenderPresent(renderer);

        int frameTicks = SDL_GetTicks() - oldTick;

        if( frameTicks < SCREEN_TICK_PER_FRAME )
        {
            SDL_Delay( SCREEN_TICK_PER_FRAME - frameTicks );
        }
    }
    isDead = false;
    quit = false;
}

void checkStar(Star &a, Texture &b, int &score, Chunk &star1, Chunk &star2, Chunk &star5)
{
    if(b.rect.x < a.rect.x + a.rect.w && b.rect.x + b.rect.w > a.rect.x)
    {
        if(b.rect.y < a.rect.y + a.rect.h && b.rect.y + b.rect.h > a.rect.y)
        {

            if(a.type == 1)
            {
                score += 1;
                star1.playonce();
            }
            else if(a.type == 2)
            {
                score += 2;
                star2.playonce();
            }
            else if(a.type == 3)
            {
                score += 5;
                star5.playonce();
            }

            a.loadTextureFromFile();
            a.setRect(-100, -100, 30, 30);
            a.dissappearTime = SDL_GetTicks();
            a.isOnTheScreen = false;
            a.tmp = rand() % 3000 + 1000;
            if(SDL_GetTicks() - a.dissappearTime >= a.tmp && a.isOnTheScreen == false)
            {
                a.createStar();
            }
        }
    }
}

void checkAllStar(AllStars &a, Texture &b, int &score, Chunk &star1, Chunk &star2, Chunk &star5)
{
    for(int i = 0; i < a.getNumber(); i++)
    {
        checkStar(a.allStars[i], b, score, star1, star2, star5);
    }
}

void checkSaw(Saw &saw, Texture &Stickman, bool &isDead)
{
    if( (Stickman.rect.x - (saw.rect.x + saw.rect.w/2)) * (Stickman.rect.x - (saw.rect.x + saw.rect.w/2)) + ((Stickman.rect.y + Stickman.rect.h) - (saw.rect.y + saw.rect.h/2)) * ((Stickman.rect.y + Stickman.rect.h) - (saw.rect.y + saw.rect.h/2)) <= 2500)
    {
        isDead = true;
    }
    if( (Stickman.rect.x + Stickman.rect.w - (saw.rect.x + saw.rect.w/2)) * (Stickman.rect.x + Stickman.rect.w - (saw.rect.x + saw.rect.w/2)) + ((Stickman.rect.y + Stickman.rect.h) - (saw.rect.y + saw.rect.h/2)) * ((Stickman.rect.y + Stickman.rect.h) - (saw.rect.y + saw.rect.h/2)) <= 2500)
    {
        isDead = true;
    }
}

void ingame(bool &isDead, Uint32 &oldTick, Texture &Stickman, int &frame, SDL_Rect* currentClip, Texture &Screen, AllPencils &allPencil, int &_type, AllStars &allStars, Texture &pauseButton, Texture &playButton, Chunk &Button, Chunk &Click)
{
    fstream fileIn;
    fstream fileOut;
    fileIn.open("HighScore.txt", ios::in);
    int highScore, score = 0, i1 = 1, i2 = 1;
    Saw saw;
    Uint32 frameTicks;
    bool isPaused = false, oldCollision = 0, checkCollision = 0;
    Chunk star1("Music/Star1.mp3"), star2("Music/Star2.mp3"), star5("Music/Star5.mp3");

    if(fileIn.is_open())
    {
        fileIn >> highScore;
    }

    while (!isDead && !quit)
    {
        oldTick = SDL_GetTicks();

        Text Score("Score : " + to_string(score), 70);
        Text HighScore("Highscore: " + to_string(highScore), 60);

        while (SDL_PollEvent(&event) != 0)
        {
            if (event.type == SDL_QUIT)
            {
                quit = true;
                quitSDL(gWindow, renderer);
                return;
            }

            if(event.type == SDL_MOUSEMOTION)
            {
                oldCollision = checkCollision;
                if(event.motion.x >= SCREEN_WIDTH - 50 && event.motion.y >= SCREEN_HEIGHT - 50)
                {
                    pauseButton.setRect(SCREEN_WIDTH - 45, SCREEN_HEIGHT - 45, 40, 40);
                    checkCollision = true;
                }
                else
                {
                    pauseButton.setRect(SCREEN_WIDTH - 50, SCREEN_HEIGHT - 50, 50, 50);
                    checkCollision = false;
                }
                if(oldCollision != checkCollision)
                {
                    Button.playonce();
                }
            }

            if(event.type == SDL_MOUSEBUTTONDOWN)
            {
                if(pauseButton.rect.w == 40)
                {
                    isPaused = true;
                    Click.playonce();
                    checkCollision = false;
                    oldCollision = false;
                    while(isPaused)
                    {
                        while (SDL_PollEvent(&event) != 0)
                        {
                            if (event.type == SDL_QUIT)
                            {
                                quit = true;
                                quitSDL(gWindow, renderer);
                                return;
                            }
                            if(event.type == SDL_MOUSEMOTION)
                            {
                                oldCollision = checkCollision;
                                if(event.motion.x >= SCREEN_WIDTH / 2 - 150 && event.motion.y >= SCREEN_HEIGHT / 2 - 150 && event.motion.x <= SCREEN_WIDTH / 2 + 150 && event.motion.y <= SCREEN_HEIGHT / 2 + 150)
                                {
                                    playButton.setRect(SCREEN_WIDTH / 2 - 120, SCREEN_HEIGHT / 2 - 120, 240, 240);
                                    checkCollision = true;
                                }
                                else
                                {
                                    playButton.setRect(SCREEN_WIDTH / 2 - 150, SCREEN_HEIGHT / 2 - 150, 300, 300);
                                    checkCollision = false;
                                }
                                if(oldCollision != checkCollision)
                                {
                                    Button.playonce();
                                }
                            }
                            if(event.type == SDL_MOUSEBUTTONDOWN && playButton.rect.w == 240)
                            {
                                isPaused = false;
                                break;
                                playButton.setRect(SCREEN_WIDTH / 2 - 150, SCREEN_HEIGHT / 2 - 150, 300, 300);
                            }
                        }
                        if(isPaused == false)
                        {
                            checkCollision = false;
                            oldCollision = false;
                            Click.playonce();
                            break;
                        }
                        playButton.render();

                        SDL_RenderPresent(renderer);
                    }
                }
                pauseButton.setRect(SCREEN_WIDTH - 50, SCREEN_HEIGHT - 50, 50, 50);
            }

            Stickman.handleEvent(event, frame, currentClip, oldTick);
        }

        allPencil.moveAllPencil();
        Stickman.stickMove(frame, &currentClip);
        allStars.moveAllStar();
        saw.moveSaw();

        checkAllPencil(allPencil, Stickman, _type, isDead);
        checkAllStar(allStars, Stickman, score, star1, star2, star5);
        checkSaw(saw, Stickman, isDead);

        SDL_SetRenderDrawColor( renderer, 0xFF, 0xFF, 0xFF, 0xFF );
        SDL_RenderClear( renderer );

        Screen.render();
        Score.textRender(700, 10);
        HighScore.textRender(10, 10);
        allPencil.renderAllPencil();
        saw.renderSaw();
        pauseButton.render();
        Stickman.render(currentClip);
        allStars.renderAllStar();

        SDL_RenderPresent(renderer);

        frameTicks = SDL_GetTicks() - oldTick;

        if( frameTicks < SCREEN_TICK_PER_FRAME )
        {
            SDL_Delay( SCREEN_TICK_PER_FRAME - frameTicks );
        }

        if(score >= 10 * i1)
        {
            i1++;
            allPencil.number++;
        }
        if(score >= 20 * i2)
        {
            i2++;
            allStars.number++;
            allPencil.minSpeed++;
        }
    }

    if(score > highScore)
    {
        highScore = score;
        fileOut.open("HighScore.txt", ios::out);
        fileOut << highScore;
    }
}

void gameover(Texture &Screen, Uint32 &oldTick, Texture &Stickman, int &frame, SDL_Rect* currentClip)
{
    Texture DeadStickman("Image/DeadStickman.png");
    Text Gameover("Gameover !", 200);
    Text Restart("Press R to restart the game or press Esc to quit the game", 40);

    Stickman.rect.y = 523;
    Stickman.jumpSpeed = 0;
    Stickman.isJumping = false;
    Stickman.isJumping2 = false;
    Stickman.isFalling = false;

    while(!quit)
    {
        while(SDL_PollEvent(&event) != NULL)
        {
            if (event.type == SDL_QUIT || event.key.keysym.sym == SDLK_ESCAPE)
            {
                quit = true;
                quitSDL(gWindow, renderer);
                return;
            }
            else if(event.key.keysym.sym == SDLK_r)
            {
                again = true;
                _again = true;
                return;
            }
            Stickman.handleEventButNotMove();
        }
        SDL_SetRenderDrawColor( renderer, 0xFF, 0xFF, 0xFF, 0xFF );
        SDL_RenderClear( renderer );

        Screen.render();
        Gameover.textRender(100, 50);
        Restart.textRender(10, 250);
        DeadStickman.render(100, 400, 720, 400);

        SDL_RenderPresent(renderer);
    }
}
