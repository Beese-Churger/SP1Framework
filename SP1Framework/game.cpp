// This is the main file for the game logic and function
//
//
#include "game.h"
#include "Framework\console.h"
#include <iostream>
#include <iomanip>
#include <sstream>

double  g_dElapsedTime;
double  g_dDeltaTime;
int MenuItem = 0;
int levelItem = 0;
SKeyEvent g_skKeyEvent[K_COUNT];
SMouseEvent g_mouseEvent;

// Game specific variables here
SGameChar   g_sChar;
EGAMESTATES g_eGameState = S_SPLASHSCREEN; // initial state

// Console object
Console g_Console(120, 68, "Relic Taker");

//--------------------------------------------------------------
// Purpose  : Initialisation function
//            Initialize variables, allocate memory, load data from file, etc. 
//            This is called once before entering into your main loop
// Input    : void
// Output   : void
//--------------------------------------------------------------
void init( void )
{
    // Set precision for floating point output
    g_dElapsedTime = 0.0;    

    // sets the initial state for the game
    g_eGameState = S_SPLASHSCREEN;

    g_sChar.m_cLocation.X = 60;
    g_sChar.m_cLocation.Y = 15;
    g_sChar.m_bActive = true;
    // sets the width, height and the font name to use in the console
    g_Console.setConsoleFont(0, 16, L"Consolas");

    // remember to set your keyboard handler, so that your functions can be notified of input events
    g_Console.setKeyboardHandler(keyboardHandler);
    g_Console.setMouseHandler(mouseHandler);
}

//--------------------------------------------------------------
// Purpose  : Reset before exiting the program
//            Do your clean up of memory here
//            This is called once just before the game exits
// Input    : Void
// Output   : void
//--------------------------------------------------------------
void shutdown( void )
{
    // Reset to white text on black background
    colour(FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);

    g_Console.clearBuffer();
}

//--------------------------------------------------------------
// Purpose  : Get all the console input events
//            This function sets up the keyboard and mouse input from the console.
//            We will need to reset all the keyboard status, because no events will be sent if no keys are pressed.
//
//            Remember to set the handlers for keyboard and mouse events.
//            The function prototype of the handler is a function that takes in a const reference to the event struct
//            and returns nothing. 
//            void pfKeyboardHandler(const KEY_EVENT_RECORD&);
//            void pfMouseHandlerconst MOUSE_EVENT_RECORD&);
// Input    : Void
// Output   : void
//--------------------------------------------------------------
void getInput( void )
{
    // resets all the keyboard events
    memset(g_skKeyEvent, 0, K_COUNT * sizeof(*g_skKeyEvent));
    // then call the console to detect input from user
    g_Console.readConsoleInput();    
}

//--------------------------------------------------------------
// Purpose  : This is the handler for the keyboard input. Whenever there is a keyboard event, this function will be called.
//            Ideally, you should pass the key event to a specific function to handle the event.
//            This is because in some states, some keys would be disabled. Hence, to reduce your code complexity, 
//            it would be wise to split your keyboard input handlers separately.
//            
//            The KEY_EVENT_RECORD struct has more attributes that you can use, if you are adventurous enough.
//
//            In this case, we are not handling any keyboard event in the Splashscreen state
//            
// Input    : const KEY_EVENT_RECORD& keyboardEvent - reference to a key event struct
// Output   : void
//--------------------------------------------------------------
void keyboardHandler(const KEY_EVENT_RECORD& keyboardEvent)
{    
    switch (g_eGameState)
    {
    case S_SPLASHSCREEN: gameplayKBHandler(keyboardEvent);
        break;
    case S_MAINMENU: gameplayKBHandler(keyboardEvent);
        break;
    case S_LEVELSELECT: gameplayKBHandler(keyboardEvent);
        break;
    case S_GAME1: gameplayKBHandler(keyboardEvent);
        break;
    case S_GAME2: gameplayKBHandler(keyboardEvent);
        break;
    case S_GAME3: gameplayKBHandler(keyboardEvent);
        break;
    case S_GAME4: gameplayKBHandler(keyboardEvent);
        break;
    case S_GAME5: gameplayKBHandler(keyboardEvent);
        break;
    case S_GAME6: gameplayKBHandler(keyboardEvent);
        break;
    case S_GAME7: gameplayKBHandler(keyboardEvent);
        break;
    case S_GAME8: gameplayKBHandler(keyboardEvent);
        break;
    case S_GAME9: gameplayKBHandler(keyboardEvent);
        break;
    case S_GAME10: gameplayKBHandler(keyboardEvent);
        break;

    }
}

