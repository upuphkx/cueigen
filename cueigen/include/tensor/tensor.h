#pragma once
#include <cueigen/include/common/type.h>

#include "common/cueigen_type.h"
namespace cueigen{
namespace tensor{



class Tensor : public Node{
public:
    virtual ~Tensor(){
        if(shape_) {
            delete shape_;
            shape_ = nullptr;
        }
        if(stride_) {
            delete stride_;
            stride_ = nullptr;
        }
    }
    Tensor(){}

    Tensor(Shape* shape, Stride* stride, void* buffer, uint32_t dims, kTensorMemoryType_t mem_type);

    Tensor(Tensor& tensor);

    Tensor(Tensor&& tensor);

    Tensor operator=(Tensor& other);

    Tensor operator=(Tensor&& other);

    std::string getGraphNodeName() override {
        return std::string("Tensor Node");
    }
    kGraphNodeType_t getGraphNodeType() override {
        return kGraphNodeType_t::kTensor;
    }

    const void* getBuffer() const;

    const Shape* getShape() const;

    const Stride* getStride() const;

    const uint32_t& getDims() const;

    const size_t getBufferBytes() const;

    const uint32_t getElementNum() const;

    const kTensorMemoryType_t& getMemType() const;

    const kTensorDataType_t& getDataType() const;

    Tensor* setBuffer(void* buffer);

    Tensor* setShape(Shape* shape);

    Tensor* setStride(Stride* stride);

    template<typename DataType> 
    Tensor* setShape(const std::initializer_list<DataType>& shape){
        shape_ = new Shape(shape);
    }

    template<typename DataType> 
    Tensor* setStride(const std::initializer_list<DataType>& stride){
        stride_ = new Stride(stride);
    }

    Tensor* setDims(const uint32_t& dims);
    Tensor* setMemType(const kTensorMemoryType_t& mem_type);
    Tensor* setDataType(const kTensorDataType_t& data_type);

    void printTensorInfo() const;
    std::string toString() const;
private:
    Shape* shape_{nullptr};
    Stride* stride_{nullptr};
    void* buffer_{nullptr};
    uint32_t dims_{0};
    kTensorDataType_t data_type_{kDataTypeNotSpecify};
    kTensorMemoryType_t mem_type_{kMemTypeNotSpecify};
};

}
}