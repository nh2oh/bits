%
% Demo of the function h(x) from W. Kahan's "Why is Floating-Point 
% Computation so Hard to Debug when it Goes Wrong?"
% http://people.eecs.berkeley.edu/~wkahan/WrongR.pdf
%
% Attempts to use the function h(x) to compute what "should" be 
% y = abs(x)
%
x = [0:0.1:2]';
y = h(x);

ph_h = plot(x,y,'-ob');  %plottools;
xlabel(ph_h.Parent,"x");
ylabel(ph_h.Parent,"h(x)");

%
% Demonstration of how y=x(1/n) -> 1 as n->infty
%
figure;
ph_sq = plot(x,x.^(1/2),'-ob',x,x.^(1/4),'-or',x,x.^(1/16),'-og');
xlabel(ph_sq(1).Parent,"x");  % NB: the "Parent" of each element of ph_sq is the same
ylabel(ph_sq(1).Parent,"x^p");
legend(ph_sq(1).Parent,{"p = 1/2","p = 1/4","p = 1/16"});

