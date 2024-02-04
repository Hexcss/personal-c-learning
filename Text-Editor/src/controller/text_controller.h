#ifndef TEXT_CONTROLLER_H
#define TEXT_CONTROLLER_H

#include "../model/text_model.h"

typedef struct {
    TextModel *model;
    int is_running;
    int is_insert_mode; 
} TextController;

TextController* create_text_controller(TextModel *model);
void destroy_text_controller(TextController *controller);
void handle_keypress(TextController *controller, char key);
void start_main_loop(TextController *controller);
void toggle_insert_mode(TextController *controller); 

#endif 
