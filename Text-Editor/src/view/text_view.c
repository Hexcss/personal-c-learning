#include "text_view.h"
#include <stdio.h>

void display_content(const TextModel *model) {

    printf("\n--- Editor Content Start ---\n");
    if (model->length == 0) {
        printf("(Empty)\n");
    } else {
        for (size_t i = 0; i < model->length; ++i) {
            char c = model->content[i];
            if (i == model->cursor_pos) {
                printf("|"); 
            }
            putchar(c);
        }
        if (model->cursor_pos == model->length) {
            printf("|"); 
        }
    }
    printf("\n--- Editor Content End ---\n\n");
}

void display_editor_commands() {
    printf("Commands:\n");
    printf("  i - Enter insert mode (type directly to insert text)\n");
    printf("  h - Move cursor left\n");
    printf("  j - Move cursor down (if applicable)\n");
    printf("  k - Move cursor up (if applicable)\n");
    printf("  l - Move cursor right\n");
    printf("  d - Delete character at cursor\n");
    printf("  s - Save changes\n");
    printf("  q - Quit editor\n\n");
    printf("Note: Press 'q' again in insert mode to exit insert mode.\n");
}
