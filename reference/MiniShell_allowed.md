# minishell allowed functions

`printf`, `malloc`, `free`, `write`, `access`, `open`, `read`
`close`, `fork`, `unlink`, `execve`, `dup`, `dup2`, `pipe`, `perror`

___
### with descriptions </br></br>


``` C
char *readline(const char *prompt);
```
- Parameters: 
```prompt``` - A string to be written as a prompt before the line is read.
- Description: Reads a line from the terminal and returns it. The line returned has the final newline removed, so you only get the text entered by the user.

``` C
void rl_clear_history(void);
```
- Parameters: None
- Description: Clears the history list by freeing all the memory associated with it.

``` C
int rl_on_new_line(void);
```
- Parameters: None
- Description: Informs the readline library that the cursor is on a new line, which is useful when you want to change the line and redraw the prompt at a new screen location.

``` C
int rl_replace_line(const char *text, int clear_undo);
```
- Parameters: 
```text``` - The text to replace the line with.
```clear_undo``` - If non-zero, the undo list is cleared.
- Description: Replaces the contents of rl_line_buffer with text.

``` C
void rl_redisplay(void);
```
- Parameters: None
- Description: This function redraws the readline line, maintaining the current cursor position. It's useful when you've changed some of the text being edited and want to update the screen to reflect the changes.

``` C
void add_history(const char *line);
```
- Parameters: 
`line` - A string to be added to the history list.
- Description: Adds a line to the history list, copying the string.

``` C
pid_t wait(int *wstatus);
```
- Parameters:
 `wstatus` - A pointer to an integer where status information is stored.
- Description: Suspends the calling process until one of its child processes terminates. The exit status of the terminated child is stored in the location pointed to by `wstatus`.

``` C
pid_t waitpid(pid_t pid, int *wstatus, int options);
```
- Parameters:
`pid` - The process ID of the child process.
`wstatus` - A pointer to an integer where status information is stored.
`options` - Options that control the behavior of `waitpid`.
- Description: Suspends the calling process until a specific child process terminates. It also provides more control than `wait` over which child state changes will cause the call to return.

``` C 
pid_t wait3(int *wstatus, int options, struct rusage *rusage);
```
- Parameters:
`wstatus` - A pointer to an integer where status information is stored.
`options` - Options that control the behavior of `wait3`.
`rusage` - A pointer to a `struct rusage` where resource usage information about the child is stored.
- Description: Suspends the calling process until a child process terminates, while also providing resource usage information about the child. Similar to `waitpid`, but also returns resource usage of the child in `rusage`.

``` C
pid_t wait4(pid_t pid, int *wstatus, int options, struct rusage *rusage);
```
- Parameters:
`pid` - The process ID of the child process.
`wstatus` - A pointer to an integer where status information is stored.
`options` - Options that control the behavior of `wait4`.
`rusage` - A pointer to a `struct rusage` where resource usage information about the child is stored.
- Description: Suspends the calling process until a specific child process terminates. It also provides more control than `wait` over which child state changes will cause the call to return, and returns resource usage of the child in `rusage`.


``` C
void (*signal(int sig, void (*func)(int)))(int);
```
- Parameters:
`sig` - The signal number.
`func` - A function to be called when the signal occurs.
- Description: Sets a function to handle signal events. When a signal `sig` is raised, the function `func` is called. If `func` is `SIG_IGN`, the signal is ignored. If `func` is `SIG_DFL`, the default action associated with the signal is invoked.


``` C
int sigaction(int signum, const struct sigaction *act, struct sigaction *oldact);
```
- Parameters:
`signum` - The signal number.
`act` - A pointer to a `struct sigaction` which specifies the action to be associated with signum.
`oldact` - A pointer to a `struct sigaction` where the previous action associated with signum is stored.
- Description: Allows the calling process to examine and/or specify the action to be associated with a specific signal. The `act` parameter specifies the new action, and `oldact` returns the previous action if it's not NULL.


``` C
int sigemptyset(sigset_t *set);
```
- Parameters:
`set` - A pointer to a signal set to be initialized.
- Description: Initializes the signal set pointed to by `set` to empty, with all signals excluded from the set. It's used to clear a signal set of all signals.


```C
int sigaddset(sigset_t *set, int signum);
```
- Parameters:
`set` - A pointer to a signal set.
`signum` - The signal number to be added to the set.
- Description: Adds a specified signal `signum` to the signal set pointed to by `set`. It's used when you want to modify a signal set to include a specific signal.


``` C
int kill(pid_t pid, int sig);
```
- Parameters:
`pid` - The process ID of the target process.
`sig` - The signal number to be sent.
- Description: Sends the signal `sig` to the process specified by `pid`. If `pid` is 0, `kill` sends the signal to every process in the process group of the calling process. If `pid` is -1, `kill` sends the signal to every process for which the calling process has permission to send signals, except for process 1 (init), but see below. If `pid` is less than -1, kill sends the signal to every process in the process group `-pid`. If sig is 0, then no signal is sent, but error checking is still performed.


