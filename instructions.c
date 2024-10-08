#include "monty.h"

/**
 * push - pushes an element onto the stack
 * @stack: double pointer to the top of the stack
 * @line_number: current line number in the script
 *
 * This function adds a new element to the stack. If no integer is provided,
 * or if malloc fails, it prints an error and exits with a failure status.
 */
void push(stack_t **stack, unsigned int line_number)
{
	char *arg;
	int value;
	stack_t *new_node;  /* Declare all variables at the beginning */

	/* Get the argument from the input */
	arg = strtok(NULL, " \n");

	/* Check for no argument or if the argument is not an integer */
	if (arg == NULL || ((value = atoi(arg)) == 0 && strcmp(arg, "0") != 0))
	{
		fprintf(stderr, "L%u: usage: push integer\n", line_number);
		exit(EXIT_FAILURE);
	}

	/* Create a new stack element */
	new_node = malloc(sizeof(stack_t));
	if (!new_node)
	{
		fprintf(stderr, "Error: malloc failed\n");
		exit(EXIT_FAILURE);
	}

	new_node->n = value;
	new_node->prev = NULL;
	new_node->next = *stack;

	/* If the stack is not empty, update the previous pointer of the current top */
	if (*stack)
		(*stack)->prev = new_node;

	/* Update the stack pointer */
	*stack = new_node;
}

/**
 * pall - prints all values on the stack, starting from the top
 * @stack: double pointer to the top of the stack
 * @line_number: current line number in the script
 *
 * This function prints the elements of the stack. It does nothing if
 * the stack is empty.
 */
void pall(stack_t **stack, unsigned int line_number)
{
	stack_t *current = *stack;

	(void)line_number;  /* To suppress unused parameter warning */

	/* Print all values from the stack */
	while (current)
	{
		printf("%d\n", current->n);
		current = current->next;
	}
}

/**
 * pint - prints the value at the top of the stack
 * @stack: double pointer to the top of the stack
 * @line_number: current line number in the script
 *
 * This function prints the value of the top element of the stack.
 * If the stack is empty, it prints an error and exits with failure.
 */
void pint(stack_t **stack, unsigned int line_number)
{
	if (!stack || !*stack)
	{
		fprintf(stderr, "L%u: can't pint, stack empty\n", line_number);
		exit(EXIT_FAILURE);
	}

	printf("%d\n", (*stack)->n);
}

/**
 * pop - Removes the top element of the stack
 * @stack: Double pointer to the stack
 * @line_number: Line number of the current operation
 */
void pop(stack_t **stack, unsigned int line_number)
{
	stack_t *top_node;

	if (*stack == NULL)  /* Check if the stack is empty */
	{
		fprintf(stderr, "L%u: can't pop an empty stack\n", line_number);
		exit(EXIT_FAILURE);
	}

	top_node = *stack;  /* Get the top node */
	*stack = top_node->next;  /* Update the stack pointer to the next node */

	if (*stack)  /* If the stack is not empty, update the previous pointer */
		(*stack)->prev = NULL;

	free(top_node);  /* Free the memory of the popped node */
}

/**
 * swap - Swaps the top two elements of the stack
 * @stack: Double pointer to the stack
 * @line_number: Line number of the current operation
 */
void swap(stack_t **stack, unsigned int line_number)
{
	stack_t *first_node, *second_node;

	if (*stack == NULL || (*stack)->next == NULL)  /* Check if there are less than 2 elements */
	{
		fprintf(stderr, "L%u: can't swap, stack too short\n", line_number);
		exit(EXIT_FAILURE);
	}

	first_node = *stack;              /* Get the top node */
	second_node = first_node->next;   /* Get the second node */

	first_node->next = second_node->next;  /* Update the links to swap the nodes */
	second_node->prev = NULL;          /* The second node will now be the top node */

	if (first_node->next != NULL)      /* Update the previous pointer for the new top */
		first_node->next->prev = first_node;

	second_node->next = first_node;    /* Link the second node to the first */
	*stack = second_node;               /* Update the stack pointer to the new top */
	first_node->prev = second_node;     /* Set the previous pointer for the first node */
}

