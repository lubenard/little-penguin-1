```
$ ls -lha /sys/kernel/debug/fortytwo/

total 0
drwxrwxrwx  2 root root 0 mars  23 14:36 .
drwx------ 30 root root 0 mars  23 14:34 ..
-rw-r--r--  1 root root 0 mars  23 14:36 foo
-rw-rw-rw-  1 root root 0 mars  23 14:36 id
-r--r--r--  1 root root 0 mars  23 14:36 jiffies

$ cat /sys/kernel/debug/fortytwo/id
lubenard

$ cat /sys/kernel/debug/fortytwo/jiffies
4296544923

$ echo 'This is a test' > /sys/kernel/debug/fortytwo/foo
$ cat /sys/kernel/debug/fortytwo/foo
This is a test
```
