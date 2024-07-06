# MiniShell

see reference/ for study materials   
use 'make debug' instead of 'make re' (won't recompile libft, and adds -g flag)   
   
   
## cjoao-de notes:
  alteracao grande no parsing das vars, 122/146 de novo.
  mas os erros de expansao quase todos fixed.
  nao sei que fazer com este teste, se calhar nada...
  
export T="echo segfault | grep segfault"
$T
bash: 
    segfault | grep segfault
minishell> 
    echo segfault | grep segfault: command not found
como e que o echo no bash desaparece????

## dde-maga notes:
  
//WIP
## BUILTINS
export TEST+=100
export TEST+=100  
    expected "100100"

## DONE
export test=42 | echo 99
99
export: command not found  // nao devia aparecer


## DONE
exit ""
exit
bash: exit: : numeric argument required
minishell just exits

## DONE
exit 1 2
exit
bash: exit: too many arguments // nao da exit
minishell: nao da erro e faz exit

## DONE
exit A 2 3
exit
bash: exit: A: numeric argument required
minishell: exit : too many arguments

## DONE
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
## DONE
<| echo ok
minishell>
 syntax error: unexpected token
'| echo ok' not parsed, double check parser
bash: syntax error near unexpected token `|'
echo $?
MS: 1
bash: 2

## SEGFAULT
    >> '$USER'
    segfault em ft_strcmp l70
    update_key l51
    export_update l56
    updating_cmds
    exec_redir
    exec_from_ast_recursive
    exec_from_ast
>> SEGFAULT


## parsing not working

 '''''''''''''''' echo ok
 echo ok
bash: : command not found
minishell: prints first arg of PATH. WTF?


### VSCODE
disable 42 Header extension for this workspace   
    (select extension, click the down arrow next to disable, select workspace)   
Add this line to your settings.json file, to prevent markdown files losing format.   
"[markdown]": {   
    "files.trimTrailingWhitespace": false   
}  
