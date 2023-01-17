# update the Driver
scp `find $OPENWIFI_DIR/driver/ -name \*.ko` $OPENWIFI_DIR/user_space/UDP_echo_server.py $OPENWIFI_DIR/user_space/UDP_echo_client.py $OPENWIFI_DIR/user_space/connect.sh $OPENWIFI_DIR/user_space/setup.sh $OPENWIFI_DIR/user_space/update_image.sh $OPENWIFI_DIR/driver/TDMA_driver/misc_module/userapp.c $OPENWIFI_DIR/driver/TDMA_driver/TDMA_Python_app/TDMA_server.py $OPENWIFI_DIR/driver/TDMA_driver/TDMA_Python_app/TDMA_client.py $OPENWIFI_DIR/kernel_boot/boards/$BOARD_NAME/output_boot_bin/BOOT.BIN root@192.168.10.122:openwifi/

# # update the user app
# scp $OPENWIFI_DIR/driver/TDMA_driver/misc_module/userapp.c $OPENWIFI_DIR/driver/TDMA_driver/TDMA_Python_app/TDMA_server.py $OPENWIFI_DIR/driver/TDMA_driver/TDMA_Python_app/TDMA_client.py root@192.168.10.122:

# # update the FPGA image
# scp $OPENWIFI_DIR/kernel_boot/boards/$BOARD_NAME/output_boot_bin/BOOT.BIN root@192.168.10.122: