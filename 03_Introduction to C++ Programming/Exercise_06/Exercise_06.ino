class Student {
  private:
    long _mnr;
    int _semester;

  public:
    Student(long mnr,int semester=1){
      _mnr=mnr;
      _semester=semester;
    }

    void print(void){
      Serial.print("MNR: ");
      Serial.print(_mnr);
      Serial.print(" Semester ");
      Serial.println(_semester);
    }

    void increaseSemester(void){
      _semester++;
    }
  
};


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
  s2.increaseSemester();
  s2.print();
}
