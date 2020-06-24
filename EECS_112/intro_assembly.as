.data
array1: .word 1,2,3
.text
li x10,0
la x22,array1

addi x10,x10,2
lw x12,4(x22)
mul x12,x12,x10

lw x13,0(x22)
lw x14,8(x22)
add x12,x13,x12
add x12,x12,x14
addi x12,x12,45

sw x12,12(x22)

ecall