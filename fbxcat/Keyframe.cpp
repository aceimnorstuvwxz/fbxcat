//
//  Keyframe.cpp
//  libcat
//
//  Created by chenbingfeng on 15/5/15.
//  Copyright (c) 2015年 chenbingfeng. All rights reserved.
//

#include "Keyframe.h"

NS_CAT_BEGIN

Keyframe::SP Keyframe::create()
{
    return SP(new Keyframe());
}

Keyframe::Keyframe()
{
    time = 0.;
    translation[0] = translation[1] = translation[2] = 0.;
    rotation[0] = rotation[1] = rotation[2] = 0.; rotation[3] = 1.;
    scale[0] = scale[1] = scale[2] = 1.;
    hasTranslation = hasRotation = hasScale = false;
}

void Keyframe::fromJSON(rapidjson::Value& value)
{
    using namespace rapidjson;
    /*
    writer << json::obj;
    writer << "keytime" = time;
    if (hasRotation)
        writer << "rotation" = rotation;
    if (hasScale)
        writer << "scale" = scale;
    if (hasTranslation)
        writer << "translation" = translation;
    writer << json::end;
     */

    // keytime
    time = value["keytime"].GetDouble();

    // rotation
    if (value.HasMember("rotation")) {
        hasRotation = true;
        rotation[0] = value["rotation"][0].GetDouble();
        rotation[1] = value["rotation"][1].GetDouble();
        rotation[2] = value["rotation"][2].GetDouble();
        rotation[3] = value["rotation"][3].GetDouble();
    }

    // scale
    if (value.HasMember("scale")) {
        hasScale = true;
        scale[0] = value["scale"][0].GetDouble();
        scale[1] = value["scale"][1].GetDouble();
        scale[2] = value["scale"][2].GetDouble();
    }

    // translation
    if (value.HasMember("translation")) {
        hasTranslation = true;
        translation[0] = value["translation"][0].GetDouble();
        translation[1] = value["translation"][1].GetDouble();
        translation[2] = value["translation"][2].GetDouble();
    }

    // end
}

NS_CAT_END