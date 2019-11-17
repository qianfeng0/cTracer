
#ifndef _UNWIND_BACKTRACE_H_
#define _UNWIND_BACKTRACE_H_

#include "stack.hpp"
int get_stack(StackBase *s);

#include "stack_warp.h"

int get_stack(StackWrap *s);

#endif