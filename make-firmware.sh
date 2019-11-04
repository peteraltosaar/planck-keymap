#!/bin/bash

echo "Password:"
read -s password

cp keymap.c ../qmk_firmware/keyboards/planck/keymaps/peteraltosaar/
cd ../qmk_firmware
sed -i '' 's/PW_PLACEHOLDER/'$password'/g' keyboards/planck/keymaps/peteraltosaar/keymap.c
make planck/rev5:peteraltosaar
rm keyboards/planck/keymaps/peteraltosaar/keymap.c
cd -
