%Compare the simulated binding times to on rates we input into the simulation
clear
%% setup for analyzing data

%set the name of the run here
run_name={'on_rate_dist_test'};
localpath={pwd};
nruns={[10,1]};

%analysis file path
analysispath='~/project_code/Motor_Freedom/analysis and visualization';

run([analysispath '/import_params_and_results.m'])

%% find mean binding time

for i=1:nruns{1}(1)
    dist(i)=params(i).center_inital(3)-params(i).R;
    bind_time(i)=mean(summary(i).t_final);
    bind_time_sem(i)=std(summary(i).t_final)/sqrt(length(summary(i).t_final));
end

%% plot mean binding time
%mean binding time is 1/on rate

errorbar(dist,bind_time,bind_time_sem,'.')
hold on
x1=linspace(0,params(1).L(1));
plot(x1,ones(size(x1))*1./params(1).pi_0(1))
kBT=.00400388;
x2=linspace(params(1).L(1),params(1).L(1)+3*sqrt(kBT/params(1).k_m(1)));
plot(x2,1./(params(1).pi_0(1)*exp(-.5*params(1).k_m(1)*(x2-params(1).L(1)).^2/kBT)))
legend('Simulated','1/on rate')
xlabel('Anchor-MT distance (\mum)')
ylabel('Mean Binding Time (s)')
set(gca,'yscale','log')

%% plot binding time distributions
%binding is assumed to be a Poisson process, so time to bind should be
%exponentially distributed

figure

cs=lines(nruns{1}(1));
clear hh

for i=5:nruns{1}(1)
    [f,x]=ecdf(summary(i).t_final);
    hh(i-4)=stairs(x,f,'Linewidth',1.5,'Color',cs(i-4,:));
    %legendentry{2*(i-1)+1}=['dist=' dist(i)];
    hold on
    plot(x,expcdf(x,1./(params(1).pi_0(1)*exp(-.5*params(1).k_m(1)*(dist(i)-params(1).L(1)).^2/kBT))),'Color',cs(i-4,:))
    %legendentry{2*(i-1)+2}=['~exp(' num2str(params(i).pi_0(1)) ')'];
end

xlim([.002,100])
xlabel('Binding Time (s)')
ylabel('Cumulative Density')
legend(hh,{'0nm','2nm','4nm','6nm','8nm','10nm'},'location','northwest')
set(gca,'xscale','log')