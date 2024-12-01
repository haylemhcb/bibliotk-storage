#!/bin/bash

DIR="$(dirname "$(readlink -f "${0}")")"

cd "$DIR"

./gen-library
./server-cgi-run-server&
./client-web.run


pkill -f server-cgi-run-server

