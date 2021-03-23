After compiling and inserting the module with insmod, we can check the file has appeared:

```
ls /dev/fortytwo
crw------- 1 root root 10, 56 mars  23 17:13 /dev/fortytwo
```

We can read from it:
```
cat /dev/fortytwo
lubenard
```

We can also write into it, but be careful to what you send:

In the first example, lubenard does not work because 'echo' also send a hidden '\n'
```
echo "lubenard" > /dev/fortytwo
-bash: echo: erreur d'ecriture : Argument invalide
echo "wow, it works" > /dev/fortytwo
-bash: echo: erreur d'ecriture : Argument invalide
```

We can avoid this behaviour with the -n option. It now works!
```
echo -n "lubenard" > /dev/fortytwo
```
