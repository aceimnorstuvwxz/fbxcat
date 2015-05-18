//
//  Mesh.cpp
//  libcat
//
//  Created by chenbingfeng on 15/5/15.
//  Copyright (c) 2015年 chenbingfeng. All rights reserved.
//

#include "Mesh.h"
#include "Logger.h"

NS_CAT_BEGIN

/*
static const char* getPrimitiveTypeString(const int &primitiveTypeId) {
    switch(primitiveTypeId){
        case 0:
            return "POINTS";
        case 1:
            return "LINES";
        case 3:
            return "LINE_STRIP";
        case 4:
            return "TRIANGLES";
        case 5:
            return "TRIANGLE_STRIP";
        default:
            return "UNKNOWN";
    }
}*/

static int primitiveTypeString2int(const char* type)
{
    if (strcmp(type, "POINTS") == 0) return 0;
    if (strcmp(type, "LINES") == 0) return 1;
    if (strcmp(type, "LINE_STRIP") == 0) return 3;
    if (strcmp(type, "TRIANGLES") == 0) return 4;
    if (strcmp(type, "TRIANGLE_STRIP") == 0) return 5;
    if (strcmp(type, "UNKNOWN") == 0) return 6;
    assert(false);
    return 6;
}


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

void MeshPart::fromJSON(rapidjson::Value& value)
{
    using namespace rapidjson;
    /*
     writer.obj(3);
     writer << "id" = id;
     writer << "type" = getPrimitiveTypeString(primitiveType);
     writer.val("indices").is().data(indices, 12);
     writer << json::end;
     */

    // id
    _id = value["id"].GetString();

    // type
    _primitiveType = primitiveTypeString2int(value["type"].GetString());

    // indices
    auto& jindices = value["indices"];
    LOG("meshpart indices=", jindices.Size());
    _indices.reserve(jindices.Size());
    for (SizeType i = 0; i < jindices.Size(); i++) {
        _indices.push_back(static_cast<unsigned short>(jindices[i].GetInt()));
    }
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

void Mesh::fromJSON(rapidjson::Value &value)
{
    using namespace rapidjson;
    LOG("Mesh::fromJSON");
    /*
     writer.obj(3);
     writer << "attributes" = attributes;
     writer.val("vertices").is().data(vertices, vertexSize);
     writer << "parts" = parts;
     writer.end();
     */

    // attributes   "attributes": ["POSITION", "NORMAL", "TEXCOORD0", "TEXCOORD1"],
    auto& jattributes = value["attributes"];
    LOG("attributes=", jattributes.Size());
    _attributes.fromJSON(jattributes);


    // vertices
    auto& jvertices = value["vertices"];
    LOG("vertices=", jvertices.Size());
    _vertices.reserve(jvertices.Size());
    _vertexSize = jvertices.Size();
    for (SizeType i = 0; i < jvertices.Size(); i++) {
        _vertices.push_back(static_cast<float>(jvertices[i].GetDouble()));
    }

    // parts
    auto& jparts = value["parts"];
    LOG("meshparts=", jparts.Size());
    for (SizeType i = 0; i < jparts.Size(); i++) {
        auto one_mesh_part = MeshPart::create();
        one_mesh_part->fromJSON(jparts[i]);
        _parts.push_back(one_mesh_part);
    }
    //end
}

NS_CAT_END