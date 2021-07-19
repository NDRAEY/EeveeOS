__asm__(".code16\n");
__asm__("jmpl $0x0000, $main\n");

void kern_putc(const int c) {
	__asm__ __volatile__("int $0x10"::"a"(0x0e00|c),"b"(0x0007));
	//										^ ^			  ^ ^
	//										|  \		  |  \
	//										al ah         bl bh
}

void kern_printc(const char *c) {
	while(*c) {
		__asm__ __volatile__("int $0x10"::"a"(0x0e00|*c),"b"(0x0007));
	++c;
	}
}


void main() {
	kern_printc("Hello! Welcome!");
	while(1){
		/*
			Doing nothing, because if I call kern_putc('A'),
			Output will be: A AA[smile]AAAAAAAAA
		*/
	}
}
