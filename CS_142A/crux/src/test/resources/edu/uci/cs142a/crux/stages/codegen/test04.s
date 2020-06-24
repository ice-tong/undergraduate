    .comm addi, 8, 8
    .globl main
main:
    enter $(8 * 4), $0
    /* $t0 = call %readInt () */
    call readInt
    movq %rax, -8(%rbp)
    /* %t0 = addressAt %addi, null */
    movq addi@GOTPCREL(%rip) , %r11
    movq %r11, -16(%rbp)
    /* store $t0, %t0 */
    movq -8(%rbp), %r10
    movq -16(%rbp), %r11
    movq %r10, 0(%r11)
    /* %t1 = addressAt %addi, null */
    movq addi@GOTPCREL(%rip) , %r11
    movq %r11, -24(%rbp)
    /* $t1 = load %t1 */
    movq -24(%rbp), %r10
    movq 0(%r10), %r10
    movq %r10, -32(%rbp)
    /* call %printInt ($t1) */
    movq -32(%rbp), %rdi
    call printInt
    leave
    ret
