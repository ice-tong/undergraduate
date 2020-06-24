    .globl main
main:
    enter $(8 * 2), $0
    /* $t0 = 42 */
    movq $42, %r10
    movq %r10, -8(%rbp)
    /* call %printInt ($t0) */
    movq -8(%rbp), %rdi
    call printInt
    leave
    ret
