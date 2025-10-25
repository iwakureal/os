SOURCES = $(shell find -name '*.cpp' -o -name '*.asm')
OBJECTS := $(addsuffix .o, $(basename $(SOURCES)))

COMPILER = gcc
CFLAGS = -g -ffreestanding -fno-pie -fno-rtti -m32 -I. -O3 -Wall -Wextra

NASM = nasm
LD = ld

kernel.bin: $(OBJECTS)
	$(LD) --verbose -o $@ -T link.ld -m elf_i386 --oformat binary $^

kernel.elf: $(OBJECTS)
	$(LD) --verbose -o $@ -T link.ld -m elf_i386 $^

%.o: %.cpp
	$(COMPILER) $(CFLAGS) -c $< -o $@

%.o: %.asm
	$(NASM) -o $@ -f elf32 -g $<

clean:
	rm -rf $(OBJECTS) *.bin *.elf
