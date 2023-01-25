#include "log.h"

void LogError(std::string error, std::string details, ErrorType type)
{
    if (type == WARNING)
    {
        std::cout << "[WARNING] " << error << ": " << details << "\n";
    }
    if (type == ERROR)
    {
        std::cout << "[ERROR] " << error << ": " << details << "\n";
    }
    if (type == FATAL)
    {
        std::cout << "[FATAL ERROR] " << error << ": " << details << "\n";
        exit(EXIT_SUCCESS);
    }
}