//
//  Model.cpp
//  libcat
//
//  Created by chenbingfeng on 15/5/15.
//  Copyright (c) 2015年 chenbingfeng. All rights reserved.
//

#include "Model.h"
#include "Logger.h"

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

    // id
    _id = doc["id"].GetString();

    // meshes
    auto& jmeshes = doc["meshes"];
    LOG("meshes.size=", jmeshes.Size());
    for (SizeType i = 0; i < jmeshes.Size(); i++) {
        auto one_mesh = Mesh::create();
        one_mesh->fromJSON(jmeshes[i]);
        _meshes.push_back(one_mesh);
    }

    // materials
    auto& jmaterials = doc["materials"];
    LOG("materials.size=", jmaterials.Size());
    for (SizeType i = 0; i < jmaterials.Size(); i++) {
        auto one_material = Material::create();
        one_material->fromJSON(jmaterials[i]);
        _materials.push_back(one_material);
    }

    // nodes
    auto& jnodes = doc["nodes"];
    LOG("nodes.size=", jnodes.Size());
    for (SizeType i = 0; i < jnodes.Size(); i++) {
        auto one_node = Node::create();
        one_node->fromJSON(jnodes[i]);
        _nodes.push_back(one_node);
    }

    // animations
    auto& janimations = doc["animations"];
    LOG("animations.size=", janimations.Size());
    for (SizeType i = 0; i < janimations.Size(); i++) {
        auto one_animation = Animation::create();
        one_animation->fromJSON(janimations[i]);
        _animations.push_back(one_animation);
    }

    // end
}


NS_CAT_END