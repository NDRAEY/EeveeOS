#include "../libstdio/stdio.h"
#include "pic.h"

/*
 * PIC is very complex, for a better understanding, visist
 * http://www.brokenthorn.com/Resources/OSDevPic.html or some other materials that explain PIC, otherwise the following code is impossible to uderstand....
 * */
void pic_init() {
    // ICW1
    kern_outb(PIC1_COMMAND, ICW1);
    kern_outb(PIC2_COMMAND, ICW1);

    // ICW2, irq 0 to 7 is mapped to 0x20 to 0x27, irq 8 to F is mapped to 28 to 2F
    kern_outb(PIC1_DATA, 0x20);
    kern_outb(PIC2_DATA, 0x28);

    // ICW3, connect master pic with slave pic
    kern_outb(PIC1_DATA, 0x4);
    kern_outb(PIC2_DATA, 0x2);

    // ICW4, set x86 mode
    kern_outb(PIC1_DATA, 1);
    kern_outb(PIC2_DATA, 1);

    // clear the mask register
    kern_outb(PIC1_DATA, 0);
    kern_outb(PIC2_DATA, 0);
}

/*
 * Tell PIC interrupt is handled
 * */
void irq_ack(uint8_t irq) {
    if(irq >= 0x28)
        kern_outb(PIC2, PIC_EOI);
    kern_outb(PIC1, PIC_EOI);
}
