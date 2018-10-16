%% setup for analyzing data

%set the name of the run here
run_name={'test_step_rate'};
localpath={pwd};
nruns={[11,1]};

%analysis file path
analysispath='~/project_code/Motor_Freedom/analysis and visualization';

run([analysispath '/import_params_and_results.m'])

%% find mean velocity

for i=1:nruns{1}(1)
    force(i)=params(i).F_ext(1);
    velocity(i)=mean((summary(i).last_bound_center(1,:)+params(i).L(1))./summary(i).t_final');
    velocity_sem(i)=std(velocity(i))/sqrt(length(summary(i).last_bound_center(1,:)));
end

%% plot mean velocity
%velocity is step size * stepping rate

errorbar(force,velocity,velocity_sem,'.')
hold on
plot(linspace(min(force),max(force)),...
    params(i).v_f(1)*(1-(abs(linspace(min(force),max(force)))/params(i).F_s(1)).^params(i).w(1)))
%ylim([0,2])
xlim([-6,1])
legend('Simulated','step\_rate*step\_dist*time')
xlabel('Force (pN)')
ylabel('Velocity (\mum/s)')

%% plot velocity distributions
%stepping is a poisson proccess, so the number of steps in a given time
%(here 1 second) is poisson distributed

figure

cs=lines(nruns{1}(1));

for i=1:nruns{1}(1)
    [f,x]=ecdf((summary(i).last_bound_center(1,:)+params(i).L(1))./params(i).step_size(1));
    hh(i)=stairs(x,f,'Linewidth',1.5,'Color',cs(i,:));
    legendentry{i}=['f=' num2str(abs(params(i).F_ext(1)))];
    hold on
    plot(x,poisscdf(x,params(i).v_f(1)/params(i).step_size(1)*(1-(abs(params(i).F_ext(1))/params(i).F_s(1)).^params(i).w(1))))
end

xlabel('Number of steps')
ylabel('Cumulative Density')
legend(hh,legendentry,'location','southeast')