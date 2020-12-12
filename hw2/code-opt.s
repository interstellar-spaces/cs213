	.file	"code.c"
	.text
.globl intarith
	.type	intarith, @function
intarith:
.LFB0:
	.cfi_startproc
	subl	%esi, %edi /* x = edi, y = esi, x-y */
	movl	%esi, %eax
	sall	$4, %eax
	leal	(%rax,%rsi), %esi
	leal	(%rsi,%rdi,4), %eax
	ret
	.cfi_endproc
.LFE0:
	.size	intarith, .-intarith
.globl longarith
	.type	longarith, @function
longarith:
.LFB1:
	.cfi_startproc
	movq	%rdi, %rdx
	movq	%rdi, %rax
	sarq	$63, %rdx
	idivq	%rsi
	movq	%rax, %rcx
	movabsq	$3279421168659475843, %rdx
	movq	%rsi, %rax
	imulq	%rdx
	sarq	$3, %rdx
	sarq	$63, %rsi
	subq	%rsi, %rdx
	leaq	(%rcx,%rdx), %rax
	ret
	.cfi_endproc
.LFE1:
	.size	longarith, .-longarith
.globl simpleif
	.type	simpleif, @function
simpleif:
.LFB2:
	.cfi_startproc
	imull	$103, %esi, %esi
	cmpl	%edi, %esi
	sete	%al
	movzbl	%al, %eax
	ret
	.cfi_endproc
.LFE2:
	.size	simpleif, .-simpleif
.globl callee
	.type	callee, @function
callee:
.LFB3:
	.cfi_startproc
	leal	0(,%rdi,4), %eax
	andl	%edi, %eax
	imull	%edi, %edi
	addl	%edi, %eax
	ret
	.cfi_endproc
.LFE3:
	.size	callee, .-callee
.globl caller
	.type	caller, @function
caller:
.LFB4:
	.cfi_startproc
	sarl	$3, %edi
	call	callee
	rep; ret
	.cfi_endproc
.LFE4:
	.size	caller, .-caller
.globl forcode
	.type	forcode, @function
forcode:
.LFB5:
	.cfi_startproc
	movl	$0, %eax
	testl	%edx, %edx
	jle	.L13
	subl	$1, %edx
	leaq	4(,%rdx,4), %r10
	movl	$0, %edx
.L14:
	imull	$29, (%rsi,%rdx), %r8d
	movl	(%rdi,%rdx), %ecx
	leal	(%rcx,%rcx,8), %r9d
	leal	(%rcx,%r9,2), %ecx
	leal	(%r8,%rcx), %ecx
	addl	%ecx, %eax
	addq	$4, %rdx
	cmpq	%r10, %rdx
	jne	.L14
.L13:
	rep; ret
	.cfi_endproc
.LFE5:
	.size	forcode, .-forcode
.globl doublearith
	.type	doublearith, @function
doublearith:
.LFB6:
	.cfi_startproc
	cmpl	$1, %esi
	jg	.L18
	xorpd	%xmm0, %xmm0
	ret
.L18:
	subl	$2, %esi
	leaq	8(,%rsi,8), %rdx
	movl	$0, %eax
	xorpd	%xmm0, %xmm0
.L20:
	movsd	(%rdi,%rax), %xmm1
	mulsd	8(%rdi,%rax), %xmm1
	addsd	%xmm1, %xmm0
	addq	$8, %rax
	cmpq	%rdx, %rax
	jne	.L20
	rep; ret
	.cfi_endproc
.LFE6:
	.size	doublearith, .-doublearith
.globl ptrif
	.type	ptrif, @function
ptrif:
.LFB7:
	.cfi_startproc
	movl	(%rdi), %eax
	cmpl	(%rsi), %eax
	setne	%al
	movzbl	%al, %eax
	ret
	.cfi_endproc
.LFE7:
	.size	ptrif, .-ptrif
