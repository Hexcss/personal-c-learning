#include "text_model.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

TextModel *create_text_model(const char *filename)
{
    TextModel *model = (TextModel *)malloc(sizeof(TextModel));
    if (model == NULL)
    {
        fprintf(stderr, "Memory allocation failed for TextModel\n");
        return NULL;
    }
    model->length = 0;
    model->content = NULL;
    if (filename != NULL)
    {
        model->filename = strdup(filename);
    }
    else
    {
        model->filename = NULL;
    }
    return model;
}

void destroy_text_model(TextModel *model)
{
    if (model != NULL)
    {
        free(model->content);
        free(model->filename);
        free(model);
    }
}

int load_file(TextModel *model)
{
    FILE *file = fopen(model->filename, "r");
    if (file == NULL)
    {
        fprintf(stderr, "Could not open file %s for reading\n", model->filename);
        return -1;
    }

    fseek(file, 0, SEEK_END);
    long length = ftell(file);
    fseek(file, 0, SEEK_SET);

    model->content = (char *)malloc(length + 1);
    if (model->content == NULL)
    {
        fprintf(stderr, "Memory allocation failed for file content\n");
        fclose(file);
        return -1;
    }

    fread(model->content, 1, length, file);
    model->content[length] = '\0';
    model->length = length;

    fclose(file);
    return 0;
}

int save_file(TextModel *model)
{
    FILE *file = fopen(model->filename, "w");
    if (file == NULL)
    {
        fprintf(stderr, "Could not open file %s for writing\n", model->filename);
        return -1;
    }

    size_t written = fwrite(model->content, 1, model->length, file);
    fclose(file);

    if (written == model->length)
    {
        model->unsaved_changes = 0; 
        return 0;
    }
    else
    {
        fprintf(stderr, "Error writing to file %s\n", model->filename);
        return -1;
    }
}

void insert_character(TextModel *model, char c, size_t pos)
{
    if (pos > model->length)
    {
        pos = model->length;
    }

    char *newContent = (char *)realloc(model->content, model->length + 2);
    if (newContent == NULL)
    {
        fprintf(stderr, "Memory allocation failed for insert_character\n");
        return;
    }
    model->content = newContent;

    memmove(&model->content[pos + 1], &model->content[pos], model->length - pos + 1);
    model->content[pos] = c;
    model->length++;
    model->unsaved_changes = 1;
}

void delete_character(TextModel *model, size_t pos)
{
    if (model->length == 0 || pos >= model->length)
    {
        return;
    }

    memmove(&model->content[pos], &model->content[pos + 1], model->length - pos);
    model->length--;

    char *newContent = (char *)realloc(model->content, model->length + 1); // +1 for '\0'
    if (newContent != NULL)
    {
        model->content = newContent;
    }
    model->content[model->length] = '\0';
    model->unsaved_changes = 1;
}

void move_cursor(TextModel *model, char direction)
{
    switch (direction)
    {
    case 'h': // Move cursor left
        if (model->cursor_pos > 0)
        {
            model->cursor_pos--;
        }
        break;
    case 'l': // Move cursor right
        if (model->cursor_pos < model->length)
        {
            model->cursor_pos++;
        }
        break;
    case 'j': // Move cursor down
        if (model->cursor_pos < model->length)
        {
            while (model->cursor_pos < model->length && model->content[model->cursor_pos] != '\n')
            {
                model->cursor_pos++;
            }
        }
    case 'k': // Move cursor up
        if (model->cursor_pos > 0)
        {
            while (model->cursor_pos > 0 && model->content[model->cursor_pos] != '\n')
            {
                model->cursor_pos--;
            }
        }
    }
}

void insert_character_at_cursor(TextModel *model, char c)
{
    insert_character(model, c, model->cursor_pos);
    model->cursor_pos++;
}

void delete_character_at_cursor(TextModel *model)
{
    if (model->cursor_pos < model->length)
    {
        delete_character(model, model->cursor_pos);
    }
}

int has_unsaved_changes(const TextModel *model)
{
    return model->unsaved_changes;
}
