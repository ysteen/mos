#include <MIDI.h>
#include <MsTimer2.h>
#include <math.h>
#include "key_to_stepmotor.h"

// Simple tutorial on how to receive and send MIDI messages.
// Here, when receiving any message on channel 4, the Arduino
// will blink a led and play back a note for 1 second.

MIDI_CREATE_DEFAULT_INSTANCE();

const int EnablePin_1 = 3;  
const int stepPin_1 = 2;  
const int EnablePin_2 = 5;  
const int stepPin_2 = 4;  
const int ledPin = 13;
const int stepsPerRevolution = 800;  

int motor_state[6][2] = {
                        {0, 0},// 첫번째는 모터 상태, 두번째는 pitch
                        {0, 0},
                        {0, 0},
                        {0, 0},
                        {0, 0},
                        {0, 0}
                        };
int pitch_bend = 0;
int motor_step[6] = {0, 0, 0, 0, 0, 0};// 지난 시간 타겟(원하는 딜레이)
int motor_count[6] = {0, 0, 0, 0, 0, 0};// 지난 시간 재기
unsigned long motor_prev[6] = {0, 0, 0, 0, 0, 0}; // 전에 기록한 시간
int motor_pin[6][3] = {
                       {stepPin_1, HIGH, EnablePin_1},// 첫번째는 스텝 핀번호, 두번째는 enable 핀 번호세번째는 pin상태
                       {stepPin_2, HIGH, EnablePin_2},
                       {6, HIGH, 7},
                       {8, HIGH, 9},
                       {10, HIGH, 11},
                       {12, HIGH, 13}
};

int change_key_to_delay(int key){
  return key_change[key][1]; // pitch를 delay값으로 변환(microsec)
}

void toggle_pin(int motor_num) {
      motor_pin[motor_num][1] = !motor_pin[motor_num][1]; 
      digitalWrite(motor_pin[motor_num][0], motor_pin[motor_num][1]);  // 토글해줘서 pwm 생성
}

void step_motor(int motor_num, int pitch) // 스텝모터 한바퀴 돌리는 함수
{   
    if(pitch_bend == 0) {
      motor_step[motor_num] = change_key_to_delay(pitch - 24);// delay 변환
    }
    unsigned long current_time_us = micros();
    motor_count[motor_num] += current_time_us -  motor_prev[motor_num]; // 현재 시간을 전 시간에 빼서 계속 더해줌, dt
    motor_prev[motor_num] = current_time_us; // 각자 시간을 따로 설정해줘야 시간 동기화가 안된다
    
    if (motor_count[motor_num] >= motor_step[motor_num]) {
      motor_count[motor_num] = 0; // 원하는 시간 흐르면 토글해주고 초기화
      toggle_pin(motor_num);
    }
}

void setup() {
    pinMode(ledPin, OUTPUT);   
    for(int i=0; i<6; i++) {
      pinMode(2*i+2, OUTPUT); //step pin
      pinMode(2*i+3, OUTPUT); // enable pin
      motor_prev[i] = micros(); 
      digitalWrite(2*i+3, HIGH);
    }
    
    
    MIDI.begin(4);  
    MIDI.setHandleNoteOn(handleNoteOn);
    MIDI.setHandleNoteOff(handleNoteOff);
    MIDI.setHandlePitchBend(handlePitchBend);
}

void loop() {
  MIDI.read();
  for(int i=0; i<6; i++){
    if(motor_state[i][0] == 1){
      step_motor(i, motor_state[i][1]); // 켜져 있는거만 스텝모터 돌림
    }
  }
}
/*
 * noteon 신호 들어오면 실행, interrupt와 같은 개념
 * 채널은 4채널로 설정해주었고 pitch값만 필요
 */
void handleNoteOn(byte channel, byte pitch, byte velocity)
{
  if(pitch <= 72 && pitch >= 24) {
    for(int i=0; i<6; i++){
      if(motor_state[i][0] == 0 && motor_state[i][1] == 0){
        motor_state[i][0] = 1;  // 모터가 켜져있는 상태로 표현
        motor_state[i][1] = pitch;  // 모터의 음계를 설정
        digitalWrite(motor_pin[i][2], LOW); // 모터를 사용하므로 enablePin을 low로
        break;
      }
    }
  }
}
/*
 * noteoff 신호가 들어오면 실행, interrupt와 같은 개념
 * 모터가 켜져있는지 안켜져있는지만 확인해본다
 */
void handleNoteOff(byte channel, byte pitch, byte velocity)
{
  for(int i=0; i<6; i++){
      if(motor_state[i][1] == pitch && motor_state[i][0] == 1){ //모터 pitch확인
        motor_state[i][0] = 0; //모터 상태 꺼진상태로
        motor_state[i][1] = 0;  //모터 pitch 초기화
        digitalWrite(motor_pin[i][2], HIGH);    // 모터 꺼지게 만들어야 하므로 enablePin을 high로
        break;
      }
    }
}

void handlePitchBend(byte channel, int bend)
{
  if(bend == 0) {
    digitalWrite(ledPin, LOW);
    pitch_bend = 0;
  }
  else {
    pitch_bend = 1;
    digitalWrite(ledPin, HIGH);
    int key = 2;
    double semitones =  (double) bend / 8192;
    double new_delay[6] = {};
    for(int i=0; i<6; i++){
      new_delay[i] = (double) change_key_to_delay(motor_state[i][1]-24) * exp(- semitones * log(2));
      motor_step[i] = (int) new_delay[i];
    }
  }
}