//--------------------------------------------------------------
// Purpose  : This is the handler for the mouse input. Whenever there is a mouse event, this function will be called.
//            Ideally, you should pass the key event to a specific function to handle the event.
//            This is because in some states, some keys would be disabled. Hence, to reduce your code complexity, 
//            it would be wise to split your keyboard input handlers separately.
//            
//            For the mouse event, if the mouse is not moved, no event will be sent, hence you should not reset the mouse status.
//            However, if the mouse goes out of the window, you would not be able to know either. 
//
//            The MOUSE_EVENT_RECORD struct has more attributes that you can use, if you are adventurous enough.
//
//            In this case, we are not handling any mouse event in the Splashscreen state
//            
// Input    : const MOUSE_EVENT_RECORD& mouseEvent - reference to a mouse event struct
// Output   : void
//--------------------------------------------------------------
void mouseHandler(const MOUSE_EVENT_RECORD& mouseEvent)
{    
    switch (g_eGameState)
    {
    case S_SPLASHSCREEN: // don't handle anything for the splash screen
        break;
    case S_GAME1: gameplayMouseHandler(mouseEvent); // handle gameplay mouse event
        break;
    }
}

//--------------------------------------------------------------
// Purpose  : This is the keyboard handler in the game state. Whenever there is a keyboard event in the game state, this function will be called.
//            
//            Add more keys to the enum in game.h if you need to detect more keys
//            To get other VK key defines, right click on the VK define (e.g. VK_UP) and choose "Go To Definition" 
//            For Alphanumeric keys, the values are their ascii values (uppercase).
// Input    : const KEY_EVENT_RECORD& keyboardEvent
// Output   : void
//--------------------------------------------------------------
void gameplayKBHandler(const KEY_EVENT_RECORD& keyboardEvent)
{
    // here, we map the key to our enums
    EKEYS key = K_COUNT;
    switch (keyboardEvent.wVirtualKeyCode)
    {
    case VK_UP: key = K_UP; break;
    case VK_DOWN: key = K_DOWN; break;
    case VK_LEFT: key = K_LEFT; break; 
    case VK_RIGHT: key = K_RIGHT; break; 
    case VK_SPACE: key = K_SPACE; break;
    case VK_ESCAPE: key = K_ESCAPE; break; 
    case VK_RETURN: key = K_ENTER; break;
    }
    // a key pressed event would be one with bKeyDown == true
    // a key released event would be one with bKeyDown == false
    // if no key is pressed, no event would be fired.
    // so we are tracking if a key is either pressed, or released
    if (key != K_COUNT)
    {
        g_skKeyEvent[key].keyDown = keyboardEvent.bKeyDown;
        g_skKeyEvent[key].keyReleased = !keyboardEvent.bKeyDown;
    }    
}

//--------------------------------------------------------------
// Purpose  : This is the mouse handler in the game state. Whenever there is a mouse event in the game state, this function will be called.
//            
//            If mouse clicks are detected, the corresponding bit for that mouse button will be set.
//            mouse wheel, 
//            
// Input    : const KEY_EVENT_RECORD& keyboardEvent
// Output   : void
//--------------------------------------------------------------
void gameplayMouseHandler(const MOUSE_EVENT_RECORD& mouseEvent)
{
    if (mouseEvent.dwEventFlags & MOUSE_MOVED) // update the mouse position if there are no events
    {
        g_mouseEvent.mousePosition = mouseEvent.dwMousePosition;
    }
    g_mouseEvent.buttonState = mouseEvent.dwButtonState;
    g_mouseEvent.eventFlags = mouseEvent.dwEventFlags;
}

