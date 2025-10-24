SOURCES = $(shell find -name '*.asm')
OBJECTS := $(addsuffix .o, $(basename $(SOURCES)))

NASM = nasm
LD = ld

boot.bin: $(OBJECTS)
	$(LD) -o $@ -T link.ld --oformat binary $^

%.o: %.asm
	$(NASM) $< -f elf64 -o $@
