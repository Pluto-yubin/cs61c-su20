.globl matmul

.text
# =======================================================
# FUNCTION: Matrix Multiplication of 2 integer matrices
#	d = matmul(m0, m1)
#   The order of error codes (checked from top to bottom):
#   If the dimensions of m0 do not make sense,
#   this function exits with exit code 2.
#   If the dimensions of m1 do not make sense,
#   this function exits with exit code 3.
#   If the dimensions don't match,
#   this function exits with exit code 4.
# Arguments:
#	a0 (int*)  is the pointer to the start of m0
#	a1 (int)   is the # of rows (height) of m0
#	a2 (int)   is the # of columns (width) of m0
#	a3 (int*)  is the pointer to the start of m1
#	a4 (int)   is the # of rows (height) of m1
#	a5 (int)   is the # of columns (width) of m1
#	a6 (int*)  is the pointer to the the start of d
# Returns:
#	None (void), sets d = matmul(m0, m1)
# =======================================================
matmul:

    # Error checks
	beq x0, a1, exit_2
	beq x0, a2, exit_2
	beq x0, a4, exit_3
	beq x0, a5, exit_3
	bne a2, a4, exit_4

	addi sp, sp, -40
	sw s0, 0(sp)
	sw s1, 4(sp)
	sw s2, 8(sp)
	sw s3, 12(sp)
	sw s4, 16(sp)
	sw s5, 20(sp)
	sw s6, 24(sp)
	sw s7, 28(sp)
	sw s8, 32(sp)
	sw ra, 36(sp)

	mv s0, a0
	mv s1, a3
	# m x n , n x k
	mv s2, a1 # s2 is m
	mv s3, a2 # s3 is n
	mv s4, a5 # s4 is k

	mv s5, a6
	mv s8, a6

	mv t0, x0
	mv t1, x0
    # Prologue
	li s6, 1 # the stride of m0
	mv s7, s3# the stride of m1


outer_loop_start:
	beq x0, s2, outer_loop_end
	addi, sp, sp, -4
	sw t0, 0(sp)
	#  get the location of first element in row t0
	mul t3, t0, s3
	slli t3, t3, 2
	# initialize the length for inner loop
	mv t2, s4
	jal, ra, inner_loop_start
	lw t0, 0(sp)
	addi sp, sp, 4
	addi t0, t0, 1
	# initialize the location for next inner loop
	mv t1, x0

	addi s2, s2, -1

	j outer_loop_start


inner_loop_start:
	beq x0, t2, inner_loop_end
	# get the location of first element in the col t1 of m1
	slli t4, t1, 2
	add a0, s0, t3
	add a1, s1, t4
	# pass parameter
	mv a2, s3
	mv a3, s6
	mv a4, s7
	addi sp, sp, -16
	sw t1, 0(sp)
	sw t2, 4(sp)
	sw t3, 8(sp)
	sw ra, 12(sp)
	jal ra, dot
	lw t1, 0(sp)
	lw t2, 4(sp)
	lw t3, 8(sp)
	lw ra, 12(sp)
	addi sp, sp, 16
	sw a0, 0(s5)

	addi s5, s5, 4

	addi t2, t2, -1
	addi t1, t1, 1

	j inner_loop_start

inner_loop_end:
	jr ra
outer_loop_end:
	mv a6, s8
	lw s0, 0(sp)
	lw s1, 4(sp)
	lw s2, 8(sp)
	lw s3, 12(sp)
	lw s4, 16(sp)
	lw s5, 20(sp)
	lw s6, 24(sp)
	lw s7, 28(sp)
	lw s8, 32(sp)
	lw ra, 36(sp)
	addi sp, sp, 40
	jr ra

exit_2:
	li a0, 2

exit_3:
	li a0,3

exit_4:
	li, a0, 4
