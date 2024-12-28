#define _CRT_SECURE_NO_WARNINGS
#define SIZE 100
#define TASK_1

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h> 

#ifdef TASK_1
int main() {
	char string[SIZE] = { 0 };
	fgets(string, sizeof(string), stdin);
	for (int i = 0; i < strlen(string); i++) {
		if ((i+1) % 2 == 0) {
			if (islower(string[i])) {
				string[i] = toupper(string[i]);
			}
			else if (isupper(string[i])) {
				string[i] = tolower(string[i]);
			}
		}
	}
	puts(string);
	return 0;
}
#endif

#ifdef TASK_2
void replace_substring(char* string, char* old_substring, char* new_substring) {
	int old_len = strlen(old_substring);
	int new_len = strlen(new_substring);
	char* buffer_string = string;
	while ((buffer_string = strstr(buffer_string, old_substring)) != NULL) {
		memmove(buffer_string + new_len, buffer_string + old_len, strlen(buffer_string + old_len) + 1);
		memcpy(buffer_string, new_substring, new_len);
		buffer_string += new_len;
	}
}
int main() {
	char string[SIZE];
	char old_substring[SIZE-1];
	char new_substring[SIZE-1];
	fgets(string, sizeof(string), stdin);
    string[strcspn(string, "")] = 0;
	scanf("%s", &old_substring);
	scanf("%s", &new_substring);
	replace_substring(string, old_substring, new_substring);
	printf("%s", string);
	return 0;
}
#endif

#ifdef TASK_3
int main() {
	char string[SIZE] = { 0 };
    int i, j, string_len = 0;
    int palindrome = 1;
	gets(string);
    string_len = strlen(string);
	for (i = 0, j = string_len - 1; i < string_len / 2; i++, j--) {
		if (string[i] != string[j]) {
			palindrome = 0;
			break;
		}
	}
	if (palindrome==1) {
		printf("Palindrome");
	}
	else {
		printf("Not a palindrome");
	}
    return 0;
}
#endif

#ifdef TASK_4
int main() {
	char string[SIZE];
	char* result = malloc((strlen(string) + 1) * sizeof(char));
	int j = 0;
	scanf("%s", string);
	for (int i = 0; i < strlen(string); i++) {
		if (string[i] == 'G') {
			result[j] = 'G';
			j++;
		}
		else if (string[i] == '(' && string[i + 1] == ')') {
			result[j] = 'o';
			i++;
			j++;
		}
		else if (string[i] == '(' && string[i + 1] == 'a' && string[i + 2] == 'l' && string[i + 3] == ')') {
			result[j] = 'a';
			result[j + 1] = 'l';
			i += 3;
			j += 2;
		}
	}
	result[j] = '\0';
	printf("%s", result);
	return 0;
}
#endif

#ifdef TASK_5
#include <complex.h>
#include <stdbool.h>
typedef struct complexNumber {
	int real;
	int imaginary;
} 
complexNumber;
	complexNumber summation(complexNumber a, complexNumber b) {
		complexNumber result;
	    result.real = a.real + b.real;
	    result.imaginary = a.imaginary + b.imaginary;
	    return result;
	}
	complexNumber subtract(complexNumber a, complexNumber b) {
		complexNumber result;
		result.real = a.real - b.real;
		result.imaginary = a.imaginary - b.imaginary;
		return result;
	}
	complexNumber multiplication(complexNumber a, complexNumber b) {
		complexNumber result;
		result.real = a.real * b.real - a.imaginary * b.imaginary;
		result.imaginary = a.real * b.imaginary + a.imaginary * b.real;
		return result;
	}
	complexNumber division(complexNumber a, complexNumber b) {
		complexNumber result;
		int denominator = b.real * b.real + b.imaginary * b.imaginary;
		if (denominator == 0) {
			printf("Does not exist ");
		}
		else {
			result.real = (a.real * b.real + a.imaginary * b.imaginary) / denominator;
		    result.imaginary = (a.imaginary * b.real - a.real * b.imaginary) / denominator;
		    return result;
	    }
	}
	bool equal(complexNumber a, complexNumber b) {
		return (a.real == b.real) && (a.imaginary == b.imaginary);
	}
	bool notEqual(complexNumber a, complexNumber b) {
		return (a.real != b.real) || (a.imaginary != b.imaginary);
	}
