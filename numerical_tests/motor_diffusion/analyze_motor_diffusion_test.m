
clear
%% setup for analyzing data

%set names, paths and numbers of runs
run_name={'test_motor_diffusion'};
localpath={pwd};
nruns={[4,8]};

%analysis file path
analysispath='~/project_code/Motor_Freedom/analysis and visualization';

%run import script
run([analysispath '/import_params_and_results.m'])

%%

for i=1:nruns{1}(1)
    for j=1:nruns{1}(2)
        
        d(i,j)=params(i,j).D_m(1);
        theta(i,j)=params(i,j).theta_c;
        mfp(i,j)=mean(summary(i,j).t_final);
        mfpsem(i,j)=std(summary(i,j).t_final)/sqrt(length(summary(i,j).t_final));
        
    end
end

%%
errorbar(theta',mfp',mfpsem','.')
hold on

cs=lines(nruns{1}(1));
%x=linspace(0,pi);
x=linspace(-pi/2,pi/2);
for i=1:nruns{1}(1)
    plot(x,params(1,1).R^2/d(i,1)*log((1-cos(pi))./(1-cos(x+pi/2))),'color',cs(i,:))
end
set(gca,'yscale','log')
ylim([10^-4,10^2])
%xlim([0,3.1415962])
xlim([-pi/2,pi/2])
legend(['D=' num2str(d(1,1))],['D=' num2str(d(2,1))],...
    ['D=' num2str(d(3,1))],['D=' num2str(d(4,1))])
ylabel('Mean First Passage Time (s)')
xlabel('Target Elevation (radians)')

%%
figure
cs=lines(nruns{1}(2));

for i=1:nruns{1}(1)
    subplot(2,2,i)
    for j=1:nruns{1}(2)
        
        [f,x]=ecdf(summary(i,j).t_final);
        stairs(x,f,'Linewidth',1.5,'Color',cs(j,:));
        hold on
        plot(x,expcdf(x,params(1,1).R^2/d(i,j)*log((1-cos(pi))./(1-cos(theta(i,j)+pi/2)))),'color',cs(j,:))
        
    end
    xlabel('First Passage Time (s)')
    ylabel('Cumulative Density')
    title(['D=' num2str(d(i,1))])
end
