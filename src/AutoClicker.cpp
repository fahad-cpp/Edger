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
    bool pressShift = c == '?';
    input.type = INPUT_KEYBOARD;

    if(pressShift){
        input.ki.wVk = VK_LSHIFT;
        input.ki.dwFlags = 0;
        SendInput(1,&input,sizeof(INPUT));
    }

    input.ki.wVk = VkKeyScanA(c);
    input.ki.dwFlags = 0;
    SendInput(1,&input,sizeof(INPUT));
    
    if(pressShift){
        input.ki.wVk = VK_LSHIFT;
        input.ki.dwFlags = KEYEVENTF_KEYUP;
        SendInput(1,&input,sizeof(INPUT));
    }
    
    Sleep(50);
    input.ki.wVk = VkKeyScanA(c);
    input.ki.dwFlags = KEYEVENTF_KEYUP;
    SendInput(1,&input,sizeof(INPUT));
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
void AutoClicker::changeAccount(unsigned int accNum){
    
}
void AutoClicker::startClicker(){
    running = true;
    std::cout << "Clicker turned on\n";
    static int accountNum = 0;
    
    //Open names file
    std::ifstream ifs;
    ifs.open(LIST_NAME);
    //select an account
    changeAccount(accountNum);
    std::string line;
    //get a name
    while(std::getline(ifs,line)){
        //For every name make search with prompt
        makeSearch((PROMPT + line ));
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