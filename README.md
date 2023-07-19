# minishell - a 42 team project ([alexehrlich](https://github.com/alexehrlich) and [leonyannick](https://github.com/leonyannick))

## Description
This project is about writing our own shell based on bash.

Features:
- connect multiples commands via pipes `|`
- use redirections and heredocs `< > << >>`
- builtin functions:
  - echo with option `-n`
  - cd
  - export
  - unset
  - env
  - exit
- working command history
- handling signals: control+D, control+C, control+\
- environmental variables
- inspecting the last exit code with `$?`
- quote handling

Read [minishell.pdf](https://github.com/leonyannick/minishell/blob/main/minishell.pdf) for detailed project instruction. </br>

## Installation
Compile executable executing `make` inside the repository

## Usage
`./minishell` starts a interactive minshell session

exit the shell by either pressing control+D on an empty prompt or via the exit builtin function (by writing `exit`)

