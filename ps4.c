#include "ps4.h"
#include <stdio.h>
#include <hidapi/hidapi.h>
//#include <bluetooth/bluetooth.h>  // コメントアウト
//#include <bluetooth/hci.h>        // コメントアウト
//#include <bluetooth/hci_lib.h>    // コメントアウト

#define VENDOR_ID  0x054C
#define PRODUCT_ID 0x09CC

hid_device *handle;
int is_wired = 1;  // 追加

void init_ps4() {
    if (hid_init()) {
        printf("Failed to initialize HIDAPI\n");
        return;
    }

    // Attempt to open USB device
    handle = hid_open(VENDOR_ID, PRODUCT_ID, NULL);
    if (handle) {
        printf("Opened Dualshock4 via USB\n");
    } else {
        printf("Unable to open Dualshock4 via USB, attempting Bluetooth\n");
        hid_exit();  // Cleanup before trying Bluetooth

        // Bluetooth initialization (コメントアウト)
        /*
        is_wired = 0;
        int dev_id = hci_get_route(NULL);
        int sock = hci_open_dev(dev_id);
        if (dev_id < 0 || sock < 0) {
            perror("Failed to open Bluetooth device");
            return;
        }
        // Additional Bluetooth initialization code
        */
    }
}

PS4Data get_ps4_data() {
    PS4Data data;
    unsigned char buf[64] = {0};

    if (!handle) {
        printf("Handle is null, cannot read from Dualshock4\n");
        data.x = 0;
        data.y = 0;
        return data;
    }

    int res = hid_read(handle, buf, sizeof(buf));
    if (res < 0) {
        printf("Error reading from Dualshock4: %d\n", res);
        data.x = 0;
        data.y = 0;
        return data;
    }

    // デバッグ用メッセージをコメントアウト
    /*
    printf("Raw data: ");
    for (int i = 0; i < res; i++) {
        printf("%02x ", buf[i]);
    }
    printf("\n");
    */

    // アナログスティックの値を取得
    data.x = buf[3] - 128;  // 左スティックのX軸
    data.y = buf[4] - 128;  // 左スティックのY軸

    return data;
}



void close_ps4() {
    if (handle) {
        hid_close(handle);
    }
    hid_exit();
}
