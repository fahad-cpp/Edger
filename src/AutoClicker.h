#include <string>
#include <Windows.h>
#define LIST_NAME "chessplayers.txt"
#define PROMPT ""
class AutoClicker{
    bool running = false;
    public:
    void makeSearch(std::string str);
    void changeAccount(int accNum);
    void startClicker();
    void stopClicker();
    void typeString(std::string str);
    void clickAt(unsigned int x,unsigned int y);
    void changeAccount(unsigned int);
    void pressKey(WORD vk);
    void run();
};