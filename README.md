# MiniShell

see reference/ for study materials   
use 'make debug' instead of 'make re' (won't recompile libft, and adds -g flag)   
   
   
## cjoao-de notes:
  
  
## dde-maga notes:
  
  
## BUILTINS
export TEST+=100
export TEST+=100  
    expected "100100"

export test=42 | echo 99
99
export: command not found  // nao devia aparecer

exit ""
exit
bash: exit: : numeric argument required
minishell just exits

exit 1 2
exit
bash: exit: too many arguments // nao da exit
minishell: nao da erro e faz exit

exit A 2 3
exit
bash: exit: A: numeric argument required
minishell: exit : too many arguments

echo "         |       "  | echo maybe          // or
echo "|"  | echo maybe                          // or
echo '|'  | echo maybe
maybe
echo $?
bash: 0
minishell: 141

cd --
minishell: cd: No such file or directory


## mixed   //DUNNO
<| echo ok
minishell>
 syntax error: unexpected token
'| echo ok' not parsed, double check parser
bash: syntax error near unexpected token `|'
echo $?
MS: 1
bash: 2



## segfault WIP
/bin/echo '$USER' "$USER" "text  ' text"

## parsing not working
cat << $USER
why
not
$USER  

export T=">>"
$T lol
bash: >>: command not found
minishell: creates lol file

cat << "$USER"
why
not
$USER

cat << "$US"E"R"
because
we
love
bash
$USER

export T="|"
minishell> $T$T$T$T$T$T$T
minishell> echo $T$T$T$T$T$T$T
bash: |||||||: command not found

export T="echo segfault | grep segfault"
minishell> echo $T
bash: echo segfault | grep segfault
ms: grep segfault: command not found

 '''''''''''''''' echo ok
bash: : command not found
minishell: just new prompt

>| echo sure
bash: sure: command not found
MS:syntax error: unexpected token
'| echo sure' not parsed, double check parser



### VSCODE
disable 42 Header extension for this workspace   
    (select extension, click the down arrow next to disable, select workspace)   
Add this line to your settings.json file, to prevent markdown files losing format.   
"[markdown]": {   
    "files.trimTrailingWhitespace": false   
}  
