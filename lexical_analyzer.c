/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexical_analyzer.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvayon <hvayon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 20:16:54 by hvayon            #+#    #+#             */
/*   Updated: 2022/05/31 21:06:24 by hvayon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//---лексический АНАЛизатор-----

int	parse_sybols(char *type) // поменять все strcmp на ft_strcmp
{
	if (!strcmp(type, ">"))
		return GREAT;
	if (!strcmp(type, "<"))
		return LESS;
	if (!strcmp(type, ">>"))
		return GREATGREAT;
	if (!strcmp(type, "<<"))
		return LESSLESS;
	if (!strcmp(type, ">&"))
		return GREATAMPERSAND;
	if (!strcmp(type, "|"))
		return PIPE;
	if (!strcmp(type, "&"))
		return AMPERSAND;
	else
		return NOTOKEN;
}

void lexical_analyzer(t_data *data)
{
	int i;
	i = 0;

	while(data)
	{
		if (strcmp(data->type, "COMMAND")) // получаем символы //поменять на ft_srtcmp
			printf("%d", parse_sybols(data->type));
		data = data->next;
	}
}