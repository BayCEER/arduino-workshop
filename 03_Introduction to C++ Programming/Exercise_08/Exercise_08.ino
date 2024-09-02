// Base class definition 
class Shape
{
  public:
  // Calculate area of shape, has to be overwritten by derived class 
  virtual float area(void)=0;

  // Public method, calls derived implementation of area(void)
  void printArea(void){
    Serial.print("Area:");
    Serial.println(area());
  }
};

// First derived class definition 
class Circle: public Shape {
  private:
    float _radius;
  public: 
    Circle(float radius){    
      _radius = radius;     
    } 
    float area(void){
      return 3.14 * _radius * _radius;
    }     
};

// Second derived class definition 
class Square: public Shape {
  private: 
    float _length;
  public:
    Square(float length){
      _length = length;     
    }
    float area(void){
      return  _length * _length;
    }   
};


void setup() {
  Serial.begin(9600);  
  Circle c(2.0);
  // Call base class method
  c.printArea();
  Square s(2.0);
  // Call base class method
  s.printArea();
}

void loop() {
}

// TODO A: Extend the code with a new function to calculate the circumference
// TODO B: Create a new class triangle which extends the shape class


