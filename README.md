# MiniShell

see reference/ for study materials   
use 'make debug' instead of 'make re' (won't recompile libft, and adds -g flag)   
   
## dde-maga notes:
echo <"./test_files/infile_big" | cat <"./test_files/infile"

minishell> echo <"./expa" | cat <"vina"
type PIPE, 
LEFT leaf, 
        type REDIR < RDONLY, 
        FILE: ./expa 
                type EXEC, args: 
                echo
RIGHT leaf, 
        type REDIR < RDONLY, 
        FILE: vina 
                type EXEC, args: 
                cat


## cjoao-de notes:
  
<!-- export T="echo segfault | grep segfault"
 $T  
bash:
segfault | grep segfault
>> executa o echo
minishell> 
    echo segfault | grep segfault: command not found
>> nao executa o echo, parse nao e refeito -->


'''''''''''''''' echo ok
ok
minishell> $?
0: command not found
>> BNF //1st arg vazio, devia parar ai, execve esta a saltar argv[0]?
type EXEC, args: 

echo
ok
bash: : command not found
bash-5.2$ $?
bash: 127: command not found


<!-- <| echo ok
bash: syntax error near unexpected token `|'
bash-5.2$ $?
bash: 2: command not found

>| echo sure
syntax error: unexpected token
>> devia ser command not found. esta a parar no parser......
minishell> $?
1: command not found
bash: sure: command not found
bash-5.2$ $?
bash: 127: command not found
>> >> clober, not implemented -->

 $EMPTY
>> newline
""
command not found
>> tem de devolver um non-printable


ls | cat << stop | ls -la | cat << stop1 | ls | cat << stop2 | ls -la > > out | cat << stop3
bash: syntax error near unexpected token `>'                            ^
bash-5.2$ $?
bash: 2: command not found
minishell executa ate ao stop2, so depois da erro
minishell> $?
minishell> 0: command not found


echo segfault <"<<<"<<amazing
> .
> amazing
<<<: No such file or directory
segfault

echo segfault <"<<<"<<amazing
> .
> amazing
bash: <<<: No such file or directory

<!-- 
minishell> echo seg <> echo seg
syntax error: unexpected token
bash$ echo seg <> echo seg
seg seg
>> The redirection operator. [ n ]<> word. causes the file whose name is the expansion of word to be opened for both reading and writing on file descriptor n , or on file descriptor 0 if n is not specified. If the file does not exist, it is created.


echo <<< echo seegf
syntax error: unexpected token
bash
echo <<< echo seegf
seegf
>> Here Strings -->


/*
export TEST+=100
export TEST+=100  
    expected "100100"
*/

minishell> export TEST=100

minishell> export TEST+=100
minishell: export: `': not a valid identifier
export -TEST=123
minishell: export: `': not a valid identifier
>> msg de erro antiga.

minishell> exit aa bb
exit
minishell: exit : too many arguments
>> devia sair

env what
minishell> lista o env
bash>   env: ‘what’: No such file or directory

## Solved
unset -TEST
>> a PATH desaparece


## testes que falham mas devem ser ignorados
## SAFE TO IGNORE (TM)
unset -TEST
bash: unset: -T: invalid option
unset: usage: unset [-f] [-v] [-n] [name ...]
>> ignorar, nao se tem de implementar options

unset TES;T
>> ignorar, nao se tem de implementar ';', erro de syntax

cd --
>> ignorar, cd with only a relative or absolute path


### VSCODE
disable 42 Header extension for this workspace   
    (select extension, click the down arrow next to disable, select workspace)   
Add this line to your settings.json file, to prevent markdown files losing format.   
"[markdown]": {   
    "files.trimTrailingWhitespace": false   
}  
