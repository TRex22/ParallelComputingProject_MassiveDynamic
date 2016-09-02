#!/bin/bash
echo 'run web-ui'
npm install
node-gyp configure
node-gyp build
node hello.js
# npm start