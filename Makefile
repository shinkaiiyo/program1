CC = sdcc

all:main.hex write

HSRC=${wildcard *.h}
RSRC=${patsubst %.h, %.rel, $(HSRC)}
WRITE="n"

$(RSRC):%.rel:%.c
		$(CC) -c $^ -o output/$@

main.rel:main.c $(HSRC)
	$(CC) -c main.c -o output/main.rel

main.ihx:main.rel $(RSRC)
	cd output && $(CC) main.rel $(RSRC) -o final/main.ihx &&cd ..

main.hex:main.ihx 
	packihx output/final/main.ihx > main.hex

write:main.hex
	@echo -n "\n编译完成,请在本目录手动执行stcflash.py main.hex来写入程序\n"

clean:
	rm -rf main.hex
	rm -rf output/*
	mkdir output/final

