/*
Code by Evan Pelletier, 101119347
*/

#ifndef STATE_MACHINE_H
#include <msp.h>
#include <stdint.h>
#include <stdlib.h>
#include "gpio_functions.h"
#define STATE_MAX 4 // Number of states for state table
#define EVT_MAX 2 // Nunber of events for state table


typedef enum{
	STATE_0,
	STATE_1, 
	STATE_2,
	STATE_3,
} state_t;

struct state_machine { 
	state_t curr_state;
};


typedef enum{
	EVT_FORWARDS,
	EVT_BACKWARDS,
} event_t;




struct state_machine *init_sm(struct state_machine *sm);
void sm_trigger(struct state_machine *sm,  event_t evt);
void sm_reset(struct state_machine *sm, state_t state);


#endif