//--------------------------------------------------------------
// Purpose  : Update function
//            This is the update function
//            double dt - This is the amount of time in seconds since the previous call was made
//
//            Game logic should be done here.
//            Such as collision checks, determining the position of your game characters, status updates, etc
//            If there are any calls to write to the console here, then you are doing it wrong.
//
//            If your game has multiple states, you should determine the current state, and call the relevant function here.
//
// Input    : dt = deltatime
// Output   : void
//--------------------------------------------------------------
void update(double dt)
{
    // get the delta time
    g_dElapsedTime += dt;
    g_dDeltaTime = dt;

    switch (g_eGameState)
    {
        case S_SPLASHSCREEN : splashScreenWait(); // game logic for the splash screen
            break;
        case S_MAINMENU: updateMainMenu();
            break;
        case S_LEVELSELECT: updateLevelSelect();
            break;
        case S_GAME1: updateGame(); // gameplay logic when we are in the game
            break;
    }
}


void splashScreenWait()    // waits for time to pass in splash screen
{
    if (g_skKeyEvent[K_ENTER].keyReleased)
        g_eGameState = S_MAINMENU;
}

void updateGame()       // gameplay logic
{
    processUserInput(); // checks if you should change states or do something else with the game, e.g. pause, exit
    moveCharacter();    // moves the character, collision detection, physics, etc
                        // sound can be played here too.
}

void updateMainMenu()
{
    if (g_skKeyEvent[K_DOWN].keyReleased && MenuItem != 3)
    {
        MenuItem++;
    }

    if (g_skKeyEvent[K_UP].keyReleased && MenuItem != 0)
    {
        MenuItem--;
    }
    if (g_skKeyEvent[K_ENTER].keyReleased) {

        switch (MenuItem) {

        case 0: {
            g_eGameState = S_GAME1;
            break;
        }

        case 1: {
            g_eGameState = S_LEVELSELECT;
            break;
        }

        case 2: {

            break;
        }

        case 3: {
            g_bQuitGame = true;
        }
        }
    }
}

void updateLevelSelect()
{
    if (g_skKeyEvent[K_RIGHT].keyReleased && levelItem != 9)
    {
        levelItem++;
    }

    if (g_skKeyEvent[K_LEFT].keyReleased && levelItem != 0)
    {
        levelItem--;
    }

    if (g_skKeyEvent[K_ESCAPE].keyReleased)
    {
        g_eGameState = S_MAINMENU;
    }
    if (g_skKeyEvent[K_ENTER].keyReleased) {

        switch (levelItem) {

        case 0: {
            g_eGameState = S_GAME1;
            break;
        }

        case 1: {
            g_eGameState = S_GAME2;
            break;
        }

        case 2: {
            g_eGameState = S_GAME3;
            break;
        }

        case 3: {
            g_eGameState = S_GAME4;
            break;
        }

        case 4: {
            g_eGameState = S_GAME5;
            break;
        }

        case 5: {
            g_eGameState = S_GAME6;
            break;
        }

        case 6: {
            g_eGameState = S_GAME7;
            break;
        }

        case 7: {
            g_eGameState = S_GAME8;
            break;
        }

        case 8: {
            g_eGameState = S_GAME9;
            break;
        }

        case 9: {
            g_eGameState = S_GAME10;
            break;
        }
        }
    }
}

