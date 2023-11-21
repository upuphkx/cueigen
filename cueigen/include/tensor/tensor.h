#pragma once
#include <cueigen/include/common/type.h>

#include "common/cueigen_type.h"
namespace cueigen{
namespace tensor{


class Shape {
public:
    Shape();
    Shape(Shape& other);
    Shape(Shape&& other);
    Shape operator=(Shape& other);
    Shape operator=(Shape&& other);;
    ~Shape();
private:
    uint32_t dims_;
};

class Stride {
public:
    Stride();
    Stride(Shape& Stride);
    ~Stride();
private:
    uint32_t dims_;
};

class Tensor {
public:
    virtual ~Tensor(){}
    Tensor();
    Tensor(Shape shape, Stride stride, void* buffer, uint32_t dims, kTensorMemoryType_t mem_type);
    Tensor(Tensor& tensor);
    Tensor(Tensor&& tensor);
    Tensor operator=(Tensor& other);
    Tensor operator=(Tensor&& other);

    void* getBuffer();
    Shape* getShape();
    Stride* getStride();

    Tensor* setBuffer(void* buffer);
    Tensor* setShape(Shape* shape);
    Tensor* setStride(Stride* Stride);
private:
    Shape shape_;
    Stride stride_;
    void* buffer_;
    uint32_t dims_;
    kTensorMemoryType_t mem_type_;




};

}
}