//
//  Basewave.h
//  libcat
//
//  Created by chenbingfeng on 15/5/16.
//  Copyright (c) 2015年 chenbingfeng. All rights reserved.
//

#ifndef __libcat__Basewave__
#define __libcat__Basewave__

#include "def.h"

#include "rapidjson/rapidjson.h"
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"

NS_CAT_BEGIN

class Basewave
{
public:
    virtual void fromJSON(rapidjson::Document& document);
    virtual void fromJSON(rapidjson::Value& value);
};

NS_CAT_END

#endif /* defined(__libcat__Basewave__) */
