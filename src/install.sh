#!/bin/bash
echo 'install websocketd for Linux'
echo 'if you dont have root access the just extract websocket binary to this folder and use it here'
wget -c https://github.com/joewalnes/websocketd/releases/download/v0.2.12/websocketd-0.2.12-linux_amd64.zip 
sudo unzip websocketd-0.2.12-linux_amd64.zip -d /usr/bin
