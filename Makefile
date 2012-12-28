
CXX = g++ -O3 -c -std=c++11 -Wall -Wextra -Iinclude -fno-strict-aliasing -DNDEBUG
LDXX = g++ -std=c++11
AR = ar rcs

VM = obj/vm.o $(subst .cpp,.o,$(subst src/,obj/,$(wildcard src/_*.cpp))) obj/instr.o
TESTS = $(subst .c,.bin,$(wildcard test/test*.c))

all: asmtest.bin run

run: run.cpp libvm.a
	@echo Creating $@...
	@$(CXX) run.cpp -o run.o
	@$(LDXX) run.o -o run -L. -lvm

include/instr_decl.hpp src/instr.cpp: instructions.rb
	@echo Generating instruction table...
	@ruby instructions.rb generate

%.s: %.c
	@echo Compiling $<...
	@gcc -march=i386 $< -S -o $@ -nostdlib -nostdinc -fno-hosted -Iplayer

%.bin: %.s $(subst .c,.s,$(wildcard player/*.c)) libgcc2.s as.rb instructions.rb parser.rb
	@echo Creating $@...
	@ruby as.rb libgcc2.s $(@:.bin=.s) $(subst .c,.s,$(wildcard player/*.c)) -o $@

libgcc2.s: ~/gcc/libgcc/libgcc2.c
	@echo Compiling libgcc2.c...
	@gcc ~/gcc/libgcc/libgcc2.c -O3 -S -o libgcc2.s \
	-I ~/gcc/gcc -I ~/gcc/host-i686-pc-linux-gnu/gcc -I ~/gcc/include -I ~/gcc/i686-pc-linux-gnu/libgcc \
	-DMIN_UNITS_PER_WORD=4 \
	-DL_divdi3 -DL_moddi3

libvm.a: $(VM)
	@echo Creating $@...
	@$(AR) $@ $(VM)

obj/%.d: |obj
	@g++ -nostdinc -std=c++11 -Iinclude -MF$@ -MG -MM -MP -MT$@ -MT$(@:.d=.o) $(subst obj/,src/,$(@:.d=.cpp))

-include $(VM:.o=.d)

obj/%.o: src/%.cpp |obj
	@echo Compiling $<...
	@$(CXX) $< -o $@
	
build-tests: $(TESTS) test/testrunner

test: $(TESTS) test/testrunner
	@for test in $(TESTS); \
		do test/testrunner $$test; \
	done

test/testrunner: test/testrunner.cpp libvm.a
	@echo Creating $@...
	@$(CXX) test/testrunner.cpp -o test/testrunner.o
	@$(LDXX) test/testrunner.o -o test/testrunner -L. -lvm

obj:
	@mkdir obj

doc:
	@echo Generating documentation...
	@doxygen doc/Doxyfile

clean: |obj
	@-rm -rf obj *.bin *.s player/*.s *.o *.a
	@-rm -rf test/*.s test/*.bin test/*.o test/testrunner run doc/html

.PHONY: all test clean doc
.SECONDARY: $(subst .c,.s, $(wildcard *.c) $(wildcard player/*.c) $(wildcard test/*.c))
