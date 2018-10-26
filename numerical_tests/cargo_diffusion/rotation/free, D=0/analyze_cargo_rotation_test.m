% analyze diffusional rotation of the cargo
% free, D=0 version
clear
%% setup for analyzing data

%set names, paths and numbers of runs
run_name={'test_cargo_rotation'};
localpath={pwd};
nruns={[4,8]};

%analysis file path
analysispath='~/project_code/Motor_Freedom/analysis and visualization';

%run import script
run([analysispath '/import_params_and_results.m'])

%%

for i=1:nruns{1}(1)
    for j=1:nruns{1}(2)
        
        r(i,j)=params(i,j).R;
        d(i,j)=.00400388/(8*pi*params(i,j).eta*r(i,j)^3);
        theta(i,j)=params(i,j).theta_c;
        mfp(i,j)=mean(summary(i,j).t_final);
        mfpsem(i,j)=std(summary(i,j).t_final)/sqrt(length(summary(i,j).t_final));
        
    end
end

%%
figure
errorbar(theta',mfp',mfpsem','.')
hold on

cs=lines(nruns{1}(1));
%x=linspace(0,pi);
x=linspace(-pi/2,pi/2);
for i=1:nruns{1}(1)
    plot(x,1/d(i,j)*log((1-cos(pi))./(1-cos(x+pi/2))),'color',cs(i,:))
    %note this is 1/D, not R^2/D - see units for rotational diffusion
end
set(gca,'yscale','log')
%ylim([10^-4,10^2])
%xlim([0,3.1415962])
%xlim([-pi/2,pi/2])
legend(['R=' num2str(r(1,1))],['R=' num2str(r(2,1))],...
    ['R=' num2str(r(3,1))],['R=' num2str(r(4,1))])
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
        plot(x,expcdf(x,1/d(i,j)*log((1-cos(pi))./(1-cos(theta(i,j)+pi/2)))),'color',cs(j,:))
        
    end
    xlabel('First Passage Time (s)')
    ylabel('Cumulative Density')
    title(['R=' num2str(r(i,1))])
end
