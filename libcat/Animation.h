//
//  Animation.h
//  libcat
//
//  Created by chenbingfeng on 15/5/15.
//  Copyright (c) 2015年 chenbingfeng. All rights reserved.
//

#ifndef __libcat__Animation__
#define __libcat__Animation__

#include <memory>
#include <vector>
#include <string>

#include "def.h"
#include "Basewave.h"
#include "Node.h"
#include "Keyframe.h"

NS_CAT_BEGIN


class NodeAnimation: public Basewave
{
public:
    typedef std::shared_ptr<NodeAnimation> SP;
    static SP create();
    
private:
    Node::SP _node;
    std::vector<Keyframe::SP> _keyframes;
    bool _translate, _rotate, _scale;

    NodeAnimation();
};

class Animation: public Basewave
{
public:
    typedef std::shared_ptr<Animation> SP;
    static SP create();

private:
    std::string _id;
    std::vector<NodeAnimation::SP> _nodeAnimations;
    Animation(){};
};


NS_CAT_END

#endif /* defined(__libcat__Animation__) */
