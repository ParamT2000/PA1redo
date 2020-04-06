WARNING = -Wall -Wshadow --pedantic
ERROR = -Wvla #-Werror
GCC = gcc -std=c99 -g $(WARNING) $(ERROR)
VAL = valgrind --tool=memcheck --log-file=memcheck.txt --leak-check=full --verbose


SRCS = pa1.c shell_array.c shell_list.c
OBJS = $(SRCS:%.c=%.o)

pa1: $(OBJS)
	$(GCC) $(TESTFALGS)  $(OBJS) -o pa1

.c.o:
	$(GCC) $(TESTFALGS) -c $*.c


testall: test1 

test1: pa1
	./pa1 -a inputs/examples/15.b output15.b
	diff -w output15.b inputs/examples/15sa.b
test2: pa1
	./pa1 -a inputs/examples/1K.b output1k.b
	diff  output1k.b  inputs/examples/1Ksa.b

testL15: pa1
	./pa1 -l inputs/examples/15.b outTest.b
	diff -w outTest.b inputs/examples/15sl.b
testL1K: pa1
	./pa1 -l inputs/examples/1K.b outTest.b
	diff -w outTest.b inputs/examples/1Ksl.b
testL1M: pa1
	./pa1 -l inputs/examples/1M.b 1Msl.b
clean: # remove all machine generated files
	rm -f pa1 *.o output?

memCheckA:
	valgrind --leak-check=full \
	--show-leak-kinds=all \
	--track-origins=yes \
	--verbose \
	./pa1 -a inputs/examples/1M.b 1Msa.b
memCheckL:
	valgrind --leak-check=full \
	--show-leak-kinds=all \
	--track-origins=yes \
	--verbose \
	./pa1 -l inputs/examples/1K.b outTest.b
