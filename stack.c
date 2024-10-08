#include "monty.h"
#include <stdio.h>
#include <stdlib.h>


/**
 * print_error - prints an error message with the line number
 * @line_number: current line number in the Monty file
 * @message: error message to display
 */
void print_error(unsigned int line_number, const char *message)
{
    printf("Error at line %u: %s\n", line_number, message);
}

/**
 * pchar - prints the char at the top of the stack
 * @stack: double pointer to the top of the stack
 * @line_number: current line number in the Monty file
 *
 * Return: void
 */
void pchar(stack_t **stack, unsigned int line_number)
{
    int value;

    if (*stack == NULL)
    {
        fprintf(stderr, "L%u: can't pchar, stack empty\n", line_number);
        exit(EXIT_FAILURE);
    }

    value = (*stack)->n;

    if (value < 0 || value > 127)
    {
        fprintf(stderr, "L%u: can't pchar, value out of range\n", line_number);
        exit(EXIT_FAILURE);
    }

    printf("%c\n", value);
}


/**
 * pstr - prints the string starting from the top of the stack
 * @stack: double pointer to the top of the stack
 * @line_number: current line number in the Monty file
 *
 * Return: void
 */
void pstr(stack_t **stack, unsigned int line_number)
{
    stack_t *current = *stack;  /* Pointer to traverse the stack */
    int value;

    /* Check is the stack is empty first*/
    if (current == NULL)
    {
	printf("\n");  /*  Print new line if stack is empty */
        return; /* No further execution */
    }

    /* Traverse the stack and print characters until conditions are met */
    while (current != NULL)
    {
        value = current->n;  /* Get the value at the top of the stack */

        /* Stop if value is 0 */
        if (value == 0)
            break;

	/* Only print valid ASCII characters */
	if (value > 0 && value <= 127)
	{
		printf("%c", value);  /* Print the ASCII character */
	}
	else
	{
		/* Print the error message when encountering an invalid ASCII value */
		print_error(line_number, "Invalid ASCII value encountered");
		return;
	}

        current = current->next;  /* Move to the next element in the stack */
    }

    printf("\n");  /* Print a new line at the end */
}
