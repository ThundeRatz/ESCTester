# Name: Makefile
# Author: Daniel Nery Silva de Oliveira
# Equipe ThundeRatz de Robótica

# MCU .......... The AVR Device you compile for
# CLOCK ........ Target AVR clock rate in MHz
# PROGRAMMER ... Options to avrdude which define the hardware you use for
#                uploading to the AVR and the interface where this hardware
#                is connected.
# H/LFUSE ...... Parameters for avrdude to flash the fuses appropriately.
# EXT .......... Files extension (c or c++)

MCU        = atmega8
CLOCK      = 8
PROGRAMMER = usbasp
LFUSE      = 0xD4
HFUSE      = 0xD9
EXT        = .c

PART       = $(MCU)

######################################################################

# Tune the lines below only if you know what you are doing:

OBJECTS = $(patsubst %$(EXT),build/%.o,$(wildcard *$(EXT)))
FUSES   = -U lfuse:w:$(LFUSE):m -U hfuse:w:$(HFUSE):m
AVRDUDE = avrdude -c $(PROGRAMMER) -p $(PART)
COMPILE = avr-gcc -Wall -Os -mcall-prologues -Wextra -DF_CPU=$(CLOCK)000000 -mmcu=$(MCU) -std=c99 -fshort-enums
SIZE    = avr-size -C --mcu=$(MCU) build/main.elf

.PHONY: all clean load reload flash size fuse read help copy copy_flash copy_fuses copy_eeprom

all: build/main.hex

build/%.o: %$(EXT) Makefile | build
	@echo "Compilando "$<
	@$(COMPILE) -c $< -o $@
	@echo "Ok."

build:
	@mkdir -p build

load:
	@echo "Gravando..."
	@$(AVRDUDE) -U flash:w:build/main.hex:i
	@make size

reload: all load

size:
	@$(SIZE)

flash: load

fuse:
	@echo "Gravando fusebits."
	@echo "High Fuse: "$(HFUSE)
	@echo "Low Fuse:  "$(LFUSE)
	@$(AVRDUDE) $(FUSES)

read:
	@rm -rf read/
	@echo "Criando diretorio read/"
	@mkdir -p read/
	@echo "Diretorio read/ criado"
	@echo "Lendo flash..."
	@$(AVRDUDE) -U flash:r:read/flash.hex:i
	@echo "Flash gravado em read/flash.hex"
	@echo "Lendo lfuse..."
	@$(AVRDUDE) -U lfuse:r:read/lfuse.hex:h
	@echo "LFuse gravado em read/lfuse.bin"
	@echo "Lendo hfuse..."
	@$(AVRDUDE) -U hfuse:r:read/hfuse.hex:h
	@echo "HFuse gravado em read/hfuse.bin"
	@echo "Lendo eeprom..."
	@$(AVRDUDE) -U eeprom:r:read/eeprom.hex:i
	@echo "Eeprom gravado em read/eeprom.hex..."

copy_flash:
	@echo "Gravando flash..."
	@$(AVRDUDE) -U flash:w:read/flash.hex:i
	@echo "Flash gravado"

copy_fuses:
	@echo "Para gravar os mesmos fusebits:"
	@echo "Troque as variaveis HFUSE e LFUSE no Makefile:"
	@echo -n "LFUSE = "
	@cat read/lfuse.hex; true
	@echo -n "HFUSE = "
	@cat read/hfuse.hex; true
	@echo "E de make fuse"

copy_eeprom:
	@echo "Gravando eeprom..."
	@$(AVRDUDE) -U eeprom:r:read/eeprom.hex:i
	@echo "Eeprom gravado"

copy: copy_eeprom copy_flash copy_fuses

clean:
	@echo "Removendo arquivos..."
	@rm -rf build
	@echo "Arquivos removidos com sucesso!"

help:
	@echo "----------------------- ThunderMakefile -----------------------"
	@echo "Bem-vindo(a) ao Makefile da ThundeRatz, cheque as configuracoes"
	@echo "             atuais e mude o arquivo se necessario             "
	@echo
	@echo "Opcoes:"
	@echo "	help:    mostra essa ajuda."
	@echo "	all:     compila todos os arquivos .c nessa pasta."
	@echo "	         Tenha somente uma funcao main entre eles;"
	@echo "	load:    carrega os arquivos compilados no microcontrolador;"
	@echo "	reload:  make all && make load;"
	@echo "	fuse:    carrega os fusebits no microcontrolador (cuidado);"
	@echo "	clean:   remove os arquivos .hex .elf e .o e a pasta read/;"
	@echo "	read:    Le a memoria flash e a eeprom e guarda em flash.hex e"
	@echo "	         eeprom.hex e lfuse e hfuse em lfuse.hex e hfuse.hex na"
	@echo "	         pasta read/. Pode regravar com opções abaixo;"
	@echo
	@echo "	Cuidado com as opcoes abaixo:"
	@echo "	copy_flash:  Grava flash.hex de read/"
	@echo "	copy_eeprom: Grava eeprom.hex de read/"
	@echo "	copy_fuses:  Intrucoes como gravar fusebits"
	@echo "	copy:        Grava todos"
	@echo
	@echo "Configuracoes atuais:"
	@echo "	MCU        = "$(MCU)
	@echo "	Clock      = "$(CLOCK)"MHz"
	@echo "	Programmer = "$(PROGRAMMER)
	@echo "	Objects    = "$(OBJECTS)
	@echo "	Low Fuse   = "$(LFUSE)
	@echo "	High Fuse  = "$(HFUSE)

# file targets:
build/main.elf: $(OBJECTS) Makefile
	@echo "Compilando main.elf para "$(MCU)", mude o Makefile se necessario."
	@$(COMPILE) -o build/main.elf $(OBJECTS)

build/main.hex: build/main.elf Makefile
	@rm -f build/main.hex
	@avr-objcopy -j .text -j .data -O ihex build/main.elf build/main.hex
