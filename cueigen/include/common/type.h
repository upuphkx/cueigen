#pragma once
#include <initializer_list>
#include <sstream>

#include "common/cueigen_log.h"

typedef enum {
    kHostMemType,
    kDeviceMemType,
    kMemTypeNotSpecify,
    MemTypeCount
} kTensorMemoryType_t;

typedef enum{
    kFP32,
    kFP16,
    kINT32,
    kINT16,
    kUINT32,
    kUINT16,
    kINT8,
    kCOMPLEX,
    kDataTypeNotSpecify,
    DataTypeCount
}kTensorDataType_t;

typedef enum{
    kOp,
    kTensor,
    kNodeTypeNotSpecify,
    NodeTypeCount
} kGraphNodeType_t;

typedef enum{
    kElement_wise_add,
    kElement_wise_mul,
    kActivation_relu,
    kActivation_softmax,
    kOpTypeNotSpecify,
    OpTypecount
}kOpNodeType_t;

typedef enum{
    kSuccess_t,
    kError_t,
    kNotImpl_t,
    cueigenErrorTypeCount
}cueigenError_t;

typedef enum{
    kOpAttr,
    kGraphAttr,
    kTensorAttr,
    kAttrTypeNotSpecify,
    AttrTypeCount
} kAttrType_t;

inline std::string memoryTypeToString(const kTensorMemoryType_t& mem_type){
    switch (mem_type){
        case kHostMemType:
        return "kHostMemType";
        case kDeviceMemType:
        return "kDeviceMemType";
        case kMemTypeNotSpecify:
        return "kMemTypeNotSpecify";
        default:
        return "kUnknowMemType";
    }
}


inline std::string dataTypeToString(const kTensorDataType_t& data_type){
    switch (data_type){
        case kFP32:
        return "kFP32";
        case kFP16:
        return "kFP16";
        case kMemTypeNotSpecify:
        return "kMemTypeNotSpecify";
        default:
        return "kUnknowMemType";
    }
}
template<class DataType, uint32_t Size>
struct SmallVec{
SmallVec(){}

SmallVec(const std::initializer_list<DataType>& init_list){
    if (Size < 5){
        cueigen::log::CUEIGEN_DEBUG_INFO("At ", __FILE__, ":", __LINE__, 
                                        ", cueigen report error: SmallVec Init Size Must > 5"); //NCDHW
        exit(-1);
    }
    for (const auto iter : init_list){
        buffer_[size_] = iter;
        size_ += 1;
    }
}

SmallVec(SmallVec<DataType, Size>& other){
    buffer_ = other.buffer_;
    size_ = other.size_;
}

SmallVec operator=(SmallVec<DataType, Size>& other){
    buffer_ = other.buffer_;
    size_ = other.size_;
}

~SmallVec(){
    if(buffer_){
         delete[] buffer_;
    }
    buffer_ = nullptr;
}

bool extend(const DataType& new_data){
    buffer_[size_] = new_data;
    size_ ++;
    return true;
}

DataType& pop(){
    size_ --;
    auto& tmp_item =  buffer_[size_];
    return tmp_item;
}

std::string toString() const {
    std::stringstream ss;
    auto visitSmallVec = [&](){
        ss << "dims: " << size_;
        ss << " [";
        for (uint32_t iter=0; iter < size_; iter++){
            ss << std::to_string(buffer_[iter]);
            ss << ", ";
        }
        ss << "]";
    };
    visitSmallVec();
    return ss.str();
} 

DataType* buffer_  = new DataType[Size];
uint32_t size_ = 0;

};

typedef SmallVec<uint32_t, 8> Shape;
typedef SmallVec<uint32_t, 8> Stride;

class Node{ // all tensor, op is Node 
public:
    virtual ~Node(){}
    virtual std::string getGraphNodeName() = 0;
    virtual kGraphNodeType_t getGraphNodeType() = 0;
};


typedef SmallVec<Node, 16> Nodes;

