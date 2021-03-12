	.file	"retlib.c"
	.section	.rodata
.LC0:
	.string	"MYSHELL"
.LC1:
	.string	"Address of buffer[]: 0x%.8x\n"
.LC2:
	.string	"Frame Pointer value: 0x%.8x\n"
	.align 4
.LC3:
	.string	"The '%s' string address is %p.\n"
	.align 4
.LC4:
	.string	"The offset between ebp start and buffer start is: %d\n"
	.text
	.globl	bof
	.type	bof, @function
bof:
.LFB2:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$56, %esp
	movl	8(%ebp), %eax
	movl	%eax, -44(%ebp)
	movl	%gs:20, %eax
	movl	%eax, -12(%ebp)
	xorl	%eax, %eax
	subl	$12, %esp
	pushl	$.LC0
	call	getenv
	addl	$16, %esp
	movl	%eax, -32(%ebp)
#APP
# 46 "retlib.c" 1
	movl %ebp, %eax
# 0 "" 2
#NO_APP
	movl	%eax, -28(%ebp)
	leal	-24(%ebp), %eax
	subl	$8, %esp
	pushl	%eax
	pushl	$.LC1
	call	printf
	addl	$16, %esp
	movl	-28(%ebp), %eax
	subl	$8, %esp
	pushl	%eax
	pushl	$.LC2
	call	printf
	addl	$16, %esp
	cmpl	$0, -32(%ebp)
	je	.L2
	subl	$4, %esp
	pushl	-32(%ebp)
	pushl	-32(%ebp)
	pushl	$.LC3
	call	printf
	addl	$16, %esp
.L2:
	movl	-28(%ebp), %edx
	leal	-24(%ebp), %eax
	subl	%eax, %edx
	movl	%edx, %eax
	subl	$8, %esp
	pushl	%eax
	pushl	$.LC4
	call	printf
	addl	$16, %esp
	pushl	-44(%ebp)
	pushl	$300
	pushl	$1
	leal	-24(%ebp), %eax
	pushl	%eax
	call	fread
	addl	$16, %esp
	movl	$1, %eax
	movl	-12(%ebp), %ecx
	xorl	%gs:20, %ecx
	je	.L4
	call	__stack_chk_fail
.L4:
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE2:
	.size	bof, .-bof
	.section	.rodata
.LC5:
	.string	"r"
.LC6:
	.string	"badfile"
.LC7:
	.string	"Returned Properly"
	.text
	.globl	main
	.type	main, @function
main:
.LFB3:
	.cfi_startproc
	leal	4(%esp), %ecx
	.cfi_def_cfa 1, 0
	andl	$-16, %esp
	pushl	-4(%ecx)
	pushl	%ebp
	.cfi_escape 0x10,0x5,0x2,0x75,0
	movl	%esp, %ebp
	pushl	%ecx
	.cfi_escape 0xf,0x3,0x75,0x7c,0x6
	subl	$100, %esp
	movl	%ecx, %eax
	movl	4(%eax), %eax
	movl	%eax, -92(%ebp)
	movl	%gs:20, %eax
	movl	%eax, -12(%ebp)
	xorl	%eax, %eax
	subl	$4, %esp
	pushl	$60
	pushl	$0
	leal	-72(%ebp), %eax
	pushl	%eax
	call	memset
	addl	$16, %esp
	subl	$8, %esp
	pushl	$.LC5
	pushl	$.LC6
	call	fopen
	addl	$16, %esp
	movl	%eax, -76(%ebp)
	subl	$12, %esp
	pushl	-76(%ebp)
	call	bof
	addl	$16, %esp
	subl	$12, %esp
	pushl	$.LC7
	call	puts
	addl	$16, %esp
	subl	$12, %esp
	pushl	-76(%ebp)
	call	fclose
	addl	$16, %esp
	movl	$1, %eax
	movl	-12(%ebp), %edx
	xorl	%gs:20, %edx
	je	.L7
	call	__stack_chk_fail
.L7:
	movl	-4(%ebp), %ecx
	.cfi_def_cfa 1, 0
	leave
	.cfi_restore 5
	leal	-4(%ecx), %esp
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE3:
	.size	main, .-main
	.ident	"GCC: (Ubuntu 5.4.0-6ubuntu1~16.04.4) 5.4.0 20160609"
	.section	.note.GNU-stack,"",@progbits
