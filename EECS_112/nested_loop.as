.data
A: .word 0,1,2,3
.text
li x5, 4  #a
li x6, 2  #b
la x10, A #A
li x7, 0  #i
li x29, 0 #j

loopi:
	bge x7,x5,ENDi
	beq x0,x0,loopj

loopj:
	bge x29,x6,ENDj
	slli x9,x7,2		#beginning arithmetic handling
	add x9,x9,x10
	lw x20,0(x9)		#load memory into register
	slli x21,x29,1
	add x20,x20,x21
	add x20,x20,x7
	sw x20,0(x9)		#storing into memory
	addi x29,x29,1	#increment j
	beq x0,x0,loopj

ENDj:
	addi x29,x0,0 	#reset j
	addi x7,x7,1		#increment i
	beq x0,x0,loopi

ENDi:
	exit:
		nop