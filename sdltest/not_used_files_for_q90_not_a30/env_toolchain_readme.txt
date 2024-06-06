1) sudo mv miyoo /opt/

2) change Makefile's arm-linux-gcc 
to
/opt/miyoo/bin/arm-linux-gcc

$ file sdltest
sdltest: ELF 32-bit LSB executable, ARM, EABI5 version 1 (SYSV), dynamically linked, interpreter /lib/ld-uClibc.so.0, with debug_info, not stripped

3) 
sudo cp sdltest /media/wmt/MAIN/
sudo cp sdltest.sh /media/wmt/MAIN/
sudo cp sdltest /media/wmt/rootfs/bin/

if readonly, restart xubuntu200464_retrobsd virtualbox

4) after musl toolchain, run relocate-sdk.sh

