addi x10,x0,100	#store n=100 in x10
jal x1,SIGMA			#call function SIGMA
beq x0,x0,END

SIGMA:
	addi sp,sp,-8
	sw x1,4(sp)
	sw x10,0(sp)
	addi x5,x0,1
	bne x10,x5,RCALL
	addi x10,x0,1
	addi sp,sp,8
	jalr x0 x1 0
RCALL:
	addi x10,x10,-1
	jal x1,SIGMA
	addi x6,x10,0
	lw x10,0(sp)
	lw x1,4(sp)
	addi sp,sp,8
	add x10,x10,x6
	jalr x0 x1 0

END:
	nop