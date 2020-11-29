#ifndef STATE_MACHINE_H
#define STATE_MACHINE_H
#include <stdlib.h>
#include <stdint.h>
#include "gpio_functions.h"
#define STATE_MAX 4 // Number of states for state table
#define EVT_MAX 2 // Nunber of events for state table
// create states
typedef enum{
	STATE_0,
	STATE_1, 
	STATE_2,
	STATE_3,
} state_t;


// Create events
typedef enum{
	EVT_FORWARDS,
	EVT_BACKWARDS,
} event_t;


// use opaque pointer to hold state machine (done more for experimentation in c, not functionality)
typedef struct _sm_t *sm_instance;

sm_instance sm_init(void); // will create a new sm_instance, starting at STATE_0
void sm_trigger(sm_instance sm,  event_t evt);
void sm_reset(sm_instance sm, state_t state); // use to set state machien to a specific state
state_t sm_get_state(sm_instance sm);
void sm_free(sm_instance *sm);

void state_0_func(void);
void state_1_func(void);
void state_2_func(void);
void state_3_func(void);

#endif
