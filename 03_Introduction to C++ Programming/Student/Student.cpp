#include "Student.h"
#include <Arduino.h>

Student::Student(long mnr,int semester=1){
  _mnr=mnr;
  _semester=semester;
}

void Student::print(void){
  Serial.print("MNR: ");
  Serial.print(_mnr);
  Serial.print(" Semester ");
  Serial.println(_semester);
}

void Student::incrementSemester(void){
  _semester++;
}

