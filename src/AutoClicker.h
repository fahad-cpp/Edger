#include <string>
#define LIST_NAME "chessplayers.txt"
#define PROMPT "What is the age of "
#include <windows.h>
class AutoClicker{
    bool running = false;
    public:
    void makeSearch(std::string str);
    void changeAccount(int accNum);
    void startClicker();
    void stopClicker();
    void typeString(std::string str);
    void clickAt(unsigned int x,unsigned int y);
    void pressKey(WORD vk);
    void run();
};