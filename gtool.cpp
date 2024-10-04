// gtool.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <locale.h>
#include <stdio.h>
#include <string.h>

#include <stdio.h>
#include <wchar.h>
#include <locale.h>
#include <stdlib.h>
#include <string.h>

// Define buffer size
#define BUFFER_SIZE (1024*128)

int w_main(int argc, char* argv[]) {
    // Set locale to handle UTF-8 properly
    setlocale(LC_ALL, "");

    // Ensure correct number of arguments
    if (argc != 4) {
        fwprintf(stderr, L"Usage: %s <arg1> <arg2> <filename>\n", argv[0]);
        return 1;
    }

    // Convert command-line arguments to wide strings (UTF-8 encoded)
    wchar_t arg1[BUFFER_SIZE], arg2[BUFFER_SIZE];
    size_t cStart, cEnd;

    mbstowcs_s(& cStart, arg1, sizeof(arg1), argv[1], BUFFER_SIZE);
    mbstowcs_s(&cEnd, arg2, sizeof (arg2), argv[2], BUFFER_SIZE);
    fwprintf(stderr, L"start-end=(%d,%d)\n", cStart, cEnd);

    // Open the file for reading
    FILE* file=NULL;
    int erro;

    erro=fopen_s(&file,argv[3], "r");
    if (file == NULL) {
        fwprintf(stderr, L"Could not open file %s for reading.\n", argv[3]);
        return 9;
    }

    // Read the entire file content into a buffer
    wchar_t winput[BUFFER_SIZE];
    char input[BUFFER_SIZE];

    erro=fread_s(input, BUFFER_SIZE, sizeof(char), BUFFER_SIZE, file);
    
    if (erro==0) {
        wprintf(L"Error reading from file.\n");
        fclose(file);
        return 8;
    }

    
    mbstowcs_s(&cStart, winput, BUFFER_SIZE, input, BUFFER_SIZE);
    // Close the file after reading
    fclose(file);

    // Find the first occurrence of arg1 and arg2 in the input
    wchar_t* start = wcsstr(winput, arg1);
    if (start == NULL)
    {
        fwprintf(stderr, L"(%s) not found\n", arg1);
        return (1);
    }
    wchar_t* end = wcsstr(start, arg2);
    if (end == NULL)
    {
        fwprintf(stderr, L"(%s) not found\n", arg2);
        return (2);
    }
    // If both arg1 and arg2 are found and in the correct order
    if (start != NULL && end != NULL && start < end) {
        // Move the pointer to the end of arg1
        start += wcslen(arg1);

        // Print everything between arg1 and arg2
        while (start < end) {
            putwchar(*start);
            start++;
        }
        wprintf(L"\n");
    }
    else {
        wprintf(L"Could not find the strings in the input or they are in the wrong order.\n");
    }

    return 0;
}


int main(int argc, char* argv[]) {

    return (w_main(argc, argv));

}
