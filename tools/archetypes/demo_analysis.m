% analyze run length

run_name='demo_mult';
localpath=pwd;

%analysis file path
analysispath='/Users/Matt/project_code/Motor_Freedom/tools/analysis and visualization';

%%

clear summaries_imported

nruns=5;

run([analysispath '/import_params_and_multiple_summaries.m'])

%%

for i=1:nruns

    run_length(i)=mean(runs(i).last_bound_center(:,1));
    bind_rate(i)=runs(i).pi_0(1);
    
    SEM(i)=std(runs(i).last_bound_center(:,1))/sqrt(length(last_bound_center(:,1)));

end

%%

errorbar(bind_rate,run_length,SEM,'.')

title(sprintf('3 Motor Run Length Demo'))
ylabel('Mean Run Length (\mum)')
xlabel('Microscopic on rate (1/s)')