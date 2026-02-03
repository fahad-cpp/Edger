#ifndef AUTOCLICKER_H
#define AUTOCLICKER_H
#include <string>
#define LIST_NAME "searchList.txt"
#define PROMPT ""
//max search delay in seconds
const int maxSearchDelay = 7;
const std::string edgePath = "C:\\Program Files (x86)\\Microsoft\\Edge\\Application";

typedef struct vec2{
    int x;
    int y;
}vec2;
const vec2 searchBarLoc = {148,54};
class AutoClicker{
    bool running = false;
    public:
    void makeSearch(std::string str);
    void startClicker();
    void stopClicker();
    void typeString(std::string str);
    void run();
};
#endif