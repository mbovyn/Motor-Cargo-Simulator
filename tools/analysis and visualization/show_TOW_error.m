experimental_CI=1.96*sqrt(experimental_fraction*(1-experimental_fraction)/experimental_n);

fractiont=fraction';
frac_error=fractiont-experimental_fraction;

figure
imagesc(frac_error);
hold on

set(gca,'Ydir','normal')
set(gca,'XTick',1:length(pi_0_axis{1}))
set(gca,'YTick',1:length(N_axis{1}))

if(small)
    
    small_y_tick_labels=num2cell(N_axis{1}(1,:));
    small_y_tick_labels(2:2:length(small_y_tick_labels))=repmat({''},numel(2:2:length(small_y_tick_labels)),1);
    y_tick_labels=small_y_tick_labels;
    
else
    
    y_tick_labels=N_axis{1}(1,:);

end

set(gca,'XTickLabel',pi_0_axis{1}(:,1))
set(gca,'YTickLabel',y_tick_labels)

within_CI=(fractiont>(experimental_fraction-experimental_CI)) & ...
    (fractiont<(experimental_fraction+experimental_CI));

caxis([min(frac_error(within_CI)) max(frac_error(within_CI))])

colormap(diverging_map())

title(titlestr)

if(~small)
    
    h=colorbar();
    ylabel(h,'Simulated - Experiment')
    
    set(h,'YTick',0);
    
    
    xlabel('On Rate (1/s)')
    ylabel('Number of Motors')
    
end


black = cat(3, zeros(size(fractiont)), zeros(size(fractiont)), zeros(size(fractiont)));
hb=imagesc(black);
alpha_data = ~ within_CI;
set(hb, 'AlphaData', alpha_data);