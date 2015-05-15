//
//  Node.cpp
//  libcat
//
//  Created by chenbingfeng on 15/5/15.
//  Copyright (c) 2015年 chenbingfeng. All rights reserved.
//

#include "Node.h"

NS_CAT_BEGIN

NodePart::SP NodePart::create()
{
    return SP(new NodePart());
}

Node::SP Node::create(const char* idt)
{
    return SP(new Node(idt));
}

Node::Node(const char* idt)
{
    memset(&_transform, 0, sizeof(Transform));
    _transform.scale[0] = _transform.scale[1] = _transform.scale[2] = 1.f;
    if (idt) {
        _id = idt; //???
    }
}

Node::SP Node::getChild(const char *idt) const
{
    for (auto node : _children){
        if (node->_id.compare(idt) == 0) {
            return node;
        }
        auto cnode = node->getChild(idt);
        if (cnode) {
            return cnode;
        }
    }
    return nullptr;
}

bool Node::hasPartsRecurisive() const
{
    if (!_parts.empty()) {
        return true;
    }
    for (auto node : _children) {
        if (node->hasPartsRecurisive()) {
            return true;
        }
    }
    return false;
}

size_t Node::getTotalNodeCount() const
{
    size_t result = _children.size();
    for (auto node : _children) {
        result += node->getTotalNodeCount();
    }
    return result;
}

size_t Node::getTotalNodePartCount() const
{
    size_t result = _parts.size();
    for (auto node : _children) {
        result += node->getTotalNodePartCount();
    }
    return result;
}

NS_CAT_END