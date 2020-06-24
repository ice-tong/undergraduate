    .globl main
main:
    enter $(8 * 2), $0
    /* $t0 = true */
    movq $1, %r10
    movq %r10, -8(%rbp)
    /* call %printBool ($t0) */
    movq -8(%rbp), %rdi
    call printBool
    /* $t1 = false */
    movq $0, %r10
    movq %r10, -16(%rbp)
    /* call %printBool ($t1) */
    movq -16(%rbp), %rdi
    call printBool
    leave
    ret
