#include "text_controller.h"
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h> 

TextController* create_text_controller(TextModel *model) 
{
    TextController *controller = (TextController *)malloc(sizeof(TextController));
    if (controller == NULL) {
        fprintf(stderr, "Failed to allocate TextController.\n");
        return NULL;
    }
    controller->model = model;
    controller->is_running = 1;
    controller->is_insert_mode = 0; 
    return controller;
}

void destroy_text_controller(TextController *controller)
{
    if (controller != NULL)
    {
        free(controller);
    }
}

void handle_keypress(TextController *controller, char key)
{
    switch (key)
    {
    case 'q':
        printf("Quit command received. Exiting...\n");
        controller->is_running = 0;
        break;
    case 'h':
        move_cursor(controller->model, 'h');
        break;
    case 'j':
        move_cursor(controller->model, 'j');
        break;
    case 'k':
        move_cursor(controller->model, 'k');
        break;
    case 'l':
        move_cursor(controller->model, 'l');
        break;
    case 'i':
        toggle_insert_mode(controller);
        break;
    case 'd':
        if (controller->is_insert_mode) {
            delete_character_at_cursor(controller->model);
        }
        break;
    case 's':
        if (save_file(controller->model) == 0)
        {
            printf("File saved.\n");
        }
        else
        {
            printf("Error saving file.\n");
        }
        break;
    default:
        if (controller->is_insert_mode) {
            insert_character_at_cursor(controller->model, key);
        }
        break;
    }
}

void toggle_insert_mode(TextController *controller) 
{
    controller->is_insert_mode = !controller->is_insert_mode;
    printf("Insert mode %s.\n", controller->is_insert_mode ? "enabled" : "disabled");
}

void start_main_loop(TextController *controller) {
    char key;
    printf("Text editor started. Press 'q' to quit.\n");

    while (controller->is_running) {
        key = getchar(); 

        if (key == '\n' || key == '\r') continue;

        handle_keypress(controller, key);

        fflush(stdout);
    }


    if (has_unsaved_changes(controller->model) == 1) {
        printf("You have unsaved changes. Save them? (y/n): ");
        key = getchar();
        if (key == 'y' || key == 'Y') {
            if (save_file(controller->model) == 0) {
                printf("Changes saved. Exiting...\n");
            } else {
                printf("Failed to save changes. Exiting anyway...\n");
            }
        } else {
            printf("Exiting without saving changes.\n");
        }
    }
}
