#include "state_machine.h"

// Define type in c file to hide implementation
typedef struct _sm_t {
   state_t curr_state;
	 //uint8_t num_triggers; // count of state advances
} sm_t;
 
// Look up table to hold states, index by [CURR_STATE][DESIRED_EVENT]
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

// Below are the functions associated to each state in the stae machine
void state_0_func(){
	
}

void state_1_func(){
	
}

void state_2_func(){
	
}

void state_3_func(){
	
}



// Create a type to hold a *function for each state
typedef struct state_function {
	
} state_function_t;
/*
	Function to initialize state machine struct, will return a pointer for the opaque pointer	
*/
sm_instance sm_init(){
	sm_instance sm = (struct _sm_t *)malloc(sizeof(struct _sm_t)); // use type sm_instance
	sm->curr_state=STATE_0;
	return sm;
}
	
/* 
	Function to free a state machine instance,  call when done using to avoid memory leaks!
*/
void sm_free(sm_instance *sm){
	free(sm);
}

/*
	Function to retrieve current state from a state machine instance
*/
state_t sm_get_state(sm_instance sm){
	return sm->curr_state;
}

/*
	Function to change state machines current state
*/
void sm_trigger(sm_instance sm,  event_t evt){
	sm->curr_state = state_table[sm->curr_state][evt]; // get the next state from state table, depending event
}

/*
	Function to set state machine to a specific state
*/
void sm_reset(sm_instance sm, state_t state){
	sm->curr_state = state;
}