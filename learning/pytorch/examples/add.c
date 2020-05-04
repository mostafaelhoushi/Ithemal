/**
content of iacaMarks.h
**/

#if defined (__GNUC__) 
#define IACA_SSC_MARK( MARK_ID )						\
__asm__ __volatile__ (									\
					  "\n\t  movl $"#MARK_ID", %%ebx"	\
					  "\n\t  .byte 0x64, 0x67, 0x90"	\
					  : : : "memory" );

#else
#define IACA_SSC_MARK(x) {__asm  mov ebx, x\
	__asm  _emit 0x64 \
	__asm  _emit 0x67 \
	__asm  _emit 0x90 }
#endif

#define IACA_START {IACA_SSC_MARK(111)}
#define IACA_END {IACA_SSC_MARK(222)}

#ifdef _WIN64
#include <intrin.h>
#define IACA_VC64_START __writegsbyte(111, 111);
#define IACA_VC64_END   __writegsbyte(222, 222);
#endif


/**
Content of add.c
**/

int main() {
	int x = 3;
	int y = 3*x + 255;
	if (y > 4) {
                IACA_START
		x++;
		x = x + 22*y;
                IACA_END
	}
	else {
		y++;
		y = y + 22*x;
	}
	return y;
}
