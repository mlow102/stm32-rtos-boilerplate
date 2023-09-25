#ifndef DEBUGGER_BREAKPOINT_H_
#define DEBUGGER_BREAKPOINT_H_
void DEBUGGER_BREAKPOINT() { __asm__ __volatile__("bkpt #0"); }
#endif