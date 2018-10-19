clear

%% setup for analyzing data

%set names, paths and numbers of runs
run_name={'radial_force_test'};
localpath={pwd};
nruns={[3,1]};

%analysis file path
analysispath='~/project_code/Motor_Freedom/analysis and visualization';

%run import script
%won't overwrite - only does import if variable params doesn't exist
run([analysispath '/import_params_and_results.m'])

%%
cs=lines(nruns{1}(1));

for i=1:nruns{1}(1)
    plot(locs(i).t_arr,locs(i).center(:,1),'o','color',cs(i,:))
    hold on
    t=linspace(0,max(locs(i).t_arr));
    %drag of the cargo through the medium
    plot(t,params(i).F_ext(1)/(6*pi*params(i).eta*params(i).R)*t,'color',cs(i,:))
    %equilibrium spring position
    plot(t,ones(size(t))*params(i).F_ext(1)/params(i).k_m(1)-params(i).L(1),'--','color',cs(i,:))
end
ylim([-.13,0])
