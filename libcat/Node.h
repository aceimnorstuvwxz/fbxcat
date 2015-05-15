//
//  Node.h
//  libcat
//
//  Created by chenbingfeng on 15/5/15.
//  Copyright (c) 2015年 chenbingfeng. All rights reserved.
//

#ifndef __libcat__Node__
#define __libcat__Node__

#include <memory>
#include <vector>
#include <string>

#include "def.h"
#include "Material.h"
#include "Mesh.h"

NS_CAT_BEGIN

typedef struct {
    float translation[3];
    float rotation[4];
    float scale[3];
} Transform;

struct Matrix4x4
{
    float data[4*4];
};

class Node;
typedef std::weak_ptr<Node> WPNode; //avoid cycle reference

class NodePart
{
public:
    typedef std::shared_ptr<NodePart> SP;
    static SP create();

private:
    MeshPart::SP _meshPart;
    Material::SP _material;
    std::vector<std::pair<WPNode, Matrix4x4> > _bones;
    std::vector<std::vector<Texture::SP>> _uvMapping;
    NodePart(){};
};

class Node
{
public:
    typedef std::shared_ptr<Node> SP;
    static SP create(const char* idt = nullptr);
    SP getChild(const char* idt) const;
    bool hasPartsRecurisive() const;
    size_t getTotalNodeCount() const;
    size_t getTotalNodePartCount() const;

private:
    Transform _transform;
    std::string _id;
    std::vector<NodePart::SP> _parts;
    std::vector<Node::SP> _children;

    Node(const char* idt = nullptr);

};



NS_CAT_END

#endif /* defined(__libcat__Node__) */
