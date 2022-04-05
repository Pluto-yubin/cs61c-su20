.globl relu

.text
# ==============================================================================
# FUNCTION: Performs an inplace element-wise ReLU on an array of ints
# Arguments:
#	a0 (int*) is the pointer to the array
#	a1 (int)  is the # of elements in the array
# Returns:
#	None
#
# If the length of the vector is less than 1,
# this function exits with error code 8.
# ==============================================================================
relu:
# Prologue
	addi sp, sp, -12
	sw s0, 0(sp)
	sw a0, 4(sp)
	sw ra, 8(sp)
	mv a0, s0

loop_start:
	beq a1, x0, loop_end
	addi, a1, a1, -1
	lw a0, 0(s0)
	jal ra, loop_continue
	sw a0, 0(s0)
	addi s0, s0, 4
	j loop_start

loop_continue:
	blt a0, x0, get_zero
	jr ra

get_zero:
	add a0, x0, x0
	j loop_continue

loop_end:
	lw s0, 0(sp)
	lw a0, 4(sp)
	lw ra, 8(sp)
	addi sp, sp, 12
	jr ra
