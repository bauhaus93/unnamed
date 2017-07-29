#include <iostream>

#include "logger/Logger.h"

using namespace std;

int main(int argc, char** argv) {
    Logger l { LogLevel::INFO };

    l.Info("SEAS");
    return 0;
}
