#include <Student.h>

Student s1(760741L,34);
Student s2(3234524);
Student s3(3234525L,14);

void setup() {
   Serial.begin(9600);
   s1.print();
   s2.print();
   s3.print();

 }

void loop() {
  s2.incrementSemester();
  s2.print();
}

