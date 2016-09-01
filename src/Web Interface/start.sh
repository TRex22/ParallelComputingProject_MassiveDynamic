#!/bin/bash
echo 'run web-ui'
npm install
node-gyp rebuild
node hello.js
# npm start