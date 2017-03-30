
set(findall(gcf,'-property','FontSize'),'FontSize',10)

fig = gcf;
fig.PaperUnits = 'centimeters';

if(small)
    fig.PaperPosition = [0 0 8 4];
    fig.PaperSize = [8 4];
else
    fig.PaperPosition = [0 0 8 8];
    fig.PaperSize = [8 8];
end
print(filename,'-dpdf')