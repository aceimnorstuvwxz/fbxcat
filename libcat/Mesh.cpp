//
//  Mesh.cpp
//  libcat
//
//  Created by chenbingfeng on 15/5/15.
//  Copyright (c) 2015年 chenbingfeng. All rights reserved.
//

#include "Mesh.h"

NS_CAT_BEGIN
MeshPart::SP MeshPart::create()
{
    return SP(new MeshPart());
}

void MeshPart::clear()
{
    _indices.clear();
    _id.clear();
    _primitiveType = 0;
}
void MeshPart::set(const char* idt, const unsigned int& primitiveType, const std::vector<unsigned short>& indices)
{
    _id = idt;
    _primitiveType = primitiveType;
    _indices.clear();
    _indices.insert(_indices.end(), indices.begin(), indices.end());
}
MeshPart::MeshPart()
{
    _primitiveType = 0;
}

Mesh::SP Mesh::create()
{
    return SP(new Mesh());
}
void Mesh::clear()
{
    _vertices.clear();
    _hashes.clear();
    _attributes = _vertexSize = 0;
    _parts.clear();
}

Mesh::Mesh()
{
    _attributes = 0;
    _vertexSize = 0;
}

NS_CAT_END