void moveCharacter()
{    
    // Updating the location of the character based on the key release
    // providing a beep sound whenver we shift the character
    if (g_skKeyEvent[K_UP].keyReleased && g_sChar.m_cLocation.Y > 0)
    {
        //Beep(1440, 30);
        g_sChar.m_cLocation.Y--;       
    }
    if (g_skKeyEvent[K_LEFT].keyReleased && g_sChar.m_cLocation.X > 0)
    {
        //Beep(1440, 30);
        g_sChar.m_cLocation.X--;        
    }
    if (g_skKeyEvent[K_DOWN].keyReleased && g_sChar.m_cLocation.Y < g_Console.getConsoleSize().Y - 1)
    {
        //Beep(1440, 30);
        g_sChar.m_cLocation.Y++;        
    }
    if (g_skKeyEvent[K_RIGHT].keyReleased && g_sChar.m_cLocation.X < g_Console.getConsoleSize().X - 1)
    {
        //Beep(1440, 30);
        g_sChar.m_cLocation.X++;        
    }
    if (g_skKeyEvent[K_SPACE].keyReleased)
    {
        g_sChar.m_bActive = !g_sChar.m_bActive;        
    }

   
}
void processUserInput()
{
    // quits the game if player hits the escape key
    if (g_skKeyEvent[K_ESCAPE].keyReleased)
        g_bQuitGame = true;    
}

//--------------------------------------------------------------
// Purpose  : Render function is to update the console screen
//            At this point, you should know exactly what to draw onto the screen.
//            Just draw it!
//            To get an idea of the values for colours, look at console.h and the URL listed there
// Input    : void
// Output   : void
//--------------------------------------------------------------
void render()
{
    clearScreen();      // clears the current screen and draw from scratch 
    switch (g_eGameState)
    {
    case S_SPLASHSCREEN: renderSplashScreen();
        break;
    case S_MAINMENU: renderMainMenu();
        break;
    case S_LEVELSELECT: renderLevelSelect();
        break;
    case S_GAME1: renderGame();
        break;
    }
    renderFramerate();      // renders debug information, frame rate, elapsed time, etc
    renderInputEvents();    // renders status of input events
    renderToScreen();       // dump the contents of the buffer to the screen, one frame worth of game
}

void clearScreen()
{
    // Clears the buffer with this colour attribute
    g_Console.clearBuffer(0x00);
}

void renderToScreen()
{
    // Writes the buffer to the console, hence you will see what you have written
    g_Console.flushBufferToConsole();
}

void renderSplashScreen()  // renders the splash screen
{
    COORD c = g_Console.getConsoleSize();
    c.Y = 10;
    c.X = c.X;
    g_Console.writeToBuffer(c, "       /$$$$$$$  /$$$$$$$$ /$$       /$$$$$$  /$$$$$$        /$$$$$$$$ /$$$$$$  /$$   /$$ /$$$$$$$$ /$$$$$$$ ", 0x0F);
    c.Y += 1;
    c.X = g_Console.getConsoleSize().X;
    g_Console.writeToBuffer(c, "      | $$__  $$| $$_____/| $$      |_  $$_/ /$$__  $$      |__  $$__//$$__  $$| $$  /$$/| $$_____/| $$__  $$", 0x0F);
    c.Y += 1;
    c.X = g_Console.getConsoleSize().X;
    g_Console.writeToBuffer(c, "      | $$  \\ $$| $$      | $$        | $$  | $$  \\__/         | $$  | $$  \\ $$| $$ /$$/ | $$      | $$  \\ $$", 0x0F);
    c.Y += 1;
    c.X = g_Console.getConsoleSize().X;
    g_Console.writeToBuffer(c, "      | $$$$$$$/| $$$$$   | $$        | $$  | $$               | $$  | $$$$$$$$| $$$$$/  | $$$$$   | $$$$$$$/", 0x0F);
    c.Y += 1;
    c.X = g_Console.getConsoleSize().X;
    g_Console.writeToBuffer(c, "      | $$__  $$| $$__/   | $$        | $$  | $$               | $$  | $$__  $$| $$  $$  | $$__/   | $$__  $$", 0x0F);
    c.Y += 1;
    c.X = g_Console.getConsoleSize().X;
    g_Console.writeToBuffer(c, "      | $$  \\ $$| $$      | $$        | $$  | $$    $$         | $$  | $$  | $$| $$\\  $$ | $$      | $$  \\ $$", 0x0F);
    c.Y += 1;
    c.X = g_Console.getConsoleSize().X;
    g_Console.writeToBuffer(c, "      | $$  | $$| $$$$$$$$| $$$$$$$$ /$$$$$$|  $$$$$$/         | $$  | $$  | $$| $$ \\  $$| $$$$$$$$| $$  | $$", 0x0F);
    c.Y += 1;
    c.X = g_Console.getConsoleSize().X;
    g_Console.writeToBuffer(c, "      |__/  |__/|________/|________/|______/ \\______/          |__/  |__/  |__/|__/  \\__/|________/|__/  |__/", 0x0F);
    c.X = 46;
    c.Y += 4;
    g_Console.writeToBuffer(c, "Press [Enter] to start", 0x0F);
}

