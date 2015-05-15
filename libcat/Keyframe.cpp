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

NS_CAT_END