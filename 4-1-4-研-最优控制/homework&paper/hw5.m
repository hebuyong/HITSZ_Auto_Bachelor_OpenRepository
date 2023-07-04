clear,close all

% the gradient method
a=0.1;t=0.5;
x_0=[0.0,0.0]';
x=x_0;
y=[];
for i=1:50
    y=[y,f(x(1),x(2))];
    x=x-a*df(x(1),x(2));
    if y>=y(1)
        a=a*t;
    end
end
k=1:50;
plot(k,y);
xlabel('k');ylabel('f(x_k)');
title('two methods');
grid on,hold on

%Newton method
b=0.6;
x_0=[0.0,0.0]';
x=x_0;
y=[];
for i=1:50
    y=[y,f(x(1),x(2))];
    d=df(x(1),x(2));
    d2=d2f(x(1),x(2));
    x=x-b*d2^-1*d; 
    end
k=1:50;
plot(k,y);
legend('gradient method','Newton method')

%function f(x)
function y=f(x1,x2)
    y=exp(x1+3*x2-0.1)+exp(x1-3*x2-0.1)+exp(-x1-0.1);
end
%function df(x)
function y=df(x1,x2)
    y=[exp(x1+3*x2-0.1)+exp(x1-3*x2-0.1)-exp(-x1-0.1);3*exp(x1+3*x2-0.1)-3*exp(x1-3*x2-0.1)];
end
%function d2f(x)
function y=d2f(x1,x2)
    y=[exp(x1+3*x2-0.1)+exp(x1-3*x2-0.1)+exp(-x1-0.1),3*exp(x1+3*x2-0.1)-3*exp(x1-3*x2-0.1);
        3*exp(x1+3*x2-0.1)-3*exp(x1-3*x2-0.1),9*exp(x1+3*x2-0.1)+9*exp(x1-3*x2-0.1)];
end











