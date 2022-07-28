%实验5
clear;clc;close all;
load data.mat;

%%表一
ds1=ds1';
x=ds1(1,:);
x1=linspace(x(1),x(end),10000);
y11=ds1(2,:);
y12=interp1(x,y11,x1,'pchip');
y21=ds1(3,:);
y22=interp1(x,y21,x1,'pchip');
y31=ds1(4,:);
y32=interp1(x,y31,x1,'pchip');
figure
plot(x1,y12);
xlabel('U/V');
ylabel('I/mA');
box on
grid on
title('单晶硅暗伏安特性曲线');
figure
plot(x1,y22);
xlabel('U/V');
ylabel('I/mA');
box on
grid on
title('多晶硅暗伏安特性曲线');
figure
plot(x1,y32);
xlabel('U/V');
ylabel('I/mA');
box on
grid on
title('非晶硅暗伏安特性曲线');

%%表二
%%开路电压
x=ds2(2,:);
x1=linspace(x(1),x(end),10000);
y11=ds2(3,:);
y12=interp1(x,y11,x1,'pchip');
y21=ds2(5,:);
y22=interp1(x,y21,x1,'pchip');
y31=ds2(7,:);
y32=interp1(x,y31,x1,'pchip');
figure
hold on
plot(x1,y12,'LineWidth',1);
plot(x1,y22,'LineWidth',2);
plot(x1,y32,'LineWidth',3);
xlabel('I/(W/m^{2})');
ylabel('U_{oc}/V');
box on
grid on
title('开路电压-光强曲线');
legend('单晶硅','多晶硅','非晶硅');
%%短路电流
x=ds2(2,:);
x1=linspace(x(1),x(end),10000);
y11=ds2(4,:);
y12=interp1(x,y11,x1,'pchip');
y21=ds2(6,:);
y22=interp1(x,y21,x1,'pchip');
y31=ds2(8,:);
y32=interp1(x,y31,x1,'pchip');
figure
hold on
plot(x1,y12,'LineWidth',1);
plot(x1,y22,'LineWidth',2);
plot(x1,y32,'LineWidth',3);
xlabel('I/(W/m^{2})');
ylabel('I_{sc}/mA');
box on
grid on
title('短路电流-光强曲线');
legend('单晶硅','多晶硅','非晶硅');
%%表三
x=ds3(7,:);
x1=linspace(x(1),x(end),10000);
y11=ds3(2,:);
y12=interp1(x,y11,x1,'pchip');
y21=ds3(5,:);
y22=interp1(x,y21,x1,'pchip');
y31=ds3(8,:);
y32=interp1(x,y31,x1,'pchip');
figure
hold on
yyaxis left
plot(x1,y12,'-','LineWidth',1);
plot(x1,y22,':','LineWidth',2);
plot(x1,y32,'-.','LineWidth',3);
box on
grid on
xlabel('U/V');
ylabel('I/mA');
title('太阳能电池输出伏安特性曲线及功率曲线');
yyaxis right
y11=ds3(3,:);
y12=interp1(x,y11,x1,'pchip');
y21=ds3(6,:);
y22=interp1(x,y21,x1,'pchip');
y31=ds3(9,:);
y32=interp1(x,y31,x1,'pchip');
plot(x1,y12,'-','LineWidth',1);
plot(x1,y22,':','LineWidth',2);
plot(x1,y32,'-.','LineWidth',3);
%%标注功率曲线顶点
for i=2:length(x1)-1
    if y12(i)>y12(i-1)&&y12(i)>y12(i+1)
        plot(x1(i),y12(i),'r^','LineWidth',2);
       
        text(x1(i),y12(i)+0.2,'R=271Ω');
    end
    if y22(i)>y22(i-1)&&y22(i)>y22(i+1)
        plot(x1(i),y22(i),'r^','LineWidth',2);
        text(x1(i),y22(i)+0.2,'R=329Ω');
    end
    if y32(i)>y32(i-1)&&y32(i)>y32(i+1)
        plot(x1(i),y32(i),'r^','LineWidth',2);
        text(x1(i),y32(i)+0.2,'R=2477Ω');
    end
end
ylabel('P_{0}/mW');
legend('伏安特性-单晶硅','伏安特性-多晶硅','伏安特性-非晶硅','功率-单晶硅','功率-多晶硅','功率-非晶硅');

