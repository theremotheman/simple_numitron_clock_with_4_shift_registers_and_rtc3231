#include <RTClib.h> //rtc with temperature for ds3231
RTC_DS3231 rtc; //setting which rtc module is used

#include <Wire.h> //wiring
#include <TimeLib.h> //time lib
#include <Time.h> //time function
#include <DS1307RTC.h> //rtc


const int latchPin = 8; //latch
const int clockPin = 12; //clock
const int dataPin = 11; //data

const int nums[10] = { //setting display array - according to docs: pin1 is common, pin2 is dot(unused in sketch), rest should be connected to shift registers one by one
  0b11110110, //0 
  0b11000000, //1 
  0b10101110, //2 
  0b11101100, //3 
  0b11011000, //4 
  0b01111100, //5 
  0b01111110, //6 
  0b11100000, //7 
  0b11111110, //8 
  0b11111100 //9 
};

int hour1; //hour first number
int hour2; //hour second number
int minute1; //minutes first number
int minute2; //minutes second number
int day1; //day first number
int day2; //day second number
int month1; //month first number
int month2; //month second number
int year1; //year first number - constant 2
int year2; //year second number - constant 0 (you wanna live that long to change it?)
int year3; //year third number
int year4; //year fourth number
int hourDecimal; //decimal parsing of hour
int minuteDecimal; //decimal parsing of minute
int dayDecimal; //decimal parsing of day
int monthDecimal; //decimal parsing of month
int year70; //year after unix epoch
int temp1; //first temperature number
int temp2; //second temperature number
int tempDecimal; //decimal parsing of temperature(first two numbers)

void setup() {

  pinMode(latchPin, OUTPUT); //set pins to output so you can control the shift register
  pinMode(clockPin, OUTPUT); //set pins to output so you can control the shift register
  pinMode(dataPin, OUTPUT); //set pins to output so you can control the shift register
}

