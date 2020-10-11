GENERATES = prog prog-a prog-so *.so README
TRASH = *.o *~ *.a test_*.txt
OUTPUT_OPTION = -o $@
TEST_PARAMS_ONE = a
TEST_PARAMS_THREE = b c d

run_progs = $(foreach CMD, $(1),LD_LIBRARY_PATH=. ./$(CMD) $(2) 1> test_$(CMD)_$(words $(2))_stdout.txt 2> test_$(CMD)_$(words $(2))_stderr.txt $(NEWLINE))
compare_progs = $(foreach CMD1,$(1),$(foreach CMD2,$(1), cmp test_$(CMD1)_$(words $(2))_$(strip $(3)).txt test_$(CMD2)_$(words $(2))_$(strip $(3)).txt $(NEWLINE)))
define NEWLINE

$(blank)
endef

all:	README prog prog-a prog-so

test: prog-so prog-a prog
	$(call run_progs,$^,)
	$(call compare_progs,$^, ,stdout)
	$(call run_progs,$^,$(TEST_PARAMS_ONE))
	$(call compare_progs,$^,$(TEST_PARAMS_ONE),stdout)
	$(call run_progs,$^,$(TEST_PARAMS_THREE))
	$(call compare_progs,$^,$(TEST_PARAMS_THREE),stdout)
	rm -rf test_*.txt


prog:	const.o fun.o prog.o

prog-a: prog.o liboutput_static.a
	$(LINK.o) $^ -L. $(LOADLIBES) $(LDLIBS) -loutput_static $(OUTPUT_OPTION)

prog-so: prog.o liboutput.so
	$(LINK.o) $< -L. $(LOADLIBES) $(LDLIBS) -loutput $(OUTPUT_OPTION)

README:	prog
	./$< 2> $@

prog.o: outlib.h

fun.o:	fun.c outlib.h
	$(COMPILE.c) -fPIC $(OUTPUT_OPTION) $<

const.o: const.c
	$(COMPILE.c) -fPIC $(OUTPUT_OPTION) $<

liboutput_static.a: const.o fun.o
	$(AR) $(ARFLAGS) $@ $^

liboutput.so: const.o fun.o
	$(LINK.c) -shared $^ $(LOADLIBES) $(LDLIBS) -o $@

clean:
	rm -f $(TRASH)

distclean:	clean
	rm -rf $(GENERATES)
