#!/bin/bash

# Ejecutar varios clientes en paralelo
./client 127.0.0.1 &
./client 127.0.0.1 &
./client 127.0.0.1 &

# Esperar a que todos los clientes terminen
wait