#!/bin/bash
echo 'compile and start everything'
bash compile.sh

websocketd --port=8080 --staticdir=web ./main.out webmode