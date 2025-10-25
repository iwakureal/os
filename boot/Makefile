SOURCES = $(shell find -name '*.asm')
OBJECTS := $(addsuffix .o, $(basename $(SOURCES)))

NASM = nasm
LD = ld

boot.bin: $(OBJECTS)
	$(LD) -o $@ -T link.ld -m elf_i386 --oformat binary $^

%.o: %.asm
	$(NASM) $< -f elf32 -o $@

clean:
	rm -rf $(OBJECTS) *.bin
