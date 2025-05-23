in one terminal
```
make && ./server
<server pid>
```
in another terminal, same directory
```
for i in {1..10}; do ./client <server pid> <long string>; echo; sleep 1; done
```
