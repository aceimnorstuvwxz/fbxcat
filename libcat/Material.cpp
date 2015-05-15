//
//  Material.cpp
//  libcat
//
//  Created by chenbingfeng on 15/5/15.
//  Copyright (c) 2015年 chenbingfeng. All rights reserved.
//

#include "Material.h"


NS_CAT_BEGIN

Texture::SP Texture::create()
{
    return SP(new Texture());
}

Texture::Texture()
{
    _usage = Unknown;
    //source = 0
    _uvTranslation[0] = _uvTranslation[1] = 0.f;
    _uvScale[0] = _uvScale[1] = 1.f;
}


std::string& Texture::getId()
{
    return _id;
}


Material::SP Material::create()
{
    return SP(new Material());
}

Texture::SP Material::getTexture(const char* idt)
{
    for (auto texture :_textures) {
        if (texture->getId().compare(idt) == 0) {
            return texture;
        }
    }
    return nullptr;
}

int Material::getTextureIndex(Texture::SP texture) const
{
    int n = (int)_textures.size(); //??
    for (int i = 0; i < n; i++) {
        if (_textures[i] == texture) return i;
    }
    return -1;
}

Material::Material(): _diffuse(), _ambient(), _emissive(), _specular(), _shininess(), _opacity()
{
    //source = 0
}

NS_CAT_END