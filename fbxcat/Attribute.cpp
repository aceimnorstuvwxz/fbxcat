//
//  Attribute.cpp
//  libcat
//
//  Created by chenbingfeng on 15/5/15.
//  Copyright (c) 2015年 chenbingfeng. All rights reserved.
//

#include "Attribute.h"
#include "Logger.h"
NS_CAT_BEGIN

unsigned int string2attribute(const char* name)
{
    for (int i = 0; i < ATTRIBUTE_COUNT; i++) {
        if (strcmp(name, AttributeNames[i]) == 0) {
            return i;
        }
    }
    return ATTRIBUTE_UNKNOWN;
}

void Attributes::add(const char* attributeName)
{
    add(string2attribute(attributeName));
}

void Attributes::fromJSON(rapidjson::Value& array)
{
    using namespace rapidjson;
    LOG("Attributes::fromJSON num=", array.Size());
    for (SizeType i = 0; i < array.Size(); i++) {
        add(array[i].GetString());
    }
    LOG("Attributes value=", value);
}


NS_CAT_END