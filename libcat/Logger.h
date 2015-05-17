//
//  Logger.h
//  libcat
//
//  Created by chenbingfeng on 15/5/16.
//  Copyright (c) 2015年 chenbingfeng. All rights reserved.
//

#ifndef libcat_Logger_h
#define libcat_Logger_h

#include "def.h"
#include <iostream>

#define LOG(...) Log(__FILE__, __FUNCTION__, __LINE__, __VA_ARGS__)

inline void LogRecursive(std::ostream& os){}

template<typename T, typename... Args>
void LogRecursive(std::ostream& os, T first, const Args&... rest)
{
    os << first << " ";
    LogRecursive(os, rest...);
}

template<typename... Args>
void Log(const char* file, const char* func, int line, const Args&... args)
{
    //std::cout << file <<":"<< "(" << line << ")"<< func<<": ";
    std::cout << func << "/" << line << ": ";
    LogRecursive(std::cout, args...);
    std::cout << std::endl;
}

#endif
