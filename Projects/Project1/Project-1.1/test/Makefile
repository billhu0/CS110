VALGRIND = valgrind --tool=memcheck --leak-check=full --track-origins=yes

rtype_TESTS = 1 2
itype_TESTS = 1 2
stype_TESTS = 1 2
sbtype_TESTS = 1
utype_TESTS = 1 2
ujtype_TESTS = 1
full_TESTS = 1

clean:
	@rm -rf out

grade: ../translator make_out_dirs run_tests
	@python3 test.py
	
make_out_dirs:
	@-mkdir -p out/rtype
	@-mkdir -p out/itype
	@-mkdir -p out/stype
	@-mkdir -p out/sbtype
	@-mkdir -p out/utype
	@-mkdir -p out/ujtype
	@-mkdir -p out/full

run_tests: run_rtype_tests run_itype_tests run_stype_tests run_sbtype_tests run_utype_tests run_ujtype_tests run_full_tests


run_rtype_tests: $(addsuffix _rtype_test, $(rtype_TESTS))

%_rtype_test: in/rtype/input_%.s
	@-$(VALGRIND) ../translator $< out/rtype/output_$*.s > /dev/null 2> out/rtype/memcheck_$*.txt || true
	

run_itype_tests: $(addsuffix _itype_test, $(itype_TESTS))

%_itype_test: in/itype/input_%.s
	@-$(VALGRIND) ../translator $< out/itype/output_$*.s > /dev/null 2> out/itype/memcheck_$*.txt || true
	
	
run_stype_tests: $(addsuffix _stype_test, $(stype_TESTS))

%_stype_test: in/stype/input_%.s
	@-$(VALGRIND) ../translator $< out/stype/output_$*.s > /dev/null 2> out/stype/memcheck_$*.txt || true


run_sbtype_tests: $(addsuffix _sbtype_test, $(sbtype_TESTS))

%_sbtype_test: in/sbtype/input_%.s
	@-$(VALGRIND) ../translator $< out/sbtype/output_$*.s > /dev/null 2> out/sbtype/memcheck_$*.txt || true
	

run_utype_tests: $(addsuffix _utype_test, $(utype_TESTS))

%_utype_test: in/utype/input_%.s
	@-$(VALGRIND) ../translator $< out/utype/output_$*.s > /dev/null 2> out/utype/memcheck_$*.txt || true


run_ujtype_tests: $(addsuffix _ujtype_test, $(ujtype_TESTS))

%_ujtype_test: in/ujtype/input_%.s
	@-$(VALGRIND) ../translator $< out/ujtype/output_$*.s > /dev/null 2> out/ujtype/memcheck_$*.txt || true
	
	
run_full_tests: $(addsuffix _full_test, $(full_TESTS))

%_full_test: in/full/input_%.s
	@-$(VALGRIND) ../translator $< out/full/output_$*.s > /dev/null 2> out/full/memcheck_$*.txt || true
