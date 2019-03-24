% absx = h(x)
%
% From W. Kahan's "Why is Floating-Point Computation so Hard to Debug 
% when it Goes Wrong?"
% http://people.eecs.berkeley.edu/~wkahan/WrongR.pdf
%
% Computes what "should" be abs(x) in the following way:
%   y = abs(x)^((1/2)^128) 
%   w = y^((2)^128)
%
% Note that x^(1/n) -> 1 as n -> infty for all x>0.  For x<1 the approach
% is from below; for x>1, the approach is from above.  If sqrt(x) is correctly 
% rounded, sqrt(x) for x >=1 is rounded to 1.  For x<1 (even by 1 ulp), 
% sqrt(x) is rounded _down_ to 1 ulp < 1 = 0.999999... (that is, the correct
% rounding of sqrt(0.99999...)==0.9999...  Thus, at the end of the first 
% step, y(i)==0.9999.... for all x(i)<1 and y(i)==1 for all x(i)>=1.  The
% second step essentially floor()'s the y's.  
% 
%

function absx = h(x)
    y = abs(x);
    for i=1:128
        y=sqrt(y);
    end
    
    w = y;
    for i=1:128
        w = w.*w;
    end

    absx = w;
end


