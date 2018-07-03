#!/bin/bash

cp keymap.c ../qmk_firmware/keyboards/planck/keymaps/peteraltosaar/
cd ../qmk_firmware
make planck/rev5:peteraltosaar
cd -
