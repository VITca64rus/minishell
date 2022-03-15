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
		tmp->comands = ft_split(*strs, ' '); // NOT RIGHT FOR echo "pine | $PATH" стоит проверять " ' перед первым сплитом
		if (!tmp->comands)
			return (NULL); //FIX_ME free all
		ft_lstadd_back(&data, tmp);
		strs++;
	}
	return (data);
}

// int main()
// {
// 	t_data *data;

// 	printf("====TEST1====\n");
// 	data = ft_parse("ls -l | echo crab");
// 	if (!strcmp(data->comands[0],"ls") && !strcmp(data->comands[1],"-l") && !strcmp(data->next->comands[0],"echo") && !strcmp(data->next->comands[1],"crab") )
// 		printf("OK\n");
// 	else
// 		printf("NO\n");
// 	printf("====TEST2====\n");
// 	data = ft_parse("ls -l | echo \"crab | pipe\"");
// 	if (!strcmp(data->comands[0],"ls") && !strcmp(data->comands[1],"-l") && !strcmp(data->next->comands[0],"echo") && !strcmp(data->next->comands[1],"crab | parse") )
// 		printf("OK\n");
// 	else
// 	{
// 		printf("NO\n");
// 	}
// }
