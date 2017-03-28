
for i=1:nruns(1)
    for j=1:nruns(2)
        
        stayed_on=runs(i,j).exit_cond==12 | runs(i,j).exit_cond==8;
        
        TOWed=sum(runs(i,j).exit_cond(stayed_on)==12);
        passed=sum(runs(i,j).exit_cond(stayed_on)==8);
        
        fraction(i,j)=TOWed/sum(stayed_on);
        SEM(i,j)=sqrt(fraction(i,j)*(1-fraction(i,j))/sum(stayed_on));
        
        pi_0(i,j)=runs(i,j).pi_0(1);
        N(i,j)=runs(i,j).N1(1);
    
    end
end

%%

experimental_CI=1.96*sqrt(experimental_fraction*(1-experimental_fraction)/experimental_n);

fraction=fraction';
frac_error=abs(fraction-experimental_fraction);

figure
imagesc(frac_error);
hold on

set(gca,'Ydir','normal')
set(gca,'XTick',1:length(pi_0))
set(gca,'YTick',1:length(N))
set(gca,'XTickLabel',pi_0(:,1))
set(gca,'YTickLabel',N(1,:))

within_CI=(fraction>(experimental_fraction-experimental_CI)) & ...
    (fraction<(experimental_fraction+experimental_CI));

h=colorbar();
caxis([min(frac_error(within_CI)) max(frac_error(within_CI))])
ylabel(h,'Error')

xlabel('On Rate (1/s)')
ylabel('Number of Motors')
title(titlestr)

%%


black = cat(3, zeros(size(fraction)), zeros(size(fraction)), zeros(size(fraction)));
hb=imagesc(black);
alpha_data = ~ within_CI;
set(hb, 'AlphaData', alpha_data);



%{
%%
set(findall(gcf,'-property','FontSize'),'FontSize',10)

% hm=gca;
% mainposition=hm.Position;
% cbarPosition=h.Position;
% h.Position=[cbarPosition(1) cbarPosition(2) cbarPosition(3)/1.3 cbarPosition(4)];
% hm.Position=mainposition;

fig = gcf;
fig.PaperUnits = 'centimeters';
fig.PaperPosition = [0 0 9 6];
fig.PaperSize = [9 6];
print('10micronHeatmap','-dpdf')

%%

h2=figure;
imagesc(fraction'>.5)

set(gca,'Ydir','normal')
set(gca,'XTick',1:length(pi_0))
set(gca,'YTick',1:length(N))
set(gca,'XTickLabel',pi_0(:,1))
set(gca,'YTickLabel',N(1,:))

colors=parula(25);
colormap(h2,[colors(2,:);colors(end-2,:)])

hold on
% plot(0,0,'s','MarkerFaceColor',colors(2,:),'Visible','Off')
% plot(0,0,'s','MarkerFaceColor',colors(end-2,:),'Visible','Off')
plot(NaN,NaN,'s','MarkerFaceColor',colors(end-2,:),'MarkerEdgeColor',colors(end-2,:),'MarkerSize',10)
plot(NaN,NaN,'s','MarkerFaceColor',colors(2,:),'MarkerEdgeColor',colors(2,:),'MarkerSize',10)



% ht = text(9, 12, {'{\color{red} o } Red', '{\color{blue} o } Blue', '{\color{black} o } Black'}, 'EdgeColor', 'k', 'BackgroundColor',colors(2,:));
% ht = text(8, 12, 'Fit', 'EdgeColor', 'k', 'BackgroundColor',colors(end-2,:));

xlabel('On Rate (1/s)')
ylabel('Number of Motors')
%title('Fraction of cargos with run lengths greater than 10 \mum')
legend('>50%','<50%')

%%
set(findall(gcf,'-property','FontSize'),'FontSize',10)

% hm=gca;
% mainposition=hm.Position;
% cbarPosition=h.Position;
% h.Position=[cbarPosition(1) cbarPosition(2) cbarPosition(3)/1.3 cbarPosition(4)];
% hm.Position=mainposition;

fig = gcf;
fig.PaperUnits = 'centimeters';
fig.PaperPosition = [0 0 7 6];
fig.PaperSize = [7 6];
print('10micronHeatmapBinary','-dpdf')

%}