void renderMainMenu()
{
    COORD c = g_Console.getConsoleSize();
    c.Y = 1;
    c.X = c.X;
    g_Console.writeToBuffer(c, "       /$$$$$$$  /$$$$$$$$ /$$       /$$$$$$  /$$$$$$        /$$$$$$$$ /$$$$$$  /$$   /$$ /$$$$$$$$ /$$$$$$$ ", 0x0F);
    c.Y += 1;
    c.X = g_Console.getConsoleSize().X;
    g_Console.writeToBuffer(c, "      | $$__  $$| $$_____/| $$      |_  $$_/ /$$__  $$      |__  $$__//$$__  $$| $$  /$$/| $$_____/| $$__  $$", 0x0F);
    c.Y += 1;
    c.X = g_Console.getConsoleSize().X;
    g_Console.writeToBuffer(c, "      | $$  \\ $$| $$      | $$        | $$  | $$  \\__/         | $$  | $$  \\ $$| $$ /$$/ | $$      | $$  \\ $$", 0x0F);
    c.Y += 1;
    c.X = g_Console.getConsoleSize().X;
    g_Console.writeToBuffer(c, "      | $$$$$$$/| $$$$$   | $$        | $$  | $$               | $$  | $$$$$$$$| $$$$$/  | $$$$$   | $$$$$$$/", 0x0F);
    c.Y += 1;
    c.X = g_Console.getConsoleSize().X;
    g_Console.writeToBuffer(c, "      | $$__  $$| $$__/   | $$        | $$  | $$               | $$  | $$__  $$| $$  $$  | $$__/   | $$__  $$", 0x0F);
    c.Y += 1;
    c.X = g_Console.getConsoleSize().X;
    g_Console.writeToBuffer(c, "      | $$  \\ $$| $$      | $$        | $$  | $$    $$         | $$  | $$  | $$| $$\\  $$ | $$      | $$  \\ $$", 0x0F);
    c.Y += 1;
    c.X = g_Console.getConsoleSize().X;
    g_Console.writeToBuffer(c, "      | $$  | $$| $$$$$$$$| $$$$$$$$ /$$$$$$|  $$$$$$/         | $$  | $$  | $$| $$ \\  $$| $$$$$$$$| $$  | $$", 0x0F);
    c.Y += 1;
    c.X = g_Console.getConsoleSize().X;
    g_Console.writeToBuffer(c, "      |__/  |__/|________/|________/|______/ \\______/          |__/  |__/  |__/|__/  \\__/|________/|__/  |__/", 0x0F);
    c.Y += 6;
    c.X = 46;
    g_Console.writeToBuffer(c, "| Play", 0x0F);
    c.Y = c.Y + MenuItem;
    c.X = 44;
    g_Console.writeToBuffer(c, ">>", 0x0F);
    c.Y = 15;
    c.X = 46;
    g_Console.writeToBuffer(c, "| Level Select", 0x0F);
    c.Y = 16;
    c.X = 46;
    g_Console.writeToBuffer(c, "| Options", 0x0F);
    c.Y = 17;
    c.X = 46;
    g_Console.writeToBuffer(c, "| Exit", 0x0F);
    
}

