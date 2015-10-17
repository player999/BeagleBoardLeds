CROSS_COMPILE=arm-linux-gnueabihf-
CC=$(CROSS_COMPILE)gcc
OC=$(CROSS_COMPILE)objcopy
LD=$(CROSS_COMPILE)ld.bfd
TARGET=toggle_led
CFLAGS=-g  -Os   -ffunction-sections -fdata-sections -fno-common -ffixed-r9 -msoft-float  -D__KERNEL__ -DCONFIG_SYS_TEXT_BASE=0x80100000 -fno-builtin -ffreestanding -nostdinc -isystem /usr/lib/gcc-cross/arm-linux-gnueabihf/4.9/include -pipe  -DCONFIG_ARM -D__ARM__ -marm -mno-thumb-interwork -mabi=aapcs-linux -mword-relocations -march=armv7-a -Wall -Wstrict-prototypes -fno-stack-protector -Wno-format-nonliteral -Wno-format-security -fstack-usage -fno-toplevel-reorder
INC+= -I/home/player999/Work/beagle/u-boot4/include
INC+= -I/home/player999/Work/beagle/u-boot4/arch/arm/include
all: clean
	$(CC) $(INC) $(CFLAGS) -c ./$(TARGET).c
	$(CC) $(INC) $(CFLAGS) -c ./stubs.c
	$(LD) -r -o libstubs.o  stubs.o
	$(LD) -g -Ttext 0x80300000 -o $(TARGET) -e $(TARGET) $(TARGET).o \
		libstubs.o -L/usr/lib/gcc-cross/arm-linux-gnueabihf/4.9 -lgcc
	$(OC) -O binary $(TARGET) ./$(TARGET).bin

clean:
	rm -f *.o *.su *.bin
	rm -f ./$(TARGET).bin
	rm -f ./$(TARGET)
	
