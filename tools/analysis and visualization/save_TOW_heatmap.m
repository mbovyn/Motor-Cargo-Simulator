


fig = gcf;
fig.PaperUnits = 'centimeters';

%letter text width = 16.5cm
%letter text height = 22.8cm

w1=7.8;
h1=7.4;

% w2=w;
% h2=2*h;

w2=8;
h2=6;

if small
    
    set(findall(gcf,'-property','FontSize'),'FontSize',10)
    
    if(small==1)
        fig.PaperPosition = [0 0 w1 h1];
        fig.PaperSize = [w1 h1];
    elseif small==2
        fig.PaperPosition = [0 0 w2 h2];
        fig.PaperSize = [w2 h2];
    else
        error('Bad value for small')
    end
    
    print(fname,'-dpdf')
    
else
    printpdf(fname)
end
