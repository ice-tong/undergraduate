    .comm canary_begin, 8, 8
    .comm x, 24, 8
    .comm canary_end, 8, 8
    .globl main
main:
    enter $(8 * 38), $0
    /* $t0 = 0 */
    movq $0, %r10
    movq %r10, -8(%rbp)
    /* %t0 = addressAt %canary_begin, null */
    movq canary_begin@GOTPCREL(%rip) , %r11
    movq %r11, -16(%rbp)
    /* store $t0, %t0 */
    movq -8(%rbp), %r10
    movq -16(%rbp), %r11
    movq %r10, 0(%r11)
    /* $t1 = 0 */
    movq $0, %r10
    movq %r10, -24(%rbp)
    /* %t1 = addressAt %canary_end, null */
    movq canary_end@GOTPCREL(%rip) , %r11
    movq %r11, -32(%rbp)
    /* store $t1, %t1 */
    movq -24(%rbp), %r10
    movq -32(%rbp), %r11
    movq %r10, 0(%r11)
    /* $t2 = 0 */
    movq $0, %r10
    movq %r10, -40(%rbp)
    /* $t3 = 1 */
    movq $1, %r10
    movq %r10, -48(%rbp)
    /* $t4 = $t2 * $t3 */
    movq -40(%rbp), %r10
    imulq -48(%rbp), %r10
    movq %r10, -56(%rbp)
    /* %t2 = addressAt %x, $t4 */
    movq -56(%rbp), %r11
    movq $8, %r10
    imul %r10, %r11
    movq x@GOTPCREL(%rip) , %r10
    addq %r10, %r11
    movq %r11, -64(%rbp)
    /* $t5 = 222 */
    movq $222, %r10
    movq %r10, -72(%rbp)
    /* store $t5, %t2 */
    movq -72(%rbp), %r10
    movq -64(%rbp), %r11
    movq %r10, 0(%r11)
    /* $t6 = 1 */
    movq $1, %r10
    movq %r10, -80(%rbp)
    /* $t7 = 1 */
    movq $1, %r10
    movq %r10, -88(%rbp)
    /* $t8 = $t6 * $t7 */
    movq -80(%rbp), %r10
    imulq -88(%rbp), %r10
    movq %r10, -96(%rbp)
    /* %t3 = addressAt %x, $t8 */
    movq -96(%rbp), %r11
    movq $8, %r10
    imul %r10, %r11
    movq x@GOTPCREL(%rip) , %r10
    addq %r10, %r11
    movq %r11, -104(%rbp)
    /* $t9 = 333 */
    movq $333, %r10
    movq %r10, -112(%rbp)
    /* store $t9, %t3 */
    movq -112(%rbp), %r10
    movq -104(%rbp), %r11
    movq %r10, 0(%r11)
    /* $t10 = 2 */
    movq $2, %r10
    movq %r10, -120(%rbp)
    /* $t11 = 1 */
    movq $1, %r10
    movq %r10, -128(%rbp)
    /* $t12 = $t10 * $t11 */
    movq -120(%rbp), %r10
    imulq -128(%rbp), %r10
    movq %r10, -136(%rbp)
    /* %t4 = addressAt %x, $t12 */
    movq -136(%rbp), %r11
    movq $8, %r10
    imul %r10, %r11
    movq x@GOTPCREL(%rip) , %r10
    addq %r10, %r11
    movq %r11, -144(%rbp)
    /* $t13 = 444 */
    movq $444, %r10
    movq %r10, -152(%rbp)
    /* store $t13, %t4 */
    movq -152(%rbp), %r10
    movq -144(%rbp), %r11
    movq %r10, 0(%r11)
    /* %t5 = addressAt %canary_begin, null */
    movq canary_begin@GOTPCREL(%rip) , %r11
    movq %r11, -160(%rbp)
    /* $t14 = load %t5 */
    movq -160(%rbp), %r10
    movq 0(%r10), %r10
    movq %r10, -168(%rbp)
    /* call %printInt ($t14) */
    movq -168(%rbp), %rdi
    call printInt
    /* $t15 = 0 */
    movq $0, %r10
    movq %r10, -176(%rbp)
    /* $t16 = 1 */
    movq $1, %r10
    movq %r10, -184(%rbp)
    /* $t17 = $t15 * $t16 */
    movq -176(%rbp), %r10
    imulq -184(%rbp), %r10
    movq %r10, -192(%rbp)
    /* %t6 = addressAt %x, $t17 */
    movq -192(%rbp), %r11
    movq $8, %r10
    imul %r10, %r11
    movq x@GOTPCREL(%rip) , %r10
    addq %r10, %r11
    movq %r11, -200(%rbp)
    /* $t18 = load %t6 */
    movq -200(%rbp), %r10
    movq 0(%r10), %r10
    movq %r10, -208(%rbp)
    /* call %printInt ($t18) */
    movq -208(%rbp), %rdi
    call printInt
    /* $t19 = 1 */
    movq $1, %r10
    movq %r10, -216(%rbp)
    /* $t20 = 1 */
    movq $1, %r10
    movq %r10, -224(%rbp)
    /* $t21 = $t19 * $t20 */
    movq -216(%rbp), %r10
    imulq -224(%rbp), %r10
    movq %r10, -232(%rbp)
    /* %t7 = addressAt %x, $t21 */
    movq -232(%rbp), %r11
    movq $8, %r10
    imul %r10, %r11
    movq x@GOTPCREL(%rip) , %r10
    addq %r10, %r11
    movq %r11, -240(%rbp)
    /* $t22 = load %t7 */
    movq -240(%rbp), %r10
    movq 0(%r10), %r10
    movq %r10, -248(%rbp)
    /* call %printInt ($t22) */
    movq -248(%rbp), %rdi
    call printInt
    /* $t23 = 2 */
    movq $2, %r10
    movq %r10, -256(%rbp)
    /* $t24 = 1 */
    movq $1, %r10
    movq %r10, -264(%rbp)
    /* $t25 = $t23 * $t24 */
    movq -256(%rbp), %r10
    imulq -264(%rbp), %r10
    movq %r10, -272(%rbp)
    /* %t8 = addressAt %x, $t25 */
    movq -272(%rbp), %r11
    movq $8, %r10
    imul %r10, %r11
    movq x@GOTPCREL(%rip) , %r10
    addq %r10, %r11
    movq %r11, -280(%rbp)
    /* $t26 = load %t8 */
    movq -280(%rbp), %r10
    movq 0(%r10), %r10
    movq %r10, -288(%rbp)
    /* call %printInt ($t26) */
    movq -288(%rbp), %rdi
    call printInt
    /* %t9 = addressAt %canary_end, null */
    movq canary_end@GOTPCREL(%rip) , %r11
    movq %r11, -296(%rbp)
    /* $t27 = load %t9 */
    movq -296(%rbp), %r10
    movq 0(%r10), %r10
    movq %r10, -304(%rbp)
    /* call %printInt ($t27) */
    movq -304(%rbp), %rdi
    call printInt
    leave
    ret
