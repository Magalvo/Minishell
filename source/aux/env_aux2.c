#include "../../include/minishell.h"

int	here_doc(char *dli, t_ms *s, t_cmd *cmd)
{
	int		file;
	char	*line;
	int		in_file;

	(void)s;
	(void)cmd;
	file = open(".here_doc", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (file == -1)
		error_msg("Error opening here_doc");
	while (1)
	{
		write(1, "> ", 2);
		line = get_next_line(0);
		if (line == NULL || ft_strncmp(dli, line, ft_strlen(dli)) == 0)
			break ;
		ft_putstr_fd(line, file);
		free(line);
	}
	free(line);
	close(file);
	in_file = open(".here_doc", O_RDONLY);
	if (in_file < 0)
		error_msg("opening here_doca");
	return (in_file);
}