#pragma once
#include <cueigen/include/tensor/tensor.h>
#include <cueigen/include/common/type.h>
#include "common/cueigen_log.h"


void testTensor(){
    cueigen::tensor::Tensor tensor;
    void* cpu_mem = malloc(sizeof(float) * 1024);
    tensor.setMemType(kHostMemType)
            ->setBuffer(cpu_mem)
            ->setDataType(kFP32)
            ->setDims(3)
            ->setShape<uint32_t>({1,32,32})
            ->setStride<uint32_t>({1,1,1});
    tensor.printTensorInfo();


    Shape shape({1,2,3,4});
    cueigen::log::CUEIGEN_DEBUG_INFO(shape.toString());
    shape.extend(5);
    cueigen::log::CUEIGEN_DEBUG_INFO(shape.toString());
    cueigen::log::CUEIGEN_DEBUG_INFO(shape.pop());
    cueigen::log::CUEIGEN_DEBUG_INFO(shape.toString());
}