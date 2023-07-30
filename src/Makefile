FLAGS = g++ -g -std=c++17 -Wall -Wextra -Werror

all: clean install

build: decompress
	qmake -o QMakefile && make -f QMakefile

install: build
	@mkdir ../build
	mv view.app ../build/MLP.app

uninstall: clean
	rm -rf ../build/MLP.app

reinstall: uninstall
	make install

dist: reinstall
	cd ../build && tar -zcf MLP.tar.gz MLP.app

dvi:
	open dvi.html

compile:
	$(FLAGS) test/tests.cc controller/*.h controller/*.cc model/*.h model/*.cc model/*/*.h model/*/*.cc model/*/*/*.h model/*/*/*.cc model/*/*/*/*.h model/*/*/*/*.cc -lgtest

tests: clean decompress compile
	./a.out

leaks: compile
	CK_FORKS=no leaks -atExit -- ./a.out

style:
	cp ../materials/linters/.clang-format .
	clang-format -n *.cc */*.h */*.cc */*/*.h */*/*.cc */*/*/*.h */*/*/*.cc */*/*/*/*.h */*/*/*/*.cc

clean:
	@rm -rf a.out* ../build-View-Desktop_x86_darwin_generic_mach_o_64bit-Debug
	@rm -rf test/tests.h.gch controller/*.h.gch model/*.h.gch model/*/*.h.gch  model/*/*/*.h.gch  model/*/*/*/*.h.gch
	@rm -rf *.o .qmake.stash .clang-format moc_* QMakefile ui_mainwindow.h qrc_resources.cpp view.pro.user
	@rm -rf ../datasets/emnist ../datasets/weights ../datasets/image ../build

decompress:
	@open ../datasets/*
	@sleep 10
