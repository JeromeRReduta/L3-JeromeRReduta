all: open-log.so rick-ropen.so

open-log.so: open-log.c
	gcc -Wall -shared -fPIC -ldl $< -o $@

rick-ropen.so: rick-ropen.c
	gcc -Wall -shared -fPIC -ldl $< -o $@

fork:
	gcc -Wall fork.c -o fork

readdir:
	gcc -Wall readdir.c -o readdir

testOpenLog:
	LD_PRELOAD=$$(pwd)/open-log.so nano roll.txt

testRickRopen:
	LD_PRELOAD=$$(pwd)/rick-ropen.so nano roll.txt

testTxt:
	LD_PRELOAD=$$(pwd)/rick-ropen.so nano fishTrace.txt
testJava:
	LD_PRELOAD=$$(pwd)/rick-ropen.so nano blank.java

clean:
	rm -f *.so
