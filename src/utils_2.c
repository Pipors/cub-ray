/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelhadj <hbelhadj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 18:17:27 by aatbir            #+#    #+#             */
/*   Updated: 2024/05/20 12:19:59 by hbelhadj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/head.h"
/* TAKING ONLY THE FIRST WORD FROM A GIVEN LINE, WHICH IS IN OUR CASE 
"NO" "SO" "WE" "EA" "F" "C" */
char	*take_first_string(char *line)
{
	char	*first_part; 
	int		i;
	int		j;

	i = 0;
	j = 0;
	first_part = malloc(2);
	if (!line || !first_part)
		return (NULL);
	if (line[i] != '\0')
	{
		while (line[i] != 32 && line[i] != '\t' && j < 2)
			first_part[j++] = line[i++];
		first_part[j] = '\0';
	}
	return (first_part);
}

/* CHECKING IF THE LEN OF THE FIRST WORD MATCHES THE LEN OF THE TARGET WHICH
IS ONE OF THESE WORDS => "NO" "SO" "WE" "EA" "F" "C" */
char	*start_with(char *first_word, char *target, size_t size)
{
	char	*tmp;

	tmp = take_first_string(first_word);
	if (ft_strncmp(tmp, target, size) == 0)
		return (free(tmp), first_word);
	else
		return (free(tmp), NULL);
}

/* FILLING THE STRUCT WITH INFO WHEN DIRECTIONS ARE WRITTEN IN CORRECT WAY
AFTER CHECKING IF THE INFO IN STR MATCHES THE THE TARGET WHILE
RESPECTING ITS LEN */
t_info	*get_info(t_info *info, char *filename)
{
	char	**str;
	int		i;

	i = 0;
	info = ft_calloc(sizeof(t_info), 1);
	// printf("s->---------%s\n",info->first_info);
	str = splimed_key_value_6(filename);
	while (str[i] != NULL)
	{
		if (start_with(str[i], "NO", 2) != NULL)
		{
			if(info->first_info != NULL)
			{
				throw_err_2("error: duplicate\n");
				exit(1);
			}
			else
				info->first_info = ft_strdup(str[i]);
		}
		else if (start_with(str[i], "SO", 2) != NULL)
		{
			if(info->second_info != NULL)
			{
				throw_err_2("error: duplicate\n");
				exit(1);
			}
			else
				info->second_info = ft_strdup(str[i]);
		}
		else if (start_with(str[i], "WE", 2) != NULL)
		{
			if(info->third_info != NULL)
			{
				throw_err_2("error: duplicate\n");
				exit(1);
			}
			else
				info->third_info = ft_strdup(str[i]);
		}
		else if (start_with(str[i], "EA", 2) != NULL)
		{
			if(info->fourth_info != NULL)
			{
				throw_err_2("error: duplicate\n");
				exit(1);
			}
			else
				info->fourth_info = ft_strdup(str[i]);
		}
		else if (start_with(str[i], "F",  1) != NULL)
		{
			if(info->first_color != NULL)
			{
				throw_err_2("error: duplicate\n");
				exit(1);
			}
			else
				info->first_color = ft_strdup(str[i]);
		}
		else if (start_with(str[i], "C", 1) != NULL)
		{
			if(info->second_color != NULL)
			{
				throw_err_2("error: duplicate\n");
				exit(1);
			}
			else
				info->second_color = ft_strdup(str[i]);
		}
		else
			throw_err_2("Wrong Identifier\n");
		i++;
	}
	return (arr_free(str), info);
}

/* REGROUP INFO IN THE STRUCT IN **CHAR TO FACILITATE DATA ACCESSING */
char	**store_get_info_in_array(t_info *info, char *filename)
{
	char	**str;

	str = (char **)malloc(sizeof(char *) * 7);
	info->first_info = 0;
	info->second_info = 0;
	info->third_info = 0;
	info->fourth_info = 0;
	info->first_color = 0;
	info->second_color = 0;
	info = get_info(info, filename);
	if (!str || !info)
		return (NULL);
	str[0] = info->first_info;
	str[1] = info->second_info;
	str[2] = info->third_info;
	str[3] = info->fourth_info;
	str[4] = info->first_color;
	str[5] = info->second_color;
	str[6] = NULL;
	free(info);
	return (str);
}