/**
 * add - Adds the top two elements of the stack
 * @stack: Double pointer to the stack
 * @line_number: Line number of the current operation
 */
void add(stack_t **stack, unsigned int line_number)
{
	stack_t *first_node, *second_node;

	if (*stack == NULL || (*stack)->next == NULL)  /* Check if there are less than 2 elements */
	{
		fprintf(stderr, "L%u: can't add, stack too short\n", line_number);
		exit(EXIT_FAILURE);
	}

	first_node = *stack;              /* Get the top node */
	second_node = first_node->next;   /* Get the second node */

	second_node->n += first_node->n;  /* Add the top two values and store the result in second node */

	/* Update the stack to point to the new top (second node) */
	second_node->prev = NULL;
	*stack = second_node;

	/* Free the old top (first_node) */
	free(first_node);
}


/**
 * nop - Does nothing
 * @stack: Double pointer to the stack
 * @line_number: Line number of the current operation
 */
void nop(stack_t **stack, unsigned int line_number)
{
    (void)stack;         /* Avoid unused parameter warnings */
    (void)line_number;   /* This does nothing */
}

/**
 * sub - Subtracts the top element from the second top element
 * @stack: Double pointer to the stack
 * @line_number: Line number of the current operation
 */
void sub(stack_t **stack, unsigned int line_number)
{
    int difference;

    if (*stack == NULL || (*stack)->next == NULL)
    {
        fprintf(stderr, "L%u: can't sub, stack too short\n", line_number);
        exit(EXIT_FAILURE);
    }

    difference = (*stack)->next->n - (*stack)->n;
    pop(stack, line_number);  /* Remove top element */
    (*stack)->n = difference;
}

/**
 * div_op - Divides the second top element by the top element
 * @stack: Double pointer to the stack
 * @line_number: Line number of the current operation
 */
void div_op(stack_t **stack, unsigned int line_number)
{
    int quotient;

    if (*stack == NULL || (*stack)->next == NULL)
    {
        fprintf(stderr, "L%u: can't div, stack too short\n", line_number);
        exit(EXIT_FAILURE);
    }

    if ((*stack)->n == 0)
    {
        fprintf(stderr, "L%u: division by zero\n", line_number);
        exit(EXIT_FAILURE);
    }

    quotient = (*stack)->next->n / (*stack)->n;
    pop(stack, line_number);  /* Remove top element */
    (*stack)->n = quotient;
}

/**
 * mul - multiplies the second top element of the stack
 * with the top element
 *
 * @stack: double pointer to the stack
 * @line_number: the line number of the current operation
 */
void mul(stack_t **stack, unsigned int line_number)
{
    int product;

    if (*stack == NULL || (*stack)->next == NULL)
    {
        fprintf(stderr, "L%u: can't mul, stack too short\n", line_number);
        exit(EXIT_FAILURE);
    }

    product = (*stack)->next->n * (*stack)->n;  /* Multiply second by first */
    pop(stack, line_number);  /* Remove the top element */
    (*stack)->n = product;
}

/**
 * mod - Computes the remainder of the division of the second top element
 *       by the top element of the stack.
 * @stack: Double pointer to the stack
 * @line_number: Line number of the current operation
 */
void mod(stack_t **stack, unsigned int line_number)
{
    int remainder;

    if (*stack == NULL || (*stack)->next == NULL)
    {
        fprintf(stderr, "L%u: can't mod, stack too short\n", line_number);
        exit(EXIT_FAILURE);
    }

    if ((*stack)->n == 0)
    {
        fprintf(stderr, "L%u: division by zero\n", line_number);
        exit(EXIT_FAILURE);
    }

    remainder = (*stack)->next->n % (*stack)->n;
    pop(stack, line_number);  /* Remove top element */
    (*stack)->n = remainder;
}
