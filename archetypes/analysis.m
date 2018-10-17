%% setup for analyzing data

%set names, paths and numbers of runs
run_name={'condition1','condition2'};
localpath={[pwd '/condition1directory'],[pwd '/condition2directory']};
nruns={[10,1],[10,1]};

%analysis file path
analysispath='~/project_code/Motor_Freedom/analysis and visualization';

%run import script
%won't overwrite - only does import if variable params doesn't exist
run([analysispath '/import_params_and_results.m'])
