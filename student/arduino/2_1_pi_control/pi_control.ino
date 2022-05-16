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

uint32_t oled_pow(uint8_t m,uint8_t n)
{
  uint32_t result=1;  
  while(n--)result*=m;    
  return result;
}
void OLED_ShowNumber(uint8_t x,uint8_t y,uint32_t num,uint8_t len)
{           
  u8 t,temp;
  u8 enshow=0;    
  oled.drawchar(x-6,y,' ');
           
  for(t=0;t<len;t++)
  {
    temp=(num/oled_pow(10,len-t-1))%10;
    oled.drawchar(x+6*t,y,temp+'0');
  }  
}
void OLED_ShowNumber_Minus(uint8_t x,uint8_t y,uint32_t num,uint8_t len)
{           
  u8 t,temp;
  u8 enshow=0;     
  oled.drawchar(x-6,y,'-');

  for(t=0;t<len;t++)
  {
    temp=(num/oled_pow(10,len-t-1))%10;
    oled.drawchar(x+6*t,y,temp+'0');
  }  
}


void Set_PWM(int PWM_value)
{
  if (PWM_value< 0)     digitalWrite(IN1, HIGH),      digitalWrite(IN2, LOW);
  else               digitalWrite(IN1, LOW),       digitalWrite(IN2, HIGH);
  analogWrite(PWM, abs(PWM_value));
}


float t = 0;
float t_step = 0.001;
float End_Time = 2;
int cart_encoder=0;
float target_cart_velocity = 20;
float prev_cart_position = 0;
float prev_cart_velocity = 0;
float error = 0;
float prev_error=0;
float alpha = 0.1;
float enc2rad = 1/520.0*3.141592;
float prev_u= 0;

float Ki = 1000;
float Kp = 100;

void control(){
    float cart_position = float(cart_encoder)*enc2rad;
    float cart_velocity = (cart_position-prev_cart_position)/t_step;

   // Fill in the Missing Code : HINT) error, u 


    
   //
    
    prev_cart_position = cart_position;
    prev_cart_velocity = cart_velocity;
    prev_error = error;
    prev_u = u;
    

    if(abs(u)>=255){
      if(u>=0)
          u = 255;
      else 
          u = -255;
    }
    if(abs(u)<=10)
        u = 0;   
        
    if(t >=End_Time){
      target_cart_velocity = 0;
      Set_PWM(0);
    }else{
      Set_PWM(u);
    }
    t +=t_step;    
    byte * time_ = (byte *) &t;
   Serial.write(time_,4);
    byte * b = (byte *) &cart_velocity;
    Serial.write(b,4);
}


void setup() {
  // OLED SETUP
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
  MsTimer2::set(1, control);      
  MsTimer2::start();              
  attachInterrupt(0, doEncoderA, CHANGE);   

  // motor stop
  digitalWrite(IN1, 0);         
  digitalWrite(IN2, 0);         
  digitalWrite(PWM, 0); 
   
  oled.drawstring(00,1,"=====PI_CONTROL=====");
  oled.display();
}
void loop() {

}
void doEncoderA(){cart_encoder += (digitalRead(ENCODER_A)==digitalRead(ENCODER_B))?1:-1;}
void doEncoderB(){cart_encoder += (digitalRead(ENCODER_A)==digitalRead(ENCODER_B))?-1:1;}
