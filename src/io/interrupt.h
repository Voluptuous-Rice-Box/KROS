#ifndef _INTERRUPT_H
#define _INTERRUPT_H

#include <stdint.h>

#define KERNEL_CS 0x08

typedef struct {
    uint16_t offset_low;
    uint16_t segment_selector;
    uint8_t always_zero;
    /*
     * Bit 7: "Interrupt is present"
     * Bits 6-5: Privilege level of caller (0=kernel..3=user)
     * Bit 4: Set to 0 for interrupt gates
     * Bits 3-0: 0b1110 = 14d = "32 bit interrupt gate"
     */
    uint8_t flags;
    uint16_t offset_high;
} __attribute((packed)) idt_gate_t;

#define NUM_IDT_ENTRIES 16
extern idt_gate_t idt[NUM_IDT_ENTRIES];

/* A pointer to the array of interrupt handlers.
 * Assembly instruction 'lidt' will read it */
typedef struct {
    uint16_t size;
    uint32_t base;
} __attribute__((packed)) idt_register_t;

void set_idt_gate(int interrupt_num, uint32_t handler);
void set_idt();

// Define list of interrupt handlers
extern "C" void interrupt_handler_0();
extern "C" void interrupt_handler_1();
extern "C" void interrupt_handler_2();
extern "C" void interrupt_handler_3();
extern "C" void interrupt_handler_4();
extern "C" void interrupt_handler_5();
extern "C" void interrupt_handler_6();
extern "C" void interrupt_handler_7();
extern "C" void interrupt_handler_8();
extern "C" void interrupt_handler_9();
extern "C" void interrupt_handler_10();
extern "C" void interrupt_handler_11();
extern "C" void interrupt_handler_12();
extern "C" void interrupt_handler_13();
extern "C" void interrupt_handler_14();
extern "C" void interrupt_handler_15();

#endif
