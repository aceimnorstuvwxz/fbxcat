//
//  Loader.cpp
//  libcat
//
//  Created by chenbingfeng on 15/5/16.
//  Copyright (c) 2015年 chenbingfeng. All rights reserved.
//


#include "Loader.h"

#include <fstream>
#include <iostream>

#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"

NS_CAT_BEGIN


bool Loader::load(const std::string& filename, Model::SP model)
{
    std::ifstream fin;
    std::cout << filename << std::endl;
    fin.open(filename, std::ios::in);
    if (!fin.is_open()) {
        std::cout << "open failed" << std::endl;
    }

    // get size
    auto pos_beg = fin.tellg();
    fin.seekg(0, std::ios::end);
    auto size = fin.tellg() - pos_beg;
    std::cout << "size = " << size <<std::endl;
    fin.seekg(0, std::ios::beg);

    std::string json_raw;
    json_raw.reserve(size);

    // read in
    std::string str;
    while (fin.good()) {
        getline(fin, str);
        json_raw.append(str);
    }

    rapidjson::Document doc;
    doc.Parse(json_raw.c_str());
//    model->fromJSON(doc);

//    std::cout << json_raw << std::endl;
    std::cout << "json_raw size=" << json_raw.size() << std::endl;
    return true;
}

//void Loader::convert(const std::string& json_raw, Model::SP model)
//{
//    using namespace rapidjson;
//    Document doc;
//    doc.Parse(json_raw.c_str());
//
//    /* the model format
//    writer.obj(6);
//    writer << "version" = version;
//    writer << "id" = id;
//    writer << "meshes" = meshes;
//    writer << "materials" = materials;
//    writer << "nodes" = nodes;
//    writer << "animations" = animations;
//    writer.end();
//     */
//
//
//    //first version, we dont have it
//
//    //id, a string
//    model->_id = doc["id"].GetString();
//
//    //meshes, an array
//    const Value& jmeshes = doc["meshes"];
//    for (SizeType i = 0; i < jmeshes.Size(); i++) {
//        auto& jmesh = jmeshes[i];
//        auto mesh = cat::Mesh::create();
//        convertAst(jmesh, mesh);
//        model->_meshes.push_back(mesh);
//    }
//
//}
//
//void Loader::void convertAst(const Value& jmesh, Mesh::SP mesh)
//{
//    //todo
//}




NS_CAT_END