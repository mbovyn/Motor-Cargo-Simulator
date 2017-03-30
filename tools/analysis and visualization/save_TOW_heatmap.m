
set(findall(gcf,'-property','FontSize'),'FontSize',10)

fig = gcf;
fig.PaperUnits = 'centimeters';

if(small)
    fig.PaperPosition = [0 0 7.8 5.3];
    fig.PaperSize = [7.8 5.3];
else
    fig.PaperPosition = [0 0 8 11];
    fig.PaperSize = [8 11];
end
print(filename,'-dpdf')