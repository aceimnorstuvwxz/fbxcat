//
//  Animation.cpp
//  libcat
//
//  Created by chenbingfeng on 15/5/15.
//  Copyright (c) 2015年 chenbingfeng. All rights reserved.
//

#include "Animation.h"
#include "Logger.h"
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

void NodeAnimation::fromJSON(rapidjson::Value &value)
{
    using namespace rapidjson;

    /*
     writer.obj(2);
     writer << "boneId" = node->id;
     writer << "keyframes" = keyframes;
     writer.end();
     */

    // boneId
    _nodeId = value["boneId"].GetString();

    // keyframes
    auto& jkeygrames = value["keyframes"];
    _keyframes.reserve(jkeygrames.Size());
    for (SizeType i = 0; i < jkeygrames.Size(); i++) {
        auto keyframe = Keyframe::create();
        keyframe->fromJSON(jkeygrames[i]);
        _keyframes.push_back(keyframe);
    }

    // end

}

Animation::SP Animation::create()
{
    return SP(new Animation());
}

void Animation::fromJSON(rapidjson::Value& value)
{
    using namespace rapidjson;
    /*
     writer.obj(2);
     writer << "id" = id;
     writer << "bones" = nodeAnimations;
     writer.end();
     */

    // id
    _id = value["id"].GetString();

    // bones
    auto& jbones = value["bones"];
    _nodeAnimations.reserve(jbones.Size());
    LOG("bones=", jbones.Size());
    for (SizeType i = 0; i < jbones.Size();  i++) {
        auto one_node_animation = NodeAnimation::create();
        one_node_animation->fromJSON(jbones[i]);
        _nodeAnimations.push_back(one_node_animation);
    }

    // end

}

NS_CAT_END