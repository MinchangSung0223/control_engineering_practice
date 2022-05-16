clear
close all;
%% Data Acquisition

% Serial Port Setup
port_name = "COM3";
baud_rate = 2000000;
s = serialport(port_name,baud_rate);

% Parameter Setup
Ts = 0.001;
End_Time = 20;
Start_Frequency = 0;
End_Frequency = 500;

% Data list
time_list = zeros(End_Time/Ts,1);
vel_list = zeros(End_Time/Ts,1);

filtered_vel=0;
for i = 1:1:size(time_list)
    time = read(s,1,"single");
    vel = read(s,1,"single");
    vel_list(i) = vel;
    time_list(i) = time;    
end

s.delete

%% DRAW BODE PLOT
Ts = 0.001;
t =  0:Ts:(End_Time-Ts);
x =chirp(t,Start_Frequency,End_Time,End_Frequency)';
y = vel_list;
L = length(y);
f = linspace(0,(1/Ts)*pi,L/2+1);

% Fast Fourier Transform for input signal
fft_x = fft(x)
P2_in = abs(fft_x /L);
P1_in = P2_in(1:L/2+1);
P1_in(2:end-1) = 2*P1_in(2:end-1);

%Fast Fourier Transform for output signal
fft_y= fft(y);
P2_out = abs(fft(y)/L);
P1_out = P2_out(1:L/2+1);
P1_out(2:end-1) = 2*P1_out(2:end-1);

% draw bodeplot
semilogx(f,20*log10((P1_out./P1_in)),"r")
hold on;

% Find Parameter
s = tf("s");
K =0;
tau =0.00;
G = K/(tau*s+1);
bode(G);



