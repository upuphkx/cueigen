#include <cueigen/include/op/op.h>

namespace cueigen{
namespace op{

const uint32_t& Op::getInputNum() const{
    return this->input_nodes_->size_;
}

const uint32_t& Op::getOutputNum() const{
    return this->output_nodes_->size_;
}



}
}