#include "minishell.h"

t_data	*ft_parse(char *str)
{
	t_data	*data;
	t_data	*tmp;
	char	**strs;

	data = NULL;
	strs = ft_split(str, '|');
	if (!strs)
		return (NULL);
	while (*strs)
	{
		tmp = (t_data *)malloc(sizeof(t_data));
		tmp->comands = ft_split(*strs, ' ');
		if (!tmp->comands)
			return (NULL); //FIX_ME free all
		ft_lstadd_back(&data, tmp);
		strs++;
	}
	return (data);
}
