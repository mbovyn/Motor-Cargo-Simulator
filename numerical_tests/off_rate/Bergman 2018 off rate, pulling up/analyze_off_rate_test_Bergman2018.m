%compare simulated association times to off rates input into simulation
%bergman 2018 off rate (symmetrical)
clear
%% setup for analyzing data

%set the name of the run here
run_name={'test_off_rate'};
localpath={pwd};
nruns={[17,1]};

%analysis file path
analysispath='~/project_code/Motor_Freedom/analysis and visualization';

run([analysispath '/import_params_and_results.m'])

%% find mean unbinding time

for i=1:nruns{1}(1)
    lbc=summary(i).last_bound_center(:,1);
    load(i)=(lbc(3)-params(i).R-params(i).L(1))*params(i).k_m(1);
    unbind_time(i)=mean(summary(i).t_final);
    unbind_time_sem(i)=std(summary(i).t_final)/sqrt(length(summary(i).t_final));
end

%% plot mean binding time
%association times is 1/unbinding rate

errorbar(load,unbind_time,unbind_time_sem,'.')
hold on
plot(linspace(0,5),1./(params(i).eps_0(1)*exp(linspace(0,5)/params(i).F_d(1))))
plot(linspace(5,25),1./(params(i).a(1)+params(i).b(1)*linspace(5,25)))
legend('Simulated','1/off rate (substall)','1/off rate (superstall)')
xlabel('Force (pN)')
ylabel('Association Time (s)')
xlim([-1,16])

%% plot binding time distributions
%Unbinding is a poisson process, so association times should be exponential

figure

cs=lines(nruns{1}(1));
clearvars hh legendentry
notrun=1;

for i=1:nruns{1}(1)
    if load(i)>5 && notrun
        title('Substall')
        xlim([.005,10])
        xlabel('Association Time (s)')
        ylabel('Cumulative Density')
        legend(hh,legendentry,'location','northwest')
        set(gca,'xscale','log')

        figure
        clearvars hh legendentry
        notrun=0;
        switchover=i-1;
    end
    [f,x]=ecdf(summary(i).t_final);
    if load(i)<5
        j=i;
    else
        j=i-switchover;
    end
    hh(j)=stairs(x,f,'Linewidth',1.5,'Color',cs(i,:));
    %legendentry{2*(i-1)+1}=['f=' num2str(load(i))];
    legendentry{j}=['f=' num2str(load(i))];
    hold on
    if load(i)<5
        rate=(params(i).eps_0(1)*exp(load(i)./params(i).F_d(1)));
        plot(x,expcdf(x,1./rate),'Color',cs(i,:))
    else
        rate=(params(i).a(1)+params(i).b(1)*load(i));
        plot(x,expcdf(x,1./rate),'Color',cs(i,:))
    end
    %legendentry{2*(i-1)+2}=['~exp(' num2str(rate) ')'];
end

title('Superstall')
xlim([.005,10])
xlabel('Association Time (s)')
ylabel('Cumulative Density')
legend(hh,legendentry,'location','northwest')
set(gca,'xscale','log')
