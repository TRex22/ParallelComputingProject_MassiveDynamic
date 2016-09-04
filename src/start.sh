#!/bin/bash
echo 'compile and start everything'
bash compile.sh

wesocketd --port=8080 --staticdir=web ./main.out