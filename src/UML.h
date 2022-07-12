#ifndef UML_H
#define UML_H

// Definir los estados
typedef enum
{
    MENU,
    IDLE,
    S1,
    S2,
    S3,
    WINNER,
    BOOM
} estados_names_t;


//******* Agreados ******
typedef enum{
    PARENT,
    SON,
    SON_EXIT,
} hierarchical_t; 

typedef struct{
    estados_names_t nombre;
    hierarchical_t level;
} states_level_t;
//******* Agreados ******

// Definir las señales principales
typedef enum
{
    A = 97,
    B,
    C,
    S = 115,
    TIME_TICK,
    ENTRY,
    EXIT
} signal_t;

// Definir las variables a trabajar
typedef struct
{
    String msg;
    uint32_t current_time;
    states_level_t levelState;
    estados_names_t activate_state;
} obj_msg_t;

typedef enum
{
    event_realizado,
    evento_ignorad,
    transicion_evento
} event_status;

// Definir el evento
typedef struct
{
    uint8_t state; // Aca se almacena el valor de las señales
} event_t;

typedef struct{
    event_t super;
    uint8_t time;
} tick_time_event_t;

void init_state(obj_msg_t *);
event_status State_machine(obj_msg_t *obj, event_t *ee);
event_status handle_state_menu(obj_msg_t *obj, event_t *ee);

event_status handle_idle_state(obj_msg_t *obj, event_t *ee);
event_status handle_state_s1(obj_msg_t *obj, event_t *ee);
event_status handle_state_s2(obj_msg_t *obj, event_t *ee);
event_status handle_state_s3(obj_msg_t *obj, event_t *ee);

event_status handle_state_boom(obj_msg_t *obj, event_t *ee);
event_status handle_state_winner(obj_msg_t *obj, event_t *ee);

#endif


