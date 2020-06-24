    .globl myPrintZero
myPrintZero:
    enter $(8 * 2), $0
    /* $t0 = 0 */
    movq $0, %r10
    movq %r10, -8(%rbp)
    /* call %printInt ($t0) */
    movq -8(%rbp), %rdi
    call printInt
    leave
    ret
    .globl myPrintOne
myPrintOne:
    enter $(8 * 2), $0
    movq %rdi, -8(%rbp)
    /* $t0 = $a */
    movq -8(%rbp), %r10
    movq %r10, -16(%rbp)
    /* call %printInt ($t0) */
    movq -16(%rbp), %rdi
    call printInt
    leave
    ret
    .globl myPrintTwo
myPrintTwo:
    enter $(8 * 4), $0
    movq %rdi, -8(%rbp)
    movq %rsi, -16(%rbp)
    /* $t0 = $a */
    movq -8(%rbp), %r10
    movq %r10, -24(%rbp)
    /* call %printInt ($t0) */
    movq -24(%rbp), %rdi
    call printInt
    /* $t1 = $b */
    movq -16(%rbp), %r10
    movq %r10, -32(%rbp)
    /* call %printInt ($t1) */
    movq -32(%rbp), %rdi
    call printInt
    leave
    ret
    .globl myPrintThree
myPrintThree:
    enter $(8 * 6), $0
    movq %rdi, -8(%rbp)
    movq %rsi, -16(%rbp)
    movq %rdx, -24(%rbp)
    /* $t0 = $a */
    movq -8(%rbp), %r10
    movq %r10, -32(%rbp)
    /* call %printInt ($t0) */
    movq -32(%rbp), %rdi
    call printInt
    /* $t1 = $b */
    movq -16(%rbp), %r10
    movq %r10, -40(%rbp)
    /* call %printInt ($t1) */
    movq -40(%rbp), %rdi
    call printInt
    /* $t2 = $c */
    movq -24(%rbp), %r10
    movq %r10, -48(%rbp)
    /* call %printInt ($t2) */
    movq -48(%rbp), %rdi
    call printInt
    leave
    ret
    .globl main
main:
    enter $(8 * 6), $0
    /* call %myPrintZero () */
    call myPrintZero
    /* call %println () */
    call println
    /* $t0 = 1 */
    movq $1, %r10
    movq %r10, -8(%rbp)
    /* call %myPrintOne ($t0) */
    movq -8(%rbp), %rdi
    call myPrintOne
    /* call %println () */
    call println
    /* $t1 = 1 */
    movq $1, %r10
    movq %r10, -16(%rbp)
    /* $t2 = 2 */
    movq $2, %r10
    movq %r10, -24(%rbp)
    /* call %myPrintTwo ($t1$t2) */
    movq -16(%rbp), %rdi
    movq -24(%rbp), %rsi
    call myPrintTwo
    /* call %println () */
    call println
    /* $t3 = 1 */
    movq $1, %r10
    movq %r10, -32(%rbp)
    /* $t4 = 2 */
    movq $2, %r10
    movq %r10, -40(%rbp)
    /* $t5 = 3 */
    movq $3, %r10
    movq %r10, -48(%rbp)
    /* call %myPrintThree ($t3$t4$t5) */
    movq -32(%rbp), %rdi
    movq -40(%rbp), %rsi
    movq -48(%rbp), %rdx
    call myPrintThree
    /* call %println () */
    call println
    leave
    ret
