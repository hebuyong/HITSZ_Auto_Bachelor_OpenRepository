%事先导入数据表格
load data.mat
%表格形式转成double
b=table2array(data);
%提取x ，y 数据
x=b(:,1);
y=[b(:,2),b(:,4),b(:,6)];
%原图
figure
plot([x,x,x],y)
xlabel('U_{G2K}/V')
ylabel('I_{A}/nA')
title('I_{A}-U_{G2K}曲线(原图)')
legend('V_{G2A}=7V','V_{G2A}=6.5V','V_{G2A}=7.5V')
%给部分未测得的y值插值，此取两端平均值
for j=1:3
    for i=1:180
        if isnan(y(i,j))==1
            y(i,j)=0.5*(y(i-1,j)+y(i+1,j));
        end
    end
end
%整体插值
x1=(0:0.1:90)';
y1(:,1)=interp1(x,y(:,1),x1,'spline');
y1(:,2)=interp1(x,y(:,2),x1,'spline');
y1(:,3)=interp1(x,y(:,3),x1,'spline');
%平滑后图
figure
plot([x1,x1,x1],y1)
xlabel('U_{G2K}/V')
ylabel('I_{A}/nA')
title('I_{A}-U_{G2K}曲线(插值)')
legend('V_{G2A}=7V','V_{G2A}=6.5V','V_{G2A}=7.5V')
%求极值
figure
plot([x1,x1,x1],y1)
xlabel('U_{G2K}/V')
ylabel('I_{A}/nA')
title('I_{A}-U_{G2K}曲线(处理后)')
hold on;
ans=zeros(7,3);
p=1;
for j=1:3
    for i=2:length(y1)-1
        if y1(i,j)>10&y1(i,j)>= y1(i-1,j)& y1(i,j)>= y1(i+1,j)
            plot(x1(i),y1(i,j),'R*');
            str=num2str(x1(i));
            text(x1(i),y1(i,j),str);
            if p<=7
                ans(p,j)=x1(i);
                p=p+1;
            end
        end
    end
    p=1;
end
%最小二乘法
temp=(1:7)';
Pfinal=[];
for i=1:3
    P=polyfit(temp,ans(:,i),1);
    Pfinal=[Pfinal;P];
end
average=(Pfinal(1,1)+Pfinal(2,1)+Pfinal(3,1))/3



