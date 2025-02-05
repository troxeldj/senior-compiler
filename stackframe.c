#include "compiler.h"
#include "helpers/vector.h"
#include <assert.h>

void stackframe_pop(struct node* function_node) {
	struct stack_frame* frame = &function_node->func.frame;
	vector_pop(frame->elements);
}

struct stack_frame_element* stackframe_back(struct node* function_node) {
	return vector_back_or_null(function_node->func.frame.elements);
}

void stackframe_pop_expecting(struct node* function_node, int expecting_type, const char* expecting_name) {
	struct stack_frame* frame = &function_node->func.frame;
	struct stack_frame_element* last_element = stackframe_back(function_node);
	assert(last_element);
	assert(last_element->type == expecting_type && last_element->name == expecting_name);
	stackframe_pop(function_node);
}

void stackframe_peek_start(struct node* function_node) {
	struct stack_frame* frame = &function_node->func.frame;
	vector_set_peek_pointer_end(frame->elements);
	vector_set_flag(frame->elements, VECTOR_FLAG_PEEK_DECREMENT);
}

struct stack_frame_element* stackframe_peek(struct node* function_node) {
	struct stack_frame* frame = &function_node->func.frame;
	return vector_peek(frame->elements);
}

struct stack_frame_element* stackframe_back_expect(struct node* function_node, int expected_type, const char* expected_name) {
	struct stack_frame_element* element = stackframe_back(function_node);
	if(element && element->type != expected_type || !S_EQ(element->name, expected_name)) {
		return NULL;
	}
	return element;
}

void stackframe_push(struct node* function_node, struct stack_frame_element* element) {
	struct stack_frame* frame = &function_node->func.frame;
	element->offset_from_bp = -vector_count(frame->elements) * STACK_PUSH_SIZE;
	vector_push(frame->elements, element);
}

void stackframe_sub(struct node* function_node, int type, const char* name, size_t amount) {
	assert((amount % STACK_PUSH_SIZE) == 0);
	size_t total_pushes = amount / STACK_PUSH_SIZE;
	for(size_t i = 0; i < total_pushes; i++) {
		stackframe_push(function_node, &(struct stack_frame_element){.type=type, .name=name});
	}
}

void stackframe_add(struct node* function_node, int type, const char* name, size_t amount) {
	assert((amount % STACK_PUSH_SIZE) == 0);
	size_t total_pushes = amount / STACK_PUSH_SIZE;
	for(size_t i = 0; i < total_pushes; i++) {
		stackframe_pop(function_node);
	}
}

void stackframe_assert_empty(struct node* function_node) {
	struct stack_frame* frame = &function_node->func.frame;
	assert(vector_count(frame->elements) == 0);
}