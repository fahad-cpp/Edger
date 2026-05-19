#include "AutoClicker.h"
#include "Logging.h"
#include <filesystem>
#include <fstream>
#include <iostream>
#include <thread>
#include <vector>
#include <windows.h>

void pressKey(WORD vk) {
    INPUT input = {0};

    // Key Down
    input.type = INPUT_KEYBOARD;
    input.ki.wVk = vk;
    SendInput(1, &input, sizeof(INPUT));

    Sleep(30);

    // Key Up
    input.ki.dwFlags = KEYEVENTF_KEYUP;
    SendInput(1, &input, sizeof(INPUT));
}
void typeChar(char c) {
    INPUT input = {0};
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
    // Hover
    SetCursorPos(x, y);
    Sleep(10);

    // Click
    mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
    Sleep(6);
    mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
    Sleep(10);
}
void AutoClicker::makeSearch(std::string str) {
    // click on search bar
    clickAt(searchBarLoc.x, searchBarLoc.y);

    // Type
    typeString(str);
    if (!running)
        return;

    // Press enter
    pressKey(VK_RETURN);

    // wait random delay from minSearchDelay to maxSearchDelay seconds
    int diff = maxSearchDelay - minSearchDelay;
    int delayTime = ((rand() % (diff + 1)) + minSearchDelay);
    int divide = 100;
    // divide delaytime and check for input 100 times while in delay for exiting
    for (int i = 0; i < divide; i++) {
        Sleep((delayTime * 1000) / divide);
        if (GetAsyncKeyState('Z')) {
            stopClicker();
            return;
        }
    }
}
void printAccounts(const std::vector<std::string> &accountDirectories) {
    std::printf("you have %zu edge accounts:\n", accountDirectories.size());
    int i = 1;
    for (const std::string &accountName : accountDirectories) {
        std::printf("%d.%s\n", i, accountName.c_str());
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
    // Assuming there will always be a default account
    accountDirectories.push_back("Default");
    for (const fs::directory_entry &entry : fs::directory_iterator(target)) {
        if (entry.is_directory()) {
            std::string folderName = entry.path().filename().string();
            if (folderName.contains("Profile ")) {
                accountDirectories.push_back(folderName);
            }
        }
    }

    return accountDirectories;
}

void openEdge(const std::string &accountName) {
    std::string exeLoc = "\"" + edgePath + "\\msedge.exe\"";

    std::string command =
        "start \"\" " + exeLoc + " --profile-directory=\"" + accountName + "\"";

    system(command.c_str());
}

void AutoClicker::startClicker() {
    // get search list and store in searchList
    running = true;

    // Open names file
    std::ifstream ifs;
    ifs.open(LIST_NAME);
    if (!ifs.is_open()) {
        std::cerr << "Failed to open " LIST_NAME "\n";
    }

    std::string line;
    std::vector<std::string> searchList = {};
    while (std::getline(ifs, line)) {
        searchList.push_back(line);
    }
    ifs.close();

    // Get all edge accounts
    std::vector<std::string> accountDirectories = getEdgeAccounts();
    int accountCount = accountDirectories.size();

    // For every account
    for (int i = 0; i < accountCount; i++) {
        openEdge(accountDirectories.at(i));
        Sleep(2000);

        // get a search line
        for (const std::string &line : searchList) {
            // search the line
            makeSearch((PROMPT + line));
            if (!running)
                return;
        }
    }

    stopClicker();
}

void AutoClicker::stopClicker() { running = false; }
void hideConsoleCursor() {
    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(out, &cursorInfo);
    cursorInfo.bVisible = false;
    SetConsoleCursorInfo(out, &cursorInfo);
}
void setIcon(const char *iconPath) {
    HWND hwnd = GetConsoleWindow();
    HICON icon = LoadIconA(GetModuleHandle(NULL), iconPath);
    SendMessage(hwnd, WM_SETICON, ICON_BIG, (LPARAM)icon);
    SendMessage(hwnd, WM_SETICON, ICON_SMALL, (LPARAM)icon);
}
void AutoClicker::run() {
    srand(time(NULL));
    setIcon("icon.ico");
    hideConsoleCursor();
    printAccounts(getEdgeAccounts());
    while (true) {
        if (!running) {
            liveLog("Edger is turned off : (press X to turn on)");
        }
        // Hotkeys
        if (GetAsyncKeyState('Z') && running) {
            liveLog("Edger is turned off : (press X to turn on)");
            stopClicker();
        }
        if (GetAsyncKeyState('X') && !running) {
            liveLog("Edger is turned on : (press Z to turn off)");
            startClicker();
        }
        // to reduce cpu usage
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
}
