/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmendelo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/25 09:26:53 by dmendelo          #+#    #+#             */
/*   Updated: 2018/11/02 16:35:11 by dmendelo         ###   ########.fr       */
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
	t_adj		*adj;

	printf("\n--------------------------------\n");
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
	if (room && room->distance)
	{
		printf("%u away from end\n", room->distance);
	}
	if (room)
	{
		printf("visited flags = %d\n", room->visited);
	}
	if (room->adjacent)
	{
		adj = room->adjacent;
		printf("adjacent to:\n");
		while (adj)
		{
			if (adj->direction)
				printf("%s -> %s\n", room->name, adj->room->name);
			else
				printf("%s <- %s\n", room->name, adj->room->name);
			adj = adj->next;
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

void			push_adj(t_adj **head, t_room *room, int direction)
{
	WOW();
	t_adj			*new;

	new = malloc(sizeof(*new));
	new->room = room;
	new->direction = direction;
	if (!(*head))
	{
		new->next = NULL;
	}
	else
	{
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
	new->distance = 0;
	new->visited = 0;
	if (sig == 1)
		new->occupied = g_ants;
	else
		new->occupied = 0;
	return (new);
}

/*
** pushes room to queue. frees line.
*/

int				parse_room(t_list **head, char **line, unsigned significance, char **phase_3)
{
	WOW();
	t_room			*new;
	char			**args;

	args = str_split(*line);
	if (ptr_count(args) != 3)
	{
		if (strchr(*line, '-'))
		{
			*phase_3 = strdup(*line);
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
	push_adj(&link->adjacent, *b, 1);
	link = *b;
	push_adj(&link->adjacent, *a, 1);
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

int				link_rooms(t_list **head, char *link1)
{
	WOW();
	char			*line;

	print_rooms(*head);
	if (!valid_link(link1) || !link_room(head, link1))
		return (0);
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
	printf("--------------------\n");
	printf("address of room = %p\n", head);
	print_rooms(*head);
	return (1);
}

t_list			*read_rooms(void)
{
	WOW();
	t_list			*rooms;
	char			*line;
	unsigned		significance;
	char			*phase_3;

	phase_3 = NULL;
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
		if (!link_rooms(&rooms, phase_3))
		{
//			if (rooms)
//				free_list(rooms);
//			return (NULL);
		}
	}
	printf("address of room = %p\n", &rooms);
	print_rooms(rooms);
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

int				is_end(t_room *room)
{
	if (room->significance == 2)
	{
		return (1);
	}
	return (0);
}

t_room			*find_end(t_list **head)
{
	t_list			*traverse;

	traverse = *head;
	while (traverse)
	{
		if (is_end((t_room *)traverse->data))
		{
			return ((t_room *)traverse->data);
		}
		traverse = traverse->next;
	}
	return (NULL);
}

void			write_distance(t_room **room, unsigned d)
{
	(*room)->distance = d;
}

int				has_dist(t_room *room)
{
	if (room && room->distance != 0)
		return (1);
	return (0);
}

int				is_visited(t_room *room)
{
	if (room->visited)
		return (1);
	return (0);
}

void			write_visited(t_room **room, int flag)
{
	(*room)->visited = flag;
}

void			write_direction(t_adj **adj, char *name, int direction)
{
	WOW();
	t_adj			*traverse;

	traverse = *adj;
	while (traverse)
	{
		if (!strcmp(traverse->room->name, name))
		{
			traverse->direction = direction;
		}
		traverse = traverse->next;
	}
}

void			push_back(t_list **head, void *new_data, size_t size)
{
	WOW();
	t_list			*new;
	t_list			*traverse;

	new = malloc(sizeof(*new));
	new->data = new_data;
	new->size = size;
	new->next = NULL;
	traverse = *head;
	if (!(*head))
	{
		*head = new;
		return ;
	}
	while (traverse)
	{
		if (traverse->next == NULL)
		{
			traverse->next = new;
			return ;
		}
		traverse = traverse->next;
	}
}

void			*pop(t_list **queue)
{
	void			*popped;
	t_list			*short_;

	popped = (*queue)->data;
	short_ = (*queue)->next;
	free(*queue);
	*queue = short_;
	return (popped);
}

void			print_room_name(t_room *room)
{
	printf("%s\n", room->name);
}

void			print_room_names(t_list *list)
{
	t_list			*traverse;

	traverse = list;
	while (traverse)
	{
		if (traverse->data)
		{
			print_room_name((t_room *)traverse->data);
		}
		traverse = traverse->next;
	}
}

t_list			*list_dup(t_list *src)
{
	WOW();
	t_list			*dup;

	if (!src)
	{
		return (NULL);
	}
	dup = malloc(sizeof(*dup));
	dup->data = malloc(src->size);
	memcpy(dup->data, src->data, src->size);
	dup->size = src->size;
	dup->next = list_dup(src->next);
	return (dup);
}

void			free_list(t_list *head)
{
	t_list			*tmp;

	while (head)
	{
		tmp = head;
		head = head->next;
		free(tmp);
	}
}

void			write_to_neighbors(t_room **room, unsigned distance)
{
	WOW();
	t_adj			*traverse;
	t_list			*queue;
	t_list			*auxiliary_queue;
	t_room			*tmp;


	print_room(*room);
	queue = NULL;
	auxiliary_queue = NULL;
	push_back(&queue, *room, sizeof(**room));
	while (queue)
	{
		auxiliary_queue = list_dup(queue);
		free_list(queue);
		queue = NULL;
		print_room_names(auxiliary_queue);
		while (auxiliary_queue)
		{
			tmp = (t_room *)pop(&auxiliary_queue);
			traverse = tmp->adjacent;
			while (traverse)
			{
				if (!traverse->room->visited)
				{
					traverse->room->distance = distance + 1;
					traverse->room->visited = 1;
					push_back(&queue, traverse->room, sizeof(*traverse->room));
				}
				traverse = traverse->next;
			}
		}
		distance += 1;
	}
}

void			bfs(t_list **head)
{
	WOW();
	t_room			*end;

	end = find_end(head);
	if (!end)
	{
		printf("error!\n");
		return ;
	}
	write_visited(&end, 1);
	write_to_neighbors(&end, 0);
	printf("-------------------(post)bfs--------------------\n");
	print_rooms(*head);
}

int				is_start(t_room *room)
{
	if (room->significance == 1)
	{
		return (1);
	}
	return (0);
}

t_room			*find_start(t_list **head)
{
	WOW();
	t_list			*traverse;

	traverse = *head;
	while (traverse)
	{
		if (is_start((t_room *)traverse->data))
		{
			return ((t_room *)traverse->data);
		}
		traverse = traverse->next;
	}
	return (NULL);
}

void			set_visited_zero(t_list **head)
{
	t_list			*traverse;

	traverse = *head;
	while (traverse)
	{
		if (traverse->data)
		{
			write_visited((t_room **)&traverse->data, 0);
		}
		traverse = traverse->next;
	}
}

int				calculate_max_paths(t_room *start, t_room *end)
{
	WOW();
	t_adj			*traverse;
	int				in;
	int				out;

	in = 0;
	out = 0;
	traverse = start->adjacent;
	while (traverse)
	{
		in += 1;
		traverse = traverse->next;
	}
	traverse = end->adjacent;
	while (traverse)
	{
		out += 1;
		traverse = traverse->next;
	}
	printf("in = %d\nout = %d\n", in, out);
	return (in < out ? in : out);
}

t_room			*lowest_hanging_fruit(t_room **room)
{
	WOW();
	t_room			*tmp;
	t_adj			*traverse;

	traverse = (*room)->adjacent;
	tmp = NULL;
	while (traverse)
	{
		if (is_end(traverse->room))
		{
			return (traverse->room);
		}
		if ((!tmp || traverse->room->distance < tmp->distance) && !traverse->room->visited)
		{
			tmp = traverse->room;
		}
		traverse = traverse->next;
	}
	tmp->visited = 1;
	print_room(tmp);
	return (tmp);
}

int				push_new_path(t_list **paths_head, t_room *start)
{
	t_list			*path;
	t_room			*traverse;

	path = NULL;
	push_back(&path, start, sizeof(start));
	traverse = start;
	while (traverse && !is_end(traverse))
	{
		print_room(traverse);
		traverse = lowest_hanging_fruit(&traverse);
		push_back(&path, traverse, sizeof(traverse));
	}
	if (!traverse)
		return (0);
	push_back(paths_head, path, sizeof(path));
	return (1);
}

t_list			*find_paths(t_room *start, int max)
{
	WOW();
	t_list			*paths;
	t_list			*path;
	t_room			*traverse;

	path = NULL;
	paths = NULL;
	while (max--)
	{	
		if (!push_new_path(&paths, start))
			break ;
	}
//	printf("---------------------printing shortest path---------------\n");
//	print_rooms((t_list *)paths->data);
	return (paths);

}

void			print_paths(t_list *paths)
{
	WOW();
	t_list			*traverse;
	int				i = 0;
	
	traverse = paths;
	while (traverse)
	{
		if (traverse->data)
		{
			printf("--------------------path %d -----------------------\n", i++);
			print_rooms(traverse->data);
		}
		traverse = traverse->next;
	}
}

t_list			*queue_paths(t_list *rooms)
{
	WOW();
	t_list			*paths;
	t_room			*start;
	t_room			*end;
	int				max_paths;

	set_visited_zero(&rooms);
	start = find_start(&rooms);
	end = find_end(&rooms);
	printf("--------------------------start---------------------------\n");
	print_room(start);
	printf("--------------------------end-----------------------------\n");
	print_room(end);
	max_paths = calculate_max_paths(start, end);
	printf("max paths = %d\n", max_paths);
	paths = find_paths(start, max_paths);
	printf("---------------------printing shortest paths---------------\n");
	print_paths(paths);
	return (paths);
}

void			move_ant(t_list **path_, t_room *room)
{
	WOW();
	t_list			*path;
	t_room			*next;
	t_room			*current;

	path = *path_;
	next = path->next->data;
	if (next->occupied && !is_end(next))
	{
		move_ant(&path->next, next);
	}
	next->occupied += 1;
	if (is_end(next))
	{
		next->occupied -= 1;
		printf("ant has left the building!\n");
	}
	current = path->data;
	current->occupied -= 1;
	printf("moved ant from room %s to room %s\n", current->name, next->name);
	if (!is_end(next))
		move_ant(&path->next, next);
}

void			move_ants(t_list **paths)
{
	WOW();
	t_list			*path;
	t_list			*traverse;
	t_room			*room;

	traverse = *paths;
	while (traverse)
	{
		path = traverse->data;
		room = path->data;
		move_ant(&path, room);
		traverse = traverse->next;
	}
}

void			lem_in(void)
{
	WOW();
	t_list			*rooms;
	t_list			*paths;

	rooms = read_stdin();
	print_rooms(rooms);
	bfs(&rooms);
	paths = queue_paths(rooms);
	move_ants(&paths);
	print_rooms(rooms);
}

int				main(void)
{
	lem_in();
	return (1);
}
