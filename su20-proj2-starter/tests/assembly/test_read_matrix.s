.import ../../src/read_matrix.s
.import ../../src/utils.s

.data
file_path: .asciiz "inputs/test_read_matrix/test_input.bin"

.text
main:
    # Read matrix into memory
	la a0, file_path
	jal ra, read_matrix
	lw a1, 0(a1)
	lw a2, 0(a2)
    # Print out elements of matrix
	jal print_int_array
    # Terminate the program
	jal exit
