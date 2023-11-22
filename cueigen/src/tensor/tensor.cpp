#include <cueigen/include/tensor/tensor.h>

namespace cueigen{
namespace tensor{

Tensor::Tensor(Shape *shape, Stride *stride, void* buffer, uint32_t dims, kTensorMemoryType_t mem_type):
        shape_(shape),
        stride_(stride),
        buffer_(buffer),
        dims_(dims),
        mem_type_(mem_type){}

Tensor::Tensor(Tensor& other){
    shape_ = other.shape_;
    stride_ = other.stride_;
    buffer_ = other.buffer_;
    dims_ = other.dims_;
    mem_type_ = other.mem_type_;
}



const void* Tensor::getBuffer()const { return buffer_; }
const Shape* Tensor::getShape() const{ return shape_; }
const Stride* Tensor::getStride() const{ return stride_; }
const uint32_t& Tensor::getDims()const{
    return dims_;
}

const uint32_t Tensor::getElementNum() const{
    uint32_t element_num = 1;
    for(auto iter = 0; iter < dims_; iter++){
        element_num *= shape_->buffer_[iter];
    }
    return element_num;
}

const size_t Tensor::getBufferBytes() const{
    if (data_type_ == kFP32 || data_type_ == kINT32){
        return this->getElementNum() * 4;
    } else if (data_type_ == kFP16 || data_type_ == kINT16){
        return this->getElementNum() * 2;
    } else {
        return 0;
    }
}

const kTensorMemoryType_t& Tensor::getMemType()const{
    return mem_type_;
}

const kTensorDataType_t& Tensor::getDataType() const{
    return data_type_;
}

Tensor* Tensor::setBuffer(void* buffer){
    buffer_ = buffer;
    return this;
}
Tensor* Tensor::setShape(Shape* shape){
    shape_ = shape;
    return this;
}

Tensor* Tensor::setStride(Stride* stride){
    stride_ = stride;
    return this;
}



Tensor* Tensor::setDims(const uint32_t& dims){
    if (dims != 0)  dims_  = dims;
    return this;
}


Tensor* Tensor::setMemType(const kTensorMemoryType_t& mem_type){
    mem_type_ = mem_type;
    return this;
}

Tensor* Tensor::setDataType(const kTensorDataType_t& data_type){
    data_type_ = data_type;
    return this;
}

std::string Tensor::toString() const {
    std::stringstream ss;
    auto f = [&](){
        ss << "Tensor info: ";
        ss << ", data type: " << dataTypeToString(data_type_);
        ss << ", buffer: @" << buffer_;
        ss << ", buffer size: " << getBufferBytes();
        ss << ", dims: " << dims_;
        ss << ", element num: " << getElementNum();
        ss << ", shape: " << shape_->toString();
        ss << ", stride: " << stride_->toString();
        ss << ", memory type: " << memoryTypeToString(mem_type_);
    };
    f();
    return ss.str();
}

void Tensor::printTensorInfo() const {
    cueigen::log::CUEIGEN_DEBUG_INFO(this->toString());
}
}
}