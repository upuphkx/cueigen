#pragma once
#include "common/cueigen_log.h"

using namespace cueigen::log;
void testMy(){
 CUEIGEN_MSG_HEADER(testMy);
 CUEIGEN_ERROR_LOCATION();
 CUEIGEN_MSG_FOOTER(testMy);
}
