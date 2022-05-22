#include "Init.h"
#include "Music.h"
#include "Chunk.h"
#include "Image.h"
#include "Texture.h"
#include "Pencil.h"
#include "AllPencil.h"
#include "Word.h"
#include "Star.h"
#include "AllStar.h"
#include "Saw.h"
#include "Booster.h"
#include "GameProcess.h"

using namespace start;

int main(int argc, char *argv[])
{
    srand(time(0));
    initSDL(gWindow, renderer);
    Music Background("Music/BackgroundMusic.mp3");
//    Background.playinfi();
gameagain:
    Image hangman("Image/Hangman.png"), screen("Image/Background.png"), h, a, n, g, m, start("Image/PlayButton1.png"), title("Image/Title.png"), rule("Image/Rule.png"), word("Image/Word.png"), wrong("Image/Wrong0.png"), gameOverScreen("Image/Gameover1.png");
    Chunk Button("Music/Button.mp3"), Click("Music/Click.mp3"), Correct("Music/Correct.mp3"), Incorrect("Music/Wrong.mp3");

//    startgame(&title, &start, &screen, &Button, &Click);

    if(quit == true) return 0;

//    part1(&screen, &rule, &wrong, &hangman, &word, &a, &n, &g, &m, &h, &Correct, &Incorrect, &gameOverScreen);

    if(again == true)
    {
        again = false;
        while(correctAnswers.size() > 0)
        {
            correctAnswers.pop_back();
        }
        goto gameagain;
    }

    Texture Screen("Image/Background.png"), Stickman("Image/Stickman1.png");

    animation(&Screen, &Stickman);
    {
        Move[0].x = 0;
        Move[0].y = 0;
        Move[0].w = 139;
        Move[0].h = 257;

        Move[1].x = 139;
        Move[1].y = 0;
        Move[1].w = 139;
        Move[1].h = 257;

        Move[2].x = 278;
        Move[2].y = 0;
        Move[2].w = 139;
        Move[2].h = 257;

        Move[3].x = 417;
        Move[3].y = 0;
        Move[3].w = 139;
        Move[3].h = 257;

        Move[4].x = 556;
        Move[4].y = 0;
        Move[4].w = 139;
        Move[4].h = 257;
    }

restartGame:

    int frame = 0, _type = -1, difficulty = 0;
    SDL_Rect* currentClip = &Move[0];
    Uint32 oldTick, instructor1 = 9999999;
    bool isDead = false;
    Texture pauseButton("Image/Pause.png");
    pauseButton.setRect(SCREEN_WIDTH - 50, SCREEN_HEIGHT - 50, 50, 50);
    Texture playButton("Image/Play.png");
    playButton.setRect(SCREEN_WIDTH / 2 - 150, SCREEN_HEIGHT / 2 - 150, 300, 300);

    instruction(oldTick, instructor1, Stickman, frame, currentClip, Screen, _type, isDead, difficulty, pauseButton, playButton, Button, Click);

    int pen, str;
    if(difficulty == 1)
    {
        pen = 2; str = 2;
    }
    else if(difficulty == 2)
    {
        pen = 4; str = 3;
    }
    else if(difficulty == 3)
    {
        pen = 6; str = 3;
    }

    quit = false;
    AllPencils allPencil(pen);
    AllStars allStars(str);

    ingame(isDead, oldTick, Stickman, frame, currentClip, Screen, allPencil, _type, allStars, pauseButton, playButton, Button, Click);

    Chunk dieSound("Music/Die.mp3");
    dieSound.playonce();

    SDL_Delay(3000);

    gameover(Screen, oldTick, Stickman, frame, currentClip);

    if(again == true)
    {
        again = false;
        goto restartGame;
    }

    quitSDL(gWindow, renderer);
    return 0;
}
