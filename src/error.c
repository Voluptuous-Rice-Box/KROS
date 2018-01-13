#include "io/terminal.h"
#include "error.h"

extern void halt_os();

void kernel_panic(const char *msg) {
    terminal_write(msg);
    halt_os();
}
