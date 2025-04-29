#!/bin/bash

# Dirección del dispositivo embebido
TARGET_USER=root
TARGET_HOST=192.168.100.222
TARGET_DIR=/usr/bin
TARGET_LIB=/usr/lib

# Archivos a copiar
BINARIES=("signal_verifier" "signal_sender" "photo")
LIBRARIES=("libsignal_sender_lib.so" "libsignal_verifier_lib.so")
LOCAL_WEBSERVER_DIR=webserver

# Ruta local a los binarios
LOCAL_BIN_DIR=build/bin

LOCAL_LIB_DIR=build/lib

# Copiar cada binario al dispositivo
for BIN in "${BINARIES[@]}"; do
    echo "Subiendo $BIN..."
    scp -O "$LOCAL_BIN_DIR/$BIN" "$TARGET_USER@$TARGET_HOST:$TARGET_DIR"
done

# Copiar las bibliotecas
for LIB in "${LIBRARIES[@]}"; do
    echo "Subiendo biblioteca $LIB..."
    scp -O "$LOCAL_LIB_DIR/$LIB" "$TARGET_USER@$TARGET_HOST:$TARGET_LIB_DIR"
done


echo "🌐 Subiendo archivos del servidor web a $WEBSERVER_TARGET_DIR..."
scp -O -r "$LOCAL_WEBSERVER_DIR"/* "$TARGET_USER@$TARGET_HOST:$WEBSERVER_TARGET_DIR"

echo "Despliegue completado en $TARGET_HOST:$TARGET_DIR"

