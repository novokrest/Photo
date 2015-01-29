#include "cameracommunication_utils.h"

bool stringToBool(const string &str)
{
    return !strcmp(str.c_str(), "true");
}

void countdown(int seconds)
{
    int i = seconds;
    while(i > 0) {
        cout << "Remaining: " << i << " seconds" << endl;
        sleep(1);
        --i;
    }
}

