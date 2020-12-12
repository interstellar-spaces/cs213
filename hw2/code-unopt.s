	.file	"code.c"
	.text
.globl intarith
	.type	intarith, @function
intarith:
.LFB0:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%rbx
	movl	%edi, -12(%rbp)
	movl	%esi, -16(%rbp)
	movl	-16(%rbp), %edx
	movl	%edx, %eax
	sall	$4, %eax
	leal	(%rax,%rdx), %ecx
	movl	-16(%rbp), %eax
	movl	-12(%rbp), %edx
	movl	%edx, %ebx
	.cfi_offset 3, -24
	subl	%eax, %ebx
	movl	%ebx, %eax
	sall	$2, %eax
	leal	(%rcx,%rax), %eax
	popq	%rbx
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	intarith, .-intarith
.globl longarith
	.type	longarith, @function
longarith:
.LFB1:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	movq	-16(%rbp), %rcx
	movabsq	$3279421168659475843, %rdx
	movq	%rcx, %rax
	imulq	%rdx
	sarq	$3, %rdx
	movq	%rcx, %rax
	sarq	$63, %rax
	movq	%rdx, %rcx
	subq	%rax, %rcx
	movq	-8(%rbp), %rax
	movq	%rax, %rdx
	sarq	$63, %rdx
	idivq	-16(%rbp)
	leaq	(%rcx,%rax), %rax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE1:
	.size	longarith, .-longarith
.globl simpleif
	.type	simpleif, @function
simpleif:
.LFB2:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movl	%edi, -4(%rbp)
	movl	%esi, -8(%rbp)
	movl	-8(%rbp), %eax
	imull	$103, %eax, %eax
	cmpl	-4(%rbp), %eax
	jne	.L6
	movl	$1, %eax
	jmp	.L7
.L6:
	movl	$0, %eax
.L7:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2:
	.size	simpleif, .-simpleif
.globl callee
	.type	callee, @function
callee:
.LFB3:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movl	%edi, -4(%rbp)
	movl	-4(%rbp), %eax
	sall	$2, %eax
	movl	%eax, %edx
	andl	-4(%rbp), %edx
	movl	-4(%rbp), %eax
	imull	-4(%rbp), %eax
	leal	(%rdx,%rax), %eax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE3:
	.size	callee, .-callee
.globl caller
	.type	caller, @function
caller:
.LFB4:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$8, %rsp
	movl	%edi, -4(%rbp)
	movl	-4(%rbp), %eax
	sarl	$3, %eax
	movl	%eax, %edi
	call	callee
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE4:
	.size	caller, .-caller
.globl forcode
	.type	forcode, @function
forcode:
.LFB5:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdi, -24(%rbp)
	movq	%rsi, -32(%rbp)
	movl	%edx, -36(%rbp)
	movl	$0, -4(%rbp)
	movl	$0, -8(%rbp)
	jmp	.L14
.L15:
	movl	-8(%rbp), %eax
	cltq
	salq	$2, %rax
	addq	-24(%rbp), %rax
	movl	(%rax), %edx
	movl	%edx, %eax
	sall	$3, %eax
	addl	%edx, %eax
	addl	%eax, %eax
	leal	(%rax,%rdx), %edx
	movl	-8(%rbp), %eax
	cltq
	salq	$2, %rax
	addq	-32(%rbp), %rax
	movl	(%rax), %eax
	imull	$29, %eax, %eax
	leal	(%rdx,%rax), %eax
	addl	%eax, -4(%rbp)
	addl	$1, -8(%rbp)
.L14:
	movl	-8(%rbp), %eax
	cmpl	-36(%rbp), %eax
	jl	.L15
	movl	-4(%rbp), %eax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE5:
	.size	forcode, .-forcode
.globl doublearith
	.type	doublearith, @function
doublearith:
.LFB6:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdi, -24(%rbp)
	movl	%esi, -28(%rbp)
	movl	$0, %eax
	movq	%rax, -8(%rbp)
	movl	$1, -12(%rbp)
	jmp	.L18
.L19:
	movl	-12(%rbp), %eax
	cltq
	subq	$1, %rax
	salq	$3, %rax
	addq	-24(%rbp), %rax
	movsd	(%rax), %xmm1
	movl	-12(%rbp), %eax
	cltq
	salq	$3, %rax
	addq	-24(%rbp), %rax
	movsd	(%rax), %xmm0
	mulsd	%xmm1, %xmm0
	movsd	-8(%rbp), %xmm1
	addsd	%xmm1, %xmm0
	movsd	%xmm0, -8(%rbp)
	addl	$1, -12(%rbp)
.L18:
	movl	-12(%rbp), %eax
	cmpl	-28(%rbp), %eax
	jl	.L19
	movq	-8(%rbp), %rax
	movq	%rax, -40(%rbp)
	movsd	-40(%rbp), %xmm0
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE6:
	.size	doublearith, .-doublearith
.globl ptrif
	.type	ptrif, @function
