//
//  Loader.h
//  libcat
//
//  Created by chenbingfeng on 15/5/16.
//  Copyright (c) 2015年 chenbingfeng. All rights reserved.
//

#ifndef __libcat__Loader__
#define __libcat__Loader__

#include <string>
#include "def.h"
#include "Model.h"

#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"

NS_CAT_BEGIN

class Model;

class Loader
{
public:
    // laod `filename` to model
    bool load(const std::string& filename, Model::SP model);

private:
//    void convert(const std::string& json_raw, Model::SP model);
//    void convertAst(const Value& jmesh, Mesh::SP mesh);
};


NS_CAT_END

#endif /* defined(__libcat__Loader__) */
