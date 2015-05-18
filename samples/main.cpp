//
//  main.cpp
//  samples
//
//  Created by chenbingfeng on 15/5/19.
//  Copyright (c) 2015年 chenbingfeng. All rights reserved.
//

#include <iostream>
#include "../fbxcat/cat.h"

int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    auto model = cat::Model::create();
    cat::Loader loader;
    loader.load("animation_case.g3dj", model);

    return 0;
}
