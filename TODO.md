# TODO LIST

### History
1 read from input after CR
2 store somewhere
3 use it on arrow up / down
4 history cmd? is builtin? if not what does it read.
5 STYLE POINTS: up / down arrow autocomplete

### Parse quotes / dquotes
1 read input
2 ..
3 profit

### FREEE
1 valgrind is your best friend
2 go first for leaks inside loops, see what breaks

### Custom prompt
1 yes / no ?

### Expander
1 normalize / refactor / adapt get_env_val
2 read and replace; this will cause aditional leaks.
3 replace on the fly; potential for seg faults.

### Hidden env vars
1 where are they
2 how to acess them to use on expander

### WEIRD cmds
1 echo $$ // what is this
2 echo $?	// error level, no
3 echo $0	// path to elf

### ERROR LEVEL / NO
1 replace wait with waitpid
2 return error level to perror (?)
3 read it and print it when cmd $?
