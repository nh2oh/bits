% B = [Bx;By]; norm(B) = 1
% Bx = cos(theta); theta = 2*pi*rand()
% p(theta)*d_theta = d_theta/(2*pi)
% 
% N = 100000; dBx = 1/1000;
% theta = 2*pi*rand([N,1]);
% Bx = cos(theta);
% bins_Bx = [-B:dBx:B]';
%
%

N = 100000;
B = 1;
theta = 2*pi*rand([N,1]);  % theta ~ [0,2*pi]
Bx = B*cos(theta);

dBx = 1/100;
bins_Bx = [-1*B:dBx:B]';
for i=1:size(bins_Bx,1)
    bins_Bx(i,2) = sum([Bx>=bins_Bx(i,1) & Bx<bins_Bx(i,1)+dBx])/N;
end

plot(bins_Bx(:,1),bins_Bx(:,2),'-ob')
plottools

B_analytic = (1/(2*pi)).*(1./sin(theta));
