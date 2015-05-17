//
//  Material.cpp
//  libcat
//
//  Created by chenbingfeng on 15/5/15.
//  Copyright (c) 2015年 chenbingfeng. All rights reserved.
//

#include "Material.h"
#include "Logger.h"

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

/*
 switch(textureUse){
	case Material::Texture::Ambient:
 return "AMBIENT";
	case Material::Texture::Bump:
 return "BUMP";
	case Material::Texture::Diffuse:
 return "DIFFUSE";
	case Material::Texture::Emissive:
 return "EMISSIVE";
	case Material::Texture::None:
 return "NONE";
	case Material::Texture::Normal:
 return "NORMAL";
	case Material::Texture::Reflection:
 return "REFLECTION";
	case Material::Texture::Shininess:
 return "SHININESS";
	case Material::Texture::Specular:
 return "SPECULAR";
	case Material::Texture::Transparency:
 return "TRANSPARENCY";
	default:
 return "UNKNOWN";
	}
 }
 */
Texture::Usage Texture::typeString2usage(const char* typestr)
{
    if (strcmp(typestr, "AMBIENT") == 0) return Ambient;
    if (strcmp(typestr, "BUMP") == 0) return Bump;
    if (strcmp(typestr, "DIFFUSE") == 0) return Diffuse;
    if (strcmp(typestr, "EMISSIVE") == 0) return Emissive;
    if (strcmp(typestr, "NONE") == 0) return None;
    if (strcmp(typestr, "NORMAL") == 0) return Normal;
    if (strcmp(typestr, "REFLECTION") == 0) return Reflection;
    if (strcmp(typestr, "SHININESS") == 0) return Shininess;
    if (strcmp(typestr, "SPECULAR") == 0) return Specular;
    if (strcmp(typestr, "TRANSPARENCY") == 0) return Transparency;
    if (strcmp(typestr, "UNKNOWN") == 0) return Unknown;
    return Unknown;
}

void Texture::fromJSON(rapidjson::Value& value)
{
    using namespace rapidjson;
    /*
     writer << json::obj;
     writer << "id" = id;
     writer << "filename" = path;
     if (uvTranslation[0] != 0.f || uvTranslation[1] != 0.f)
     writer << "uvtranslation" = uvTranslation;
     if (uvScale[0] != 1.f || uvScale[1] != 1.f)
     writer << "uvscaling" = uvScale;
     writer << "type" = getTextureUseString(usage);
     writer << json::end;
     */

    // id
    _id = value["id"].GetString();

    // path
    _path = value["filename"].GetString();

    // uvtranslation
    if (value.HasMember("uvtranslation")) {
        auto& juv = value["uvtranslation"];
        _uvTranslation[0] = juv[0].GetDouble();
        _uvTranslation[1] = juv[1].GetDouble();
    }

    // uvScale
    if (value.HasMember("uvscaling")) {
        auto& juvsc = value["uvscaling"];
        _uvScale[0] = juvsc[0].GetDouble();
        _uvScale[1] = juvsc[1].GetDouble();
    }

    // type
    _usage = typeString2usage(value["type"].GetString());

    // end
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

void Material::fromJSON(rapidjson::Value& value)
{
    using namespace rapidjson;
    /*
     writer << json::obj;
     writer << "id" = id;
     if (ambient.valid)
     writer << "ambient" = ambient.value;
     if (diffuse.valid)
     writer << "diffuse" = diffuse.value;
     if (emissive.valid)
     writer << "emissive" = emissive.value;
     if (opacity.valid)
     writer << "opacity" = opacity.value;
     if (specular.valid)
     writer << "specular" = specular.value;
     if (shininess.valid)
     writer << "shininess" = shininess.value;
     if (!textures.empty())
     writer << "textures" = textures;
     writer << json::end;
     */
    // id
    _id = value["id"].GetString();

    // ambient
    if (value.HasMember("ambient")) {
        _ambient.valid = true;
        auto& jambient = value["ambient"];
        _ambient.value[0] = jambient[0].GetDouble();
        _ambient.value[1] = jambient[1].GetDouble();
        _ambient.value[2] = jambient[2].GetDouble();
    }

    // diffuse
    if (value.HasMember("diffuse")) {
        _diffuse.valid = true;
        auto& jdiffuse = value["diffuse"];
        _diffuse.value[0] = jdiffuse[0].GetDouble();
        _diffuse.value[1] = jdiffuse[1].GetDouble();
        _diffuse.value[2] = jdiffuse[2].GetDouble();
    }

    // emissive
    if (value.HasMember("emissive")) {
        _emissive.valid = true;
        auto& jemissive = value["emissive"];
        _emissive.value[0] = jemissive[0].GetDouble();
        _emissive.value[1] = jemissive[1].GetDouble();
        _emissive.value[2] = jemissive[2].GetDouble();
    }

    // opacity
    if (value.HasMember("opacity")) {
        _opacity.valid = true;
        _opacity.value = value["opacity"].GetDouble();
    }

    // specular
    if (value.HasMember("specular")) {
        _specular.valid = true;
        auto& jspecular = value["specular"];
        _specular.value[0] = jspecular[0].GetDouble();
        _specular.value[1] = jspecular[1].GetDouble();
        _specular.value[2] = jspecular[2].GetDouble();
    }

    // shininess
    if (value.HasMember("shininess")) {
        _shininess.valid = true;
        _shininess.value = value["shininess"].GetDouble();
    }

    // textures
    auto& jtextures = value["textures"];
    LOG("textures=", jtextures.Size());
    for (SizeType i = 0; i < jtextures.Size(); i++) {
        auto one_texture = Texture::create();
        one_texture->fromJSON(jtextures[i]);
        _textures.push_back(one_texture);
    }
    //end
}

NS_CAT_END