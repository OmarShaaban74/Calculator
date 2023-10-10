/*
 * Calcualtor.c
 *
 *  Created on: Oct 4, 2023
 *      Author: omars
 */

#include "keypad.h"
#include "lcd.h"
#include <util/delay.h>


void reset(uint8 *inputArr,uint8 *operators,sint64 *operands,uint8 *inputArrCounter,uint8 *operatorsCounter,uint8 *operandsCounter,uint8 *key,uint8 *cursorLoc,sint64 *result,uint8 *mul_div_counter){
uint8 i;
for(i=0;i<17;i++){
	inputArr[i]=0;
	operators[i]=0;
	 operands[i]=0;
	*inputArrCounter=0;
	*operatorsCounter=0;
	*operandsCounter=0;
	*key=0;
	*cursorLoc=0;
	*result=0;
	*mul_div_counter=0;
}
LCD_sendCommand(CLEAR_DISP);
}


void collectNums(uint8 *inputArr,sint64 *operands,uint8 *operandsCounter,uint8 *operators,uint8 *operatorsCounter,uint8 *mul_div_counter){
	uint8 i=0;
	while(inputArr[i]!='='){
	if(inputArr[i]=='-'){
		i++;
		while(inputArr[i]>=0 && inputArr[i]<=9){
			operands[*operandsCounter]=10*operands[*operandsCounter]+inputArr[i];
			i++;
		}
		operands[*operandsCounter]*=-1;
		(*operandsCounter)++;
	}
	else{
		while(inputArr[i]>=0 && inputArr[i]<=9){
					operands[*operandsCounter]=10*operands[*operandsCounter]+inputArr[i];
					i++;
				}
		(*operandsCounter)++;
	}
	if(inputArr[i]=='+' || inputArr[i]=='-' || inputArr[i]=='*' || inputArr[i]=='/' ){
		operators[*operatorsCounter]=inputArr[i];
		(*operatorsCounter)++;
		if(inputArr[i]=='*' || inputArr[i]=='/' ){
			(*mul_div_counter)++;
		}
		i++;

	}
	else if(inputArr[i]=='='){
		operators[*operatorsCounter]=inputArr[i];
		return;
	}


	}
}

uint8 calcResult(uint8 *operators,sint64 *operands,sint64 *result,uint8 *operandsCounter,uint8 *operatorsCounter,uint8 *mul_div_counter){
uint8 i=0,k=0;

while((*mul_div_counter)!=0){
	switch(operators[i]){
	case '*':
		operands[i]=operands[i]*operands[i+1];
		for(k=i+1;k<(*operandsCounter)-1;k++){
			operands[k]=operands[k+1];
			operators[k-1]=operators[k];
		}
		(*operandsCounter)--;
		(*operatorsCounter)--;
		(*mul_div_counter)--;
		i--;
		break;
		case '/':
		if(operands[i+1]==0){
			LCD_sendCommand(CLEAR_DISP);
			LCD_moveCursor(0,2);
			LCD_displayString("Math Error");
			_delay_ms(2000);
			return 0;
		}
		else{
		operands[i]=operands[i]/operands[i+1];
		for(k=i+1;k<(*operandsCounter)-1;k++){
				operands[k]=operands[k+1];
				operators[k-1]=operators[k];
		}
		(*mul_div_counter)--;
		(*operandsCounter)--;
		(*operatorsCounter)--;
		i--;
		}
		break;
		}
	i++;
}
i=0;
while((*operatorsCounter)!=0){
	switch(operators[i]){
	case '+':
		operands[i]=operands[i]+operands[i+1];
		for(k=i+1;k<(*operandsCounter)-1;k++){
			operands[k]=operands[k+1];
			operators[k-1]=operators[k];
		}
		(*operandsCounter)--;
		(*operatorsCounter)--;
		i--;
		break;
		case '-':
		operands[i]=operands[i]-operands[i+1];
		for(k=i+1;k<(*operandsCounter)-1;k++){
				operands[k]=operands[k+1];
				operators[k-1]=operators[k];
		}
		(*operandsCounter)--;
		(*operatorsCounter)--;
		i--;

		break;
	}
	i++;
}

*result=operands[0];
return 1;
}



int main(void){
	uint8 inputArr[17]={0};
	uint8 operators[16]={0};
	sint64 operands[16]={0};
	uint8 inputArrCounter=0;
	uint8 operatorsCounter=0;
	uint8 mul_div_counter=0;
	uint8 operandsCounter=0;
	uint8 key;
	uint8 cursorLoc=0;
	sint64 result=0;
	uint8 calcRet;
	LCD_init();
	LCD_moveCursor(0,2);
	LCD_displayString("*Calculator*");
	LCD_moveCursor(1,0);
	LCD_displayString("By Omar Shaaban");
	_delay_ms(2000);
	LCD_sendCommand(CLEAR_DISP);
	LCD_moveCursor(0,5);
	LCD_displayString("EDGES");
	LCD_moveCursor(1,0);
	LCD_displayString("Embedded diploma");
	_delay_ms(2000);
	LCD_sendCommand(CLEAR_DISP);
	LCD_sendCommand(CUSROR_BLINKING);
	while(1){
		key=KEYPAD_getPressedKey();
		switch(key){
		case 0 ... 9:
		if(cursorLoc==15){

		}
		else{
			cursorLoc++;
			LCD_intgerToString(key);
			inputArr[inputArrCounter]=key;
			inputArrCounter++;

		}
		break;

		case '+':
		case '-':
		case '*':
		case '/':
			if (cursorLoc == 15) {

			}
			else {
				cursorLoc++;
				LCD_displayCharacter(key);
				inputArr[inputArrCounter] =key;
				inputArrCounter++;

			}
			break;
		case ON_BUTTON:
			reset(inputArr,operators,operands,&inputArrCounter,&operatorsCounter,&operandsCounter,&key,&cursorLoc,&result,&mul_div_counter);
			break;

		case '=':
			inputArr[inputArrCounter]=key;
			LCD_moveCursor(1,0);
			collectNums(inputArr,operands,&operandsCounter,operators,&operatorsCounter,&mul_div_counter);
			calcRet=calcResult(operators,operands,&result,&operandsCounter,&operatorsCounter,&mul_div_counter);
			if(calcRet==0){
				reset(inputArr,operators,operands,&inputArrCounter,&operatorsCounter,&operandsCounter,&key,&cursorLoc,&result,&mul_div_counter);

			}
			else
			{
			LCD_displayCharacter(key);
			LCD_intgerToString(result);
			}

		}
		_delay_ms(500);
	}


}