ptrif:
.LFB7:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	movq	-8(%rbp), %rax
	movl	(%rax), %edx
	movq	-16(%rbp), %rax
	movl	(%rax), %eax
	cmpl	%eax, %edx
	je	.L22
	movl	$1, %eax
	jmp	.L23
.L22:
	movl	$0, %eax
.L23:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE7:
	.size	ptrif, .-ptrif
.globl whilecode
	.type	whilecode, @function
whilecode:
.LFB8:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdi, -8(%rbp)
	movl	%esi, -12(%rbp)
	jmp	.L26
.L28:
	movq	-8(%rbp), %rax
	movq	24(%rax), %rax
	movq	%rax, -8(%rbp)
.L26:
	cmpq	$0, -8(%rbp)
	je	.L27
	movq	-8(%rbp), %rax
	movq	8(%rax), %rdx
	movl	-12(%rbp), %eax
	cltq
	cmpq	%rax, %rdx
	jl	.L28
.L27:
	cmpq	$0, -8(%rbp)
	setne	%al
	movzbl	%al, %eax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE8:
	.size	whilecode, .-whilecode
.globl switchcode
	.type	switchcode, @function
switchcode:
.LFB9:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	movq	-8(%rbp), %rax
	movl	(%rax), %edx
	movq	-16(%rbp), %rax
	movl	(%rax), %eax
	cmpl	%eax, %edx
	je	.L31
	movl	$0, %eax
	jmp	.L32
.L31:
	movq	-8(%rbp), %rax
	movl	(%rax), %eax
	cmpl	$1, %eax
	je	.L35
	cmpl	$1, %eax
	jb	.L34
	cmpl	$2, %eax
	je	.L36
	jmp	.L38
.L34:
	movq	-8(%rbp), %rax
	movq	16(%rax), %rax
	movzbl	(%rax), %edx
	movq	-16(%rbp), %rax
	movq	16(%rax), %rax
	movzbl	(%rax), %eax
	cmpb	%al, %dl
	setle	%al
	movzbl	%al, %eax
	jmp	.L32
.L35:
	movq	-8(%rbp), %rax
	movq	16(%rax), %rax
	movzwl	(%rax), %edx
	movq	-16(%rbp), %rax
	movq	16(%rax), %rax
	movzwl	(%rax), %eax
	cmpw	%ax, %dx
	sete	%al
	movzbl	%al, %eax
	jmp	.L32
.L36:
	movq	-8(%rbp), %rax
	movq	16(%rax), %rax
	movl	(%rax), %edx
	movq	-16(%rbp), %rax
	movq	16(%rax), %rax
	movl	(%rax), %eax
	cmpl	%eax, %edx
	setge	%al
	movzbl	%al, %eax
	jmp	.L32
.L38:
	movl	$0, %eax
.L32:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE9:
	.size	switchcode, .-switchcode
.globl simplerecursive
	.type	simplerecursive, @function
simplerecursive:
.LFB10:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movl	%esi, -12(%rbp)
	cmpq	$0, -8(%rbp)
	jne	.L40
	movl	$0, %eax
	jmp	.L41
.L40:
	movq	-8(%rbp), %rax
	movq	8(%rax), %rdx
	movl	-12(%rbp), %eax
	cltq
	cmpq	%rax, %rdx
	jne	.L42
	movl	$1, %eax
	jmp	.L41
.L42:
	movq	-8(%rbp), %rax
	movq	8(%rax), %rdx
	movl	-12(%rbp), %eax
	cltq
	cmpq	%rax, %rdx
	jle	.L43
	movq	-8(%rbp), %rax
	movq	24(%rax), %rax
	movl	-12(%rbp), %edx
	movl	%edx, %esi
	movq	%rax, %rdi
	call	simplerecursive
	jmp	.L41
.L43:
	movq	-8(%rbp), %rax
	movq	32(%rax), %rax
	movl	-12(%rbp), %edx
	movl	%edx, %esi
	movq	%rax, %rdi
	call	simplerecursive
.L41:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE10:
	.size	simplerecursive, .-simplerecursive
.globl complexrecursive
	.type	complexrecursive, @function
complexrecursive:
.LFB11:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%rbx
	subq	$24, %rsp
	movq	%rdi, -24(%rbp)
	cmpq	$0, -24(%rbp)
	jne	.L46
	.cfi_offset 3, -24
	movl	$0, %eax
	jmp	.L47
.L46:
	movq	-24(%rbp), %rax
	movq	8(%rax), %rax
	movl	%eax, %ebx
	movq	-24(%rbp), %rax
	movq	24(%rax), %rax
	movq	%rax, %rdi
	call	complexrecursive
	addl	%eax, %ebx
	movq	-24(%rbp), %rax
	movq	32(%rax), %rax
	movq	%rax, %rdi
	call	complexrecursive
	leal	(%rbx,%rax), %eax
.L47:
	addq	$24, %rsp
	popq	%rbx
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE11:
	.size	complexrecursive, .-complexrecursive
	.ident	"GCC: (GNU) 4.4.7 20120313 (Red Hat 4.4.7-23)"
	.section	.note.GNU-stack,"",@progbits
