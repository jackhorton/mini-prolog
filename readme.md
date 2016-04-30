# mini-prolog

### Build instructions
```
make
```

This places an executable in ./bin/prolog that reads from stdin and takes no command line arguments. 

### Features
This interpreter currently implements basic fact (`apple.`), relation (`likes(mary, john).`), and rule (`parent(Child1, Child2, Parent) :- child(Child1, Parent), child(Child2, Parent).`) parsing. External definition loading, `is`, and other advanced features are not currently implemented.
