I followed this tutorial

You will need to have the kernel headers to compile this module !

On debian:
```
sudo apt-get install linux-headers-$(uname -r)
```
On arch linux:
```
sudo pacman -S linux-headers
```

https://www.thegeekstuff.com/2013/07/write-linux-kernel-module/

The ```MODULE_LICENSE``` is mandatory
