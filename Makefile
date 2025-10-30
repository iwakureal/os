BOOT_SOURCES = $(shell find boot -name '*.asm')
BOOT_OBJECTS := $(patsubst %.asm,%.oo,$(BOOT_SOURCES))

KERNEL_SOURCES = $(shell find kernel -name '*.cpp' -o -name '*.asm')
KERNEL_OBJECTS := $(patsubst %.cpp,%.o,$(patsubst %.asm,%.oo,$(KERNEL_SOURCES)))

COMPILER = g++
CFLAGS = -g -ffreestanding -mno-red-zone -mno-sse -mno-sse2 -mno-mmx -mno-80387 -fno-pie -m32 -I./kernel -Og -Wall -Wextra

NASM = nasm
LD = ld

QEMU = qemu-system-i386

IMAGE_SIZE = 1048576

run: os.img
	$(QEMU) -hda $< -boot c -d int,nochain -monitor stdio

debug: os.img kernel.elf
	$(QEMU) -S -s -hda $< -boot c -d guest_errors,int &
	gdb -ex "target remote localhost:1234" -ex "symbol-file kernel.elf"

os.img: boot.bin kernel.bin
	cat $^ > $@
	fallocate -l $(IMAGE_SIZE) $@

boot.bin: $(BOOT_OBJECTS)
	$(LD) -o $@ -T boot/link.ld -m elf_i386 --oformat binary $^

kernel.bin: $(KERNEL_OBJECTS)
	$(LD) -o $@ -T kernel/link.ld -m elf_i386 --oformat binary $^

kernel.elf: $(KERNEL_OBJECTS)
	$(LD) --verbose -o $@ -T kernel/link.ld -m elf_i386 $^

%.o: %.cpp
	$(COMPILER) $(CFLAGS) -c $< -o $@

%.oo: %.asm
	$(NASM) -o $@ -f elf32 -g $<

clean:
	rm -rf $(BOOT_OBJECTS) $(KERNEL_OBJECTS) *.img *.bin *.elf
