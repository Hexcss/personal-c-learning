#include "./model/text_model.h"
#include "./view/text_view.h"
#include "./controller/text_controller.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
    char filename[1024] = {0}; // Initialize the buffer to zero

    // Determine whether a new file is being created or an existing one is being opened
    int isNewFile = 0;

    if (argc < 2)
    {
        printf("Enter a filename or path to edit (or 'new' for a new file): ");
        if (fgets(filename, sizeof(filename), stdin) == NULL)
        {
            fprintf(stderr, "Error reading input.\n");
            return EXIT_FAILURE;
        }

        size_t len = strlen(filename);
        if (len > 0 && filename[len - 1] == '\n')
        {
            filename[len - 1] = '\0'; // Remove trailing newline
        }

        if (strcmp(filename, "new") == 0)
        {
            printf("Creating a new file. Enter filename: ");
            if (fgets(filename, sizeof(filename), stdin) == NULL)
            {
                fprintf(stderr, "Error reading input.\n");
                return EXIT_FAILURE;
            }
            len = strlen(filename);
            if (len > 0 && filename[len - 1] == '\n')
            {
                filename[len - 1] = '\0'; // Remove trailing newline
            }
            isNewFile = 1; // Mark as a new file
        }
    }
    else
    {
        strncpy(filename, argv[1], sizeof(filename) - 1);
    }

    TextModel *model = create_text_model(filename);
    if (model == NULL)
    {
        fprintf(stderr, "Failed to create model for file: %s\n", filename);
        return EXIT_FAILURE;
    }

    if (!isNewFile && load_file(model) != 0)
    {
        fprintf(stderr, "Failed to load file: %s\n", filename);
        destroy_text_model(model);
        return EXIT_FAILURE;
    }

    TextController *controller = create_text_controller(model);
    if (controller == NULL)
    {
        fprintf(stderr, "Failed to create controller.\n");
        destroy_text_model(model);
        return EXIT_FAILURE;
    }

    display_content(model);
    display_editor_commands();
    start_main_loop(controller);

    // Cleanup
    destroy_text_controller(controller);
    destroy_text_model(model);

    return EXIT_SUCCESS;
}
