//
//  Basewave.cpp
//  libcat
//
//  Created by chenbingfeng on 15/5/16.
//  Copyright (c) 2015年 chenbingfeng. All rights reserved.
//

#include "Basewave.h"
#include <iostream>
NS_CAT_BEGIN

void Basewave::fromJSON(rapidjson::Document &document)
{
    std::cout << "error, baseware from json document." << std::endl;
}

void Basewave::fromJSON(rapidjson::Value& value)
{
    std::cout << "error, baseware from json value."  << std::endl;
}

NS_CAT_END