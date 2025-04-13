all: sa_prod sa_debug clean

.INTERMEDIATE: *.o

sa_debug: stack_allocator_debug.o
	gcc -O0 -g stack_allocator.o validate.o -o allocator_debug

sa_prod: stack_allocator_prod.o
	gcc stack_allocator.o validate.o -o allocator

stack_allocator_debug.o: ../src/stack_allocator.c ../src/validate.c
	gcc -O0 -c -g -I ../include ../src/validate.c ../src/stack_allocator.c

stack_allocator_prod.o: ../src/stack_allocator.c ../src/validate.c
	gcc -DNDEBUG -c -I ../include ../src/validate.c ../src/stack_allocator.c

clean: 
	rm -rf *.o
