
#include <unwind.h>

#include "stack_warp.h"
#include "unwind_backtrace.h"

// get stack
_Unwind_Reason_Code unwind_backtrace_callback(struct _Unwind_Context* context, void* arg) {

    void* pc = (void*)_Unwind_GetIP(context);
    StackBase *s = (StackBase*)arg;
    if (pc) {
        if (s->isEnd()){
            return _URC_END_OF_STACK;
        }
        s->save(pc);
    }

    return _URC_NO_REASON;
}

int get_stack(StackBase *s){
    _Unwind_Reason_Code rc = _Unwind_Backtrace(unwind_backtrace_callback, s);
    return rc == _URC_END_OF_STACK ? 0 : -1;
}

_Unwind_Reason_Code unwind_backtrace_callback_1(struct _Unwind_Context* context, void* arg)
{
    // _Unwind_Reason_Code ret = _URC_NO_REASON;
    StackWrap *sw = (StackWrap*)arg;

    void* pc = (void*)_Unwind_GetIP(context);
    if (pc) {
        if (sw->offset > 0){
            sw->offset--;
            return _URC_NO_REASON;
        }
        if (sw->cur >= sw->max){
            return _URC_END_OF_STACK;
        }

        sw->stack_trace[sw->cur] = pc;
        sw->cur++;
        // if (sw->cur < sw->max){
        //     sw->stack_trace[sw->cur] = pc;
        //     sw->cur++;
        // }else{
        //     ret = _URC_END_OF_STACK;
        // }
    }

    return _URC_NO_REASON;
}

int get_stack(StackWrap *s){
    _Unwind_Reason_Code rc = _Unwind_Backtrace(unwind_backtrace_callback_1, s);
    if (s->cur < s->max)
        s->stack_trace[s->cur] = nullptr;
    return rc == _URC_END_OF_STACK ? 0 : -1;
}