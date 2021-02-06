#ifndef __BINARY_H_
#define __BINARY_H_

#ifndef HEAP_DEFAULT_SIZE
#define HEAP_DEFAULT_SIZE 10
#endif

#ifndef MAX
#define MAX(a, b) ((a >= b) ? (a) : (b))
#endif

typedef struct bin_node_s {
	float weight;
	void* data;
} bin_node_t;

typedef struct bin_heap_s {
	size_t max_size;
	size_t size;
	bin_node_t* nodes;
} bin_heap_t;

// binary.c
bin_heap_t* bin_heap_create();
bin_heap_t* bin_heap_create_reserve(size_t max_size);
void bin_heap_destroy(bin_heap_t* heap);
void bin_heap_destroy_full(bin_heap_t* heap, void (*func)(void*));

// binary_actions.c
int bin_heap_append(bin_heap_t* heap, float weight, void* data);
int bin_heap_append_from_node(bin_heap_t* heap, const bin_node_t* node);
void* bin_heap_extract_min(bin_heap_t* heap, float *weight);

#endif // !__BINARY_H_

