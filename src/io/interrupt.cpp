#include "interrupt.h"

void set_idt() {
    idt_register.base = (uint32_t) &idt;
    idt_register.size = NUM_IDT_ENTRIES * sizeof(idt_gate_t) - 1;
    /* Don't make the mistake of loading &idt -- always load &idt_reg */
    __asm__ __volatile__("lidtl (%0)" : : "r" (&idt_register));
}

void set_idt_gate(int interrupt_num, uint32_t handler) {
    uint16_t offset_high = (handler & 0xffff0000) >> 16;
    uint16_t offset_low = (handler & 0xffff);
    idt[interrupt_num].offset_high = offset_high;
    idt[interrupt_num].offset_low = offset_low;
    idt[interrupt_num].segment_selector = KERNEL_CS;
    idt[interrupt_num].always_zero = 0;
    idt[interrupt_num].flags = 0x8E;
}
