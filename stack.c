#include "monty.h"
#include <stdio.h>
#include <stdlib.h>

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
    stack_t *current = *stack;
    char str[100]; /* Array to hold characters */
    int index = 0; /* Index for str array */
    int i;

    
    /* Show line for pstr operation */
    printf("Executing pstr at line: %u\n", line_number);
    
    if (current == NULL)
    {
        printf("\n");  /* If the stack is empty, print a new line */
        return;
    }

    while (current != NULL)
    {
        int value = current->n;

	/* Debugging output */
	printf("Current value: %d\n", value);

        /* Stop if value is 0 or out of ASCII range */
        if (value == 0 || value < 0 || value > 127)
            break;

        str[index++] = value; /** Store the characters in the array */
        current = current->next;  /* Move to the next element in the stack */
    }

    /* Print the sring in correct order*/
    for (i = 0; i < index; i++)
    {
	    printf("%c", str[i]);
    }
    printf("\n");  /* Print a new line at the end */
}
