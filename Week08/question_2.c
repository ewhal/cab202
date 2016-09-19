/*	CAB202: Tutorial 7
*	Question 2 - Template
*
*	B.Talbot, April 2016
*	Queensland University of Technology
*/
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define LINE_LENGTH 79

#define NUM_PROBS 10
#define NUM_TESTS 50

#define STR_PASS "PASSED!"
#define STR_FAIL "FAILED!"

/*
* Function declarations (all of these are already implemented)
*/
void print_heading(char bkgChar, char* heading, int offset);

/*
* Complete each of these functions correctly to complete the exercise If you are
* correct, the corresponding test will pass. YOU DO NOT HAVE TO MODIFY ANYTHING
* IN THIS FILE, BESIDES THE 10 FUNCTIONS BELOW!!!
1. Set a bit (override)
2. Clear a bit (override)
3. Set a bit (unchanged)
4. Clear a bit (unchanged)
5. Toggle a byte
6. Toggle a bit (unchanged)
7. Reading a specific bit
8. Set a bit, toggle the byte, read a bit
9. Set all bits up to and including n
10.For a pointer to a byte, extract data in the 2 M.S.B.
*/
unsigned char answer_1(int arg0) {
    arg0 = (1 << arg0);
    return arg0;
}

unsigned char answer_2(unsigned char arg0) {
    arg0 = ~(1 << arg0);
    return arg0;
}

unsigned char answer_3(unsigned char arg0, int arg1) {
    arg0 = arg0 | (1 << arg1);
    return arg0;
}

unsigned char answer_4(unsigned char arg0, int arg1) {
    arg0 = arg0 & ~(1 << arg1);
    return arg0;
}

unsigned char answer_5(unsigned char arg0) {
    arg0 = ~arg0;
    return arg0;
}

unsigned char answer_6(unsigned char arg0, int arg1) {
    arg0 =  arg0 ^ (1 << arg1);
    return arg0;
}

unsigned char answer_7(unsigned char arg0, int arg1) {
    arg0 = (arg0 >> arg1) & 1;
    return arg0;
}

unsigned char answer_8(unsigned char arg0, int arg1, int arg2) {
    arg0 = (~(arg0 | (1 << arg1)) >> arg2) & 1;
    return arg0;
}

unsigned char answer_9(int arg0) {
    unsigned char cha = ~(~0 << (arg0+1));
    return cha;
}

unsigned char answer_10(unsigned char *arg0) {
    arg0 = (*arg0 & 0xC0) >> 6;
    return arg0;
}

