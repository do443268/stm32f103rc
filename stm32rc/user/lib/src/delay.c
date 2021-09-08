#include "delay.h"

void Delay_ms(uint16_t time)
{
	// tang bien dem len 12000 lan
	uint32_t time_n = time * 12000;
	// cho den khi biem time_n giam =0 thi thoat
	while (time_n != 0)
	{
		time_n--;
	}
}
