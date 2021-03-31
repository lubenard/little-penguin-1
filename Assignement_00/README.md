First, i installed a debian VM, with no UI.

Then, i installed git:

```
apt install git make gcc libncurses-dev flex bison libssl-dev libelf-dev
```

Then cloned the Torvald's git repo:

```
wget https://git.kernel.org/pub/scm/linux/kernel/git/torvalds/linux.git/snapshot/linux-5.12-rc1.tar.gz
```

Warning: This version of the kernel does not exist anymore, see [here](https://www.generation-nt.com/linux-rc1-bug-swap-linus-torvalds-actualite-1986065.html) and [here](https://lkml.org/lkml/2021/3/3/1332) why

Extract it:

```
tar -xvf linux-5.12-rc1.tar.gz
cd linux-5.12-rc1
```

and created .conf file:

```
make menuconfig
```

From there, you can enable the CONFIG_LOCALVERSION_AUTO option:

```
GENERAL SETUP -> Automatically append version version infornation to the version string
```

Save the file to .config

We can check the option has been checked using grep

```
cat .config | grep "CONFIG_LOCALVERSION_AUTO"
```

We should get this line:

```
CONFIG_LOCALVERSION_AUTO=y
```

We can compile the kernel:

WARNING: Before compiling, assure you have at least 20Gb free on your disk

```
make -j8
```

If during compiling process you encounter a signature error, you can comment 

```
CONFIG_SYSTEM_TRUSTED_KEY
CONFIG_MODULE_SIG_KEY
```

in the .config file, then relaunch compilation

Then:

```
make modules
make modules_install
make install
reboot
```

Congrats ! You have booted on your new kernel !

You can now copy your .config file and /var/log/kern.log file