``` C
void exit(int status);
```
- Parameters:
`status` - The exit status that is returned to the parent process.
- Description: Terminates the calling process and returns the exit status to the parent process. The value of `status` is used to indicate the exit status of the process.


getcwd
``` C
char *getcwd(char *buf, size_t size);
```
- Parameters:
`buf` - A pointer to a buffer where the current working directory string will be placed.
`size` - The size of the buffer pointed to by `buf`.
- Description: Gets the current working directory of the process and stores it in the buffer pointed to by `buf`. The size of the buffer is specified by `size`. If the length of the absolute pathname of the current working directory, including the terminating null byte, exceeds `size` bytes, NULL is returned, and `errno` is set to `ERANGE`.


``` C
int chdir(const char *path);
```
- Parameters:
`path` - A string that specifies the path to the new working directory.
- Description: Changes the current working directory of the calling process to the directory specified in `path`. The new working directory is used for resolving relative file paths in subsequent commands.


``` C
int stat(const char *pathname, struct stat *statbuf);
```
- Parameters:
`pathname` - A string that specifies the path to the file.
`statbuf` - A pointer to a `struct stat` where the file information is stored.
- Description: Retrieves the status of the file pointed to by `pathname` and fills in the `struct stat` pointed to by `statbuf`. The `struct stat` includes information such as file size, creation time, access permissions, etc.


``` C
int lstat(const char *pathname, struct stat *statbuf);
```
- Parameters:
`pathname` - A string that specifies the path to the file or symbolic link.
`statbuf` - A pointer to a `struct stat` where the file or symbolic link information is stored.
- Description: Similar to `stat`, but when `pathname` is a symbolic link, then it returns information about the link itself, not the file that it refers to. It's useful when you want to retrieve information about a symbolic link itself.


``` C
int fstat(int fd, struct stat *statbuf);
```
- Parameters:
`fd` - A file descriptor of an open file.
`statbuf` - A pointer to a `struct stat` where the file information is stored.
- Description: Retrieves the status of the file that is open on the file descriptor `fd`, and fills in the `struct stat` pointed to by `statbuf`. The `struct stat` includes information such as file size, creation time, access permissions, etc.


``` C
DIR *opendir(const char *name);
```
- Parameters:
`name` - A string that specifies the path to the directory.
- Description: Opens a directory stream corresponding to the directory name, and returns a pointer to the directory stream. The stream is positioned at the first entry in the directory.


``` C
struct dirent *readdir(DIR *dirp);
```
- Parameters:
`dirp` - A pointer to a directory stream.
- Description: Returns a pointer to a `dirent` structure representing the next directory entry in the directory stream pointed to by `dirp`. It returns NULL on reaching the end of the directory stream or if an error occurred.


``` C
int closedir(DIR *dirp);
```
- Parameters:
`dirp` - A pointer to an open directory stream.
- Description: Closes the directory stream associated with `dirp`. A successful call to `closedir` also closes the underlying file descriptor associated with `dirp`. The directory stream descriptor `dirp` is not available after this call.


``` C
char *strerror(int errnum);
```
- Parameters:
`errnum` - An error number, usually retrieved from `errno`.
- Description: Returns a pointer to a string that describes the error code passed in the argument `errnum`. The string is static and should not be modified or freed.


``` C
int isatty(int fd);
```
- Parameters:
`fd` - A file descriptor.
- Description: Checks if the file descriptor `fd` is associated with a terminal device. Returns 1 if `fd` is an open file descriptor referring to a terminal; otherwise 0 is returned, and `errno` is set to indicate the error.


``` C
char *ttyname(int fd);
```
- Parameters:
`fd` - A file descriptor.
- Description: Returns a pointer to a string that contains the null-terminated pathname of the terminal device that is open on the file descriptor `fd`. The string is static and may be overwritten by subsequent calls to `ttyname` or `ttyname_r`.


``` C
int ttyslot(void);
```
- Parameters: None
- Description: Returns the index of the current process's controlling terminal in the system's list of terminals (tty). It's typically used in system programs that manage multiple terminal lines. If the current process does not have a controlling terminal, `ttyslot` returns 0.


``` C
int ioctl(int fd, unsigned long request, ...);
```
- Parameters:
`fd` - A file descriptor.
`request` - A device-dependent request code.
`...` - Additional arguments, depending on `request`.
= Description: Performs a generic I/O operation on `fd`. The operation is device specific and is determined by `request`. Additional arguments may be required based on the value of `request`. It's typically used for device-specific operations (e.g., setting terminal parameters in the case of a terminal device) where no standard interface exists.


