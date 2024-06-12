#!/bin/bash


#Ejecutable
EJECUTABLE="./build/player"

# Valor de texto que deseas pasar como parametro al main
EquipoA="VodkaJuniorsA"
EquipoB="VodkaJuniorsB"
Portero="goalie"

# Bucle para abrir 10 terminales y ejecutar main en cada una
for ((i=1; i<=3; i++))
do
    if [ $i -eq 1 ]; then
        # En la primera ejecución, ejecutar el comando con el portero
        gnome-terminal -- bash -c "$EJECUTABLE $EquipoA $Portero; exec bash"
        gnome-terminal -- bash -c "$EJECUTABLE $EquipoB $Portero; exec bash"
    else
        # Para las demás ejecuciones, ejecutar el comando sin el portero
        gnome-terminal -- bash -c "$EJECUTABLE $EquipoA; exec bash"
        gnome-terminal -- bash -c "$EJECUTABLE $EquipoB; exec bash"
    fi
done


