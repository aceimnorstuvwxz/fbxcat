//
//  Mesh.h
//  libcat
//
//  Created by chenbingfeng on 15/5/15.
//  Copyright (c) 2015年 chenbingfeng. All rights reserved.
//

#ifndef __libcat__Mesh__
#define __libcat__Mesh__

#include <memory>
#include <vector>
#include <string>

#include "def.h"
#include "Basewave.h"
#include "Attribute.h"

NS_CAT_BEGIN

class MeshPart: public Basewave
{
public:
    typedef std::shared_ptr<MeshPart> SP;
    static SP create();

    void clear();
    void set(const char* idt, const unsigned int& primitiveType, const std::vector<unsigned short>& indices);

    std::string& getId() const;
    std::vector<unsigned short>& getIndices() const;
    unsigned int getPrimitiveType() const;

    void fromJSON(rapidjson::Value& value) override;
private:
    // FbxCluster sourceBones
    MeshPart();

    std::string _id;
    std::vector<unsigned short> _indices;
    unsigned int _primitiveType;
};

class Mesh: public Basewave
{
public:
    typedef std::shared_ptr<Mesh> SP;
    static SP create();
    void clear();

    //? why all unsigned int???????
    inline unsigned int indexCount() {
        unsigned int result = 0;
        for (auto part : _parts) {
            result += part->getIndices().size();
        }
        return result;
    }

    inline unsigned int add(const float* vertex) {
        const unsigned int hash = calcHash(vertex, _vertexSize);
        const unsigned int n = (unsigned int)_hashes.size();
        for (unsigned int i = 0; i < n; i++) {
            if ((_hashes[i] == hash) && compare(&_vertices[i*_vertexSize], vertex, _vertexSize))
                return i;
        }
        _hashes.push_back(hash);
        _vertices.insert(_vertices.end(), &vertex[0], &vertex[_vertexSize]);
        return (unsigned int)_hashes.size() - 1;
    }

    inline unsigned int calcHash(const float *vertex, const unsigned int size) {
        unsigned int result = 0;
        for (unsigned int i = 0; i < size; i++)
            result += ((*((unsigned int *)&vertex[i])) & 0xffffff00) >> 8;
        return result;
    }

    inline bool compare(const float* lhs, const float* rhs, const unsigned int &n) {
        for (unsigned int i = 0; i < n; i++)
            if ((*(unsigned int*)&lhs[i] != *(unsigned int*)&rhs[i]) && lhs[i] != rhs[i])
                return false;
        return true;
    }

    void fromJSON(rapidjson::Value& value) override;
private:
    Attributes _attributes;
    unsigned int _vertexSize;
    std::vector<float> _vertices;
    std::vector<unsigned int> _hashes;
    std::vector<MeshPart::SP> _parts;

    Mesh();

};

NS_CAT_END

#endif /* defined(__libcat__Mesh__) */
