#include "../include/minishell.h"

char	*ft_getrnd_str(void)
{
	int fd;
	char	res[STR_SIZE + 1];
	char	buf[1];
	int		i;

	i = 0;
	// buf = '\0';
	fd = open("/dev/urandom", O_RDONLY);
	if (!fd)
		return (NULL);
	while (i < STR_SIZE)
	{
		read(fd, buf, 1);
		if (ft_isalnum(buf[0]))
		{
			res[i] = buf[0];
			i++;
		}
	}
	close(fd);
	res[STR_SIZE] = '\0';
	return (ft_strdup(res));
}
