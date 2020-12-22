CXX	= g++
CXX_FLAGS = -Wall -O2 -std=c++14
TARGETS = relu conv_multi conv_multi_lock conv_multi_assign

.cpp.o:
	${CXX} ${CXX_FLAGS} -c $< -fopenmp

.PHONY: all
all: ${TARGETS}

.PHONY: clean
clean:
	${RM} -f *.o ${TARGETS}

relu: relu.o
	${CXX} ${CXX_FLAGS} -o $@ $^ -fopenmp

conv_multi: conv_multi.o
	${CXX} ${CXX_FLAGS} -o $@ $^ -fopenmp

conv_multi_lock: conv_multi_lock.o
	${CXX} ${CXX_FLAGS} -o $@ $^ -fopenmp

conv_multi_assign: conv_multi_assign.o
	${CXX} ${CXX_FLAGS} -o $@ $^ -fopenmp