int main() {
	int real1, real2, imaginary1, imaginary2;
	printf("Enter as 'real' + 'imaginary'i\n");
	scanf("%d + %di", &real1, &imaginary1);
	scanf("%d + %di", &real2, &imaginary2);
	complexNumber number1 = { real1, imaginary1 };
	complexNumber number2 = { real2, imaginary2 };
	printf("Summation: %d + %di\n", summation(number1, number2).real, summation(number1, number2).imaginary);
	printf("Subtract: %d + %di\n", subtract(number1, number2).real, subtract(number1, number2).imaginary);
	printf("Multiplication: %d + %di\n", multiplication(number1, number2).real, multiplication(number1, number2).imaginary);
	printf("Division: %d + %di\n", division(number1, number2).real, division(number1, number2).imaginary);
	if (equal(number1, number2)) {
		printf("Equal\n");
	}
	else {
		printf("Not equal\n");
	}
	if (notEqual(number1, number2)) {
		printf("Not equal\n");
	}
	else {
		printf("Equal\n");
	}
	return 0;
}
#endif

#ifdef TASK_6
#include <stdbool.h>
struct point {
	double x;
	double y;
};
struct circle {
	double radius;
	struct point center;
};
/*6.1*/
int concentricSearch(struct circle circle1, struct circle circle2) {
	return (circle1.center.x == circle2.center.x && circle1.center.y == circle2.center.y);
}
/*6.2*/
int nestedSearch(struct circle circle1, struct circle circle2) {
	return (circle1.radius < circle2.radius) && ((circle1.center.x - circle2.center.x) * (circle1.center.x - circle2.center.x) + (circle1.center.y - circle2.center.y) * (circle1.center.y - circle2.center.y) < circle2.radius * circle2.radius);
}
/*6.3*/
int intersectingSearch(struct circle circle1, struct circle circle2) {
	double distance = (circle1.center.x - circle2.center.x) * (circle1.center.x - circle2.center.x) + (circle1.center.y - circle2.center.y) * (circle1.center.y - circle2.center.y);
	return distance < (circle1.radius + circle2.radius) * (circle1.radius + circle2.radius);
}
/*6.4*/
int isolatedSearch(struct circle plane[], int n, int index) {
	for (int i = 0; i < n; i++) {
		if (i != index) {
			double distance = (plane[i].center.x - plane[index].center.x) * (plane[i].center.x - plane[index].center.x) + (plane[i].center.y - plane[index].center.y) * (plane[i].center.y - plane[index].center.y);
			if (distance < (plane[i].radius + plane[index].radius) * (plane[i].radius + plane[index].radius)) {
				return 0;
			}
		}
	}
	return 1;
}
int main() {
	struct circle plane[SIZE / 2];
	bool concentricFound, nestedFound = false;
	bool intersectingFound, isolatedFound = false;
	for (int i = 0; i < 50; i++) {
		for (int j = i + 1; j < 50; j++) {
			if (concentricSearch(plane[i], plane[j]) == 1) {
				concentricFound = true;
			}
			if (nestedSearch(plane[i], plane[j]) == 1) {
				nestedFound = true;
			}
			if (intersectingSearch(plane[i], plane[j]) == 1) {
				intersectingFound = true;
			}
		}
		if (isolatedSearch(plane, 50, i) == 1) {
			isolatedFound = true;
		}
	}
	if (concentricFound) {
		printf("At least 2 concentric circles found\n");
	}
	else {
		printf("No concentric circles found\n");
	}
	if (nestedFound) {
		printf("At least 2 nested circles found\n");
	}
	else {
		printf("No nested circles found\n");
	}
	if (intersectingFound) {
		printf("At least 3 intersecting circles found\n");
	}
	else {
		printf("No intersecting circles found\n");
	}
	if (isolatedFound) {
		printf("At least 1 isolated circle found\n");
	}
	else {
		printf("No isolated circles found\n");
	}
	return 0;
}
#endif