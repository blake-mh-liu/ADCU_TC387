%clear;clc; close all;

%% Execution time
stop_time=0.5;

%% Motor Parameter(temp)
Np=12;        % number of poles
Rs=20e-2;    % (ohms)     
Lq_tab=0.7e-3*ones(3,3);   % (H)
Ld_tab=0.6e-3*ones(3,3);   % (H)
% Lq must greater than Ld
lambda_m=0.05*ones(3,3); %(V/(rad/s)) 
J=0.01;  % inertia of the motor (kg-m^2 for SI)(s for pu)
B=0.001; 
Imax=5;
Vdc=24;
Lamda_m_prime=0.015;
kT=(3/2)*(Np/2)*Lamda_m_prime;
%% current breakpoints
id_bp=[-200,0,200];
iq_bp=[-200,0,200];

%% PI controller
% Spd controller
Ki_s=0.1 ;Kp_s=100; 

% Iq controller
Ki_q=5000;Kp_q=500;

% Id controller
Ki_d=6000;Kp_d=600;

