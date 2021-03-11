Help of those:

First, we need to install the linux headers in order to compile the module.

Second thing: The filename ```99-rules-usb-kbd.rules``` is special.

We specify that we want our script loading at the end (that's why the 99 and not 01)

Do not forget to compile the module first.

Copy the rules file into ```/etc/udev/rules.d/```

You can reload the rules either by doing ```udevadm trigger```

Or, if you have a systemD linux:

```systemctl restart systemd-udevd.service```

Check if it has worked inside dmesg or for errors inside journalctl

Useful ressources:

https://makelinux.net/ldd3/chp-13-sect-4.shtml

https://www.kernel.org/doc/html/latest/driver-api/usb/writing_usb_driver.html

https://git.kernel.org/pub/scm/linux/kernel/git/stable/linux.git/tree/drivers/usb/usb-skeleton.c

https://doc.ubuntu-fr.org/udev

https://linuxconfig.org/tutorial-on-how-to-write-basic-udev-rules-in-linux#h6-how-rules-are-organized
