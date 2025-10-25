IMAGE_SIZE = 1048576

all: run

run: os.img
	qemu-system-x86_64 -hda $< -boot c -monitor stdio

debug: os.img kernel.elf
	qemu-system-x86_64 -S -s -hda $< -boot c -d guest_errors,int &
	gdb -ex "target remote localhost:1234" -ex "symbol-file kernel/kernel.elf"

os.img: boot/boot.bin kernel/kernel.bin
	cat $^ > $@
	fallocate -l $(IMAGE_SIZE) $@

boot/boot.bin:
	$(MAKE) -C boot boot.bin

kernel/kernel.bin:
	$(MAKE) -C kernel kernel.bin

kernel/kernel.elf:
	$(MAKE) -C kernel kernel.elf

clean:
	$(MAKE) -C boot clean
	$(MAKE) -C kernel clean
	rm -rf *.img
