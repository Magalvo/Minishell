// #include "../include/minishell.h"

// char	*ft_getrnd_str(void)
// {
// 	int fd;
// 	char	res[STR_SIZE + 1];
// 	char	buf[1];
// 	int		i;

// 	i = 0;
// 	// buf = '\0';
// 	fd = open("/dev/urandom", O_RDONLY);
// 	if (!fd)
// 		return (NULL);
// 	while (i < STR_SIZE)
// 	{
// 		read(fd, buf, 1);
// 		if (ft_isalnum(buf[0]))
// 		{
// 			res[i] = buf[0];
// 			i++;
// 		}
// 	}
// 	close(fd);
// 	res[STR_SIZE] = '\0';
// 	return (ft_strdup(res));
// }

// char	*ft_get_empty(void)
// {
// 	char	no_char;
// 	char	*empty;

// 	no_char = (char)17;
// 	empty = ft_calloc(1, 2);
// 	empty[0] = no_char;
// 	empty[1] = '\0';
// 	return (empty);
// }
