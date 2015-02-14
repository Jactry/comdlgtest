default: all

dialog.o: dialog.c
	i686-w64-mingw32-gcc -c dialog.c -o dialog.o -I ./ -mwindows

dialog_res.o: dialog.rc dialog_res.h
	i686-w64-mingw32-windres dialog.rc -o dialog_res.o -lcomctl32

dialog.dll: dialog.o dialog_res.h dialog_res.o
	i686-w64-mingw32-gcc -o dialog.dll -s -shared dialog_res.o dialog.o -lcomctl32

# main_res.o: main.rc
# 	i686-w64-mingw32-windres main.rc -o main_res.o

main.o: main.c main_res.h
	i686-w64-mingw32-gcc -c -o main.o main.c

# main.exe: main.o main_res.o main_res.h dialog.dll
# 	i686-w64-mingw32-gcc -o main.exe main_res.o -s main.o -L. -ldialog -mwindows -lcomctl32

main.exe: main.o main_res.h dialog.dll
	i686-w64-mingw32-gcc -o main.exe -s main.o -L. -ldialog -mwindows -lcomctl32

all: main.exe

clean:
	find . -name "*.o" -exec rm -f {} \;
	find . -name "*~" -exec rm -f {} \;
	find . -name "*.exe" -exec rm -f {} \;
	find . -name "*.dll" -exec rm -f {} \;
