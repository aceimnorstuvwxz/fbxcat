//
//  Node.cpp
//  libcat
//
//  Created by chenbingfeng on 15/5/15.
//  Copyright (c) 2015年 chenbingfeng. All rights reserved.
//

#include "Node.h"
#include "Logger.h"

NS_CAT_BEGIN

NodePart::SP NodePart::create()
{
    return SP(new NodePart());
}

void NodePart::fromJSON(rapidjson::Value& value)
{
    using namespace rapidjson;
    /*
    writer << json::obj;
    writer << "meshpartid" = meshPart->id;
    writer << "materialid" = material->id;
    if (!bones.empty()) {
        writer.val("bones").is().arr();
        for (std::vector<std::pair<Node *, FbxAMatrix> >::const_iterator it = bones.begin(); it != bones.end(); ++it) {
            writer << json::obj;
            writer << "node" = it->first->id;
            writeAsFloat(writer, "translation", it->second.GetT().mData);
            writeAsFloat(writer, "rotation", it->second.GetQ().mData);
            writeAsFloat(writer, "scale", it->second.GetS().mData);
            writer << json::end;
        }
        writer.end();
    }
    if (!uvMapping.empty()) {
        writer.val("uvMapping").is().arr(uvMapping.size(), 16);
        for (std::vector<std::vector<Material::Texture *> >::const_iterator it = uvMapping.begin(); it != uvMapping.end(); ++it) {
            writer.arr((*it).size(), 16);
            for (std::vector<Material::Texture *>::const_iterator tt = (*it).begin(); tt != (*it).end(); ++tt)
                writer << material->getTextureIndex(*tt);
            writer.end();
        }
        writer.end();
    }
    writer << json::end;
     */
    // meshpartid
    _meshPartId = value["meshpartid"].GetString();
    // TODO

    // materialid
    _materialId = value["materialid"].GetString();

    // bones
    if (value.HasMember("bones")) {
        auto& jbones = value["bones"];
        LOG("bones=", jbones.Size());
        _bones.reserve(jbones.Size());
        for (SizeType i = 0; i < jbones.Size(); i++) {
            auto& jbone = jbones[i];
            Matrix4x4 mat44;
            mat44.translation[0] = jbone["translation"][0].GetDouble();
            mat44.translation[1] = jbone["translation"][1].GetDouble();
            mat44.translation[2] = jbone["translation"][2].GetDouble();
            mat44.translation[3] = jbone["translation"][3].GetDouble();
            mat44.rotation[0] = jbone["rotation"][0].GetDouble();
            mat44.rotation[1] = jbone["rotation"][1].GetDouble();
            mat44.rotation[2] = jbone["rotation"][2].GetDouble();
            mat44.rotation[3] = jbone["rotation"][3].GetDouble();
            mat44.scale[0] = jbone["scale"][0].GetDouble();
            mat44.scale[1] = jbone["scale"][1].GetDouble();
            mat44.scale[2] = jbone["scale"][2].GetDouble();
            mat44.scale[3] = jbone["scale"][3].GetDouble();
            _bones.push_back({jbone["node"].GetString(), mat44});
        }
    }

    //uvMapping
    if (value.HasMember("uvMapping")) {
        auto& jarrout = value["uvMapping"];
        _uvMapping.reserve(jarrout.Size());
        std::vector<int> vec;
        for (SizeType i = 0; i < jarrout.Size(); i++) {
            auto& jarrin = jarrout[i];
            vec.reserve(jarrin.Size());
            for (SizeType i = 0; i < jarrin.Size(); i++) {
                vec.push_back(jarrin[i].GetInt());
            }
        }
        _uvMapping.push_back(vec);
    }

    // end
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

void Node::fromJSON(rapidjson::Value& value)
{
    using namespace rapidjson;
    /*
     writer << json::obj;
     writer << "id" = id;
     if (transform.rotation[0] != 0. || transform.rotation[1] != 0. || transform.rotation[2] != 0. || transform.rotation[3] != 1.)
     writer << "rotation" = transform.rotation;
     if (transform.scale[0] != 1. || transform.scale[1] != 1. || transform.scale[2] != 1.)
     writer << "scale" = transform.scale;
     if (transform.translation[0] != 0. || transform.translation[1] != 0. || transform.translation[2] != 0.)
     writer << "translation" = transform.translation;
     if (!parts.empty())
     writer << "parts" = parts;
     if (!children.empty())
     writer << "children" = children;
     writer << json::end;
     */

    // id
    _id = value["id"].GetString();

    // rotation
    if (value.HasMember("rotation")) {
        auto& jrotation = value["rotation"];
        _transform.rotation[0] = jrotation[0].GetDouble();
        _transform.rotation[1] = jrotation[1].GetDouble();
        _transform.rotation[2] = jrotation[2].GetDouble();
        _transform.rotation[3] = jrotation[3].GetDouble();
    }

    // scale
    if (value.HasMember("scale")) {
        auto& jscale = value["scale"];
        _transform.scale[0] = jscale[0].GetDouble();
        _transform.scale[1] = jscale[1].GetDouble();
        _transform.scale[2] = jscale[2].GetDouble();
    }

    // translation
    if (value.HasMember("translation")) {
        auto& jtrans = value["translation"];
        _transform.translation[0] = jtrans[0].GetDouble();
        _transform.translation[1] = jtrans[1].GetDouble();
        _transform.translation[2] = jtrans[2].GetDouble();
    }

    // parts
    if (value.HasMember("parts")) {
        auto& jparts = value["parts"];
        for (SizeType i = 0; i < jparts.Size(); i++) {
            auto one_part = NodePart::create();
            one_part->fromJSON(jparts[i]);
            _parts.push_back(one_part);
        }
    }

    // children
    if (value.HasMember("children")) {
        auto& jchildren = value["children"];
        for (SizeType i = 0; i < jchildren.Size(); i++) {
            auto one_node = Node::create();
            one_node->fromJSON(jchildren[i]);
            _children.push_back(one_node);
        }
    }

    // end

}

NS_CAT_END