#include <iostream>
#include "colors.h"

namespace colors {
    // Define ANSI escape codes for text color
    const std::string RED_TEXT = "\033[1;31m";
    const std::string GREEN_TEXT = "\033[1;32m";
    const std::string LIGHT_BLUE_TEXT = "\033[1;34m";
    const std::string RESET_TEXT = "\033[0m";

    std::string GREEN() {
        return GREEN_TEXT;
    }

    std::string LIGHT_BLUE() {
        return LIGHT_BLUE_TEXT;
    }

    std::string RESET() {
        return RESET_TEXT;
    }
}