#include "minishell.h"

int	ft_dquote(char *str)
{
	int i;
	i = 1;

	while(str[i] != '\0')
	{
		if (str[i] == '"')
		{
			str[i + 1] = '\0';
			break;
		}
	}
	if (str[i] != '"')
		return (NULL);
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '$')
			get_env_var(&str[i + 1]);
	}
}


t_data	*ft_parse(char *str)
{
	t_data	*data;
	t_data	*tmp;
	char	**strs;
	int		i;

	i = 0;
	data = NULL;
	while (*str)
	{
		tmp = (t_data *)malloc(sizeof(t_data));
		if (str[i] == '"')
			ft_dquote(str);
		tmp->comands = ft_split(*strs, ' '); // NOT RIGHT FOR echo "pine | $PATH" стоит проверять " ' перед первым сплитом
		if (!tmp->comands)
			return (NULL); //FIX_ME free all
		ft_lstadd_back(&data, tmp);
		strs++;
	}
	return (data);
}
