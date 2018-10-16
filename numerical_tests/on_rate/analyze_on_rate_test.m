%Compare the simulated binding times to on rates we input into the simulation

%% setup for analyzing data

%set the name of the run here
run_name={'test_on_rate'};
localpath={pwd};
nruns={[5,1]};

%analysis file path
analysispath='~/project_code/Motor_Freedom/analysis and visualization';

run([analysispath '/import_params_and_results.m'])

%% find mean binding time

for i=1:nruns{1}(1)
    on_rate(i)=params(i).pi_0(1);
    bind_time(i)=mean(summary(i).t_final);
    bind_time_sem(i)=std(bind_time(i))/sqrt(length(summary(i).t_final));
end

%% plot mean binding time
%mean binding time is 1/on rate

errorbar(on_rate,bind_time,bind_time_sem,'.')
hold on
plot(linspace(0,max(on_rate)+1),1./linspace(0,max(on_rate)+1))
ylim([0,2])
xlim([0,11])
legend('Simulated','1/on rate')
xlabel('Micro On Rate (1/s)')
ylabel('Mean Binding Time (s)')

%% plot binding time distributions
%binding is assumed to be a Poisson process, so time to bind should be
%exponentially distributed

figure

cs=lines(nruns{1}(1));

for i=1:nruns{1}(1)
    [f,x]=ecdf(summary(i).t_final);
    stairs(x,f,'Linewidth',1.5,'Color',cs(i,:))
    legendentry{2*(i-1)+1}=['kon=' num2str(params(i).pi_0(1))];
    hold on
    plot(x,expcdf(x,1./params(i).pi_0(1)),'Color',cs(i,:))
    legendentry{2*(i-1)+2}=['~exp(' num2str(params(i).pi_0(1)) ')'];
end

xlim([.001,10])
xlabel('Binding Time (s)')
ylabel('Cumulative Density')
legend(legendentry,'location','northwest')
set(gca,'xscale','log')