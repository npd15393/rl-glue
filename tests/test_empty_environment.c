/* 
* Copyright (C) 2007, Brian Tanner

 Licensed under the Apache License, Version 2.0 (the "License");
 you may not use this file except in compliance with the License.
 You may obtain a copy of the License at

     http://www.apache.org/licenses/LICENSE-2.0

 Unless required by applicable law or agreed to in writing, software
 distributed under the License is distributed on an "AS IS" BASIS,
 WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 See the License for the specific language governing permissions and
 limitations under the License.

* 
*  $Revision$
*  $Date$
*  $Author$
*  $HeadURL$
* 
*/
#ifdef HAVE_CONFIG_H
#include <config.h>
#endif


#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <rlglue/Environment_common.h>
#include <rlglue/utils/C/RLStruct_util.h>

#include "useful_functions.h"

static char* responseMessage=0;
static observation_t *emptyObservation=0;
static observation_t *nonEmptyObservation=0;


int env_whichEpisode=0;


const char* env_init()
{    
	env_whichEpisode=0;

	emptyObservation=allocateRLStructPointer(0,0,0);
	nonEmptyObservation=allocateRLStructPointer(0,0,0);

	set_k_ints_in_abstract_type(nonEmptyObservation,2);
	set_k_doubles_in_abstract_type(nonEmptyObservation,4);
	set_k_chars_in_abstract_type(nonEmptyObservation,5);

	return "";
}

const observation_t *env_start()
{
	env_whichEpisode++;
	
	if(env_whichEpisode%2==0)
		return emptyObservation;

	return nonEmptyObservation;
}

const reward_observation_t *env_step(const action_t *a)
{
	static reward_observation_t ro={0};

	if(env_whichEpisode%2==0)
		ro.observation=emptyObservation;
	else
		ro.observation=nonEmptyObservation;
		
	ro.reward=0;
	ro.terminal=0;
	
	return &ro;
}

void env_cleanup()
{
	freeRLStructPointer(emptyObservation);
	freeRLStructPointer(nonEmptyObservation);
	if(responseMessage!=0){
		free(responseMessage);
		responseMessage=0;
	}
}

void env_set_state(const state_key_t *sk)
{
}
     
void env_set_random_seed(const random_seed_key_t *rsk)
{
}

const state_key_t *env_get_state()
{
	state_key_t *theKey=0;
	clearRLStruct(theKey);
	return theKey;
}

const random_seed_key_t *env_get_random_seed()
{
	random_seed_key_t *theKey=0;
	clearRLStruct(theKey);
	return theKey;
}

const char* env_message(const char* inMessage) {
	return "";
}
	
