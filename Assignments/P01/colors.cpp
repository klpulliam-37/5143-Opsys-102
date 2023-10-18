#include <iostream>
#include "colors.h"

namespace colors {
    // Define ANSI escape codes for text color
    const std::string RED_TEXT = "\033[1;31m";
    const std::string GREEN_TEXT = "\033[1;32m";
    const std::string BLUE_TEXT = "\033[0;34m";
    const std::string LIGHT_BLUE_TEXT = "\033[1;34m";
    const std::string YELLOW_TEXT = "\033[1;33m";
    const std::string RESET_TEXT = "\033[0m";

    std::string RED() {
        return RED_TEXT;
    }

    std::string GREEN() {
        return GREEN_TEXT;
    }

    std::string BLUE() {
        return BLUE_TEXT;
    }

    std::string LIGHT_BLUE() {
        return LIGHT_BLUE_TEXT;
    }

    std::string YELLOW() {
        return YELLOW_TEXT;
    }

    std::string RESET() {
        return RESET_TEXT;
    }

    std::string RemoveAnsi(std::string input) {
        size_t pos = 0;
        while ((pos = input.find("\033[")) != std::string::npos) {
            // Find the position of 'm' after "\033["
            size_t endPos = input.find('m', pos);

            if (endPos != std::string::npos) {
                // Remove the escape code
                input.erase(pos, endPos - pos + 1);
            }
        }

        return input;
    }
}