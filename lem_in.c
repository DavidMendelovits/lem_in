/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmendelo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/25 09:26:53 by dmendelo          #+#    #+#             */
/*   Updated: 2018/10/26 12:17:10 by dmendelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

unsigned		g_ants;
unsigned		g_err;

void			print_strings(char **strings, int p)
{
	if (!strings)
		return ;
	if (strings[p])
	{
		printf("%s\n", strings[p]);
	}
	if (strings[p + 1])
	{
		print_strings(strings, p + 1);
	}
}

int				ptr_count(char **ptrs)
{
	WOW();
	int				p;

	p = 0;
	while (ptrs[p])
	{
		p += 1;
	}
	return (p);
}

char		*replace_char(char *s, int old, int new)
{
	WOW();
	char			*ret;
	int				p;

	ret = strdup(s);
	p = 0;
	while (s[p])
	{
		if (s[p] == old)
		{
			ret[p] = new;
		}
		p += 1;
	}
	return (ret);
}

void			free_2d(char **ptrs)
{
	WOW();
	int				p;
	int				len;

	len = ptr_count(ptrs);
	p = 0;
	while (p < len)
	{
		free(ptrs[p]);
		p += 1;
	}
	free(ptrs);
}

char			*ft_strdup_range(const char *str, int begin, int end)
{
	WOW();
	int				p;
	char			*dup;
	int				dp;

	if (begin > end)
		return (NULL);
	p = begin;
	dup = malloc(sizeof(char) * (end - begin + 2));
	bzero(dup, end - begin + 2);
	dp = 0;
	while (p <= end)
	{
		dup[dp] = str[p];
		dp += 1;
		p += 1;
	}
	printf("dup = %s\n", dup);
	return (dup);
}

int				skip_whitespaces(char *s, int p)
{
	while (s[p] && (s[p] == ' ' || s[p] == '\t'))
	{
		p += 1;
	}
	return (p);
}

int				count_words(char *s)
{
	WOW();
	int				p;
	int				count;

	p = 0;
	count = 0;
	while (s[p])
	{
		if (s[p] == ' ' || s[p] == '\t')
		{
			p = skip_whitespaces(s, p);
		}
		else
		{
			count += 1;
			while (s[p] && s[p] != ' ' && s[p] != '\t')
			{
				p += 1;
			}
		}
	}
	return (count);
}

char			**str_split(char *s)
{
	WOW();
	int				p;
	char			**strings;
	int				sp;
	int				word_count;
	int				begin;

	word_count = count_words(s);
	p = 0;
	sp = 0;
	strings = malloc(sizeof(*strings) * (word_count + 1));
	while (s[p])
	{
		if (s[p] == ' ' || s[p] == '\t')
		{
			p = skip_whitespaces(s, p);
		}
		else
		{
			begin = p;
			while (s[p] && s[p] != '\t' && s[p] != ' ')
			{
				p += 1;
			}
			strings[sp] = ft_strdup_range(s, begin, p - 1);
			sp += 1;
		}
	}
	strings[sp] = NULL;
	return (strings);
}

int				is_num(char *str)
{
	int				p;

	p = 0;
	while (str[p])
	{
		if (!(str[p] >= '0' && str[p] <= '9'))
		{
			return (0);
		}
		p += 1;
	}
	return (1);
}

unsigned		read_first_line(void)
{
	WOW();
	char			buffer[1024];
	int				p;

	bzero(buffer, 1024);
	p = 0;
	while (read(0, &buffer[p], 1))
	{
		printf("buffer[%d] = %c\n", p, buffer[p]);
		if (buffer[p] == '\n')
		{
			buffer[p] = 0;
			break ;
		}
		p += 1;
	}
	printf("1\n");
	if (is_num(buffer))
		return(atoi(buffer));
	return (0);
}

void			print_room(t_room *room)
{
	WOW();
	t_room		*tmp;

	if (room && room->name)
		printf("room -> %s\n", room->name);
	if (room && room->significance)
			(room->significance == 1) ? printf("(is start)\n") : printf("(is end)\n");
	if (room && room->occupied)
		printf("has %u ants\n", room->occupied);
	if (room)
	{
		printf("located at [%d][%d]\n", room->coordinates.x, room->coordinates.y);
	}
	if (room->adjacent)
	{
		printf("adjacent to:\n");
		while (room->adjacent)
		{
			tmp = (t_room *)room->adjacent->data;
			printf("%s -> %s\n", room->name, tmp->name);
			room->adjacent = room->adjacent->next;
		}
	}
	printf("\n--------------------------------\n");
}

void			print_rooms(t_list *rooms)
{
	WOW();
	while (rooms)
	{
		if (rooms->data)
		{
			print_room((t_room *)rooms->data);
		}
		rooms = rooms->next;
	}
}

void			push(t_list **head, void *new_data, size_t size)
{
	WOW();
	t_list			*new;

	new = malloc(sizeof(*new));
	new->data = new_data;
	new->size = size;
	if (!(*head))
	{
		printf("Head doesn't exist\n");
		new->next = NULL;
	}
	else
	{
		printf("pushed!\n");
		new->next = *head;
	}
	*head = new;
}

char			*read_line(void)
{
	WOW();
	char			buffer[1024];
	int				p;

	p = 0;
	bzero(buffer, 1024);
	while (read(0, &buffer[p], 1))
	{
		if (buffer[p] == '\n')
		{
			buffer[p] = 0;
			break ;
		}
		p += 1;
	}
	if (p)
		return (strdup(buffer));
	else
		return (NULL);
}

t_room			*new_room(char **args, unsigned sig)
{
	WOW();
	t_room			*new;

	print_strings(args, 0);
	new = malloc(sizeof(*new));
	new->name = strdup(args[0]);
	new->coordinates.x = atoi(args[1]);
	new->coordinates.y = atoi(args[2]);
	new->significance = sig;
	new->adjacent = NULL;
	if (sig == 1)
		new->occupied = g_ants;
	else
		new->occupied = 0;
	return (new);
}

/*
** pushes room to queue. frees line.
*/