void renderLevelSelect()
{
    COORD c = g_Console.getConsoleSize();
    c.Y = 1;
    c.X = c.X;
    g_Console.writeToBuffer(c, " $$$$$$\\  $$$$$$$$\\ $$\\       $$$$$$$$\\  $$$$$$\\ $$$$$$$$\\       $$\\       $$$$$$$$\\ $$\\    $$\\ $$$$$$$$\\ $$\\       ", 0x0F);
    c.Y += 1;
    c.X = g_Console.getConsoleSize().X;
    g_Console.writeToBuffer(c, "$$  __$$\\ $$  _____|$$ |      $$  _____|$$  __$$\\\\__$$  __|      $$ |      $$  _____|$$ |   $$ |$$  _____|$$ |      ", 0x0F);
    c.Y += 1;
    c.X = g_Console.getConsoleSize().X;
    g_Console.writeToBuffer(c, "$$ /  \\__|$$ |      $$ |      $$ |      $$ /  \\__|  $$ |         $$ |      $$ |      $$ |   $$ |$$ |      $$ |      ", 0x0F);
    c.Y += 1;
    c.X = g_Console.getConsoleSize().X;
    g_Console.writeToBuffer(c, "\\$$$$$$\\  $$$$$\\    $$ |      $$$$$\\    $$ |        $$ |         $$ |      $$$$$\\    \\$$\\  $$  |$$$$$\\    $$ |     ", 0x0F);
    c.Y += 1;
    c.X = g_Console.getConsoleSize().X;
    g_Console.writeToBuffer(c, " \\____$$\\ $$  __|   $$ |      $$  __|   $$ |        $$ |         $$ |      $$  __|    \\$$\\$$  / $$  __|   $$ |     ", 0x0F);
    c.Y += 1;
    c.X = g_Console.getConsoleSize().X;
    g_Console.writeToBuffer(c, "$$\\   $$ |$$ |      $$ |      $$ |      $$ |  $$\\   $$ |         $$ |      $$ |        \\$$$  /  $$ |      $$ |      ", 0x0F);
    c.Y += 1;
    c.X = g_Console.getConsoleSize().X;
    g_Console.writeToBuffer(c, "\\$$$$$$  |$$$$$$$$\\ $$$$$$$$\\ $$$$$$$$\\ \\$$$$$$  |  $$ |         $$$$$$$$\\ $$$$$$$$\\    \\$  /   $$$$$$$$\\ $$$$$$$$\\ ", 0x0F);
    c.Y += 1;
    c.X = g_Console.getConsoleSize().X;
    g_Console.writeToBuffer(c, " \\______/ \\________|\\________|\\________| \\______/   \\__|         \\________|\\________|    \\_/    \\________|\\________|", 0x0F);
    c.Y = 13;
    c.X = 22 + 7 * levelItem;
    g_Console.writeToBuffer(c, "v", 0x0F);
    c.Y = 17;
    c.X = 22 + 7 * levelItem;
    g_Console.writeToBuffer(c, "^", 0x0F);
    c.Y = 15;
    c.X = 20;
    g_Console.writeToBuffer(c, "| 1 |", 0x0F);
    c.Y = 15;
    c.X = 27;
    g_Console.writeToBuffer(c, "| 2 |", 0x0F);
    c.Y = 15;
    c.X = 34;
    g_Console.writeToBuffer(c, "| 3 |", 0x0F);
    c.Y = 15;
    c.X = 41;
    g_Console.writeToBuffer(c, "| 4 |", 0x0F);
    c.Y = 15;
    c.X = 48;
    g_Console.writeToBuffer(c, "| 5 |", 0x0F);
    c.Y = 15;
    c.X = 55;
    g_Console.writeToBuffer(c, "| 6 |", 0x0F);
    c.Y = 15;
    c.X = 62;
    g_Console.writeToBuffer(c, "| 7 |", 0x0F);
    c.Y = 15;
    c.X = 69;
    g_Console.writeToBuffer(c, "| 8 |", 0x0F);
    c.Y = 15;
    c.X = 76;
    g_Console.writeToBuffer(c, "| 9 |", 0x0F);
    c.Y = 15;
    c.X = 83;
    g_Console.writeToBuffer(c, "| X |", 0x0F);

}

void renderGame()
{
    renderMap();        // renders the map to the buffer first
    renderCharacter();  // renders the character into the buffer
}

