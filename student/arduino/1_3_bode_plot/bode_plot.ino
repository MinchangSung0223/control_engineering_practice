#include <SSD1306.h>
#include <MsTimer2.h>
// OLED Setup
#define OLED_DC 5  
#define OLED_CLK 8
#define OLED_MOSI 7
#define OLED_RESET 6
SSD1306 oled(OLED_MOSI, OLED_CLK, OLED_DC, OLED_RESET, 0);
//MOTOR driver pin
#define PWM 9
#define IN1 10
#define IN2 11
//Encoder Pin
#define ENCODER_A 3
#define ENCODER_B 2

float t = 0;
float u =0;
float Sampling_Time = 0.001;
float Start_Frequency =0;
float End_Frequency = 200;
float End_Time=20.0;
int cart_encoder = 0;
float cart_position = 0.0;
float prev_cart_position = 0.0;
float prev_filtered_velocity = 0.0;

void Set_PWM(int motor)
{
 // Fill in the Missing Code
}
float getChirpSignal(float Start_Frequency, float End_Frequency, float Sampling_Time,float End_Time ,float t){

   // Fill in the Missing Code, HINT: f(t) = ct+f0 , c = f1-f0/End_Time , x(t) = sin(2pi(c/2*t^2+f0*t)

  //

}


void control(){
    cart_position = float(cart_encoder)/520*PI;
    // Fill in the Missing Code
    
    //
    u = getChirpSignal(Start_Frequency,End_Frequency,Sampling_Time ,End_Time,t);
    if(t >End_Time)
      Set_PWM(0);
    else
      Set_PWM(u*255);
    t +=Sampling_Time;
    // Serial Write
    byte * time_ = (byte *) &t;    
    byte * filtered_velocity_ = (byte *) &filtered_velocity;
    Serial.write(time_,4);    
    Serial.write(filtered_velocity_,4);

}


 
void setup() {
  //display setup
  int fff = 1;
  TCCR1B =(TCCR1B & 0xF8) | fff;
  oled.ssd1306_init(SSD1306_SWITCHCAPVCC);
  oled.clear();   // clears the screen and buffer    
  
  //motor driver setup
  pinMode(IN1, OUTPUT);          
  pinMode(IN2, OUTPUT);          
  pinMode(PWM, OUTPUT); 
  
  //Encoder Setup
  pinMode(ENCODER_A, INPUT);
  pinMode(ENCODER_B, INPUT);
  Serial.begin(2000000);  
  delay(200);                     
  //Timer Setup
  MsTimer2::set(1, control);      
  MsTimer2::start();              
  //Interrupt Setup
  attachInterrupt(0, doEncoderA, CHANGE);   
  attachInterrupt(1, doEncoderB, CHANGE);   
  
  // motor STOP        
  digitalWrite(IN1, 0);         
  digitalWrite(IN2, 0);         
  digitalWrite(PWM, 0);
  
  
  oled.drawstring(00,2,"BODE_PLOT");
  oled.display();
         
}

void loop(){
}
void doEncoderA(){// Fill in the Missing Code
}
void doEncoderB(){// Fill in the Missing Code
}