``` C
char *getenv(const char *name);
```
- Parameters:
```name``` - A string that specifies the name of the environment variable.
- Description: Returns a pointer to a string that is the value of the environment variable `name`. If the specified environment variable does not exist, the function returns NULL. The string returned by `getenv` is static and should not be modified or freed.


``` C
int tcsetattr(int fd, int optional_actions, const struct termios *termios_p);
```
- Parameters:
`fd` - A file descriptor that refers to a terminal.
`optional_actions` - Specifies when the changes take effect. This can be `TCSANOW` (change immediately), `TCSADRAIN` (change after all output has been written), or `TCSAFLUSH` (change after all output has been written and discard any input that has not been read).
`termios_p` - A pointer to a `struct termios` that contains the new terminal I/O settings.
- Description: Sets the terminal attributes for the terminal referred to by the open file descriptor `fd`. The `termios_p` argument is a pointer to a `termios` structure that contains the new input and output terminal settings. The changes specified by `termios_p` are made according to the value of `optional_actions`.


``` C
int tcgetattr(int fd, struct termios *termios_p);
```
- Parameters:
`fd` - A file descriptor that refers to a terminal.
`termios_p` - A pointer to a `struct` termios where the terminal I/O settings are stored.
- Description: Gets the current terminal I/O settings for the terminal referred to by the open file descriptor `fd`. The settings are stored in the `termios` structure pointed to by `termios_p`.


tgetent
``` C
int tgetent(char *bp, const char *name);
```
- Parameters:
`bp` - A pointer to a buffer where the terminal description is stored.
`name` - The name of the terminal.
= Description: Searches the terminfo database for a terminal named `name` and stores its description in the buffer pointed to by `bp`. The function returns 1 if the terminal is found, 0 if it is not found, and -1 if an error occurred.


``` C
int tgetflag(char *id);
```
- Parameters:
`id` - A two-character string indicating a boolean capability from the terminfo database.
- Description: Checks for a boolean capability in the terminfo database. The `id` parameter is a two-character string that represents a boolean capability of the terminal. The function returns 1 if the terminal has the capability, and 0 otherwise.


``` C
int tgetnum(char *id);
```
- Parameters:
`id` - A two-character string indicating a numeric capability from the terminfo database.
- Description: Retrieves a numeric capability from the terminfo database. The `id` parameter is a two-character string that represents a numeric capability of the terminal. The function returns the numeric value of the capability if it exists and is positive, -1 if it does not exist, and -2 if it exists but is negative.



``` C
char *tgetstr(char *id, char **area);
```
- Parameters:
`id` - A two-character string indicating a string capability from the terminfo database.
`area` - A pointer to a pointer to an area where the function can store the result string.
- Description: Retrieves a string capability from the terminfo database. The `id` parameter is a two-character string that represents a string capability of the terminal. The function returns a pointer to the string if it exists, and NULL otherwise. The `area` parameter is used to provide memory for the result string.


tgoto
``` C
char *tgoto(const char *cap, int col, int row);
```
- Parameters:
`cap` - A string that specifies the cursor motion capability from the terminfo database.
`col` - The column number.
`row` - The row number.
- Description: Constructs a cursor motion string for a terminal. The `cap` parameter is a string that specifies the cursor motion capability (usually obtained from `tgetstr`). The `col` and `row` parameters specify the target position for the cursor. The function returns a pointer to a static area containing an escape sequence that can be used to move the cursor to the specified position.


``` C
int tputs(const char *str, int affcnt, int (*putc)(int));
```
- Parameters:
`str` - A string that specifies the cursor motion capability from the terminfo database.
`affcnt` - The number of lines affected, or number of repetitions of the operation.
`putc` - A pointer to a function that takes a single character and outputs it to the terminal.
- Description: Applies padding information to a string and outputs it to the terminal. The `str` parameter is a string that specifies a terminal capability (usually obtained from `tgetstr`). The `affcnt` parameter is the number of lines affected by the operation, or the number of repetitions of the operation. The `putc` parameter is a pointer to a function that takes a single character and outputs it to the terminal. The function returns ERR upon failure and OK upon successful completion.
satty(int fd);
```
- Parameters:
`fd` - A file descriptor.
- Description: Checks if the file descriptor `fd` is associated with a terminal device. Returns 1 if `fd` is an open file descriptor referring to a terminal; otherwise 0 is returned, and `errno` is set to indicate the error.


``` C
char *ttyname(int fd);
```
- Parameters:
`fd` - A file descriptor.
- Description: Returns a pointer to a string that contains the null-terminated pathname of the terminal device that is open on the file descriptor `fd`. The string is static and may be overwritten by subsequent calls to `ttyname` or `ttyname_r`.


``` C
int ttyslot(void);
```