.globl whilecode
	.type	whilecode, @function
whilecode:
.LFB8:
	.cfi_startproc
	testq	%rdi, %rdi
	je	.L26
	movslq	%esi, %rsi
	cmpq	%rsi, 8(%rdi)
	jge	.L26
.L29:
	movq	24(%rdi), %rdi
	testq	%rdi, %rdi
	je	.L26
	cmpq	%rsi, 8(%rdi)
	jl	.L29
.L26:
	testq	%rdi, %rdi
	setne	%al
	movzbl	%al, %eax
	ret
	.cfi_endproc
.LFE8:
	.size	whilecode, .-whilecode
.globl switchcode
	.type	switchcode, @function
switchcode:
.LFB9:
	.cfi_startproc
	movl	(%rdi), %eax
	cmpl	(%rsi), %eax
	jne	.L32
	cmpl	$1, %eax
	je	.L34
	cmpl	$1, %eax
	jb	.L33
	cmpl	$2, %eax
	.p2align 4,,2
	jne	.L32
	.p2align 4,,5
	jmp	.L38
.L33:
	movq	16(%rdi), %rdx
	movq	16(%rsi), %rax
	movzbl	(%rdx), %edx
	cmpb	(%rax), %dl
	setle	%al
	movzbl	%al, %eax
	ret
.L34:
	movq	16(%rdi), %rdx
	movq	16(%rsi), %rax
	movzwl	(%rdx), %edx
	cmpw	(%rax), %dx
	sete	%al
	movzbl	%al, %eax
	ret
.L38:
	movq	16(%rdi), %rdx
	movq	16(%rsi), %rax
	movl	(%rdx), %edx
	cmpl	(%rax), %edx
	setge	%al
	movzbl	%al, %eax
	ret
.L32:
	movl	$0, %eax
	ret
	.cfi_endproc
.LFE9:
	.size	switchcode, .-switchcode
.globl simplerecursive
	.type	simplerecursive, @function
simplerecursive:
.LFB10:
	.cfi_startproc
	subq	$8, %rsp
	.cfi_def_cfa_offset 16
	movl	$0, %eax
	testq	%rdi, %rdi
	je	.L41
	movq	8(%rdi), %rcx
	movslq	%esi, %rdx
	movb	$1, %al
	cmpq	%rdx, %rcx
	je	.L41
	cmpq	%rdx, %rcx
	jle	.L43
	movq	24(%rdi), %rdi
	call	simplerecursive
	jmp	.L41
.L43:
	movq	32(%rdi), %rdi
	call	simplerecursive
.L41:
	addq	$8, %rsp
	.cfi_def_cfa_offset 8
	ret
	.cfi_endproc
.LFE10:
	.size	simplerecursive, .-simplerecursive
.globl complexrecursive
	.type	complexrecursive, @function
complexrecursive:
.LFB11:
	.cfi_startproc
	movq	%rbx, -16(%rsp)
	movq	%rbp, -8(%rsp)
	subq	$24, %rsp
	.cfi_def_cfa_offset 32
	.cfi_offset 6, -16
	.cfi_offset 3, -24
	movq	%rdi, %rbx
	movl	$0, %eax
	testq	%rdi, %rdi
	je	.L47
	movq	24(%rdi), %rdi
	call	complexrecursive
	movl	%eax, %ebp
	movq	32(%rbx), %rdi
	call	complexrecursive
	leal	0(%rbp,%rax), %eax
	addl	8(%rbx), %eax
.L47:
	movq	8(%rsp), %rbx
	movq	16(%rsp), %rbp
	addq	$24, %rsp
	.cfi_def_cfa_offset 8
	ret
	.cfi_endproc
.LFE11:
	.size	complexrecursive, .-complexrecursive
	.ident	"GCC: (GNU) 4.4.7 20120313 (Red Hat 4.4.7-23)"
	.section	.note.GNU-stack,"",@progbits
