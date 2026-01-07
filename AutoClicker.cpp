#include "AutoClicker.h"
#include <windows.h>
#include <iostream>
#include <fstream>
void pressEnter(){
    INPUT input = {0};

    // ENTER DOWN
    input.type = INPUT_KEYBOARD;
    input.ki.wVk = VK_RETURN;
    SendInput(1, &input, sizeof(INPUT));

    Sleep(30);

    // ENTER UP
    input.ki.dwFlags = KEYEVENTF_KEYUP;
    SendInput(1, &input, sizeof(INPUT));
}
void AutoClicker::typeString(std::string str){

    INPUT input = {};
    for(char c : str){
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
        input.ki.dwFlags = KEYEVENTF_KEYUP;
        SendInput(1,&input,sizeof(INPUT));

        Sleep(50);
        
        if(GetAsyncKeyState('Z') && (c != 'Z' && c != 'z')){
            stopClicker();
            return;
        }
    }
}

void AutoClicker::makeSearch(std::string str){
    //Hover on search bar
    SetCursorPos(148,54);
    Sleep(10);

    //Click on search bar
    mouse_event(MOUSEEVENTF_LEFTDOWN,0,0,0,0);
    Sleep(6);
    mouse_event(MOUSEEVENTF_LEFTUP,0,0,0,0);
    Sleep(10);

    //Type
    typeString(str);

    //Press enter
    pressEnter();
    

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
        if(running){
            startClicker();
            if(GetAsyncKeyState('Z')){
                stopClicker();
            }
        }
        if(GetAsyncKeyState('X')){
            startClicker();
        }
    }
}