#pragma once
#include <cueigen/include/common/type.h>

namespace cueigen{
namespace attr{

class Attr{
public:
virtual ~Attr(){}
virtual kAttrType_t getAttrType() = 0; // op attr, graph attr, tensor attr ...
};

class OpAttr : public Attr{
public:
kAttrType_t getAttrType() override {
    return kAttrType_t::kOpAttr;
}
};

class GraphAttr : public Attr{
public:
kAttrType_t getAttrType() override {
    return kAttrType_t::kGraphAttr;
}
};

class TensorAttr : public Attr{
public:
kAttrType_t getAttrType() override {
    return kAttrType_t::kTensorAttr;
}
};

}
}