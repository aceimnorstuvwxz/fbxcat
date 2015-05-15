//
//  Animation.cpp
//  libcat
//
//  Created by chenbingfeng on 15/5/15.
//  Copyright (c) 2015年 chenbingfeng. All rights reserved.
//

#include "Animation.h"

NS_CAT_BEGIN

NodeAnimation::SP NodeAnimation::create()
{
    return SP(new NodeAnimation());
}

NodeAnimation::NodeAnimation()
{
    _node = nullptr;
    _translate = _rotate = _scale = false;
}

Animation::SP Animation::create()
{
    return SP(new Animation());
}

NS_CAT_END