#include "Logging.h"
#include <iostream>
void liveLog(const std::string &str) {
    static int lastlength = 0;
    std::cout << std::flush << str;
    if (lastlength > str.length()) {
        std::cout << std::string(" ", lastlength - str.length());
    }
    std::cout << '\r';
    lastlength = str.length();
}
