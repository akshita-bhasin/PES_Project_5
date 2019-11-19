PES PROJECT 5 README 

This is a readme for Project #5 for the Principles of Embedded Software (Fall 2019) class.

Team Members : Akshita Bhasin & Madhukar Arora

Source Files:

1. circularbuffer.h

2. circularbuffer.c

3. countcharacters.h

4. countcharacters.c

5. led_control.h

6. led_control.c

7. timestamp.h

8. timestamp.c

9. uart.h

10. uart.c

11. timestamp.h

12. timestamp.c

13. test.h

14. test.c

Guides on Compilation / Execution Notes:

Hardware USED : Freedom Board FRDM KL25Z

IDE USED : MCU Xpresso ([https://mcuxpresso.nxp.com/en/welcome](https://mcuxpresso.nxp.com/en/welcome))

1. Clean before building any build targets.

2. Go to logger.c and choose log_level_a as 0 for TEST, 1 for Debug and 2 for Normal:
   
   Please refer to the following enums along with their functionality for compilation.
   
   1. log_level - Debug
      
      If selected, the program will run in debug mode with detailed messages logged to the UART.
   
   2. log_level - Normal
      
      If selected, the program will run in normal mode with normal messages logged to the UART.
   
   3. log_level - Test
      
      If selected, the program will run in test mode with detailed test messages logged to the UART.
      
      Note : If there are any elf errors, delete the existing Debug folder and create a new one.

RUNNING THE CODE IN APPLICATION MODE:

The program prompts the user to press a return key in order to run in application mode. If a enter key(ASCII 13) is pressed, a character report is printed that will show all the characters received along with counts.

For example, if the PC sent the characters in the word “Characters" the resulting report

would look like (with data in ASCII value order):

C – 1; a – 2; c – 1; e – 1; h – 1; r – 2; s – 1; t – 1

Observations:

1. Getting UART to work with interrupts took us sometime due to an issue with the interrupt flag setting.

2. Setting the right system clock/ oversample rate was the key which was understood well after reading the datasheet. Understood timing diagrams to get it working.

3. Unit test cases did not print, and solving the fsl_common issue took us a while. The Debug_console_init function returned various errors, and using an auto-generated makefile was the only way out.

4. Getting circular buffer and uart working together, making the character report stop for a character(tested by altering code so it prints infinitely until a charcter is received)


