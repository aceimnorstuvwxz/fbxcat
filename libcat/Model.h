//
//  Model.h
//  libcat
//
//  Created by chenbingfeng on 15/5/15.
//  Copyright (c) 2015年 chenbingfeng. All rights reserved.
//

#ifndef __libcat__Model__
#define __libcat__Model__

#include <vector>
#include <memory>
#include <string>

#include "def.h"
#include "Mesh.h"
#include "Material.h"
#include "Node.h"
#include "Animation.h"

NS_CAT_BEGIN

class Animation;
class Material;
class Mesh;
class Node;

class Model
{
public:
    typedef std::shared_ptr<Model> SP;
    static SP create();
    Node::SP getNode(const char* idt) const;
    Material::SP getMaterial(const char* idt) const;
    size_t getTotalNodeCount() const;
    size_t getTotalNodePartCount() const;
    size_t getMeshpartCount() const;
    size_t getTotalVertexCount() const;
    size_t getTotalIndexCount() const;
    size_t getTotalTextureCount() const;

private:
    Model(){};

    std::string _id;
    std::vector<Animation::SP> _animations;
    std::vector<Material::SP> _materials;
    std::vector<Mesh::SP> _meshes;
    std::vector<Node::SP> _nodes;
};


NS_CAT_END

#endif /* defined(__libcat__Model__) */
