#include "pid.h"

void pid_reset(pid_data_t* data)
{
	data->integral = 0;
	data->prev_error = 0;
}

float pid_calc(pid_const_t* consts, pid_data_t* state, float curr, float tgt)
{
	float x, e, i, d;

	e = tgt - curr;
	i = state->integral;
	i += e;
	d = e - state->prev_error;

	x  = e * consts->p;
	x += i * consts->i;
	x += d * consts->d;

	state->integral -= consts->i_decay;
	state->integral += e;
	state->prev_error = e;

	return x < consts->out_max ? (x > consts->out_min ? x : consts->out_min) : consts->out_max;
}