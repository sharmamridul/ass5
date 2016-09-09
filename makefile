#Var Definitions

CC = avr-gcc
OBCP = avr-objcopy 
PORT = /dev/ttyUSB0
BD = 57600 
ATMG = atmega328p
FLAGS = -F -V  
PRL = stk500v1 

NAME = part1_2
ELF = $(NAME).elf
SFILE = $(NAME).s
OBJ = $(NAME).o
HX = $(NAME).hex
CFILE = $(NAME).c
OUT = $(NAME).o

RM = rm -rf
FU = 16000000UL
AVRD = avrdude
EEPROM = .eeprom
IHX = ihex

compile = COMPILE
upload = UPLOAD
all = all

.PHONY: all
$(all): COMPILE UPLOAD


.PHONY: COMPILE 
$(compile): $(CFILE)
	$(CC) -Os -DF_CPU=$(FU) -mmcu=$(ATMG) -c -o $(OUT) $(CFILE)
	$(CC) -mmcu=$(ATMG) $(OUT) -o $(NAME)
	$(OBCP) -O $(IHX) -R $(EEPROM) $(NAME) $(HX)

.PHONY:UPLOAD
$(upload): $(HEX)
	sudo $(AVRD) -p $(ATMG) -b $(BD) -P $(PORT) -c arduino -U flash:w:$(HX) -F

.PHONY: clean

clean:
	$(RM) $(OUT) $(HX) $(NAME)