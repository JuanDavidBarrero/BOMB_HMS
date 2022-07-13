#include <Arduino.h>
#include "UML.h"

void init_state(obj_msg_t *obj)
{
    event_t ee;
    ee.state = ENTRY;
    obj->level = PARENT;
    obj->activate_state_son = IDLE;
    obj->activate_state = MENU;
    obj->current_time = 20;
    State_machine(obj, &ee);
}

event_status State_machine(obj_msg_t *obj, event_t *ee)
{
    switch (obj->activate_state)
    {
    case MENU:
        return handle_state_menu(obj, ee);
        break;
    case BOOM:
        return handle_state_boom(obj, ee);
        break;
    case WINNER:
        return handle_state_winner(obj, ee);
        break;

    default:
        Serial.printf("No esta contemplado, Reiniciando\n");
        init_state(obj);
        return evento_ignorad;
    }
    return evento_ignorad;
}

event_status handle_state_menu(obj_msg_t *obj, event_t *ee)
{
    switch (ee->state)
    {
    case ENTRY:
        if (obj->level == PARENT)
        {
            obj->msg = "Menu";
            Serial.printf("Hola bienvenido al %s\n", obj->msg);
            obj->level = SON;
        }
        break;

    case TIME_TICK:
        if (obj->current_time == 0)
        {

            obj->activate_state = BOOM;
            obj->level = SON_EXIT;
            return transicion_evento;
        }
        break;

    case EXIT:
        if (obj->level == PARENT)
        {
            obj->msg = "Menu";
            Serial.printf("Adios desde %s\n\n", obj->msg);
            return event_realizado;
            break;
        }
    }

    if (obj->level == SON || obj->level == SON_EXIT)
    {
        switch (obj->activate_state_son)
        {
        case IDLE:
            return handle_idle_state(obj, ee);
            break;
        case S1:
            return handle_state_s1(obj, ee);
            break;

        case S2:
            return handle_state_s2(obj, ee);
            break;
        case S3:
            return handle_state_s3(obj, ee);
            break;
        }
    }

    return evento_ignorad;
}

event_status handle_idle_state(obj_msg_t *obj, event_t *ee)
{
    switch (ee->state)
    {
    case ENTRY:
        Serial.println("Bienvenido al juego");
        return event_realizado;
        break;

    case S:
        obj->activate_state = MENU;
        obj->activate_state_son = S1;
        return transicion_evento_hijo;

    case EXIT:
        if (obj->level == SON_EXIT)
        {
            obj->activate_state = MENU;
            obj->level = PARENT;
        }
        obj->msg = "Juego";
        Serial.printf("Iniciando el %s\n\n", obj->msg);
        return event_realizado;
        break;
    }
    return evento_ignorad;
}

event_status handle_state_s1(obj_msg_t *obj, event_t *ee)
{
    switch (ee->state)
    {
    case ENTRY:
        obj->msg = "Presione la letra de la secuancia [A]";
        Serial.println("Presione la letra de la secuancia [A]");
        return event_realizado;
        break;

    case A:
        obj->activate_state = MENU;
        obj->activate_state_son = S2;
        return transicion_evento_hijo;

    case TIME_TICK:
        obj->current_time -= 1;
        Serial.printf("Le quedan desde S1 %d seg\n", obj->current_time);
        return event_realizado;

    case EXIT:
        if (obj->level == SON_EXIT)
        {
            obj->activate_state = MENU;
            obj->level = PARENT;
        }
        obj->msg = "Juego";
        Serial.printf("Salida del S1 %s\n\n", obj->msg);
        return event_realizado;
        break;
    }
    return evento_ignorad;
}

event_status handle_state_s2(obj_msg_t *obj, event_t *ee)
{
    switch (ee->state)
    {
    case ENTRY:
        Serial.println("Presione la letra de la secuancia [B]");
        return event_realizado;
        break;

    case A:
        obj->activate_state = MENU;
        obj->activate_state_son = S1;
        return transicion_evento_hijo;

    case B:
        obj->activate_state = MENU;
        obj->activate_state_son = S3;
        return transicion_evento_hijo;

    case TIME_TICK:
        obj->current_time -= 1;
        Serial.printf("Le quedan desde S2 %d seg\n", obj->current_time);
        return event_realizado;

    case EXIT:
        if (obj->level == SON_EXIT)
        {
            obj->activate_state = MENU;
            obj->level = PARENT;
        }
        obj->msg = "Juego";
        Serial.printf("Salida del S2 %s\n\n", obj->msg);
        return event_realizado;
        break;
    }
    return evento_ignorad;
}

event_status handle_state_s3(obj_msg_t *obj, event_t *ee)
{
    switch (ee->state)
    {
    case ENTRY:
        Serial.println("Presione la letra de la secuancia [C]");
        return event_realizado;
        break;

    case A:
        obj->activate_state = MENU;
        obj->activate_state_son = S1;
        return transicion_evento_hijo;

    case B:
        obj->activate_state = MENU;
        obj->activate_state_son = S1;
        return transicion_evento_hijo;

    case C:
        obj->activate_state = WINNER;
        obj->level = PARENT;
        return transicion_evento;

    case TIME_TICK:
        obj->current_time -= 1;
        Serial.printf("Le quedan desde S3 %d seg\n", obj->current_time);
        return event_realizado;

    case EXIT:
        if (obj->level == SON_EXIT)
        {
            obj->activate_state = MENU;
            obj->level = PARENT;
        }
        obj->msg = "Juego";
        Serial.printf("Salida del S3 %s\n\n", obj->msg);
        return event_realizado;
        break;
    }
    return evento_ignorad;
}


event_status handle_state_boom(obj_msg_t *obj, event_t *ee)
{
    switch (ee->state)
    {
    case ENTRY:
        Serial.printf("La bomba BOOOOOOOOOOOM perdio\n");
        Serial.printf("Para volver al menu oprima la lentra A\n");
        return event_realizado;
        break;
    case A:
        obj->level = PARENT;
        obj->activate_state_son = IDLE;
        obj->current_time = 20;
        obj->activate_state = MENU;
        return transicion_evento;

    case EXIT:
        Serial.printf("Reiniciando el juego porque perdi...\n");
        return event_realizado;
        break;
    }
    return evento_ignorad;
}

event_status handle_state_winner(obj_msg_t *obj, event_t *ee)
{
    switch (ee->state)
    {
    case ENTRY:
        obj->msg = "Felicitaciones ";
        Serial.printf("La bomba no exploto s\n", obj->msg);
        Serial.println("Para volver al menu oprima la lentra A\n");
        return event_realizado;
        break;

    case A:
        obj->level = PARENT;
        obj->activate_state_son = IDLE;
        obj->current_time = 20;
        obj->activate_state = MENU;
        return transicion_evento;

    case EXIT:
        Serial.printf("Reiniciando el juego porque gane\n");
        return event_realizado;
        break;
    }
    return evento_ignorad;
}
