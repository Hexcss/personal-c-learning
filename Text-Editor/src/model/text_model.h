#ifndef TEXT_MODEL_H
#define TEXT_MODEL_H

#include <stddef.h>

typedef struct {
    char *content;   
    size_t length;    
    char *filename;   
    size_t cursor_pos; 
    int unsaved_changes;
} TextModel;

TextModel* create_text_model(const char *filename);
void destroy_text_model(TextModel *model);
int load_file(TextModel *model);
int save_file(TextModel *model);
int has_unsaved_changes(const TextModel *model);
void insert_character(TextModel *model, char c, size_t pos);
void delete_character(TextModel *model, size_t pos);
void move_cursor(TextModel *model, char direction);
void insert_character_at_cursor(TextModel *model, char c);
void delete_character_at_cursor(TextModel *model);

#endif 
