/*
* @author Pedro Arthur Medeiros Fernandes
* @author Yuri Alessandre Martins
/

#include <iostream>
#include <string>
#include <fstream>
#include <string>
#include <sstream>
#include <unistd.h>
#include <iomanip>
#include <time.h>

#include "BlackGPIO/BlackGPIO.h"

#define PATH_ADC "/sys/bus/iio/devices/iio:device0/in_voltage"

int seed ( int i ) {
	srand (time(NULL));
	return std::rand()%i + 1;
}

int readAnalog(int number){
   std::stringstream ss;
   ss << PATH_ADC << number << "_raw";
   std::fstream fs;
   fs.open(ss.str().c_str(), std::fstream::in);
   fs >> number;
   fs.close();
   return number;
}

int main(int argc, char * argv[]){
	BlackLib::BlackGPIO   ledRun(BlackLib::GPIO_50,BlackLib::output, BlackLib::SecureMode);
	BlackLib::BlackGPIO   button1(BlackLib::GPIO_115,BlackLib::input);

	// LED RGB
	BlackLib::BlackGPIO   ledR(BlackLib::GPIO_60,BlackLib::output, BlackLib::SecureMode);
	BlackLib::BlackGPIO   ledG(BlackLib::GPIO_30,BlackLib::output, BlackLib::SecureMode);
	BlackLib::BlackGPIO   ledB(BlackLib::GPIO_51,BlackLib::output, BlackLib::SecureMode);
	///////////////////
	ledRun.setValue(BlackLib::high);
	ledR.setValue(BlackLib::low);
	ledG.setValue(BlackLib::low);
	ledB.setValue(BlackLib::low);

	std::cout << "WELCOME TO TABLE-LIGHT!\n";
	std::cout << "Creating a number between [";

	int tableMax = readAnalog(0);
	tableMax = (tableMax*150)/4096;

	std::cout << "1-" << tableMax << "]...\n\n";

	int nRandom = seed(tableMax);
	int lTry = 0;
	int score = 100;

	std::cout << "Tray your luck: Use the KNOB to guess a number...\n";
	std::cout << "\t >>> You have to tray to guess the number\n\t>>> generated randomly in the given range.\n";
	std::cout << "\t PRESS THE BUTTON TO CONFIRME YOUR ATTEMPT\n";
	std::cout << "Inicial score: " << score << std::endl;

	while(1){
		if(button1.getNumericValue()){
			if( score <= 0 ){
				std::cout << "GAME OVER!\n";
				std::cout << "The answer is: " << nRandom << std::endl;
				return EXIT_SUCCESS;
			}

			int number = readAnalog(1);
			number = ((number*tableMax )/4096) + 1;
			lTry = number;
			std::cout << "\t >>> Your guess: " << number << std::endl;
        	if( number == nRandom ){
        		ledG.setValue(BlackLib::high);
        		std::cout << "CONGRATULATIONS!!! YOU WIN!\n";
        		std::cout << ">>> Final score: " << score << std::endl;
        		sleep(3);
        		ledG.setValue(BlackLib::low);
        		break;
        	}
			else if( number >= (nRandom - 5) && number <= (nRandom + 5)){
        		ledB.setValue(BlackLib::high);
        		sleep(1);
        		std::cout << "Tray again...\n";
        		ledB.setValue(BlackLib::low);
        		sleep(1);
        		system("clear");
        		score -= 7;
        	}
        	else{
        		ledR.setValue(BlackLib::high);
        		sleep(1);
        		std::cout << "Tray again...\n";
        		ledR.setValue(BlackLib::low);
        		sleep(1);
        		system("clear");
        		score -= 2;
        	}
        	std::cout << "Lest Attempt: " << lTry << std::endl;
        	std::cout << "SCORE: " << score << std::endl;
		}
	}

	ledRun.setValue(BlackLib::low);
	return EXIT_SUCCESS;
}
