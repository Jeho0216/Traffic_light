/*
 * Traffic_light.c
 *
 * Created: 2019-03-28 오후 2:25:30
 * Author : kccistc
 */ 
#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
/*
//수직도로 신호등
#define V_RED 0
#define V_YEL 1
#define V_DIR 2
#define V_GRE 3
//수평도로 신호등
#define H_RED 7
#define H_YEL 6
#define H_DIR 5
#define H_GRE 4
*/

//신호등 순서 : 녹색 -> 황색 -> 적색&녹색화살표 -> 적색&황색 -> 적색.

/*
void h_road_light(){		//수평도로 차례
	PORTD = (0x01 << V_RED);
	PORTF = (0x01 << V_RED);		//수직도로에 적색 점등.
	
	//직진 신호
	PORTD |= (0x01 << H_GRE);
	PORTF |= (0x01 << H_GRE);		//수평도로에 녹색 점등.
	_delay_ms(5000);
	PORTD &= ~(0x01 << H_GRE);
	PORTF &= ~(0x01 << H_GRE);		//녹색 소등
	
	//좌회전 신호
	PORTD |= (0x01 << H_YEL);
	PORTF |= (0x01 << H_YEL);		//수평도로에 황색 점등.
	_delay_ms(1000);
	PORTD &= ~(0x01 << H_YEL);
	PORTF &= ~(0x01 << H_YEL);
	PORTD |= (0x01 << H_DIR) | (0x01 << H_RED);
	PORTF |= (0x01 << H_DIR) | (0x01 << H_RED);		//황색 소등 및 적색, 녹색화살표 점등.
	_delay_ms(3000);
	PORTD &= ~(0x01 << H_DIR);
	PORTF &= ~(0x01 << H_DIR);		//녹색화살표 소등.
	
	//정지 신호
	PORTD |= (0x01 << H_YEL);
	PORTF |= (0x01 << H_YEL);
	_delay_ms(1000);
	PORTD &= ~(0x01 << H_YEL);
	PORTF &= ~(0x01 << H_YEL);		//황색 점등
}

void v_road_light(){
	PORTD = (0x01 << H_RED);
	PORTF = (0x01 << H_RED);		//수평도로에 적색 점등.
	
	//직진 신호
	PORTD |= (0x01 << V_GRE);
	PORTF |= (0x01 << V_GRE);		//수직도로에 녹색 점등.
	_delay_ms(5000);
	PORTD &= ~(0x01 << V_GRE);
	PORTF &= ~(0x01 << V_GRE);		//녹색 소등
	
	//좌회전 신호
	PORTD |= (0x01 << V_YEL);
	PORTF |= (0x01 << V_YEL);		//수직도로에 황색 점등.
	_delay_ms(1000);
	PORTD &= ~(0x01 << V_YEL);
	PORTF &= ~(0x01 << V_YEL);
	PORTD |= (0x01 << V_DIR) | (0x01 << V_RED);
	PORTF |= (0x01 << V_DIR) | (0x01 << V_RED);		//황색 소등 및 적색, 녹색화살표 점등.
	_delay_ms(3000);
	PORTD &= ~(0x01 << V_DIR);
	PORTF &= ~(0x01 << V_DIR);		//녹색화살표 소등.
	
	//정지 신호
	PORTD |= (0x01 << V_YEL);
	PORTF |= (0x01 << V_YEL);
	_delay_ms(1000);
	PORTD &= ~(0x01 << V_YEL);
	PORTF &= ~(0x01 << V_YEL);		//황색 점등
}

*/

unsigned char h_light[5] = {0x01, 0x04, 0x0A, 0x0C, 0x08};
unsigned char v_light[5] = {0x08, 0x02, 0x05, 0x03, 0x01};

void delay_time(int i){
	switch(i){
		case 0:
			_delay_ms(5000);
			break;
		case 1:
		case 3:
			_delay_ms(1000);
			break;
		case 2:
			_delay_ms(3000);
		break;
	}
}

void h_road_light(){
	int i = 0;
	for(i = 0; i < 5; i++){
		PORTD = h_light[i] | 0x01;
		PORTF = h_light[i] | 0x01;
		delay_time(i);
	}
}

void v_road_light(){
	int i = 0;
	for(i = 0; i < 5; i++){
		PORTD = v_light[i] | 0x80;
		PORTF = v_light[i] | 0x80;
		delay_time(i);
	}
}
int main(void)
{
	DDRD = 0xFF;
	DDRF = 0xFF;
	PORTD = 0x00;
	PORTF = 0x00;
    while (1) 
    {
		v_road_light();		//수평도로 직진
		_delay_ms(100);
		h_road_light();		//수직도로 직진
    }
}

