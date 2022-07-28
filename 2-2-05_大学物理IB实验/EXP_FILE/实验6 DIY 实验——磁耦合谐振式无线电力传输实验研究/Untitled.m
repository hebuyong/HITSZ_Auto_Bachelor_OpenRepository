%实验6
load data.mat;

x1=(2.115:0.001:2.435)';
y1=interp1(data(1,1:end-1),data(2,1:end-1),x1,'pchip');
plot(x1,y1);
hold on
plot(data(1,1:end-1),data(2,1:end-1),'b-*');

for i=1:9
    str1=num2str(data(1,i));
    str2=num2str(data(2,i));
    str=['(',str1,',',str2,')'];
    text(data(1,i),data(2,i),str,'FontSize',8);
end
grid on;
box on;
xlabel('f/MHz');
ylabel('Vpp/V');
title('Vpp-f曲线');

figure;
x2=(10:0.1:37)';
y2=interp1(data(3,1:end),data(4,1:end),x2,'pchip');
plot(x2,y2);
hold on
plot(data(3,1:end),data(4,1:end),'b-*');

for i=1:10
    str1=num2str(data(3,i));
    str2=num2str(data(4,i));
    str=['(',str1,',',str2,')'];
    text(data(3,i),data(4,i),str,'FontSize',8);
end
grid on;
box on;
xlabel('距离d/cm');
ylabel('Vpp/V');
title('Vpp-d曲线');