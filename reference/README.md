# minishell reference

open book-riscv-rev3.pdf and search for shell,
see code onj github or reference/xv6-riscv


# POSIX.1-2017
defines a standard operating system interface and environment, including   
a command interpreter (or "shell"), and common utility programs...   

Shell Command Language   
https://pubs.opengroup.org/onlinepubs/9699919799.2018edition/nframe.html   
(Select a volume >> Shell & Utilities)   
   
sh - shell, the standard command language interpreter   
https://pubs.opengroup.org/onlinepubs/9699919799.2018edition/utilities/sh.html#tag_20_117   
   
   
# Online Books

Shells also provide a small set of built-in commands (builtins) implementing functionality   
impossible or inconvenient to obtain via separate utilities.   
For example, cd, break, continue, and exec cannot be implemented outside   
of the shell because they directly manipulate the shell itself.   
The history, getopts, kill, or pwd builtins, among others, could be implemented   
in separate utilities, but they are more convenient to use as builtin commands...   
   
Bash Reference Manual   
https://www.gnu.org/savannah-checkouts/gnu/bash/manual/bash.html   
   
   
# From 42 docs (that's all there is)   
   
minishell   
   
MiniShell will introduce you to the world of shells, which provide a convenient   
text interface to interact with your system. Shells might seem very easy   
to understand but have very specific and defined behaviour in almost every   
single case, most of which will need to be handled properly.   
   
### Prerequisites   
   
Your shell needs to do a bunch of stuff, so just make sure you don't do the following stuff:   
   
    Have very spaghetti code which makes adding stuff in the future very hard,   
	as doing it properly will make it easier to do projects like 21sh and 42sh;   
    Wildcard and priority support will take you another month at the least,   
	if you want to do them, make sure you have the according amount of time to do them;   
    Do not leak memory and leak file descriptors (also not in your child processes   
	on command execution);   
    Your shell must not crash in any scenario, its a shell, the only possible interaction   
	 you have with your OS, dont let it crash as then you shall be doomed.   
   
Getting started   

#### There is a github repository that obeys the order of proceedings pretty nicely:   
	https://github.com/Swoorup/mysh   
    Please make sure to do a lexer -> parser -> expander -> executor   
	to make your life easier.   
	Here is a solid start. (PDF: Chapter5-WritingYourOwnShell)   
    Make sure that you understand the shell syntax (POSIX link above)   
