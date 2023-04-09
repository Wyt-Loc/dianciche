#include "PID.h"



//λ��ʽPID��ʼ��  ���ڶ������
void PidInit_wz(pid_param_t * pid)
{
    pid->kp        = 0.08f;  //��������
    pid->ki        = 0;     
    pid->kd        = 0.08f;     //Խ��ӦԽ��
    pid->imax      = 0;     
    pid->out_p     = 0;			
    pid->out_i     = 0;  		
    pid->out_d     = 0;
    pid->out       = 0;
    pid->integrator= 0;
    pid->last_error= 0;
    pid->last_derivative = 0;
    pid->last_t    = 0;
}


float PidLocCtrl_wz(pid_param_t * pid, float error)
{
	
	pid->out_p = pid->kp * error; 			// Kp * ��� + KD * ������� �� �ϴεĲ�
	pid->out_d = pid->kd * (error - pid->last_error);
	pid->last_error = error;

	pid->out = pid->out_p + pid->out_d;

	return pid->out;
	
}


