The first step is to create a copy of the Makefile

```
cp linux-5.12-rc1/Makefile .
```

Then, we modify the EXTRAVERSION field to be compliant with the subject

```
diff -u linux-5.12-rc1/Makefile Makefile > Makefile.patch
```

Then, just in case, we backup the original Makefile, and apply the patch

```
cp linux-5.12-rc1/Makefile linux-5.12-rc1/Makefile.old
cd linux-5.12-rc1
patch < ../Makefile.patch
```

From there, check the patch has been applied correctly:

```
cat Makefile | grep EXTRAVERSION
```

Should return

```
EXTRAVERSION = -thor_kernel
```

Then, recompile the kernel, install it, and reboot
