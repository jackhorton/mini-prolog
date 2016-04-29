# mini-prolog

### Build instructions
```
make
```

This places an executable in ./bin/prolog that reads from stdin and takes no command line arguments. 

### Features
This interpreter currently only implements basic fact (`apple.`) and relation (`likes(mary, john).`) parsing. It will happily parse and try to execute rules, but the execution context does not flow through the program correctly, so false outputs will be produced. External definition loading, `is`, and other advanced features are not currently implemented.
