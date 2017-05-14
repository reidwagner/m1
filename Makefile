export PYTHONPATH := $(shell pwd):$(PYTHONPATH)
.PHONY: all test clean

all: m1.so

m1.so: src/m1.c setup.py
	python3 setup.py build
	cp build/lib.macosx-10.11-x86_64-3.5/m1.cpython-35m-darwin.so m1.so

test:
	@echo $(PYTHONPATH)
	./test/m1_test.py -v

clean:
	rm -rf build
	rm m1.so
