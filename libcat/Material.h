//
//  Material.h
//  libcat
//
//  Created by chenbingfeng on 15/5/15.
//  Copyright (c) 2015年 chenbingfeng. All rights reserved.
//

#ifndef __libcat__Material__
#define __libcat__Material__

#include <memory>
#include <vector>
#include <string>

#include "def.h"

NS_CAT_BEGIN
template<typename T, size_t n=1>
struct OptionalValue {
    bool valid;
    T value[n];
    OptionalValue() : valid(false) {
        for (int i = 0; i < n; ++i)
            value[i] = (T)0;
    }
    inline void unset() {
        valid = false;
    }
    void set(T v0, ...) {
        va_list vl;
        value[0] = v0;
        va_start(vl, v0);
        for (int i = 1; i < n; i++)
            value[i] = va_arg(vl, T);
        va_end(vl);
        valid = true;
    }
    template <typename S, size_t m> void set(const S (&v)[m]) {
        const int c = m > n ? n : m;
        for (int i = 0; i < c; i++)
            value[i] = (T)v[i];
        valid = true;
    }
};

template<typename T>
struct OptionalValue<T, 1> {
    bool valid;
    T value;
    OptionalValue() : valid(false), value((T)0) {}
    inline void unset() {
        valid = false;
    }
    inline void set(T v) {
        valid = true;
        value = v;
    }
};

class Texture
{
public:
    enum Usage {
        Unknown = 0,
        None = 1,
        Diffuse = 2,
        Emissive = 3,
        Ambient = 4,
        Specular = 5,
        Shininess = 6,
        Normal = 7,
        Bump = 8,
        Transparency = 9,
        Reflection = 10
    };

    typedef std::shared_ptr<Texture> SP;
    static SP create();

    void test() const;
    std::string& getId();

private:
    // fbxFileTexture source
    std::string _id;
    std::string _path;
    float _uvTranslation[2];
    float _uvScale[2];
    //Fixme add Matrix3<float> uvTransform;???
    Usage _usage;
    Texture();
};

class Material
{
public:
    typedef std::shared_ptr<Material> SP;
    static SP create();
    Texture::SP getTexture(const char* idt);
    int getTextureIndex(Texture::SP texture) const;

private:
    //fbxSurfaceMaterial source
    std::string _id;
    OptionalValue<float, 3> _diffuse;
    OptionalValue<float, 3> _ambient;
    OptionalValue<float, 3> _emissive;
    OptionalValue<float, 3> _specular;
    OptionalValue<float> _shininess;
    OptionalValue<float> _opacity;
    std::vector<Texture::SP> _textures;
    Material();
};

NS_CAT_END

#endif /* defined(__libcat__Material__) */
