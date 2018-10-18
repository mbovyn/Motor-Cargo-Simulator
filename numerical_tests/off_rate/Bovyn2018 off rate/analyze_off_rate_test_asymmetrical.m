%compare simulated association times to off rates input into simulation

%% setup for analyzing data

%set the name of the run here
run_name={'test_off_rate','test_off_rate'};
localpath={[pwd '/assisting'],[pwd '/hindering']};
nruns={[17,1],[17,1]};

%analysis file path
analysispath='~/project_code/Motor_Freedom/analysis and visualization';

run([analysispath '/import_params_and_results.m'])

%% find mean unbinding time

for j=1:length(run_name)
    for i=1:nruns{j}(1)
        if j>1
            k=i+nruns{1}(1);
        else
            k=i;
        end
        lbh=summary(i,j).last_bound_head{1}(1,:,1);
        load(k)=(lbh(1)-sign(lbh(1))*params(i,j).R-sign(lbh(1))*params(i,j).L(1))*params(i,j).k_m(1);
        unbind_time(k)=mean(summary(i,j).t_final);
        unbind_time_sem(k)=std(unbind_time(k))/sqrt(length(summary(i,j).t_final));
    end
end

%% plot mean binding time
%association times is 1/unbinding rate

errorbar(load,unbind_time,unbind_time_sem,'.')
hold on
plot(linspace(0,5),1./(params(i).eps_0(1)*exp(linspace(0,5)/params(i).F_d(1))))
plot(linspace(5,25),1./(params(i).a(1)*exp(linspace(5,25)/params(i).b(1))))
plot(linspace(-25,0),1./(7.4*exp(abs(linspace(-25,0)/12.9436))))
legend('Simulated','1/off rate (substall)','1/off rate (superstall)','1/off rate (assisting)')
xlabel('Force (pN)')
ylabel('Association Time (s)')
%xlim([-1,16])

%% plot binding time distributions
%Unbinding is a poisson process, so association times should be exponential

figure

cs=lines(nruns{1}(1));
clearvars hh legendentry
notrun=1;

for j=1:length(run_name)
    for i=1:nruns{j}(1)
        
        if j>1
            k=i+nruns{1}(1);
        else
            k=i;
        end
        
        if j==2 && load(k)>5 && notrun
            title('Substall')
            xlim([.01,10])
            xlabel('Binding Time (s)')
            ylabel('Cumulative Density')
            legend(hh,legendentry,'location','northwest')
            set(gca,'xscale','log')

            figure
            clearvars hh legendentry
            notrun=0;
            switchover=i-1;
        end
        [f,x]=ecdf(summary(i,j).t_final);
        if load(k)<5 || j==1
            l=i;
        else
            l=i-switchover;
        end
        hh(l)=stairs(x,f,'Linewidth',1.5,'Color',cs(i,:));
        %legendentry{2*(i-1)+1}=['f=' num2str(load(i))];
        legendentry{l}=['f=' num2str(load(k))];
        hold on
        if j==1
            rate=7.4*exp(abs(load(k)./12.9436));
        else 
            if load(k)<5
                rate=(params(i,j).eps_0(1)*exp(load(k)./params(i,j).F_d(1)));
            else
                rate=(params(i,j).a(1)*exp(load(k)./params(i,j).b(1)));
            end
        end
        plot(x,expcdf(x,1./rate),'Color',cs(i,:))
        %legendentry{2*(i-1)+2}=['~exp(' num2str(rate) ')'];
    end
    if j==1
        title('Assisting')
        xlim([.001,.5])
        xlabel('Binding Time (s)')
        ylabel('Cumulative Density')
        legend(hh,legendentry,'location','northwest')
        set(gca,'xscale','log')

        figure
        clearvars hh legendentry
    end
        
end

title('Superstall')
xlim([.001,2])
xlabel('Binding Time (s)')
ylabel('Cumulative Density')
legend(hh,legendentry,'location','northwest')
set(gca,'xscale','log')