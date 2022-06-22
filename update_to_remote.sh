# update the Driver
scp `find $OPENWIFI_DIR/driver/ -name \*.ko` lihao@192.168.81.44:~/tmp

# update the user app
scp $OPENWIFI_DIR/driver/TDMA_driver/misc_module/userapp.c $OPENWIFI_DIR/driver/TDMA_driver/TDMA_Python_app/TDMA_server.py $OPENWIFI_DIR/driver/TDMA_driver/TDMA_Python_app/TDMA_client.py lihao@192.168.81.44:~/tmp

# update the FPGA image
scp $OPENWIFI_DIR/kernel_boot/boards/$BOARD_NAME/output_boot_bin/BOOT.BIN lihao@192.168.81.44:~/tmp

