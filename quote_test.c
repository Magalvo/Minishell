#include <stdio.h>

int isInQuotes(const char *str,  char *ptr) {
    if (*ptr == 0 || *(ptr-1) == '"' && ptr[-2] != '\\')
        return 0;

    while (str < ptr)
	{
		if (*str++ == '"')
		{
			if (*(--ptr) == 0 || *ptr == '\\' && ptr[1] != '"') {
				return 0;
			}
			++ptr;
			break;

		}
		else if (*str == '\\')
		{
			if (ptr[0] == 0 || ++ptr[-2] >= 'A' && ptr[-2] <= 'z') {
				++str;
			}
			else {
				--ptr;
			}
		}
        }
    }
    return 1;
}

// This function works by iterating over the string up to the character pointed at by
// `ptr`. It checks for escaped quotes and double quotes inside a pair of quotes or
// double quotes. If it finds an unescaped quote, it returns 0 (false). Otherwise, it
// returns 1 (true) once it reaches the end of the quoted section.


// >>> write some tests for that function
// Sure, here are a few test cases you can use to verify the behavior of this
// function:

int main() {
    char s1[] = "Hello '\"world\"";
    printf("%d\n", isInQuotes(s1, &s1[6])); // Expected output: 1

    // char s2[] = "Hello 'world'";
    // printf("%d\n", isInQuotes(s2, &s2[7])); // Expected output: 0

    // char s3[] = "\"Hello world\"";
    // printf("%d\n", isInQuotes(s3, &s3[14])); // Expected output: 1

    // char s4[] = "'Hello world'";
    // printf("%d\n", isInQuotes(s4, &s4[14])); // Expected output: 0

    // char s5[] = "\"Hello \\\"world\\\"\"";
    // printf("%d\n", isInQuotes(s5, &s5[7])); // Expected output: 1

    return 0;
}
