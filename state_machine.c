/*
Code by Evan Pelletier, 101119347
*/

#include "state_machine.h"

static state_t state_table[STATE_MAX][EVT_MAX] = {
	// state 0:	
	{STATE_1, STATE_3},
	// state 1
	{STATE_2, STATE_0},
	// state 2
	{STATE_3, STATE_1},
	// state 3
	{STATE_0, STATE_2}
};

/*
	Function to set LED's for STATE_0
	r = 0, rgb = 0
*/
void state_0_func(){
	set_red_led(0);
	set_rgb_led(0);
}

/*
	Function to set LED's for STATE_1
	r = 1, rgb = r
*/
void state_1_func(){
	set_red_led(1);
	set_rgb_led(1);
}

/*
	Function to set LED's for STATE_2
	r = 0, rgb = g
*/
void state_2_func(){
	set_red_led(0);
	set_rgb_led(2);
}

/*
	Function to set LED's for STATE_0
	r = 1, rgb = b
*/
void state_3_func(){
	set_red_led(1);
	set_rgb_led(3);
}

/*
Define type holding pointer to a functoin
*/
typedef struct {
	void (*function)(void);
} state_function_t;


/*
Array index by state_t, returns state_function_t holding pointer to function
*/
static state_function_t state_functions[] = {
	&state_0_func,
	&state_1_func,
	&state_2_func,
	&state_3_func
};

/*
Initilaize the state machine,  starting at state 0
*/
struct state_machine *init_sm(struct state_machine *sm){
	sm->curr_state = STATE_0;
	state_functions[sm->curr_state].function(); // Call the function for state 0
	return sm; 
}

/*
Change the state, takes an sm instance as well as an event
*/
void sm_trigger(struct state_machine *sm,  event_t evt){
	sm->curr_state = state_table[sm->curr_state][evt];
	state_functions[sm->curr_state].function();
}


/*
Go to a specific state in the state machine
*/
void sm_reset(struct state_machine *sm, state_t state){
	sm->curr_state = state;
}

