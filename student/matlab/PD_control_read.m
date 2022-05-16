close all;
clear;
%% Data Acquisition

port_name = "COM3";
baud_rate = 2000000;
endTime = 1;
Ts = 0.001;
target_value = 1;
s = serialport(port_name,baud_rate);

pos_list = zeros(endTime/Ts,1);
time_list = zeros(endTime/Ts,1);
for i = 1:1:size(pos_list)
    time = read(s,1,"single");
    pos = read(s,1,"single");
    pos_list(i) = pos;
    time_list(i) = time;    
end
s.delete
plot(time_list,pos_list);
hold on;



% 파라미터 세팅
T_d = 0; % 부하
R_a=4.29; % 전기자 저항
L_a = 0; % 전기자 인덕턴스
b = 0; % 모터 점성마찰계수
K_t=0.183; % 토크 상수
K_e=0.208; % back emf 상수
Gear_ratio = 20; % 기어비
max_current = 1.2 % 모터드라이버최대출력전류 A
motor_voltage = 10 % 모터 최대 전압
bit_resolution = 2^8; % PWM 출력 0~255 8bit
J=7.083e-06+1.8e-06*Gear_ratio^2; % 동기 폴리가 모터 샤프트를 중심으로 회전할 때의 관성 모먼트
A = motor_voltage/bit_resolution  % 모터 전압 / 모터 드라이버 최대출력전류/PWM bit resolution

zeta = 0.0; % 감쇠비
w_n = 0; % 고유진동수

s = tf('s');
K_P = 0; % 이 부분을 알맞게 수정하시오
K_D=  0; % 이 부분을 알맞게 수정하시오
G = 0;  % 이 부분을 알맞게 수정하시오

%그림 그리기
G_d = c2d(G,0.001,'zoh');
step(G,'-',G_d,'--')
axis([0 time_list(end) 0 target_value+target_value*0.1])


