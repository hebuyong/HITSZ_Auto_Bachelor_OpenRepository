%实验7
close all; clear;
ds1=xlsread('data.xlsx','A2:I3');
%%
figure;hold on;box on;grid on;
x=ds1(1,:);
y=ds1(2,:);
y=y/2/100;
plot(x,y,'*r','MarkerSize',10);
for i=1:length(x)
    str1=num2str(x(i));
    str2=num2str(y(i));
    str=['(',str1,',',str2,')'];
    text(x(i),y(i),str,'FontSize',12);
end
x1=linspace(x(1),x(end),10000);
y1=interp1(x,y,x1,'pchip');
plot(x1,y1,'k','LineWidth',2);
xlabel('频率{\mu}/HZ');
ylabel('振幅A/mm');
title('A-{\mu}曲线');