function []=pfit(theta,p,SE,c,ft,opt)

%fit curve
%weights given by 1/variance
%https://www.mathworks.com/help/curvefit/least-squares-fitting.html

if opt==0
    SE(SE==0)=.1;
    f=fit(theta',p',ft,'Weights',1./SE.^2);
else
    f=fit(theta',p',ft,opt);
end

dom=linspace(theta(1),theta(end));
plot(dom,f(dom),'Color',c)    

end

