#include "AutoClicker.h"
#include <windows.h>
#include <iostream>
#include <fstream>
#include <filesystem>
#include <vector>
#include <sstream>

void pressKey(WORD vk) {
    INPUT input = { 0 };

    //Key Down
    input.type = INPUT_KEYBOARD;
    input.ki.wVk = vk;
    SendInput(1, &input, sizeof(INPUT));

    Sleep(30);

    //Key Up
    input.ki.dwFlags = KEYEVENTF_KEYUP;
    SendInput(1, &input, sizeof(INPUT));
}
void typeChar(char c) {
    INPUT input = { 0 };
    bool pressShift = c == '?';
    input.type = INPUT_KEYBOARD;

    if (pressShift) {
        input.ki.wVk = VK_LSHIFT;
        input.ki.dwFlags = 0;
        SendInput(1, &input, sizeof(INPUT));
    }

    input.ki.wVk = VkKeyScanA(c);
    input.ki.dwFlags = 0;
    SendInput(1, &input, sizeof(INPUT));

    if (pressShift) {
        input.ki.wVk = VK_LSHIFT;
        input.ki.dwFlags = KEYEVENTF_KEYUP;
        SendInput(1, &input, sizeof(INPUT));
    }

    Sleep(50);
    input.ki.wVk = VkKeyScanA(c);
    input.ki.dwFlags = KEYEVENTF_KEYUP;
    SendInput(1, &input, sizeof(INPUT));
}

void AutoClicker::typeString(std::string str) {
    for (char c : str) {
        typeChar(c);

        if (GetAsyncKeyState('Z') && (c != 'Z' && c != 'z')) {
            stopClicker();
            return;
        }
    }
}
void clickAt(unsigned int x, unsigned int y) {
    //Hover
    SetCursorPos(x, y);
    Sleep(10);

    //Click
    mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
    Sleep(6);
    mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
    Sleep(10);
}
void AutoClicker::makeSearch(std::string str) {
    //click on search bar
    clickAt(searchBarLoc.x, searchBarLoc.y);

    //Type
    typeString(str);
    if(!running)return;

    //Press enter
    pressKey(VK_RETURN);

    //wait random delay from minSearchDelay to maxSearchDelay seconds
    int diff = maxSearchDelay - minSearchDelay;
    int delayTime = ((rand() % (diff + 1)) + minSearchDelay);
    int divide = 100;
    //divide delaytime and check for input 100 times while in delay for exiting
    std::printf("Waiting %d seconds...\n",delayTime);
    for(int i=0;i<divide;i++){
        Sleep((delayTime * 1000)/divide);
        if (GetAsyncKeyState('Z')) {
            stopClicker();
            return;
        }
    }
}
void printAccounts(std::vector<std::string>& accountDirectories){
    std::printf("%d accounts found:\n",accountDirectories.size());
    int i=1;
    for(const std::string& accountName : accountDirectories){
        std::printf("%d.%s\n",i,accountName.c_str());
        i++;
    }
}
std::vector<std::string> getEdgeAccounts() {
    namespace fs = std::filesystem;
    std::vector<std::string> accountDirectories = {};
    std::string envPath = "%APPDATA%\\..\\local\\Microsoft\\Edge\\User Data";
    const size_t MAX_LEN = 1024;
    char buffer[MAX_LEN];
    ExpandEnvironmentStringsA(envPath.c_str(), buffer, MAX_LEN);
    fs::path target = buffer;
    //Assuming there will always be a default account
    accountDirectories.push_back("Default");
    for (const fs::directory_entry& entry : fs::directory_iterator(target)) {
        if (entry.is_directory()) {
            std::string folderName = entry.path().filename().string();
            if (folderName.contains("Profile ")){
                accountDirectories.push_back(folderName);
            }
        }
    }

    printAccounts(accountDirectories);

    return accountDirectories;
}

void openEdge(const std::string& accountName) {
    std::string exeLoc = "\"" + edgePath  + "\\msedge.exe\"";

    std::string command = "start \"\" " + exeLoc + " --profile-directory=\""+accountName+"\"";
    std::cout << "Strting Edge on:" << accountName << "\n";
    //std::cout << "Executing Command: " << command << "\n";
    system(command.c_str());
}

void AutoClicker::startClicker() {
    //get search list and store in searchList
    running = true;
    std::cout << "Clicker turned on\n";
    
    //Open names file
    std::ifstream ifs;
    ifs.open(LIST_NAME);
    if (!ifs.is_open()) {
        std::cerr << "Failed to open "  LIST_NAME  "\n";
    }

    std::string line;
    std::vector<std::string> searchList = {};
    while(std::getline(ifs,line)){
        searchList.push_back(line);
    }
    ifs.close();

    //Get all edge accounts
    std::vector<std::string> accountDirectories = getEdgeAccounts();
    int accountCount = accountDirectories.size();

    //For every account
    for(int i=0;i<accountCount;i++){
        openEdge(accountDirectories.at(i));
        Sleep(2000);
        
        //get a search line
        int searchCount = 0;
        for(const std::string& line : searchList){
            //search the line
            std::cout << "Search Counter:" << searchCount << "\n";
            searchCount++;
            makeSearch((PROMPT + line));
            if (!running) return;
        }
    }

    stopClicker();
}

void AutoClicker::stopClicker() {
    running = false;
    std::cout << "Clicker turned off\n";
}
void AutoClicker::run() {
    srand(time(NULL));
    while (1) {
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