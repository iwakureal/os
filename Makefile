BOOT_SOURCES = $(shell find boot -name '*.asm')
BOOT_OBJECTS := $(patsubst %.asm,%.oo,$(BOOT_SOURCES))

KERNEL_SOURCES = $(shell find kernel -name '*.c' -o -name '*.asm')
KERNEL_OBJECTS := $(patsubst %.c,%.o,$(patsubst %.asm,%.oo,$(KERNEL_SOURCES)))

COMPILER = gcc
CFLAGS = -g -ffreestanding -fno-pie -fno-builtin -mno-red-zone -mno-sse -mno-sse2 -mno-mmx -mno-80387 -m32 -I./kernel -Og -Wall -Wextra

NASM = nasm
LD = ld

QEMU = qemu-system-i386
QEMU_FLAGS = -hda $< -boot c -audiodev pa,id=speaker -machine pcspk-audiodev=speaker

IMAGE_SIZE = 1048576

all: os.img kernel.elf

run: os.img
	$(QEMU) $(QEMU_FLAGS) -monitor stdio

debug: os.img kernel.elf
	$(QEMU) $(QEMU_FLAGS) -S -s -d guest_errors,int &
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

%.o: %.c
	$(COMPILER) $(CFLAGS) -c $< -o $@

%.oo: %.asm
	$(NASM) -o $@ -f elf32 -g $<

clean:
	rm -rf $(BOOT_OBJECTS) $(KERNEL_OBJECTS) *.img *.bin *.elf
