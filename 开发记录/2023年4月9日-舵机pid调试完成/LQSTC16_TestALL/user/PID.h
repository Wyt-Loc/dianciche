

typedef struct PID
{
    float                kp;         //P
    float                ki;         //I
    float                kd;         //D
    float                imax;       //�����޷�

    float                out_p;  //KP���
    float                out_i;  //KI���
    float                out_d;  //KD���
    float                out;    //pid���

    float                integrator; //< ����ֵ
    float                last_error; //< �ϴ����
    float                last_derivative;//< �ϴ���������ϴ����֮��
    unsigned long        last_t;     //< �ϴ�ʱ��

}pid_param_t;



void PidInit_wz(pid_param_t * pid);
float PidLocCtrl_wz(pid_param_t * pid, float error);


