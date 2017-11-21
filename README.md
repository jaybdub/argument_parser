C++ Argument Parser
===================

This repository contains a simple C++ header / source file for parsing command
line arguments.  The syntax for adding command line arguments is as follows.

    ArgumentSet args;

    args.Add(new Flag("help", "print help for this program", 'h'));
    args.Add(new Flag("other-flag", "set some other flag", 'f'));
    args.Add(new PositionalArgument("output", "the output file", 'o'));
    args.Add(new NamedArgument("myarg", "my optional named argument");
    args.Parse(argc, argv);

    
