clear
clc

original = table2array(readtable('signal.txt'));

nonoise = table2array(readtable('signal_nonoise.txt'));

r2c_output = table2array(readtable('output.txt'));

filtered = table2array(readtable('filtered_output.txt'));

filtered_new = filtered/length(filtered);

%% 
samplerate = 1000.0;
figure(1)
hold on
plot(0:1/samplerate:(length(original)-1)*(1/samplerate), original);
hold off

figure(2)
hold on
plot(0:1/samplerate:(length(nonoise)-1)*(1/samplerate), nonoise);
hold off

figure(3)
hold on
plot(r2c_output(:,1), r2c_output(:,2));
hold off