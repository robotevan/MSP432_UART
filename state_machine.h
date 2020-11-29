#ifndef STATE_MACHINE_H
#include <stdlib.h>
#include <stdint.h>

// create states
typedef enum{
	STATE_0,
	STATE_1, 
	STATE_2,
	STATE_3,
} state_t;
#define STATE_MAX 4 // Number of states for state table

// Create events
typedef enum{
	EVT_FORWARDS,
	EVT_BACKWARDS,
} event_t;
#define EVT_MAX 2 // Nunber of events for state table

// use opaque pointer to hold state machine
typedef struct _sm_t *sm_instance;

sm_instance sm_init(); // will create a new sm_instance, starting at STATE_0
void sm_trigger(sm_instance sm,  event_t evt);
void sm_reset(sm_instance sm, state_t state); // use to set state machien to a specific state
state_t sm_get_state(sm_instance sm);
void sm_free(sm_instance *sm);
#endif


