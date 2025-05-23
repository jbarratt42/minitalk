in one terminal
```
make && ./server
<server pid>
```
in another terminal, same directory
```
while true; do ./client <server pid> <long string>; sleep 1; done
```
