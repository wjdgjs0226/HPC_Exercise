clear
clc

result = table2array(readtable('result.txt'));
t = 0:0.001:0.199;
x = 0:0.05:1;

%% 
figure(1)
hold on
surface(x,t,flip(result));
hold off