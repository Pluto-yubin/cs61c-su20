.globl read_matrix

.text
# ==============================================================================
# FUNCTION: Allocates memory and reads in a binary file as a matrix of integers
#   If any file operation fails or doesn't read the proper number of bytes,
#   exit the program with exit code 1.
# FILE FORMAT:
#   The first 8 bytes are two 4 byte ints representing the # of rows and columns
#   in the matrix. Every 4 bytes afterwards is an element of the matrix in
#   row-major order.
# Arguments:
#   a0 (char*) is the pointer to string representing the filename
#   a1 (int*)  is a pointer to an integer, we will set it to the number of rows
#   a2 (int*)  is a pointer to an integer, we will set it to the number of columns
# Returns:
#   a0 (int*)  is the pointer to the matrix in memory
#
# If you receive an fopen error or eof,
# this function exits with error code 50.
# If you receive an fread error or eof,
# this function exits with error code 51.
# If you receive an fclose error or eof,
# this function exits with error code 52.
# ==============================================================================
read_matrix:
	addi sp, sp, -24
	sw s0, 0(sp)  # the file description
	sw s1, 4(sp)  # number of row
	sw s2, 8(sp)  # number of columns
	sw s3, 12(sp) # the length of array, aka row * col
	sw s4, 16(sp) # the pointer to the matrix memory
	sw ra, 20(sp)

	jal ra, open_file
	li t0, -1
	beq t0, a0, exit_50
    # Prologue
	mv s0, a0 # save file description to s0

	# read row and col
	mv a1, s0
	li a3, 8
	mv a0, a3 # a3 is the number of bytes to read from the file.
	jal ra, malloc # malloc, which allocates a0 bytes on the heap, and returns a pointer to them in a0.
	mv a2, a0
	jal ra, read_file # a0 is the number of bytes actually read from the file.
	mv s1, a0 # the row of matrix
	addi a0, a0, 4
	mv s2, a0

	lw t0, 0(s1)
	lw t1, 0(s2)
	mul s3, t1, t2 # the length of matrix
	slli t0, s3, 2
	mv a0, t0
	jal ra malloc
	mv s4, a0
	mv t0, s4

read_loop:
	beq s3, x0, loop_end
	addi sp, sp, -4
	sw t0, 0(sp)
	mv a1, s0
	li a3, 4
	mv a2, t0
	jal ra, read_file
	lw t0, 0(sp)
	addi t0, t0, 4
	addi sp, sp, 4
	addi, s3, s3, -1
	j read_loop

open_file: # a0 is a file descriptor as a return value. On failure, a0 is set to -1.
	addi sp, sp, -4
	sw ra, 0(sp)
	mv a1, a0 # a1 is a pointer to a string containing the filename of the file to open
	mv a2, x0 # a2 is an integer denoting the permissions we open the file with.
	jal ra, fopen
	lw ra, 0(sp)
	addi, sp, sp, 4
	jr ra

# a1 is the file descriptor of the file we want to read from, previously returned by fopen.
# a2 is a pointer to the buffer that we’re going to read the bytes from the file into. This must be an appropriate amount of memory that was allocated before calling the function, and passed in as a pointer.
# a3 is the number of bytes to read from the file.

read_file:
	addi sp, sp, -4
	sw ra, 0(sp)
	jal ra, fread # a0 is the number of bytes actually read from the file.
	bne a3, a0, exit_51
	lw ra, 0(sp)
	addi sp, sp, 4
	jr ra

loop_end:
	mv a1, s0
	jal ra, fclose
	bne a0, x0, exit_52
	mv a0, s4
	mv a1, s1
	mv a2, s2
	lw s0, 0(sp)
	lw s1, 4(sp)  # number of row
	lw s2, 8(sp)  # number of columns
	lw s3, 12(sp) # the length of array, aka row * col
	lw s4, 16(sp) # the pointer to the matrix memory
	lw ra, 20(sp)

	addi sp, sp, 24
	jr ra

exit_50:
	li a0, 50
	lw s0, 0(sp)
	lw s1, 4(sp)  # number of row
	lw s2, 8(sp)  # number of columns
	lw s3, 12(sp) # the length of array, aka row * col
	lw s4, 16(sp) # the pointer to the matrix memory
	lw ra, 20(sp)
	addi sp, sp, 24
	jr ra

exit_51:
	li a0, 50
	addi sp, sp, 4
	lw s0, 0(sp)
	lw s1, 4(sp)  # number of row
	lw s2, 8(sp)  # number of columns
	lw s3, 12(sp) # the length of array, aka row * col
	lw s4, 16(sp) # the pointer to the matrix memory
	lw ra, 20(sp)
	addi sp, sp, 24
	jr ra

exit_52:
	li a0, 52
	lw s0, 0(sp)
	lw s1, 4(sp)  # number of row
	lw s2, 8(sp)  # number of columns
	lw s3, 12(sp) # the length of array, aka row * col
	lw s4, 16(sp) # the pointer to the matrix memory
	lw ra, 20(sp)
	addi sp, sp, 24
	jr ra
