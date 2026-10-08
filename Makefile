SRC_DIR ?= ./
OBJ_DIR ?= ./

SOURCES ?= src/Main.c src/graphics/ui.c src/maze/MatrixGenerator.c src/graphics/graphics.c src/graphics/text.c src/IO/input.c src/IO/switches.c src/pathfinder/BFS.c src/pathfinder/DFS.c src/pathfinder/Dijkstra.c dtekv-lib.c boot.S src/maze/Walls.c src/maze/startDestination.c

OBJECTS ?= $(addsuffix .o, $(basename $(notdir $(SOURCES))))
LINKER ?= $(SRC_DIR)/dtekv-script.lds

TOOLCHAIN ?= riscv32-unknown-elf-
CFLAGS ?= -Wall -nostdlib -O3 -mabi=ilp32 -march=rv32imzicsr -fno-builtin -I include -I .


build: clean main.bin

main.elf: 
	$(TOOLCHAIN)gcc -c $(CFLAGS) $(SOURCES)
	$(TOOLCHAIN)ld -o $@ -T $(LINKER) $(filter-out boot.o, $(OBJECTS)) softfloat.a

main.bin: main.elf
	$(TOOLCHAIN)objcopy --output-target binary $< $@
	$(TOOLCHAIN)objdump -D $< > $<.txt

clean:
	rm -f *.o *.elf *.bin *.txt

TOOL_DIR ?= ./tools
run: main.bin
	make -C $(TOOL_DIR) "FILE_TO_RUN=$(CURDIR)/$<"
