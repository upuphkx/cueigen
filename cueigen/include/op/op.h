#pragma once
#include <map>
#include <cueigen/include/common/type.h>
#include <cueigen/include/common/attr.h>

namespace cueigen{
namespace op{
using namespace cueigen::attr;
using namespace cueigen::log;


class Op : public Node{
public:
    virtual ~Op() {CUEIGEN_DEBUG_INFO("call ~Op");}
    std::string getGraphNodeName() override {
        return "Op";
    }
    kGraphNodeType_t getGraphNodeType()override {
        return kGraphNodeType_t::kOp;
    }

    virtual std::string getName() = 0;
     
    virtual kOpNodeType_t getType() = 0;

    const uint32_t& getInputNum() const;

    const uint32_t& getOutputNum() const;

    virtual Attr* getAttr() = 0;

    virtual bool isCuOp() = 0; //host / dev

    virtual cueigenError_t execute() = 0;

    virtual cueigenError_t setInputNodes(Nodes* nodes) = 0;

    virtual cueigenError_t setOutputNodes(Nodes* nodes) = 0;

    virtual cueigenError_t insetInputNode(Node& node) = 0;

    virtual cueigenError_t insetOutputNode(Node& node) = 0;

    virtual cueigenError_t clearInputNodes() = 0;

    virtual cueigenError_t clearOutputNodes() = 0;

    virtual cueigenError_t removeInputNodebyNodeName(std::string& node_name) = 0;

    virtual cueigenError_t removeOutputNodebyNodeName(std::string& node_name) = 0;

    const virtual Nodes* getInputNode() const = 0;
    
    const virtual Nodes* getOutputNode() const = 0; 
public:
    Attr* attr_{nullptr};
    Nodes* input_nodes_{nullptr};
    Nodes* output_nodes_{nullptr};
    kOpNodeType_t op_type_{kOpTypeNotSpecify};
private:

};

typedef void* (*create_func_ptr)(); 

template<typename T>
class StaticHelper{
public:
    static T& getStaticObject(){
        static T object;
        return object;
    }
};

using op_creater_map = StaticHelper<std::map<std::string, create_func_ptr>>;
using op_deleter_map = StaticHelper<std::map<std::string, Op*>>;
class OpCreater{
public:
    static cueigenError_t registerOp(const std::string& op_name, const create_func_ptr& func_ptr){
        if(op_creater_map::getStaticObject().find(op_name) != op_creater_map::getStaticObject().end()){
            CUEIGEN_DEBUG_INFO(op_name, "is registered!");
        } else{ 
            CUEIGEN_DEBUG_INFO("register ", op_name);
            op_creater_map::getStaticObject().insert(std::make_pair(op_name, func_ptr));
        }
        return kSuccess_t;
    }
    Op* createOp(const std::string& op_name){
        if(op_creater_map::getStaticObject().find(op_name) != op_creater_map::getStaticObject().end()){
            void* _ptr = op_creater_map::getStaticObject()[op_name]();
            if(op_deleter_map::getStaticObject().find(op_name) == op_deleter_map::getStaticObject().end()){
                op_deleter_map::getStaticObject().insert(std::make_pair(op_name, reinterpret_cast<Op*>(_ptr)));
            }
            return reinterpret_cast<Op*>(_ptr);
        } else{ 
            CUEIGEN_DEBUG_INFO(op_name, "is not registered!");
            return nullptr;
        }
    }

    void destroyOp(){
        for (auto iter = op_deleter_map::getStaticObject().begin(); iter != op_deleter_map::getStaticObject().end(); iter++){
            if (iter->second){
                CUEIGEN_DEBUG_INFO("destory op ", iter->first, ", addr: @", iter->second);
                delete iter->second;
                iter->second = nullptr;
            }
        }
    }
    ~OpCreater(){
        CUEIGEN_DEBUG_INFO("call ~OpCreater");
        destroyOp();
    }

private:

};


class RegistHelper{
public:
    RegistHelper(const std::string& op_name, const create_func_ptr& func_ptr){
        OpCreater::registerOp(op_name, func_ptr);
    }
};

#define RegOp(OpName)                                                           \
        void* OpName##CallOpConstruct(){                                        \
            return new OpName;                                                  \
        }                                                                       \
        RegistHelper OpName##RegistHelper(#OpName, OpName##CallOpConstruct);


}
}

