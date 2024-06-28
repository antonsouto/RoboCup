#!/bin/bash

# Ejecutable
EJECUTABLE="./build/player"

# Valor de texto que deseas pasar como parámetro al main
EquipoA="VodkaJuniorsA"
EquipoB="VodkaJuniorsB"
Portero="goalie"
Jugador="jugador"

# Bucle para abrir 10 terminales y ejecutar main en cada una
for ((i=1; i<=11; i++))
do
    if [ $i -eq 1 ]; then
        # En la primera ejecución, ejecutar el comando con el portero
        xterm -hold -e "$EJECUTABLE $EquipoA $Portero" &
        xterm -hold -e "$EJECUTABLE $EquipoB $Portero" &
    else
        # Para las demás ejecuciones, ejecutar el comando sin el portero
        xterm -hold -e "$EJECUTABLE $EquipoA $Jugador" &
        xterm -hold -e "$EJECUTABLE $EquipoB $Jugador" &
    fi
done
