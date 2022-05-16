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

int cart_encoder = 0;
int pwm_u = -100;

//================================OLED FUNCTION===================================//
uint32_t oled_pow(uint8_t m,uint8_t n){
  uint32_t result=1;  
  while(n--)result*=m;    
  return result;
} 
void OLED_ShowNumber(uint8_t x,uint8_t y,uint32_t num,uint8_t len){           
  u8 t,temp;
  u8 enshow=0;    
  oled.drawchar(x-6,y,' ');
  for(t=0;t<len;t++){
    temp=(num/oled_pow(10,len-t-1))%10;
    oled.drawchar(x+6*t,y,temp+'0');
  }  
} 

void OLED_ShowNumber_Minus(uint8_t x,uint8_t y,int num_,uint8_t len){           
  uint32_t num = (uint32_t)(-1*num_);
  u8 t,temp;
  u8 enshow=0;     
  oled.drawchar(x-6,y,'-');
  for(t=0;t<len;t++)  {
    temp=(num/oled_pow(10,len-t-1))%10;
    oled.drawchar(x+6*t,y,temp+'0');
  }
} 

void OLED_Show()
{
  oled.drawstring(00,1,"====ENCODER_READ====");
  oled.drawstring(00,2,"encoder:");
  if(cart_encoder<0)
    OLED_ShowNumber_Minus(70,2,cart_encoder,4);
  else
    OLED_ShowNumber(70,2,cart_encoder,4);
  oled.drawstring(00,4,"Encoder A:");
  if(digitalRead(ENCODER_A)==HIGH)
    oled.drawstring(70,4,"HIGH");
  else
    oled.drawstring(70,4," LOW");
  oled.drawstring(00,5,"Encoder B:");
  if(digitalRead(ENCODER_B)==HIGH)
    oled.drawstring(70,5,"HIGH");
  else
    oled.drawstring(70,5," LOW");
  oled.display();
  oled.drawstring(00,6,"PWM :");
  if(pwm_u<0)
    OLED_ShowNumber_Minus(70,6,pwm_u,3);
  else
    OLED_ShowNumber(70,6,pwm_u,3);
  oled.drawstring(00,7,"DIR :");
  if(pwm_u>0)
    oled.drawstring(70,7,"CW");
  else
    oled.drawstring(70,7,"CCW");  
  
}
//================================================================================//








void Set_PWM(int motor)
{
      // Fill in the Missing Code, HINT: digitalWrite, analogWrite

      //
}

void doEncoderA(){
      // Fill in the Missing Code, HINT: digitalRead

      
      //
}
void doEncoderB(){
      // Fill in the Missing Code, HINT: digitalRead

      
      //
}


void control(){
    Set_PWM(pwm_u);
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
  // motor STOP        
  digitalWrite(IN1, 0);         
  digitalWrite(IN2, 0);         
  digitalWrite(PWM, 0);

  
  //Encoder Setup
  pinMode(ENCODER_A, INPUT);
  pinMode(ENCODER_B, INPUT);

  // Serial Setup
  Serial.begin(2000000);  
  delay(200);          
             
  //Timer Setup
  MsTimer2::set(1, control);      
  MsTimer2::start();              
  //Interrupt Setup
  attachInterrupt(0, doEncoderA, CHANGE);   
  attachInterrupt(1, doEncoderB, CHANGE);    
  

}

void loop(){
  OLED_Show();
  Serial.println(cart_encoder);
}

