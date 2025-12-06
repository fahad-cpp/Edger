#include "AutoClicker.h"
#include <iostream>
#include <fstream>
void AutoClicker::pressKey(WORD vk){
    INPUT input = {0};

    //Key Down
    input.type = INPUT_KEYBOARD;
    input.ki.wVk = vk;
    SendInput(1, &input, sizeof(INPUT));

    Sleep(30);

    //Key Up
    input.ki.dwFlags = KEYEVENTF_KEYUP;
    SendInput(1, &input, sizeof(INPUT));
}
void typeChar(char c){
    INPUT input = {0};
    input.type = INPUT_KEYBOARD;
    input.ki.wVk = VkKeyScanA(c);
    input.ki.dwFlags = 0;
    //KeyDown
    SendInput(1,&input,sizeof(INPUT));
    Sleep(50);
    //KeyUp
    input.ki.dwFlags = KEYEVENTF_KEYUP;
    SendInput(1,&input,sizeof(INPUT));

    Sleep(50);
}
void AutoClicker::typeString(std::string str){
    for(char c : str){
        typeChar(c);

        if(GetAsyncKeyState('Z') && (c != 'Z' && c != 'z')){
            stopClicker();
            return;
        }
    }
}
void AutoClicker::clickAt(unsigned int x,unsigned int y){
    //Hover
    SetCursorPos(x,y);
    Sleep(10);

    //Click
    mouse_event(MOUSEEVENTF_LEFTDOWN,0,0,0,0);
    Sleep(6);
    mouse_event(MOUSEEVENTF_LEFTUP,0,0,0,0);
    Sleep(10);
}
void AutoClicker::makeSearch(std::string str){
    //click on search bar
    clickAt(148,54);

    //Type
    typeString(str);

    //Press enter
    pressKey(VK_RETURN);
    
    //Wait
    Sleep(5000);
}
void AutoClicker::changeAccount(int accNum){

    //Select account list
    clickAt(1789,612);
    Sleep(10);

    //TODO: Note for yamin : find out distance in pixels between accounts and store them in dist
    //then find out position of first account and put that in place of x and y in firstAccountPos variable
    //then Uncomment everything below and test and tweak the function to see if it works


    //const int dist = ;
    //const POINT firstAccountPos = {x,y};

    //clickAt(firstAccountPos.x,firstAccountPos.y += (dist * accNum));
}
void printCursorPos(){
    POINT point;
    GetCursorPos(&point);
    std::cout << "\rCursor Pos :" << point.x << " " << point.y << std::flush;
}
void AutoClicker::startClicker(){
    running = true;
    std::cout << "Clicker turned on\n";

    //Open names file
    std::ifstream ifs;
    ifs.open(LIST_NAME);
    if (!ifs.is_open()) {
        std::cerr << "Error: Could not open " << LIST_NAME << "\n";
        stopClicker();
        return;
    }
    std::string name;
    //get a name
    while(std::getline(ifs,name)){
        //For every name make search with prompt
        makeSearch((PROMPT + name ));
        if(!running) return;
    }
    stopClicker();
}

void AutoClicker::stopClicker(){
    running = false;
    std::cout << "Clicker turned off\n";
}
void AutoClicker::run(){
    while(1){
         while (true) {

        if (running)
            startClicker();

        // Hotkeys
        if (GetAsyncKeyState('Z') && running)
            stopClicker();

        if (GetAsyncKeyState('X') && !running)
            startClicker();
    }
    }
}