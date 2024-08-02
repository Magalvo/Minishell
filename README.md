# MiniShell

see reference/ for study materials
use 'make debug' instead of 'make re' (won't recompile libft, and adds -g flag)

## dde-maga notes:

===================================

minishell> cota << OLA
> |
>
> ""
> ' '
> '
> \\
> //
> /' }
>
> "OLA"
> OLA
==256294==
==256294== FILE DESCRIPTORS: 3 open (3 std) at exit.
==256294==
==256294== HEAP SUMMARY:
==256294==     in use at exit: 224,730 bytes in 700 blocks
==256294==   total heap usage: 1,027 allocs, 327 frees, 246,929 bytes allocated
==256294==
==256294== 2 bytes in 1 blocks are still reachable in loss record 1 of 89
==256294==    at 0x4848899: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==256294==    by 0x40BA29: itoa_loop (in /home/guest/Minishell/minishell)
==256294==    by 0x40B9DD: ft_itoa (in /home/guest/Minishell/minishell)
==256294==    by 0x4095EE: setting_value (env_aux3.c:27)
==256294==    by 0x4026DC: new_env_node (env_cmd.c:90)
==256294==    by 0x40361A: init_list (export_aux.c:100)
==256294==    by 0x4015C7: init_minishell (minishell_aux.c:50)
==256294==    by 0x40132A: minishell (minishell.c:51)
==256294==    by 0x40149E: main (minishell.c:83)
==256294==
==256294== 2 bytes in 1 blocks are still reachable in loss record 2 of 89
==256294==    at 0x4848899: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==256294==    by 0x40BA29: itoa_loop (in /home/guest/Minishell/minishell)
==256294==    by 0x40B9DD: ft_itoa (in /home/guest/Minishell/minishell)
==256294==    by 0x4095EE: setting_value (env_aux3.c:27)
==256294==    by 0x4026DC: new_env_node (env_cmd.c:90)
==256294==    by 0x40361A: init_list (export_aux.c:100)
==256294==    by 0x4015D8: init_minishell (minishell_aux.c:51)
==256294==    by 0x40132A: minishell (minishell.c:51)
==256294==    by 0x40149E: main (minishell.c:83)
==256294==
==256294== 4 bytes in 1 blocks are still reachable in loss record 5 of 89
==256294==    at 0x4848899: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==256294==    by 0x40BB6C: ft_substr (in /home/guest/Minishell/minishell)
==256294==    by 0x4068CC: parse_redir (parse_redir.c:38)
==256294==    by 0x405F38: parse_args (parse_exec.c:68)
==256294==    by 0x405C49: parse_exec (parse_exec.c:33)
==256294==    by 0x406CF4: parse_pipe (parse.c:79)
==256294==    by 0x406C96: parse_cmd (parse.c:69)
==256294==    by 0x406BA5: parse_input (parse.c:43)
==256294==    by 0x401375: minishell (minishell.c:57)
==256294==    by 0x40149E: main (minishell.c:83)
==256294==
==256294== 5 bytes in 1 blocks are still reachable in loss record 6 of 89
==256294==    at 0x4848899: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==256294==    by 0x40B7B0: ft_strdup (in /home/guest/Minishell/minishell)
==256294==    by 0x406128: expand_sw_vars (parse_prechecks.c:42)
==256294==    by 0x405ECB: parse_args (parse_exec.c:63)
==256294==    by 0x405C49: parse_exec (parse_exec.c:33)
==256294==    by 0x406CF4: parse_pipe (parse.c:79)
==256294==    by 0x406C96: parse_cmd (parse.c:69)
==256294==    by 0x406BA5: parse_input (parse.c:43)
==256294==    by 0x401375: minishell (minishell.c:57)
==256294==    by 0x40149E: main (minishell.c:83)
==256294==
==256294== 12 bytes in 1 blocks are still reachable in loss record 12 of 89
==256294==    at 0x4848899: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==256294==    by 0x40B7B0: ft_strdup (in /home/guest/Minishell/minishell)
==256294==    by 0x406268: expand_sw_tilde (parse_prechecks.c:68)
==256294==    by 0x406B57: parse_input (parse.c:37)
==256294==    by 0x401375: minishell (minishell.c:57)
==256294==    by 0x40149E: main (minishell.c:83)
==256294==
==256294== 16 bytes in 1 blocks are still reachable in loss record 16 of 89
==256294==    at 0x4848899: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==256294==    by 0x40B739: ft_calloc (in /home/guest/Minishell/minishell)
==256294==    by 0x40481D: create_dptr (aux.c:44)
==256294==    by 0x405C19: parse_exec (parse_exec.c:30)
==256294==    by 0x406CF4: parse_pipe (parse.c:79)
==256294==    by 0x406C96: parse_cmd (parse.c:69)
==256294==    by 0x406BA5: parse_input (parse.c:43)
==256294==    by 0x401375: minishell (minishell.c:57)
==256294==    by 0x40149E: main (minishell.c:83)
==256294==
==256294== 22 bytes in 1 blocks are still reachable in loss record 18 of 89
==256294==    at 0x4848899: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==256294==    by 0x40BC16: ft_strjoin (in /home/guest/Minishell/minishell)
==256294==    by 0x4057F6: cmd_heredoc (init_heredoc.c:30)
==256294==    by 0x4069AE: redir_sw (parse_redir.c:52)
==256294==    by 0x4068DF: parse_redir (parse_redir.c:38)
==256294==    by 0x405F38: parse_args (parse_exec.c:68)
==256294==    by 0x405C49: parse_exec (parse_exec.c:33)
==256294==    by 0x406CF4: parse_pipe (parse.c:79)
==256294==    by 0x406C96: parse_cmd (parse.c:69)
==256294==    by 0x406BA5: parse_input (parse.c:43)
==256294==    by 0x401375: minishell (minishell.c:57)
==256294==    by 0x40149E: main (minishell.c:83)
==256294==
==256294== 80 bytes in 1 blocks are still reachable in loss record 30 of 89
==256294==    at 0x4848899: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==256294==    by 0x40B739: ft_calloc (in /home/guest/Minishell/minishell)
==256294==    by 0x4054C6: cmd_init (init_cmd.c:19)
==256294==    by 0x4054EC: cmd_exec (init_cmd.c:27)
==256294==    by 0x405BC0: parse_exec (parse_exec.c:24)
==256294==    by 0x406CF4: parse_pipe (parse.c:79)
==256294==    by 0x406C96: parse_cmd (parse.c:69)
==256294==    by 0x406BA5: parse_input (parse.c:43)
==256294==    by 0x401375: minishell (minishell.c:57)
==256294==    by 0x40149E: main (minishell.c:83)
==256294==
==256294== 80 bytes in 1 blocks are still reachable in loss record 31 of 89
==256294==    at 0x4848899: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==256294==    by 0x40B739: ft_calloc (in /home/guest/Minishell/minishell)
==256294==    by 0x4054C6: cmd_init (init_cmd.c:19)
==256294==    by 0x40576B: cmd_heredoc (init_heredoc.c:22)
==256294==    by 0x4069AE: redir_sw (parse_redir.c:52)
==256294==    by 0x4068DF: parse_redir (parse_redir.c:38)
==256294==    by 0x405F38: parse_args (parse_exec.c:68)
==256294==    by 0x405C49: parse_exec (parse_exec.c:33)
==256294==    by 0x406CF4: parse_pipe (parse.c:79)
==256294==    by 0x406C96: parse_cmd (parse.c:69)
==256294==    by 0x406BA5: parse_input (parse.c:43)
==256294==    by 0x401375: minishell (minishell.c:57)
==256294==
==256294== 96 bytes in 1 blocks are still reachable in loss record 35 of 89
==256294==    at 0x4848899: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==256294==    by 0x40BE2D: ft_split (in /home/guest/Minishell/minishell)
==256294==    by 0x4083E3: env_paths (env_aux2.c:33)
==256294==    by 0x4015E5: init_minishell (minishell_aux.c:52)
==256294==    by 0x40132A: minishell (minishell.c:51)
==256294==    by 0x40149E: main (minishell.c:83)
==256294==
==256294== 149 bytes in 11 blocks are still reachable in loss record 36 of 89
==256294==    at 0x4848899: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==256294==    by 0x40BC16: ft_strjoin (in /home/guest/Minishell/minishell)
==256294==    by 0x4019B1: add_slash (builtins.c:27)
==256294==    by 0x40842B: env_paths (env_aux2.c:39)
==256294==    by 0x4015E5: init_minishell (minishell_aux.c:52)
==256294==    by 0x40132A: minishell (minishell.c:51)
==256294==    by 0x40149E: main (minishell.c:83)
==256294==
==256294== 520 bytes in 1 blocks are still reachable in loss record 41 of 89
==256294==    at 0x4848899: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==256294==    by 0x40B739: ft_calloc (in /home/guest/Minishell/minishell)
==256294==    by 0x40993D: create_env_array (env_aux4.c:75)
==256294==    by 0x40876E: env_convert (env_aux2.c:118)
==256294==    by 0x4015F2: init_minishell (minishell_aux.c:53)
==256294==    by 0x40132A: minishell (minishell.c:51)
==256294==    by 0x40149E: main (minishell.c:83)
==256294==
==256294== 807 bytes in 64 blocks are still reachable in loss record 45 of 89
==256294==    at 0x4848899: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==256294==    by 0x40B858: ft_strndup (in /home/guest/Minishell/minishell)
==256294==    by 0x40958C: key_dup (env_aux3.c:17)
==256294==    by 0x4026A1: new_env_node (env_cmd.c:87)
==256294==    by 0x40361A: init_list (export_aux.c:100)
==256294==    by 0x4015C7: init_minishell (minishell_aux.c:50)
==256294==    by 0x40132A: minishell (minishell.c:51)
==256294==    by 0x40149E: main (minishell.c:83)
==256294==
==256294== 807 bytes in 64 blocks are still reachable in loss record 46 of 89
==256294==    at 0x4848899: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==256294==    by 0x40B858: ft_strndup (in /home/guest/Minishell/minishell)
==256294==    by 0x40958C: key_dup (env_aux3.c:17)
==256294==    by 0x4026A1: new_env_node (env_cmd.c:87)
==256294==    by 0x40361A: init_list (export_aux.c:100)
==256294==    by 0x4015D8: init_minishell (minishell_aux.c:51)
==256294==    by 0x40132A: minishell (minishell.c:51)
==256294==    by 0x40149E: main (minishell.c:83)
==256294==
==256294== 2,048 bytes in 64 blocks are still reachable in loss record 59 of 89
==256294==    at 0x4848899: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==256294==    by 0x40B739: ft_calloc (in /home/guest/Minishell/minishell)
==256294==    by 0x40262A: new_env_node (env_cmd.c:81)
==256294==    by 0x40361A: init_list (export_aux.c:100)
==256294==    by 0x4015C7: init_minishell (minishell_aux.c:50)
==256294==    by 0x40132A: minishell (minishell.c:51)
==256294==    by 0x40149E: main (minishell.c:83)
==256294==
==256294== 2,048 bytes in 64 blocks are still reachable in loss record 60 of 89
==256294==    at 0x4848899: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==256294==    by 0x40B739: ft_calloc (in /home/guest/Minishell/minishell)
==256294==    by 0x40262A: new_env_node (env_cmd.c:81)
==256294==    by 0x40361A: init_list (export_aux.c:100)
==256294==    by 0x4015D8: init_minishell (minishell_aux.c:51)
==256294==    by 0x40132A: minishell (minishell.c:51)
==256294==    by 0x40149E: main (minishell.c:83)
==256294==
==256294== 2,878 bytes in 63 blocks are still reachable in loss record 62 of 89
==256294==    at 0x4848899: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==256294==    by 0x40B7B0: ft_strdup (in /home/guest/Minishell/minishell)
==256294==    by 0x40960B: setting_value (env_aux3.c:30)
==256294==    by 0x4026DC: new_env_node (env_cmd.c:90)
==256294==    by 0x40361A: init_list (export_aux.c:100)
==256294==    by 0x4015C7: init_minishell (minishell_aux.c:50)
==256294==    by 0x40132A: minishell (minishell.c:51)
==256294==    by 0x40149E: main (minishell.c:83)
==256294==
==256294== 2,878 bytes in 63 blocks are still reachable in loss record 63 of 89
==256294==    at 0x4848899: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==256294==    by 0x40B7B0: ft_strdup (in /home/guest/Minishell/minishell)
==256294==    by 0x40960B: setting_value (env_aux3.c:30)
==256294==    by 0x4026DC: new_env_node (env_cmd.c:90)
==256294==    by 0x40361A: init_list (export_aux.c:100)
==256294==    by 0x4015D8: init_minishell (minishell_aux.c:51)
==256294==    by 0x40132A: minishell (minishell.c:51)
==256294==    by 0x40149E: main (minishell.c:83)
==256294==
==256294== 3,751 bytes in 64 blocks are still reachable in loss record 64 of 89
==256294==    at 0x4848899: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==256294==    by 0x40B739: ft_calloc (in /home/guest/Minishell/minishell)
==256294==    by 0x4082A3: join_key_value (env_aux.c:86)
==256294==    by 0x4087C1: env_convert (env_aux2.c:123)
==256294==    by 0x4015F2: init_minishell (minishell_aux.c:53)
==256294==    by 0x40132A: minishell (minishell.c:51)
==256294==    by 0x40149E: main (minishell.c:83)
==256294==
==256294== LEAK SUMMARY:
==256294==    definitely lost: 0 bytes in 0 blocks
==256294==    indirectly lost: 0 bytes in 0 blocks
==256294==      possibly lost: 0 bytes in 0 blocks
==256294==    still reachable: 16,205 bytes in 468 blocks
==256294==         suppressed: 208,525 bytes in 232 blocks
==256294==
==256294== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
--256294--
--256294-- used_suppression:     66 leak readline readline.supp:9 suppressed: 204,407 bytes in 225 blocks
--256294-- used_suppression:      4 leak add_history readline.supp:3 suppressed: 4,118 bytes in 7 blocks
==256294==
==256294== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
cota : command not found

=====================================

ls -la | cat -e | wc -l > OUT

cat >./outfiles/outfile01 <missing >./test_files/invalid_permission
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
### NOT WORKING
./executable is the same as executable
####
echo segfault <"<<<"<<amazing
bash
echo segfault <"<<<"<<amazing
> amazing
bash: <<<: No such file or directory
minishell
echo segfault <"<<<"<<amazing
> amazing
<<<: No such file or directory
segfault                                << ops
####




works:
export +=cenas

segfault protc when argv[0] is not null but invalid
- what?!?
- select between > <  >
    < to here, mid click on prompt, enjoy.

JUST THIS NOW
./cenas.exe     should work (and it does)
&&
cenas.exe       should not work (but it does)



"		"
minishell> "            "
                 : command not found
<!-- bash is joking -->
bash: $'\t\t': command not found


just ">"
$?
minishell 1
bash 2

## ENV -i

<!-- done from here -->
export T=e E=c S=h L=o
$T$E"C"$L "" -""n

export T="s"
l$T -a
export T="|"
$T$T$T$T$T$T$T
p""''''w''''''""""""''''''''''''''''''''''''''''''''d
<| echo ok
>| echo sure

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

## Solved
minishell> exit aa bb
exit
minishell: exit : too many arguments
>> devia sair

## Solved
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
