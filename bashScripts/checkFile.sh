#!/bin/bash

# Verifica que se haya pasado un parámetro
if [ $# -ne 1 ]; then
    echo "Uso: $0 <nombre_archivo_o_directorio>"
    exit 1
fi

nombre="$1"
ruta=$(pwd)
ruta_completa="$ruta/$nombre"

# Verifica si existe
if [ -e "$ruta_completa" ]; then
    if [ -f "$ruta_completa" ]; then
        echo "\"$nombre\" es un archivo."
    elif [ -d "$ruta_completa" ]; then
        cantidad=$(ls -1A "$ruta_completa" | wc -l)
        echo "\"$nombre\" es un directorio que contiene $cantidad elemento(s)."
    else
        echo "\"$nombre\" existe, pero no es ni archivo regular ni directorio."
    fi
else
    echo "\"$nombre\" no existe en la ruta actual: $ruta"
fi

