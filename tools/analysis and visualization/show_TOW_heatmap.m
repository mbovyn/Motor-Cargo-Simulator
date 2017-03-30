fractiont=fraction';

figure
imagesc(fractiont);

set(gca,'Ydir','normal')
set(gca,'XTick',1:length(pi_0_axis{1}))
set(gca,'YTick',1:length(N_axis{1}))

if(small)
    
%     small_y_tick_labels=num2cell(N_axis{1}(1,:));
%     small_y_tick_labels(2:2:length(small_y_tick_labels))=repmat({''},numel(2:2:length(small_y_tick_labels)),1);
%     y_tick_labels=small_y_tick_labels;
    
    y_tick_labels=N_axis{1}(1,:);
    
else
    
    y_tick_labels=N_axis{1}(1,:);

end

set(gca,'XTickLabel',pi_0_axis{1}(:,1))
set(gca,'YTickLabel',y_tick_labels)

colormap(colorcet('L9'))
caxis([0 1])

title(titlestr)

if(~small)
    
    h=colorbar();
    ylabel(h,'ToW Probability')
    
    xlabel('On Rate (1/s)')
    ylabel('Number of Motors')
   
end