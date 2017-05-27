/*
 * CS 261 Assignment 5
 * Name: Jonathan Ingram
 * Date: 5/28/17
 */

#include "dynamicArray.h"
#include "task.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

/**
 * Loads into heap a list from a file with lines formatted like
 * "priority, name".
 * @param heap
 * @param file
 */
void listLoad(DynamicArray* heap, FILE* file)
{
    const int FORMAT_LENGTH = 256;
    char format[FORMAT_LENGTH];
    snprintf(format, FORMAT_LENGTH, "%%d, %%%d[^\n]", TASK_NAME_SIZE);

    Task temp;
    while (fscanf(file, format, &temp.priority, &temp.name) == 2)
    {
        dyHeapAdd(heap, taskNew(temp.priority, temp.name), taskCompare);
    }
}

/**
 * Writes to a file all tasks in heap with lines formatted like
 * "priority, name".
 * @param heap
 * @param file
 */
void listSave(DynamicArray* heap, FILE* file)
{
    for (int i = 0; i < dySize(heap); i++)
    {
        Task* task = dyGet(heap, i);
        fprintf(file, "%d, %s\n", task->priority, task->name);
    }
}

/**
 * Prints every task in heap.
 * @param heap
 */
void listPrint(DynamicArray* heap)
{
    DynamicArray* temp = dyNew(1);
    dyCopy(heap, temp);
     while (dySize(temp) > 0)
    {
        Task* task = dyHeapGetMin(temp);
        printf("\n");
        taskPrint(task);
        printf("\n");
        dyHeapRemoveMin(temp, taskCompare);
    }
    dyDelete(temp);
}

/**
 * Handles the given command.
 * @param list
 * @param command
 */
void handleCommand(DynamicArray* list, char command)
{
    // FIXME: Implement
    char *fileName = (char*)malloc(sizeof(char) * 256);
    char *tskDecript = (char*)malloc(sizeof(char) * 256);
    int tskPriority;

    //command loop
    while(command){
        case 'l':
            printf("Enter file to load: ");
            fgets(fileName, 100, stdin);
            if(fileName[strlen(fileName) - 1] == '\n'){
                fileName[strlen(fileName) - 1] = 0;
            }
            FILE *read = fopen(fileName, "r");
            listLoad(list, read);
            printf("Loaded from file. \n \n");
            fclose(read);
            break;
        case 's':
            printf("Enter file to store: ");
            fgets(fileName, 100, stdin));
            if(fileName[strlen(fileName) - 1] == 'n'){
                fileName[strlen(fileName) - 1] = 0;
            }
            FILE *fileWRR = fopen(fileName, "w+");
            listSave(list, fileWRR);
            break;
        case 'a':
            printf("Task description: ");
            fgets(tskDecript, 100, stdin);
            if(tskDecript[strlen(tskDecript) - 1] == '\n'){
                tskDecript[strlen(tskDecript) - 1] = 0;
            }
            printf("Assign task priority (0-999): ");
            scanf("%d", &tskPriority);
            while(getchar() != '\n');
            Task *newTask = taskNew(tskPriority, tskDecript);
            dyHeapAdd(list, newTask, taskCompare);
            printf("Task added. \n\n");
            break;
        case 'g':
            if(dySize(list) != 0){
                printf("1st task: %s\n", ((struct Task*)dyHeapGetMin(list))->name);
            }
            else{
                printf("Empty To Do List. \n\n");
            }
            break;
        case 'r';
            if(dySize(list) == 0){
                printf("Empty To Do list.\n");
            }
            else{
                struct Task* removeTask = (struct Task*)dyHeapGetMin(list);
                printf("Removed task: %s\n", removeTask->name);
                taskDelete(removeTask);
            }
            printf("\n\n");
            break;
        case 'p':
            if(dySize(list) == 0){
                printf("Empty To Do list.\n");
            }
            else{
                listPrint(list);
            }
            break;
        case 'e':
            printf("Good Bye");
            break;
    }
    free(tskDecript);
    free(fileName);

}

int main()
{
    // Implement
    printf("\n\n** TO-DO LIST APPLICATION **\n\n");
    DynamicArray* list = dyNew(8);
    char command = ' ';
    do
    {
        printf("Press:\n"
               "'l' to load to-do list from a file\n"
               "'s' to save to-do list to a file\n"
               "'a' to add a new task\n"
               "'g' to get the first task\n"
               "'r' to remove the first task\n"
               "'p' to print the list\n"
               "'e' to exit the program\n"
        );
        command = getchar();
        // Eat newlines
        while (getchar() != '\n');
        handleCommand(list, command);
    }
    while (command != 'e');
 /* free dynamically allocated List pointers in array to avoid memory leaks */
         /* Fix it */

    dyDelete(list);
    return 0;
}
