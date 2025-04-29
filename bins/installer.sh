#!/bin/bash

# Dirección del dispositivo embebido
TARGET_USER=root
TARGET_HOST=192.168.100.222
TARGET_DIR=/usr/bin

# Archivos a copiar
BINARIES=("signal_verifier" "signal_sender" "photo")
LOCAL_WEBSERVER_DIR=webserver

# Ruta local a los binarios
LOCAL_BIN_DIR=build/bin

# Copiar cada binario al dispositivo
for BIN in "${BINARIES[@]}"; do
    echo "Subiendo $BIN..."
    scp -O "$LOCAL_BIN_DIR/$BIN" "$TARGET_USER@$TARGET_HOST:$TARGET_DIR"
done


echo "🌐 Subiendo archivos del servidor web a $WEBSERVER_TARGET_DIR..."
scp -O -r "$LOCAL_WEBSERVER_DIR"/* "$TARGET_USER@$TARGET_HOST:$WEBSERVER_TARGET_DIR"

echo "Despliegue completado en $TARGET_HOST:$TARGET_DIR"

