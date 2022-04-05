.globl argmax

.text
# =================================================================
# FUNCTION: Given a int vector, return the index of the largest
#	element. If there are multiple, return the one
#	with the smallest index.
# Arguments:
#	a0 (int*) is the pointer to the start of the vector
#	a1 (int)  is the # of elements in the vector
# Returns:
#	a0 (int)  is the first index of the largest element
#
# If the length of the vector is less than 1,
# this function exits with error code 7.
# =================================================================
argmax:
	addi sp, sp, -8
	sw s0, 0(sp)
	sw ra, 4(sp)
	mv s0, a0
	lw t0, 0(s0) # t0 is the current max value
	add t1, x0, x0 # t1 is the index of current max value
	add t2, x0, x0
    # Prologue

loop_start:
	beq a1, x0, loop_end
	addi a1, a1, -1
	lw a0, 0(s0)
	blt t0, a0, get_max
	addi t2, t2, 1
	addi s0, s0, 4

get_max:
	mv t0, a0
	mv t1, t2
	jr ra


loop_end:
   mv a0, t1
   lw s0, 0(sp)
   lw ra, 4(sp)
   addi sp, sp, 8
   jr ra

    # Epilogue


    ret
