%Compare the simulated binding times to on rates we input into the simulation
% as we change the distance between the anchor and the MT
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
%on rate for dist<L is flat
plot(x1,ones(size(x1))*1./params(1).pi_0(1))
kBT=.00400388;
x2=linspace(params(1).L(1),params(1).L(1)+3*sqrt(kBT/params(1).k_m(1)));
%on rate for dist>L is half of gaussian with standard deviation kBT/k_m
plot(x2,1./(params(1).pi_0(1)*exp(-.5*params(1).k_m(1)*(x2-params(1).L(1)).^2/kBT)))
legend('Simulated','1/on rate','location','northwest')
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
    hold on
    %binding times should be exponentially distributed
    plot(x,expcdf(x,1./(params(1).pi_0(1)*exp(-.5*params(1).k_m(1)*(dist(i)-params(1).L(1)).^2/kBT))),'Color',cs(i-4,:))
end

xlim([.005,50])
xlabel('Binding Time (s)')
ylabel('Cumulative Density')
diststrs=string(dist-params(1).L(1));
diststrs="anchor-MT dist="+diststrs+"\mum";
legend(hh,diststrs(5:end),'location','northwest')
set(gca,'xscale','log')