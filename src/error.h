#ifndef _ERROR_H
#define _ERROR_H

// This method should be called when a fatal error
// has occurred and the kernel cannot continue. An
// error is printed to the user, and the system is halted.
void kernel_panic(const char *msg);

#endif