/*
* Main - there's no need to look any further. The question is about completing
* the bitwise operations above correctly. Yes, hints at the answers are in here,
* but deciphering the hints is more difficult than simply completing the correct
* implementation for the above functions.
*/
int main() {
    // Get some randomness happening to keep things interesting...
    time_t t;
	srand((unsigned) time(&t));

    // Print the title section
    print_heading('~', NULL, 0);
    print_heading('~', "Playing with bits and bytes", (LINE_LENGTH-27)/2);
    print_heading('~', NULL, 0);
    printf("\n");

    // Loop through each of the problems: display description, text expected vs actual, display results
    int n, m;
    unsigned char b, *b_p, ex_uc, ac_uc;
    bool failed[NUM_PROBS];
    for (int i = 0; i < NUM_PROBS; i++) {
        switch (i) {
            case 0:
                print_heading('.', "|PROBLEM 1|", 5);
                printf("'answer_1()' receives a bit number. Return a byte with the corresponding bit\nset, and all other bits cleared.\nTesting...\n");
                for (int ii = 0; ii < NUM_TESTS; ii++) {
                    n = rand() % 8;
                    ex_uc = (1 << n);
                    ac_uc = answer_1(n);
                    failed[i] = !(ex_uc == ac_uc);
                    if (failed[i]) {
                        break;
                    }
                }
                printf("Expected return:\t0x%02X\t\tActual return:\t0x%02X\t\t%s\n", ex_uc, ac_uc, failed[i] ? STR_FAIL : STR_PASS);
                break;
            case 1:
                print_heading('.', "|PROBLEM 2|", 5);
                printf("'answer_2()' receives a bit number. Return a byte with the corresponding bit\ncleared, and all other bits set.\nTesting...\n");
                for (int ii = 0; ii < NUM_TESTS; ii++) {
                    n = rand() % 8;
                    ex_uc = ~(1 << n);
                    ac_uc = answer_2(n);
                    failed[i] = !(ex_uc == ac_uc);
                    if (failed[i]) {
                        break;
                    }
                }
                printf("Expected return:\t0x%02X\t\tActual return:\t0x%02X\t\t%s\n", ex_uc, ac_uc, failed[i] ? STR_FAIL : STR_PASS);
                break;
            case 2:
                print_heading('.', "|PROBLEM 3|", 5);
                printf("'answer_3()' receives a byte and bit number. Return the same byte with the\ncorresponding bit set, and all other bits unchanged.\nTesting...\n");
                for (int ii = 0; ii < NUM_TESTS; ii++) {
                    n = rand() % 8;
                    b = rand() % 256;
                    ex_uc = b | (1 << n);
                    ac_uc = answer_3(b, n);
                    failed[i] = !(ex_uc == ac_uc);
                    if (failed[i]) {
                        break;
                    }
                }
                printf("Expected return:\t0x%02X\t\tActual return:\t0x%02X\t\t%s\n", ex_uc, ac_uc, failed[i] ? STR_FAIL : STR_PASS);
                break;
            case 3:
                print_heading('.', "|PROBLEM 4|", 5);
                printf("'answer_4()' receives a byte and bit number. Return the same byte with the\ncorresponding bit cleared, and all other bits unchanged.\nTesting...\n");
                for (int ii = 0; ii < NUM_TESTS; ii++) {
                    n = rand() % 8;
                    b = rand() % 256;
                    ex_uc = b & ~(1 << n);
                    ac_uc = answer_4(b, n);
                    failed[i] = !(ex_uc == ac_uc);
                    if (failed[i]) {
                        break;
                    }
                }
                printf("Expected return:\t0x%02X\t\tActual return:\t0x%02X\t\t%s\n", ex_uc, ac_uc, failed[i] ? STR_FAIL : STR_PASS);
                break;
            case 4:
                print_heading('.', "|PROBLEM 5|", 5);
                printf("'answer_5()' receives a byte. Return the byte with all 8 bits toggled.\nTesting...\n");
                for (int ii = 0; ii < NUM_TESTS; ii++) {
                    b = rand() % 256;
                    ex_uc = ~b;
                    ac_uc = answer_5(b);
                    failed[i] = !(ex_uc == ac_uc);
                    if (failed[i]) {
                        break;
                    }
                }
                printf("Expected return:\t0x%02X\t\tActual return:\t0x%02X\t\t%s\n", ex_uc, ac_uc, failed[i] ? STR_FAIL : STR_PASS);
                break;
            case 5:
                print_heading('.', "|PROBLEM 6|", 5);
                printf("'answer_6()' receives a byte and bit number. Return the same byte with the\ncorresponding bit toggled, and all other bits unchanged.\nTesting...\n");
                for (int ii = 0; ii < NUM_TESTS; ii++) {
                    n = rand() % 8;
                    b = rand() % 256;
                    ex_uc = b ^ (1 << n);
                    ac_uc = answer_6(b, n);
                    failed[i] = !(ex_uc == ac_uc);
                    if (failed[i]) {
                        break;
                    }
                }
                printf("Expected return:\t0x%02X\t\tActual return:\t0x%02X\t\t%s\n", ex_uc, ac_uc, failed[i] ? STR_FAIL : STR_PASS);
                break;
            case 6:
                print_heading('.', "|PROBLEM 7|", 5);
                printf("'answer_7()' receives a byte and bit number. Return the value (set or unset)\nof the corresponding bit.\nTesting...\n");
                for (int ii = 0; ii < NUM_TESTS; ii++) {
                    n = rand() % 8;
                    b = rand() % 256;
                    ex_uc = (b >> n) & 1;
                    ac_uc = answer_7(b, n);
                    failed[i] = !(ex_uc == ac_uc);
                    if (failed[i]) {
                        break;
                    }
                }
                printf("Expected return:\t%d\t\t\tActual return:\t%d\t\t\t%s\n", ex_uc, ac_uc, failed[i] ? STR_FAIL : STR_PASS);
                break;
            case 7:
                    print_heading('.', "|PROBLEM 8|", 5);
                    printf("'answer_8()' receives a byte and two bit numbers. Set the bit corresponding\nto the first bit number, toggle every bit in the byte, then return the value of\nthe bit corresponding to the second bit number.\nTesting...\n");
                    for (int ii = 0; ii < NUM_TESTS; ii++) {
                        n = rand() % 8;
                        m = rand() % 8;
                        b = rand() % 256;
                        ex_uc = (~(b | (1 << n)) >> m) & 1;
                        ac_uc = answer_8(b, n, m);
                        failed[i] = !(ex_uc == ac_uc);
                        if (failed[i]) {
                            break;
                        }
                    }
                    printf("Expected return:\t%d\t\t\tActual return:\t%d\t\t\t%s\n", ex_uc, ac_uc, failed[i] ? STR_FAIL : STR_PASS);
                    break;
            case 8:
                    print_heading('.', "|PROBLEM 9|", 5);
                    printf("'answer_9()' receives a bit number. Return a byte with every bit up to\nand including that bit number set, with all other bits cleared.\nTesting...\n");
                    for (int ii = 0; ii < NUM_TESTS; ii++) {
                        n = rand() % 8;
                        ex_uc = ~(~0 << (n+1));
                        ac_uc = answer_9(n);
                        failed[i] = !(ex_uc == ac_uc);
                        if (failed[i]) {
                            break;
                        }
                    }
                    printf("Expected return:\t0x%02X\t\tActual return:\t0x%02X\t\t%s\n", ex_uc, ac_uc, failed[i] ? STR_FAIL : STR_PASS);
                    break;
            case 9:
                    print_heading('.', "|PROBLEM 10|", 5);
                    printf("'answer_10()' receives a pointer to a byte. Return the data in the two most\nsignificant bits of that byte.\nTesting...\n");
                    for (int ii = 0; ii < NUM_TESTS; ii++) {
                        b = rand() % 256;
                        b_p = &b;
                        ex_uc = (*b_p & 0xC0) >> 6;
                        ac_uc = answer_10(b_p);
                        failed[i] = !(ex_uc == ac_uc);
                        if (failed[i]) {
                            break;
                        }
                    }
                    printf("Expected return:\t0x%02X\t\tActual return:\t0x%02X\t\t%s\n", ex_uc, ac_uc, failed[i] ? STR_FAIL : STR_PASS);
                    break;
            default:
                return -1;
        }
        print_heading('.', NULL, 0);
        printf("\n\n");
    }

    // Compile the results
    int total = 0;
    for (int i = 0; i<NUM_PROBS; i++) {
        total += failed[i] ? 0 : 1;
    }

    // Print a verbose summary
    char buff[80];
    print_heading('~', NULL, 0);
    sprintf(buff, "Your total score for the problems was: %.2d / %.2d", total, NUM_PROBS);
    print_heading('~', buff, (LINE_LENGTH-46)/2);
    print_heading('~', NULL, 0);
    if (total == NUM_PROBS) {
        sprintf(buff, "You managed to find where all of your missing data was!");
        sprintf(buff, "Well done. You've mastered playing with bits and bytes!");
    } else {
        sprintf(buff, "Keep on playing with my bits until you get them all ...");
    }
    print_heading('~', buff, (LINE_LENGTH-55)/2);
    print_heading('~', NULL, 0);

    // Return
    return 0;
}

/*
* Function implementations
*/
void print_heading(char bkgChar, char *heading, int offset) {
    char buff[LINE_LENGTH+1];
    bool endFound = false;
    for (int i = 0; i<=LINE_LENGTH; i++) {
        if (i == LINE_LENGTH) {
            buff[i] = '\0';
        } else if (heading == NULL) {
            buff[i] = bkgChar;
        } else if (i == offset) {
            buff[i] = ' ';
        } else if (i > offset && !endFound && heading[i-offset-1] == '\0') {
            buff[i] = ' ';
            endFound = true;
        } else if (i > offset && !endFound) {
            buff[i] = heading[i-offset-1];
        } else {
            buff[i] = bkgChar;
        }
    }
    printf("%s\n", buff);
}
