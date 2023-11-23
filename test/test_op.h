#include <cueigen/include/op/op.h>
using namespace cueigen::op;
using namespace cueigen::log;

void testOp(){
    OpCreater op_c;
    Op* element_op = op_c.createOp("Element_wise");
    CUEIGEN_DEBUG_INFO("op name: ", element_op->getName(), ", addr @", element_op);
    op_c.createOp("test_not_registe_op");
}

