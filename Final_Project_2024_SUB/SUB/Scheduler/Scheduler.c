#include "Header_USER.h"

extern uint32 Scheduler1msFlag;
extern uint32 Scheduler10msFlag;
extern uint32 Scheduler100msFlag;


void AppScheduling(void)
{
    if (Scheduler1msFlag == 1)
    {
        Scheduler1msFlag = 0;
        Task1ms();


        if (Scheduler100msFlag == 1)
        {
            Scheduler100msFlag = 0;
            Task100ms();
        }
    }
}

void Task1ms(void)
{
    cnt1ms++;
    //DHT11_read(&temperature, &humidity);


}

void Task10ms(void)
{
    cnt10ms++;
//    DHT11_read(&temperature, &humidity);
}

void Task100ms(void)
{
    cnt100ms++;
    DHT11_read(&temperature, &humidity);
    check_temperature_and_send_warning();

}