int				parse_room(t_list **head, char **line, unsigned significance, int *phase_3)
{
	WOW();
	t_room			*new;
	char			**args;

	args = str_split(*line);
	if (ptr_count(args) != 3)
	{
		if (strchr(*line, '-'))
		{
			*phase_3 = 1;
			return (0);
		}
		else
		{
			free(*line);
			printf("invalid room!\n");
			return (0);
		}
	}
	if (!is_num(args[1]) || !is_num(args[2]))
	{
		return (0);
	}
	new = new_room(args, significance);
	push(head, new, sizeof(new));
	print_room((*head)->data);
	print_rooms(*head);
	free_2d(args);
	return (1);
}

int				valid_link(char *line)
{
	WOW();
	char			**args;

	if (!strchr(line, '-'))
	{
		return (0);
	}
	args = str_split(line);
	if (ptr_count(args) != 1)
	{
		free_2d(args);
		return (0);
	}
	free_2d(args);
	printf("is valid!\n");
	return (1);
}

int				match_room_names(char *room_name, t_room *room)
{
	WOW();
	if (!strcmp(room_name, room->name))
	{
		printf("%s - %s\n", room_name, room->name);
		return (1);
	}
	printf("false\n");
	return (0);
}

t_room			*find_room(t_list **head, char *room)
{
	WOW();
	t_list			*traverse;

	traverse = *head;
	while (traverse && traverse->data)
	{
		if (match_room_names(room, traverse->data))
		{
			return ((t_room *)traverse->data);
		}
		traverse = traverse->next;
	}
	return (NULL);
}

void			link_(t_room **a, t_room **b)
{
	WOW();
	t_room			*link;

	link = *a;
	push(&link->adjacent, *b, sizeof(*b));
	link = *b;
	push(&link->adjacent, *a, sizeof(*a));
}

int				link_room(t_list **head, char *link)
{
	WOW();
	char			**args;
	char			*split;
	t_room			*room1;
	t_room			*room2;

	split = replace_char(link, '-', ' ');
	args = str_split(split);
	free(split);
	if (!(room1 = find_room(head, args[0])))
	{
		free_2d(args);
		return (0);
	}
	if (!(room2 = find_room(head, args[1])))
	{
		free_2d(args);
		return (0);
	}
	link_(&room1, &room2);
	return (1);
}

int				link_rooms(t_list **head)
{
	WOW();
	char			*line;

	print_rooms(*head);
	while ((line = read_line()))
	{
		if (line[0] == '#')
		{
			free(line);
			continue ;
		}
		if (!valid_link(line))
		{
			free(line);
			return (0);
		}
		if (!link_room(head, line))
		{
			free(line);
			return (0);
		}
	}
	print_rooms(*head);
	return (1);
}

t_list			*read_rooms(void)
{
	WOW();
	t_list			*rooms;
	char			*line;
	unsigned		significance;
	int				phase_3;

	phase_3 = 0;
	rooms = NULL;
	while ((line = read_line()))
	{
		printf("[%s]\n", line);
		significance = 0;
		if (!strcmp(line, "##start") || !strcmp(line, "##end"))
			significance = (!strcmp(line, "##end")) ? 2 : 1;
		else if (line[0] == '#')
		{
			free(line);
			continue ;
		}
		printf("significance = %u\n", significance);
		if (significance)
		{
			free(line);
			line = read_line();
		}
		if (!(parse_room(&rooms, &line, significance, &phase_3)))
		{
			if (phase_3)
				break ;
			else if (rooms)
//				free_list(rooms);
			return (NULL);
		}
//		push(&rooms, room, sizeof(t_room));
//		print_rooms(rooms);
	}
	print_rooms(rooms);
	if (phase_3)
	{		
		if (!link_rooms(&rooms))
		{
//			if (rooms)
//				free_list(rooms);
//			return (NULL);
		}
	}
	return (rooms);
}

t_list			*read_stdin(void)
{
	WOW();
	t_list			*rooms;

	g_ants = 0;
	g_ants += read_first_line();
	if (!g_ants)
		return (NULL);
	rooms = read_rooms();
	return (rooms);
}

void			lem_in(void)
{
	WOW();
	t_list			*rooms;

	rooms = read_stdin();
}

int				main(void)
{
	lem_in();
	return (1);
}
