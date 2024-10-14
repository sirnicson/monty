#include "monty.h"
#include <stdio.h>
#include <stdlib.h>

#define MAX_LENGTH 100  /* Define the maximum length for the output string */

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
    int length = 0; /* Current length of printed string */

    (void)line_number;  /* Ignore unused parameter */

    /* Check if the stack is empty */
    if (current == NULL)
    {
        printf("\n");  /* Print new line if stack is empty */
        return;  /* No further execution */
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
            /* Check if adding this character exceeds the max length */
            if (length >= MAX_LENGTH)
            {
                return;  /* Exit the function if length exceeds */
            }
            printf("%c", value);  /* Print the ASCII character */
            length++;  /* Increment the length of the output */
        }
        else
        {
            printf("0\n");  /* Print 0 for invalid ASCII value */
            return;  /* Exit function */
        }

        current = current->next;  /* Move to the next element in the stack */
    }

    printf("\n");  /* Print a new line at the end */
}


/**
 * rotl - rotates the stack to the top
 * @stack: double pointer to the top of the stack
 * @line_number: current line number in the Monty file (unused)
 *
 * Description: The top element becomes the last one, and the second top
 * element becomes the first one. rotl never fails.
 * Return: void
 */
void rotl(stack_t **stack, unsigned int line_number)
{
    stack_t *first, *last;
    (void)line_number;      /* Ignore unused parameter */

    if (*stack == NULL || (*stack)->next == NULL)
        return;  /* No need to rotate if the stack is empty or has one element */

    first = *stack;
    last = *stack;

    /* Traverse to the last node of the stack */
    while (last->next != NULL)
        last = last->next;

    *stack = first->next;  /* The second element becomes the new top */
    (*stack)->prev = NULL; /* Set the new top's previous to NULL */

    first->next = NULL;    /* The former top element's next is NULL */
    last->next = first;    /* Attach the old top to the end of the stack */
    first->prev = last;    /* Set the previous pointer of the old top to the last element */
}