void loop() {
  tmElements_t tm; //naming from DS1307RTC library
  RTC.read(tm); // read rtc time/date/year

  minuteDecimal = tm.Minute / 10; //parse output to be readable(shorter) by dividing by ten
  hourDecimal = tm.Hour / 10; //parse output to be readable(shorter) by dividing by ten

  dayDecimal = tm.Day / 10; //parse output to be readable(shorter) by dividing by ten
  monthDecimal = tm.Month / 10; //parse output to be readable(shorter) by dividing by ten

  year70 = tm.Year - 30; //display real year by subtracting from unix epoch(1970)

  hour1 = hourDecimal; //simple as that
  hour2 = tm.Hour - 10 * hourDecimal; //make calculations to display only second number from two digits string
  minute1 = minuteDecimal; //simple
  minute2 = tm.Minute - 10 * minuteDecimal; //make calculations to display only second number from two digits string

  day1 = dayDecimal; //simple
  day2 = tm.Day - 10 * dayDecimal; //make calculations to display only second number from two digit string
  month1 = monthDecimal; //simple
  month2 = tm.Month - 10 * monthDecimal; //make calculations to display only second number from two digit string

  year1 = 2; //first year number, do you really need to change that? you got flying cars and etc?
  year2 = 0; //second year number, if you need to change that you should be playing with grandkids instead
  year3 = year70 / 10; //parse output to be readable(shorter) by dividing by ten
  year4 = year70 - 10 * year3; //make calculations to display only second number from two digit string

  tempDecimal = rtc.getTemperature()/10; //parse output to be readable(shorter) by dividing by ten

  temp1 = tempDecimal; //simple
  temp2 = rtc.getTemperature() - 10 * tempDecimal; //make calculations to display only second number from two digit string

  digitalWrite(latchPin, LOW); //setting latch low and awaiting data

  shiftOut(dataPin, clockPin, MSBFIRST, nums[minute2]);//shift out the bits (MSBFIRST = most significant bit first)
  shiftOut(dataPin, clockPin, MSBFIRST, nums[minute1]);
  shiftOut(dataPin, clockPin, MSBFIRST, nums[hour2]);
  shiftOut(dataPin, clockPin, MSBFIRST, nums[hour1]); //this is first displayed number
  digitalWrite(latchPin, HIGH); //send everything

  delay(60000); //shows time for 60 seconds - can be changed for quicker toggling

  digitalWrite(latchPin, LOW); //setting latch low and awaiting data

  shiftOut(dataPin, clockPin, MSBFIRST, 0b00000000); // Blanking/fading
  shiftOut(dataPin, clockPin, MSBFIRST, 0b00000000); // Blanking/fading
  shiftOut(dataPin, clockPin, MSBFIRST, 0b00000000); // Blanking/fading
  shiftOut(dataPin, clockPin, MSBFIRST, 0b00000000); // Blanking/fading
  digitalWrite(latchPin, HIGH); //send everything

  delay(500); //numitron tured off for 0.5 sec to make 'breathing' effect

  digitalWrite(latchPin, LOW); //setting latch low and awaiting data

  shiftOut(dataPin, clockPin, MSBFIRST, nums[month2]);// shift out the bits (MSBFIRST = most significant bit first)
  shiftOut(dataPin, clockPin, MSBFIRST, nums[month1]);
  shiftOut(dataPin, clockPin, MSBFIRST, nums[day2]);
  shiftOut(dataPin, clockPin, MSBFIRST, nums[day1]); //this is first displayed number
  digitalWrite(latchPin, HIGH); //send everything

  delay(1500); //display date for 1.5 sec

  digitalWrite(latchPin, LOW); //setting latch low and awaiting data

  shiftOut(dataPin, clockPin, MSBFIRST, 0b00000000); // Blanking/fading
  shiftOut(dataPin, clockPin, MSBFIRST, 0b00000000); // Blanking/fading
  shiftOut(dataPin, clockPin, MSBFIRST, 0b00000000); // Blanking/fading
  shiftOut(dataPin, clockPin, MSBFIRST, 0b00000000); // Blanking/fading
  digitalWrite(latchPin, HIGH); //send everything

  delay(500); //numitron tured off for 0.5 sec to make 'breathing' effect

  digitalWrite(latchPin, LOW); //setting latch low and awaiting data
  
  shiftOut(dataPin, clockPin, MSBFIRST, nums[year4]);// shift out the bits (MSBFIRST = most significant bit first)
  shiftOut(dataPin, clockPin, MSBFIRST, nums[year3]);
  shiftOut(dataPin, clockPin, MSBFIRST, nums[year2]);
  shiftOut(dataPin, clockPin, MSBFIRST, nums[year1]); //this is first displayed number
  digitalWrite(latchPin, HIGH); //send everything

  delay(1500); //year displayed for 1.5 sec

  digitalWrite(latchPin, LOW); //setting latch low and awaiting data

  shiftOut(dataPin, clockPin, MSBFIRST, 0b00000000); // Blanking/fading
  shiftOut(dataPin, clockPin, MSBFIRST, 0b00000000); // Blanking/fading
  shiftOut(dataPin, clockPin, MSBFIRST, 0b00000000); // Blanking/fading
  shiftOut(dataPin, clockPin, MSBFIRST, 0b00000000); // Blanking/fading
  digitalWrite(latchPin, HIGH); //send everything

  delay(500); //numitron tured off for 0.5 sec to make 'breathing' effect

  digitalWrite(latchPin, LOW); //setting latch low and awaiting data

  shiftOut(dataPin, clockPin, MSBFIRST, 0b00110110); // celcius
  shiftOut(dataPin, clockPin, MSBFIRST, 0b00000000); //blank
  shiftOut(dataPin, clockPin, MSBFIRST, nums[temp2]);
  shiftOut(dataPin, clockPin, MSBFIRST, nums[temp1]); //this is first displayed number
  digitalWrite(latchPin, HIGH); //send everything

  delay(1500); //temperature displayed for 1.5 sec

  digitalWrite(latchPin, LOW); //setting latch low and awaiting data

  shiftOut(dataPin, clockPin, MSBFIRST, 0b00000000); // Blanking/fading
  shiftOut(dataPin, clockPin, MSBFIRST, 0b00000000); // Blanking/fading
  shiftOut(dataPin, clockPin, MSBFIRST, 0b00000000); // Blanking/fading
  shiftOut(dataPin, clockPin, MSBFIRST, 0b00000000); // Blanking/fading
  digitalWrite(latchPin, HIGH); //send everything

  delay(500); //numitron tured off for 0.5 sec to make 'breathing' effect

}
