%Analyze test of motor tangential force
%In this test, a torque is applied to the cargo which rotates the cargo
%until the motor is stretched and the anchor drags through the membrane.
%This drag force becomes balanced by the force exerted
%by the motor
clear
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

%% Plot rotational velocity

kBT=.00400388;

%in the simulation we only record differences in angle, not true rotational
%velocities. Need to divide by timestep to convert
w=omega.vector(2:end,2)./diff(omega.t_arr);

plot(omega.t_arr(2:end),w,'o')
hold on
%rotational velocity if just encountering drag from the cargo rotating
%through the surrounding fluid
plot(omega.t_arr,ones(size(omega.t_arr))*...
    params.T_ext(2)/(8*pi*params.eta*params.R^3),'--','linewidth',1.5)
%rotational velocity at steady state when rotating against both an anchor
%and the surrounding fluid
wpredicted=params.T_ext(2)/(8*pi*params.eta*params.R^3+params.R^2*kBT/params.D_m(1));
plot(omega.t_arr,ones(size(omega.t_arr))*...
    wpredicted,'--','linewidth',1.5)

ylabel('Rotatial Velocity (radians/s)')
xlabel('Time (s)')
xlim([0,2.5E-4])
legend('Simulated','Free velocity','Equilibrium velocity','location','east')

%%

print('rotational velocity vs time','-dpng')

%% plot motor tangential force

figure
plot(forces.t_arr,forces.Ftangential{1}(:,1),'o')
hold on
%force predicted on the anchor from the anchor drag
plot(forces.t_arr(2:end),ones(size(forces.t_arr(2:end)))*...
    kBT/params.D_m(1)*params.R.*wpredicted,'linewidth',1.5)
ylabel('Tangential force on motor (pN)')
xlabel('Time (s)')
xlim([0,2.5E-4])
legend('Simulated','Drag force','location','southeast')

%%

print('force vs time','-dpng')