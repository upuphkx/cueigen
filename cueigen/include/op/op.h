#pragma once

#include <cueigen/include/common/type.h>
#include <cueigen/include/common/attr.h>

namespace cueigen{
namespace op{
using namespace cueigen::attr;
class Op : public Node{
public:
    virtual std::string getName();

    virtual kOpNodeType_t getType();

    const uint32_t& getInputNum() const;

    const uint32_t& getOutputNum() const;

    virtual Attr* getAttr();

    virtual bool isCuOp(); //host / dev

    virtual cueigenError_t execute();

    virtual cueigenError_t setInputNodes(Nodes* nodes);

    virtual cueigenError_t setOutputNodes(Nodes* nodes);

    virtual cueigenError_t insetInputNode(Node& node);

    virtual cueigenError_t insetOutputNode(Node& node);

    virtual cueigenError_t clearInputNodes();

    virtual cueigenError_t clearOutputNodes();

    virtual cueigenError_t removeInputNodebyNodeName(std::string& node_name);

    virtual cueigenError_t removeOutputNodebyNodeName(std::string& node_name);

    const virtual Nodes* getInputNode() const;
    
    const virtual Nodes* getOutputNode() const; 
public:
    Attr* attr_{nullptr};
    Nodes* input_nodes_{nullptr};
    Nodes* output_nodes_{nullptr};
    kOpNodeType_t op_type_{kOpTypeNotSpecify};
private:

};

}
}