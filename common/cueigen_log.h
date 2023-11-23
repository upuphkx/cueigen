#pragma once
#include <iostream>
#include <string>

#include "cueigen_type.h"
namespace cueigen{
namespace log{
static uint32_t cueigen_msg_level = 0; //default close msg
static uint32_t tab_count = 0; //default 0

uint32_t inline cueigen_log_level(){
    char* is_msg = getenv("CUEIGEN_MSG_LEVEL");
    if (nullptr!=is_msg){
        cueigen_msg_level = std::stoi(is_msg);
    }
    return cueigen_msg_level;
}

inline void CUEIGEN_DEBUG_INFO(){
    std::cout << std::endl;
}

template<typename Ts, typename ... Rs>
inline void CUEIGEN_DEBUG_INFO(const Ts& ts, const Rs& ... rs){
    if(cueigen_log_level()){
        std::cout << ts << " ";
        CUEIGEN_DEBUG_INFO(rs...);
    }
}

inline void cueigen_log(const std::string& log){
    std::string s_tab = "";
    for (uint32_t iter = 0; iter < tab_count; iter++) s_tab += "    ";
    CUEIGEN_DEBUG_INFO(s_tab + log);
}

#define CUEIGEN_ERROR_LOCATION() \
    CUEIGEN_DEBUG_INFO("At ", __FILE__, ": ", __LINE__);   \

#define CUEIGEN_MSG_HEADER(expr) \
    cueigen_log("+call "#expr);   \
    tab_count++;

#define CUEIGEN_MSG_FOOTER(expr) \
    tab_count--;                 \
    cueigen_log("-call "#expr);   

}
}
