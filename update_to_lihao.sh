# update the Driver
scp `find $OPENWIFI_DIR/driver/ -name \*.ko` lihao@192.168.81.44:~/tmp

# update the FPGA image
scp $OPENWIFI_DIR/kernel_boot/boards/$BOARD_NAME/output_boot_bin/BOOT.BIN lihao@192.168.81.44:~/tmp

