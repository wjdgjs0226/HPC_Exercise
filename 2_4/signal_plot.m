original = table2array(readtable('signal.txt'));
%filtered = table2array(readtable('filtered_output.txt'));
samplerate = 1000.0;
figure(1)
hold on
plot(0:1/samplerate:(length(original)-1)*(1/samplerate), original);
%plot(0:1/samplerate:(length(filtered)-1)*(1/samplerate), filtered);
hold off