This is the file c formatted ans working.

This module create a device under /dev/reverse.

When we write on it:  ```echo "this is a test" > /dev/reverse```

It record our sentence.

When we read from it: ```cat /dev/reverse```

It output the sentence backward 

Example, ```this``` become ```sith```
