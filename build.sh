#!/bin/bash
rm -rf ./out
gn gen ./out
ninja -C ./out
