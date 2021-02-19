all: open-log.so rick-ropen.so

open-log.so: open-log.c
	gcc -Wall -shared -fPIC -ldl $< -o $@

rick-ropen.so: rick-ropen.c
	gcc -Wall -shared -fPIC -ldl $< -o $@

fork:
	gcc -Wall fork.c -o fork

readdir:
	gcc -Wall readdir.c -o readdir

clean:
	rm -f *.so
