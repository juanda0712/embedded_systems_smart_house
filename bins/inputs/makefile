# Variables de entorno
CC = arm-poky-linux-gnueabi-gcc --sysroot=$(SYSROOT)
SYSROOT = /opt/poky/5.0.8/sysroots/cortexa7t2hf-neon-vfpv4-poky-linux-gnueabi

# Opciones de compilador
CFLAGS = -Wall \
         -I$(SYSROOT)/usr/include \
         -mthumb -mfpu=neon-vfpv4 -mfloat-abi=hard -mcpu=cortex-a7 \
         -fstack-protector-strong -O2 -D_FORTIFY_SOURCE=2 \
         -Wformat -Wformat-security -Werror=format-security \
         -D_TIME_BITS=64 -D_FILE_OFFSET_BITS=64

# Opciones de linker
LDFLAGS = -L$(SYSROOT)/usr/lib -L$(SYSROOT)/lib -lgpiod

# Rutas de proyecto
SRC_DIR = src
BIN_DIR = bin
INCLUDE_DIR = include

SRC = $(wildcard $(SRC_DIR)/*.c)
TARGET = $(BIN_DIR)/signal_verifier

# Regla principal
all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -I$(INCLUDE_DIR) $^ -o $@ $(LDFLAGS)

# Limpieza
clean:
	rm -f $(BIN_DIR)/*

.PHONY: all clean

