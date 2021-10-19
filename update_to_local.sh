# update the Driver
scp `find $OPENWIFI_DIR/driver/ -name \*.ko` root@192.168.10.122:openwifi/

# update the FPGA image
scp $OPENWIFI_DIR/kernel_boot/boards/$BOARD_NAME/output_boot_bin/BOOT.BIN root@192.168.10.122:


