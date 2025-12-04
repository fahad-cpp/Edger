#include <string>
#define LIST_NAME "chessplayers.txt"
#define PROMPT "What is the age of "
class AutoClicker{
    bool running = false;
    public:
    void makeSearch(std::string str);
    void startClicker();
    void stopClicker();
    void typeString(std::string str);
    void run();
};