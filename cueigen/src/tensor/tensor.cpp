#include <cueigen/include/tensor/tensor.h>

namespace cueigen{
namespace tensor{

Tensor::Tensor(Shape shape, Stride stride, void* buffer, uint32_t dims, kTensorMemoryType_t mem_type):
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



}
}