%实验4
close all; clc;clear;
ds1=xlsread('data.xlsx','A2:AD4');
ds2=xlsread('data.xlsx','A6:T8');
%%
%△T-\tau曲线
figure;hold on;box on;grid on;
y=(ds1(2,:)-ds1(3,:))./0.04;
x=ds1(1,:)./60;
plot(x,y,'linewidth',1,'displayname','橡胶');
y=(ds2(2,:)-ds2(3,:))./0.04;
x=ds2(1,:)./60;
plot(x,y,'linewidth',3,'displayname','有机玻璃');
xlabel('\tau/min');
ylabel('△T/K');
legend('show');
title('△T-\tau曲线');
%T-\tau曲线
figure;hold on;box on;grid on;
y=ds1(3,:)./0.04;
x=ds1(1,:)./60;
plot(x,y,'linewidth',1,'displayname','橡胶');
y=ds2(3,:)./0.04;
x=ds2(1,:)./60;
plot(x,y,'linewidth',3,'displayname','有机玻璃');
xlabel('\tau/min');
ylabel('T/K');
legend('show');
title('T-\tau曲线');
