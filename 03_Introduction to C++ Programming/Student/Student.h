#ifndef STUDENT_H
#define STUDENT_H
  class Student {  
    private: // Protected scope (encapsulated variables !)
      long _mnr;
      int _semester;

    public:  // Public scope
      // Method declarations only 
      Student(long mnr,int semester=1); 
      void print(void);
      void incrementSemester(void);
  };
#endif