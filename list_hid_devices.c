#include <stdio.h>
#include <hidapi/hidapi.h>

int main() {
    if (hid_init()) {
        printf("Failed to initialize HIDAPI\n");
        return -1;
    }

    struct hid_device_info *devs, *cur_dev;
    devs = hid_enumerate(0x0, 0x0);
    cur_dev = devs;
    while (cur_dev) {
        printf("Vendor ID: %04hx, Product ID: %04hx, Path: %s\n", 
               cur_dev->vendor_id, cur_dev->product_id, cur_dev->path);
        cur_dev = cur_dev->next;
    }
    hid_free_enumeration(devs);
    hid_exit();

    return 0;
}