void renderMap()
{
    // Set up sample colours, and output shadings
    const WORD colors[] = {
        0x00, 0x2B, 0x3C, 0x4D, 0x5E, 0x6F,
        0xA1, 0xB2, 0xC3, 0xD4, 0xE5, 0xF6
    };

    COORD c;
    for (int i = 0; i < 12; ++i)
    {
        c.X = 5 * i;
        c.Y = i + 1;
        colour(colors[i]);
        g_Console.writeToBuffer(c, " hi", colors[i]);
    }
}

void renderCharacter()
{
    // Draw the location of the character
    WORD charColor = 0x0F;
    
    g_Console.writeToBuffer(g_sChar.m_cLocation, (char)1, charColor);
}

void renderRock()
{
   
}

void renderFramerate()
{
    COORD c;
    // displays the framerate
    std::ostringstream ss;
    ss << std::fixed << std::setprecision(3);
    ss << 1.0 / g_dDeltaTime << "fps";
    c.X = g_Console.getConsoleSize().X - 9;
    c.Y = 0;
    g_Console.writeToBuffer(c, ss.str());

    // displays the elapsed time
    ss.str("");
    ss << g_dElapsedTime << "s";
    c.X = 0;
    c.Y = 0;
    g_Console.writeToBuffer(c, ss.str(), 0x0F);
}

// this is an example of how you would use the input events
void renderInputEvents()
{
    // keyboard events
    COORD startPos = {98, 2};
    std::ostringstream ss;
    std::string key;
    for (int i = 0; i < K_COUNT; ++i)
    {
        ss.str("");
        switch (i)
        {
        case K_UP: key = "UP";
            break;
        case K_DOWN: key = "DOWN";
            break;
        case K_LEFT: key = "LEFT";
            break;
        case K_RIGHT: key = "RIGHT";
            break;
        case K_SPACE: key = "SPACE";
            break;
        default: continue;
        }
        if (g_skKeyEvent[i].keyDown)
            ss << key << " pressed";
        else if (g_skKeyEvent[i].keyReleased)
            ss << key << " released";
        else
            ss << key << " not pressed";

        COORD c = { startPos.X, startPos.Y + i };
        g_Console.writeToBuffer(c, ss.str(), 0x0F);
    }

    // mouse events    
    ss.str("");
    ss << "Mouse position (" << g_mouseEvent.mousePosition.X << ", " << g_mouseEvent.mousePosition.Y << ")";
    g_Console.writeToBuffer(g_mouseEvent.mousePosition, ss.str(), 0x0F);
    ss.str("");
    switch (g_mouseEvent.eventFlags)
    {
    case 0:
        if (g_mouseEvent.buttonState == FROM_LEFT_1ST_BUTTON_PRESSED)
        {
            ss.str("Left Button Pressed");
            g_Console.writeToBuffer(g_mouseEvent.mousePosition.X, g_mouseEvent.mousePosition.Y + 1, ss.str(), 0x59);
        }
        else if (g_mouseEvent.buttonState == RIGHTMOST_BUTTON_PRESSED)
        {
            ss.str("Right Button Pressed");
            g_Console.writeToBuffer(g_mouseEvent.mousePosition.X, g_mouseEvent.mousePosition.Y + 2, ss.str(), 0x59);
        }
        else
        {
            ss.str("Some Button Pressed");
            g_Console.writeToBuffer(g_mouseEvent.mousePosition.X, g_mouseEvent.mousePosition.Y + 3, ss.str(), 0x59);
        }
        break;
    case DOUBLE_CLICK:
        ss.str("Double Clicked");
        g_Console.writeToBuffer(g_mouseEvent.mousePosition.X, g_mouseEvent.mousePosition.Y + 4, ss.str(), 0x59);
        break;        
    case MOUSE_WHEELED:
        if (g_mouseEvent.buttonState & 0xFF000000)
            ss.str("Mouse wheeled down");
        else
            ss.str("Mouse wheeled up");
        g_Console.writeToBuffer(g_mouseEvent.mousePosition.X, g_mouseEvent.mousePosition.Y + 5, ss.str(), 0x59);
        break;
    default:        
        break;
    }
    
}



