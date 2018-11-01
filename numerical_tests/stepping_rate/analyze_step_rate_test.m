%check velocities and stepping vs. input stepping rate
clear
%% setup for analyzing data

%set the name of the run here
run_name={'test_step_rate','test_step_rate'};
localpath={[pwd '/hindering'],[pwd '/assisting']};
nruns={[11,1],[5,1]};

%analysis file path
analysispath='~/project_code/Motor_Freedom/analysis and visualization';

run([analysispath '/import_params_and_results.m'])

%% find mean velocity
for j=1:length(run_name)
    for i=1:nruns{j}(1)
        force{j}(i)=params(i,1,j).F_ext(1);
        velocity{j}(i)=mean((summary(i,1,j).last_bound_center(1,:))./summary(i,1,j).t_final');
        velocity_sem{j}(i)=std((summary(i,1,j).last_bound_center(1,:))./summary(i,1,j).t_final')/sqrt(length(summary(i,1,j).last_bound_center(1,:)));
    end
    
    errorbar(force{j},velocity{j},velocity_sem{j},'.')
    hold on
end

% plot mean velocity
%velocity is step size * stepping rate
%note negative value for velocity at 0 - this is due to stretch in motor

x=linspace(min(force{1}),max(force{1}));
plot(x,params(1,1,1).v_f(1)*(1-(abs(x)/params(1,1,1).F_s(1)).^params(1,1,1).w(1)))
x=linspace(0,max(force{2}));
plot(x,ones(size(x))*params(1,1,1).v_f(1))
%ylim([0,2])
xlim([-6,11])
legend('Simulated hindering','Simulated assisting','step\_rate*step\_dist*time','location','SouthEast')
xlabel('Force (pN)')
ylabel('Velocity (\mum/s)')

%%

print('mean velocity vs force','-dpng')

%% plot velocity distributions
%stepping is a poisson proccess, so the number of steps in a given time
%(here 1 second) is poisson distributed

figure

cs=lines(nruns{1}(1));

for i=1:nruns{1}(1)
    [f,x]=ecdf((summary(i).last_bound_center(1,:))./params(i).step_size(1));
    hh(i)=stairs(x,f,'Linewidth',1.5,'Color',cs(i,:));
    legendentry{i}=['f=' num2str(abs(params(i).F_ext(1)))];
    hold on
    plot(x,poisscdf(x,params(i).v_f(1)/params(i).step_size(1)*(1-(abs(params(i).F_ext(1))/params(i).F_s(1)).^params(i).w(1))))
end

xlabel('Number of steps')
ylabel('Cumulative Density')
legend(hh,legendentry,'location','southeast')