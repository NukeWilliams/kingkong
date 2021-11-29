#pragma once

#include "kingkong/settings.h"
#include <cstdio>
#include <ctime>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <string>

namespace kingkong {
    enum class LogLevel
    {
#ifndef ERROR
#ifndef DEBUG
    DEBUG = 0,
    INFO,
    WARNING,
    ERROR,
    CRITICAL,
#endif
#endif
    }
}