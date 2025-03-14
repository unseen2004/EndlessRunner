//
// Created by maks on 3/14/25.
//
#include "../headers/ReplayScreen.h"

ReplayScreen::ReplayScreen(StateMachine &sm) : stateMachine(sm) {
}

ReplayScreen::~ReplayScreen(){
    std::cout<<"destructionReplayScreen"<<std::endl;
}

void ReplayScreen::handleInput() {
    if (IsKeyPressed(KEY_ENTER)) {
        stateMachine.changeState(std::make_unique<WelcomeScreen>(stateMachine));
    }

}

void ReplayScreen::update(){
    return;
    }

void ReplayScreen::render() {
    BeginDrawing();
    ClearBackground(GetColor(0x052c46ff));


    // Use the inline config variables for fog and snow.
    const char *fogStatus = " press enter to change";

    Vector2 startPos  { 200, 200 };
    // Draw status text below the main message.
    DrawTextEx(GetFontDefault(), fogStatus, (Vector2){ startPos.x, startPos.y + 40 }, 20, 1, YELLOW);





    EndDrawing();
}