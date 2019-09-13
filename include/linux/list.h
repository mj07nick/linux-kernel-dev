/**
 * TODO: Have to add the following functions and macros related to list:-
 *		> list_add_tail
 *		> __list_add_rcu
 *		> list_add_rcu
 *		> list_add_tail_rcu
 *		> __list_del
 *		> list_del
 *		> list_del_rcu
 *		> list_replace
 *		> list_replace_init
 *		> list_replace_rcu
 *		> list_move
 *		> list_move_tail
 *		> list_is_last
 *		> list_empty
 *		> list_empty_careful
 *		> list_is_singular
 *		> __list_splice
 *		> list_splice
 *		> list_splice_init
 *		> list_splice_init_rcu
 *		> list_first_entry
 *		> list_for_each
 *		> __list_for_each
 *		> list_for_each_prev
 *		> list_for_each_safe
 *		> list_for_each_prev_safe
 *		> list_for_each_entry
 *		> list_for_each_entry_reverse
 *		> list_prepare_entry
 *		> list_for_each_entry_continue
 *		> list_for_each_continue_reverse
 *		> list_for_each_entry_from
 *		> list_for_each_entry_safe
 *		> list_for_each_entry_safe_from
 *		> list_for_each_entry_safe_from_reverse
 *		> list_for_each_rcu
 *		> __list_for_each_rcu
 *		> list_for_each_entry_rcu
 *		> list_for_each_continue_rcu
 *
 * TODO: Have to add the fully supported functions and macros related to hash
 *	 tables.
 */


#ifndef _LINUX_LIST_H
#define _LINUX_LIST_H

/**
 * offsetof - Used to calculate the difference between a struct object with it's
 * 		internal variables.
 * @TYPE - The container (eg. struct, enum, etc.) of the variable.
 * @MEMBER - The variable whose offset you want to find with the container.
 *
 * *** WORKING ***
 *  Firstly, we declare the memory address of TYPE to be 0 by '((TYPE *)0)'
 *
 *  After that we find out the memory address of the variable MEMBER. Since, the
 *  TYPE is assigned at the memory address of 0, it will give us and offset in
 *  hexadecimal type by '&((TYPE *)0)->MEMBER'
 *
 *  This hexadecimal value is converted into size_t data type implicitly.
 */

#define offsetof(TYPE, MEMBER) ((size_t) &((TYPE*)0)->MEMBER)

/**
 * Simple double ll implementation.
 *
 * Just declare a variable of data type struct list_head inside your structure
 * that you want to convert into a doubly linked list.
 */

struct list_head{
        struct list_head * next;
        struct list_head * prev;
};

/**
 * INIT_LIST_HEAD - used to initialize the struct list_head inside the container
 *			that you want to convert into linked list.
 *
 * @list - The list_head pointer inside the container structure.
 */

static inline void INIT_LIST_HEAD(struct list_head * list){
        list->prev = list;
	list->next = list;
}

/**
 * LIST_HEAD_INIT - macro that can be used as an alternative for INIT_LIST_HEAD.
 * @name - The struct list_head pointer inside the container structure.
 */

#define LIST_HEAD_INIT(name) { &(name), &(name) }

/**
 * container_of - A magical macro to find out the base address of the container
 *			structure via a member of it's.
 * @ptr - Temporary variable of type 'struct list_head', which contains the
 *		address of the member whose container address we need to find.
 * @type - The type of the structure which is linked list in your code.
 * @member - The object of 'struct list_head' that is declared inside your ll.
 */

#define container_of(ptr, type, member)({ \
	const typeof( ((type*)0)->member ) *__mptr = (ptr); \
	(type *)( (char*)__mptr - offsetof(type, member) );})

/**
 * list_entry - Driver macro for finding out the base address of the container
 *		structure via a member it's.
 * @ptr - Temporary variable of type 'struct list_head', which contains the
 *              address of the member whose container address we need to find.
 * @type - The type of the structure which is linked list in your code.
 * @member - The object of 'struct list_head' that is declared inside your ll.
 */

#define list_entry(ptr, type, member) \
	container_of(ptr, type, member)

/**
 * LIST_HEAD - macro to declare and initialize a structure as a head node in the
 *		given linked list.
 * name - The name that you want to give to your head node. It need not to be
 *		declared in your main file before.
 */

#define LIST_HEAD(name)	\
	struct list_head name = LIST_HEAD_INIT(name)

/**
 * __list_add - Function to add a given list_head node inside the linked list.
 * @new - The pointer to the list_head that you want to add inside your ll.
 * @prev - The pointer to the previous node of the position for new.
 * @next - The pointer to the next node of the position for new.
 *
 * Can also be manipulated to make a stack or a queue also.
 */

static inline void __list_add(struct list_head * new,
			    struct list_head * prev,
			    struct list_head * next){
	prev->next = new;
	new->prev = prev;
	new->next = next;
	next->prev = new;
}

/**
 * list_add - The driver function to implement a push function for a circular
 *		doubly ll. The data is inserted in 'First In' method here, i.e.
 *		just like a stack.
 */

static inline void list_add(struct list_head * new, struct list_head * head){
	__list_add(new, head, head->next);
}

/**
 * list_for_each - A simple for loop to iterate all over the linked list.
 * @pos - A temporary variable of type 'struct list_head' where we can store the
 *		link of the link list's elements.
 * @head - The head node of the given linked list.
 */

#define list_for_each(pos, head) \
	for((pos) = (head)->next; (pos)!=(head); (pos) = pos->next)

#endif
