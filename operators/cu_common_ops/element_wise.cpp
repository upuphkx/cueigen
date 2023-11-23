#include <cueigen/include/op/op.h>

namespace cueigen{
namespace op{

class Element_wise : public Op{
public:
    ~Element_wise(){CUEIGEN_DEBUG_INFO("call ~Element_wise");}
    
     std::string getName()  override{
        return "Element_wise";
     }

     kOpNodeType_t getType() override{
        return op_type_;
     }

     Attr* getAttr() override{
        return attr_;
     }

     bool isCuOp() override{
        return true;
     }

     cueigenError_t execute() override{
        return kNotImpl_t;
     }

     cueigenError_t setInputNodes(Nodes* nodes) override{
        input_nodes_ = nodes;
        return kSuccess_t;
     }

     cueigenError_t setOutputNodes(Nodes* nodes) override{
        output_nodes_ = nodes;
        return kSuccess_t;
     }

     cueigenError_t insetInputNode(Node& node) override{
        input_nodes_->extend(node);
        return kSuccess_t;
     }

     cueigenError_t insetOutputNode(Node& node) override{
        output_nodes_->extend(node);
        return kSuccess_t;
     }

     cueigenError_t clearInputNodes() override{
        if (input_nodes_->size_){
            input_nodes_->pop();
        }
        return kSuccess_t;
     }

     cueigenError_t clearOutputNodes() override{
        if (output_nodes_->size_){
            output_nodes_->pop();
        }
        return kSuccess_t;
     }

     cueigenError_t removeInputNodebyNodeName(std::string& node_name) override{
        return kNotImpl_t;
     }

     cueigenError_t removeOutputNodebyNodeName(std::string& node_name) override{
        return kNotImpl_t;
     }

     const Nodes* getInputNode() const override{
        return input_nodes_;
     }
    
     const Nodes* getOutputNode() const override{
        return output_nodes_;
     }

private:

};

RegOp(Element_wise);

}
}