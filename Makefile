arch ?= x86_64
kernel := build/kernel-$(arch).bin
img := build/os-$(arch).img

linker_script := src/arch/$(arch)/linker.ld
grub_cfg := src/arch/$(arch)/grub.cfg
assembly_source_files := $(wildcard src/arch/$(arch)/*.asm)
assembly_object_files := $(patsubst src/arch/$(arch)/%.asm, \
   build/arch/$(arch)/%.o, $(assembly_source_files))

.PHONY: all clean run img

all: $(kernel)

clean:
	@rm -r build

run: $(img)
	@qemu-system-x86_64 -drive format=raw,file=$(img)

img: $(img)

$(img): $(kernel) $(grub_cfg)
	@mkdir -p build/imgfiles/boot/grub
	@cp $(kernel) build/imgfiles/boot/kernel.bin
	@cp $(grub_cfg) build/imgfiles/boot/grub
	@dd if=/dev/zero of=$(img) bs=512 count=32768
	@parted $(img) mklabel msdos
	@parted $(img) mkpart primary fat32 2048s 20720s
	@parted $(img) set 1 boot on
	@losetup /dev/loop0 $(img)
	@losetup /dev/loop1 $(img) -o 1048576
	@mkdosfs -F32 -f 2 /dev/loop1
	@mount /dev/loop1 /mnt/fatgrub
	@mkdir -p /mnt/fatgrub/boot/grub
	@mkdir -p /mnt/fatgrub/boot 
	@cp $(grub_cfg) /mnt/fatgrub/boot/grub 
	@cp $(kernel) /mnt/fatgrub/boot
	@sudo grub-install --root-directory=/mnt/fatgrub --no-floppy --modules="normal part_msdos ext2 multiboot2" /dev/loop0 -d /usr/lib/grub/i386-pc
	@umount /mnt/fatgrub
	@losetup -d /dev/loop0
	@losetup -d /dev/loop1

$(kernel): $(assembly_object_files) $(linker_script)
	@ld -n -T $(linker_script) -o $(kernel) $(assembly_object_files)

# compile assembly files
build/arch/$(arch)/%.o: src/arch/$(arch)/%.asm
	@mkdir -p $(shell dirname $@)
	@nasm -felf64 $< -o $@
