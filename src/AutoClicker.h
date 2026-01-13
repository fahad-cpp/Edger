#include <string>
#include <Windows.h>
#define LIST_NAME "searchlist.txt"
#define PROMPT ""
class AutoClicker{
    bool running = false;
    public:
    void makeSearch(std::string str);
    void startClicker();
    void stopClicker();
    void typeString(std::string str);
    void clickAt(unsigned int x,unsigned int y);
    void changeAccount(unsigned int);
    void pressKey(WORD vk);
    void run();
};