#
# Copyright (c) 2013 HuangTao All rights reserved.
#
# huangtao@antiy.com
#

adfs:master.c slave.c inkprotocol.o
	gcc -pthread inkprotocol.o -o master master.c
	gcc -o slave slave.c

inkprotocol.o:inkprotocol.c inkprotocol.h


.PHONY:clean
clean:
	rm -rf *.o master slave

