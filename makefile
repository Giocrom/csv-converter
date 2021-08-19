csvconverter: src/csvconverter.c src/Objs/errors.o src/Objs/output.o
	gcc -o csvconverter src/csvconverter.c src/Objs/errors.o src/Objs/output.o

src/Objs/errors.o: src/Librares/errors.c src/Librares/errors.h
	gcc -c src/Librares/errors.c -o src/Objs/errors.o

src/Objs/output.o: src/Librares/output.c src/Librares/output.h
	gcc -c src/Librares/output.c -o src/Objs/output.o
