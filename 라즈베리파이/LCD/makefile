all: lcdTest lcdmultiTest

lcdTest: lcd1602.o lcdmain.o
	gcc -o lcdTest lcd1602.o lcdmain.o -lwiringPi

lcdmultiTest: lcd1602.o lcdmulti.o
	gcc -o lcdmulti lcd1602.o lcdmulti.o -lwiringPi

lcd1602.o: lcd1602.c lcd1602.h
	gcc -c lcd1602.c -lwiringPi

lcdmain.o: lcdmain.c lcd1602.h
	gcc -c lcdmain.c -lwiringPi

lcdmulti.o: lcdmulti.c lcd1602.h
	gcc -c lcdmulti.c -lwiringPi

clean:
	rm -f lcd1602.o lcdmain.o lcdmulti.o lcdTest lcdmulti
