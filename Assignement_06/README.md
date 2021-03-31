Get the ```next``` tag for the day:

```
git clone https://git.kernel.org/pub/scm/linux/kernel/git/torvalds/linux.git
cd linux
git remote add linux-next https://git.kernel.org/pub/scm/linux/kernel/git/next/linux-next.git
git fetch linux-next
git fetch --tags linux-next
# Thoses are not necessarely needed, it's just to be safe
git checkout master
git remote update
# list recent release tag
git tag -l "next-*" | tail
```

Source:

https://www.kernel.org/doc/man-pages/linux-next.html
