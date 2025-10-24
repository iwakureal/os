BOOT_SOURCES = $(shell find boot -name '*.asm')
BOOT_OBJECTS := $(addsuffix .o, $(basename $(BOOT_SOURCES)))

KERNEL_SOURCES = $(shell find kernel -name '*.cpp' -o -name '*.asm')
KERNEL_OBJECTS := $(addsuffix .o, $(basename $(KERNEL_SOURCES)))

COMPILER = gcc
CFLAGS = -g -ffreestanding -fno-pie -fno-rtti -m32 -I./kernel -O3 -Wall -Wextra

NASM = nasm
LD = ld

IMAGE_SIZE = 1048576

run: os.img
	qemu-system-x86_64 -hda $< -boot c -monitor stdio

debug: os.img kernel.elf
	qemu-system-x86_64 -S -s -hda $< -boot c -d guest_errors,int &
	gdb -ex "target remote localhost:1234" -ex "symbol-file kernel.elf"

os.img: boot.bin kernel.bin
	cat $^ > $@
	fallocate -l $(IMAGE_SIZE) $@

boot.bin: $(BOOT_OBJECTS)
	$(LD) -o $@ -T boot/link.ld -m elf_i386 --oformat binary $^

kernel.bin: $(KERNEL_OBJECTS)
	$(LD) --verbose -o $@ -T kernel/link.ld -m elf_i386 --oformat binary $^

kernel.elf: $(KERNEL_OBJECTS)
	$(LD) --verbose -o $@ -T kernel/link.ld -m elf_i386 $^

%.o: %.cpp
	$(COMPILER) $(CFLAGS) -c $< -o $@

%.o: %.asm
	$(NASM) -o $@ -f elf32 -g $<

clean:
	rm -rf $(BOOT_OBJECTS) $(KERNEL_OBJECTS) *.img *.bin *.elf
