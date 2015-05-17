//
//  Keyframe.h
//  libcat
//
//  Created by chenbingfeng on 15/5/15.
//  Copyright (c) 2015年 chenbingfeng. All rights reserved.
//

#ifndef __libcat__Keyframe__
#define __libcat__Keyframe__

#include <memory>
#include "def.h"
#include "Basewave.h"
#include "Node.h"

NS_CAT_BEGIN

class Keyframe:public Basewave
{
public:
    typedef std::shared_ptr<Keyframe> SP;

    float time;
    float translation[3];
    float rotation[4];
    float scale[3];
    bool hasTranslation;
    bool hasRotation;
    bool hasScale;

    static SP create();
private:
    Keyframe();
};

NS_CAT_END


#endif /* defined(__libcat__Keyframe__) */
