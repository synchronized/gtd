	.file	"func.cpp"
	.section .rdata,"dr"
LC0:
	.ascii "2.%d\12\0"
	.text
	.globl	__Z1ff
	.def	__Z1ff;	.scl	2;	.type	32;	.endef
__Z1ff:
LFB7:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$24, %esp
	flds	8(%ebp)
	fstpl	4(%esp)
	movl	$LC0, (%esp)
	call	_printf
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
LFE7:
	.ident	"GCC: (GNU) 4.8.2"
	.def	_printf;	.scl	2;	.type	32;	.endef
