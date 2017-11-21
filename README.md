C++ Argument Parser
===================

This repository contains a simple C++ header / source file for parsing command
line arguments.  The syntax for adding command line arguments is as follows.

```c++
    #include "argument_parser.h"
    
    ArgumentSet args;
    args.AddFlag("help").Description("print help menu").Shorthand('h');
    args.AddPositionalArgument("output").Description("output file");
    args.AddFlag("other-flag").Description("other flag").Shorthand('f');
    args.AddNamedArgument("myarg").Description("my argument").Shorthand('m');
    
    int main(int argc, char * argv[]) {
        args.Parse(argc, argv);
        return 0;
    }
```

The program takes arguments using the following format

    ./program -hf --myarg myarg_value output_value

also,

    ./program -h -f --myarg myarg_value output_value

and

    ./program output_value

or
    
    ./program --myarg myarg_value output_value
    
etc.
