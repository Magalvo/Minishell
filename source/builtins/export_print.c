#include "../../include/minishell.h"

int	print_export(t_ms *s)
{
	t_env	*env;

	env = s->env;
	while(env)
	{
		if (env->value != NULL)
			printf("%s=%s\n", env->key, env->value);
		env = env->next;
	}	
	return (1);
}