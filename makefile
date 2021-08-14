csvconverter: Docs/csvconverter.c Docs/Objs/errors.o Docs/Objs/output.o
	gcc -o csvconverter Docs/csvconverter.c Docs/Objs/errors.o Docs/Objs/output.o

Docs/Objs/errors.o: Docs/Librares/errors.c Docs/Librares/errors.h
	gcc -c Docs/Librares/errors.c -o Docs/Objs/errors.o

Docs/Objs/output.o: Docs/Librares/output.c Docs/Librares/output.h
	gcc -c Docs/Librares/output.c -o Docs/Objs/output.o
