# SHRILL SHELL

This is a Linux shell written in C called Shrill with basic functionalities like inbuilt commands (eg. `ls` and `cd`) along with user-defined functions (eg. `clock`, `pinfo`) and normal terminal commands that are executed from within SHRILL. It has the capability to run both background and foreground processes.

## RUNNING

- run `make`

- execute by using `./SHRILL`

- type `quit` to exit the shell

## FILES
- main.c : main file which contains shell loop
- execute.c : contains execution loop, calls every function based on user command
- input.c : parses user input from command line into commands and tokens
- cd.c - changes directory
- ls.c - displays list of all files and directories 
- echo.c - echoes whatever the user typed
- pwd.c - displays present working directory
- pinfo.c - prints the process related info of your shell program or given process ID
- clock.c - displays dynamic date and time in the shell, updated based on fixed time interval
- remindme.c - reminds user with a custom message after the given number of seconds elapse