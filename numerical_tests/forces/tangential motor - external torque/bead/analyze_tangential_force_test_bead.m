clear
close all

%% setup for analyzing data

%set names, paths and numbers of runs
run_name={'tangential_force_test'};
localpath={pwd};
nruns={[1,1]};

%analysis file path
analysispath='~/project_code/Motor_Freedom/analysis and visualization';

%run import script
%won't overwrite - only does import if variable params doesn't exist
run([analysispath '/import_params_and_results.m'])

%%

kBT=.00400388;

plot(omega.t_arr(2:end),omega.vector(2:end,2)./diff(omega.t_arr),'o')
hold on
plot(omega.t_arr,ones(size(omega.t_arr))*params.T_ext(2)/(8*pi*params.eta*params.R^3),'--')
%plot(omega.t_arr,ones(size(omega.t_arr))*params.T_ext(2)/(8*pi*params.eta*params.R^3/params.R+params.R^2*kBT/params.D_m(1)))
%ylim([0 Inf])


%% bead version

figure
plot(forces.t_arr,forces.Ftangential{1}(:,1),'o')
hold on
plot(forces.t_arr,ones(size(forces.t_arr))*params.T_ext(2)/params.R,'Linewidth',1.5)
ylim([0,1.1])