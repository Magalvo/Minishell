/*
write a parsing function that takes a str as input and a pointer to a char
on that string. then parses the string for quotes and double quotes, telling
if the pointer is inside quotes and if is inside nested quotes,
it should indicate that if pointer is inside qutes or nested quotes what type
 of quotes are they. this is to detect if pointer is expandable or no.

Here's a function in C that accomplishes this task. It uses a stack to keep track
of the nested quotes. The function isInQuotes takes a string str and
a pointer ptr to a character in that string as input. It returns the depth
of nested quotes the character is in, or -1 if the character is not in any quotes.
It also prints the type of quote the character is in.
*/

// GitHub Copilot
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
	char quote;
	int depth;
} QuoteInfo;

QuoteInfo isInQuotes(const char *str, const char *ptr) {
	QuoteInfo *stack = (QuoteInfo*)malloc(strlen(str) * sizeof(QuoteInfo));
	int top = -1;
	int i = 0;

	while (str[i] != '\0') {
		if (str[i] == '"' || str[i] == '\'') {
			if (top != -1 && stack[top].quote == str[i]) {
				// Ending quote found, pop from stack
				top--;
			} else {
				// Starting quote found, push to stack
				stack[++top] = (QuoteInfo){.quote = str[i], .depth = top + 1};
			}
		}

		if (&str[i] == ptr) {
			// Pointer found, return current quote info
			QuoteInfo result = (top != -1) ? stack[top] : (QuoteInfo){.quote = '\0', .depth = -1};
			free(stack);
			return result;
		}

		i++;
	}

	free(stack);
	return (QuoteInfo){.quote = '\0', .depth = -1};
}

int main() {
	// const char *str = "This is a 'test' and this is a \"'nested' test\".";
	const char *str = "A 'a' 'quote \"string\"' with "" NULL n '' null.";
	const char *ptr = &str[28]; // Points to the 't' in "with"
	QuoteInfo info = isInQuotes(str, ptr);
	if (info.depth != -1) {
		printf("Character is inside %d nested quotes of type %c\n", info.depth, info.quote);
	} else {
		printf("Character is not inside any quotes\n");
	}
	ptr = &str[17]; // Points to the 't' in "string"
	info = isInQuotes(str, ptr);
	if (info.depth != -1) {
		printf("Character is inside %d nested quotes of type %c\n", info.depth, info.quote);
	} else {
		printf("Character is not inside any quotes\n");
	}
	return 0;
}

/*
This function works by iterating over each character in the string.
If it encounters a quote, it checks if the top of the stack contains the same
type of quote. If it does, it pops from the stack, indicating the end of a quote.
If it doesn't, it pushes the quote to the stack, indicating the start of a new quote.
When it encounters the character pointed to by ptr, it returns the current depth
of nested quotes and the type of quote, which are the number of elements
in the stack and the type of the top quote.
If it doesn't find the character in any quotes, it returns -1 and \0
for the depth and quote type, respectively.
*/
