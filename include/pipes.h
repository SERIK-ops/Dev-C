#ifndef __PIPES_H_
#define __PIPES_H_

#define YES 1
#define NO 0

#include "binary.h"
#include "cities.h"

/*
** structure qui   relie deux villes
*/
typedef struct pipe_s {
	city_t* left;
	city_t* right;
} pipe_t;


// pipes.c
pipe_t* pipe_create(city_t* left, city_t* right);
void pipe_destroy_void(void* pipe);
void pipe_destroy(pipe_t* pipe);
float pipe_calc_distance(city_t* first, city_t* second);
int pipe_is_useless(pipe_t* pipe);

#endif // !__PIPES_H_