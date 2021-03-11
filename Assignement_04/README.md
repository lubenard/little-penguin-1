Help of those:

https://makelinux.net/ldd3/chp-13-sect-4.shtml

https://www.kernel.org/doc/html/latest/driver-api/usb/writing_usb_driver.html

https://git.kernel.org/pub/scm/linux/kernel/git/stable/linux.git/tree/drivers/usb/usb-skeleton.c

https://doc.ubuntu-fr.org/udev

Do not forget to compile the module first.

You can trigger the udev rule with udevadm trigger <OPTIONS>

Check if it has worked inside dmesg or for errors inside journalctl
