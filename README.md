# minishell

This group project between [alexehrlich](https://github.com/alexehrlich) and [leonyannick](https://github.com/leonyannick) of the 42 core curriculium is about writing our own shell program by recreating (at least some of) the functionality of BASH.
We learned to organize a big problem in different submodules, determine interfaces between them and organize our workflow with a shared repository.

# Fuctionality

* connect multiples commands via pipes |
* use redirections and heredocs < > << >>
* builtin functions:
   * echo with option -n
   * cd
   * export
   * unset
   * env
   * exit
* working command history
* handling signals: control+D, control+C, control+\
* environmental variables
* inspecting the last exit code with $?
* quote handline

Read [minishell.pdf](https://github.com/alexehrlich/42Berlin-Core-minishell/blob/main/resources/minishell.pdf) for detailed project instruction. 

# Installation and Usage

Head to the code directory and build the project with `make` into an executable and launch it with `./minishell`.

# Project structure

The project was splitted into the submodules `Lexer/Expander`, `Parser` and `Executor`.

## Lexer/Expander

The Lexer takes a stream of bytes, which the user types into the terminal via the `readline()` function.
Through the implemented lexical analysis the bytestream is split up into different tokens of type _WORD_, 
_I_RED(<)_, _O_RED(>)_, _I_RED_HD(<<)_ and _O_RED_APP(>>)_.
The Lexer also removes whitespaces at the end, merges WORDS (hell"o" -> hello) and expands variables (e.g. $PATH).

![Workflow Lexer/Expander](https://github.com/alexehrlich/42Berlin-Core-minishell/blob/main/resources/Images/LEXER.png)

## Parser

The parser takes the linked list of tokens and generates another linked list of commands. Information about arguments, pipes, redirections and command type (BUILTIN or PATH) is extracted by the parsing algorithm and stored inside a command struct.
The Parser works as follows:


![Parsing Algorithm Flowchart](https://github.com/alexehrlich/42Berlin-Core-minishell/blob/main/resources/Images/Flowchart%20Parser.png)

The linked list of commands looks like this:


![Workflow of Parser](https://github.com/alexehrlich/42Berlin-Core-minishell/blob/main/resources/Images/PARSER.png)

## Executor

The executor takes the linked list of commands and executes them in the desired way. If there is only a single BUILTIN command (e.g. cd) called, the command gets executed in the current minishell-process. If a PATH command or piped mixed commands are called (e.g. echo  hello | grep hello) the minishell-process forks child processes to execute every command in its own child process and waits for its execution and grabs the exit code to give it back to the calling process.

![Workflow of Executor](https://github.com/alexehrlich/42Berlin-Core-minishell/blob/main/resources/Images/EXECUTOR.png)











