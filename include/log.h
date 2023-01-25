#include <iostream>
#include <stdlib.h>

enum ErrorType { WARNING, ERROR, FATAL };

void LogError(std::string error, std::string details, ErrorType type);