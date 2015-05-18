//
//  main.cpp
//  libcat
//
//  Created by chenbingfeng on 15/5/15.
//  Copyright (c) 2015年 chenbingfeng. All rights reserved.
//

#include <iostream>
#include <memory>
#include "Loader.h"


static int main2(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    auto model = cat::Model::create();
    cat::Loader loader;
    loader.load("animation_case.g3dj", model);

    return 0;
}
