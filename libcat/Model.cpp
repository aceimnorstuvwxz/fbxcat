//
//  Model.cpp
//  libcat
//
//  Created by chenbingfeng on 15/5/15.
//  Copyright (c) 2015年 chenbingfeng. All rights reserved.
//

#include "Model.h"

NS_CAT_BEGIN

Model::SP Model::create()
{
    return SP(new Model());
}

void Model::fromJSON(rapidjson::Document& doc)
{
    using namespace rapidjson;
    /*
     writer.obj(6);
     writer << "version" = version;
     writer << "id" = id;
     writer << "meshes" = meshes;
     writer << "materials" = materials;
     writer << "nodes" = nodes;
     writer << "animations" = animations;
     writer.end();
     */

    //id
    _id = doc["id"].GetString();

    //meshes
    auto& jmeshes = doc["meshes"];
    for (SizeType i = 0; i < jmeshes.Size(); i++) {
        
    }
}


NS_CAT_END