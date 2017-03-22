
%%
%set the name of the run here
run_name='demo_mult';
localpath=pwd;

%analysis file path
analysispath='~/project_code/Motor_Freedom/tools/analysis and visualization';

nruns=[5,5];

run([analysispath '/import_params_and_multiple_summaries2.m'])

clearvars -except runs nruns

%%

for i=1:nruns(1)
    for j=1:nruns(2)
        
        run_length(i,j)=mean(runs(i,j).last_bound_center(:,1));
        pi_0(i,j)=runs(i,j).pi_0(1);
        eps_0(i,j)=runs(i,j).eps_0(1);
    
    end
end

%%

imagesc(run_length)

set(gca,'Ydir','normal')
set(gca,'YTick',1:length(pi_0))
set(gca,'XTick',1:length(eps_0))
set(gca,'YTickLabel',pi_0(1,:))
set(gca,'XTickLabel',eps_0(:,1))

h=colorbar;

ylabel(h,'Mean Run Length (\mum)')

ylabel('On Rate')
xlabel('Off Rate')
title('3 Motor run lengths (capped at 5 \mum)')