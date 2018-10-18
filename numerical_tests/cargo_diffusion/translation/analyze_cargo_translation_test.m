clear

%% setup for analyzing data

%set names, paths and numbers of runs
run_name={'test_cargo_translation'};
localpath={pwd};
nruns={[4,1]};

%analysis file path
analysispath='~/project_code/Motor_Freedom/analysis and visualization';

%run import script
run([analysispath '/import_params_and_results.m'])

%%

kBT=.00400388;
cs=lines(nruns{1}(1));

fill_between_lines = @(X,Y1,Y2,C) fill( [X fliplr(X)],  [Y1 fliplr(Y2)], C );

%% 3D displacement

figure

for i=1:nruns{1}(1)
    
    %started at 0
    %displacements would be sqrt(sum(locs(i).center.^2,2))
    sqdisp3=sum(locs(i).center.^2,2);
    
    msd=mean(sqdisp3,3);
    sem=std(sqdisp3,[],3)/sqrt(size(sqdisp3,3));
    
    t=squeeze(locs(i).t_arr(:,:,1));
    hh(i)=plot(t,msd,'color',cs(i,:));
    hold on
    plot(t,6*kBT/(6*pi*params(i).eta*params(i).R)*t,'--','color',cs(i,:),'linewidth',1.5)
    
    h=fill_between_lines(t(2:end)',msd(2:end)'-sem(2:end)',msd(2:end)'+sem(2:end)',cs(i,:));
    set(h,'facealpha',.3)
    
end
set(gca,'yscale','log')
ylim([50^-1,50])
xlim([0,1])

xlabel('Time (s)')
ylabel('Mean Square Displacement')
legend(hh,['R=' num2str(params(1).R)],['R=' num2str(params(2).R)],...
    ['R=' num2str(params(3).R)],['R=' num2str(params(4).R)],...
    'location','northwest')

%% location distributions
titles={'x component','y component','z component'};
figure
for j=1:3
    subplot(3,1,j)
    for i=1:nruns{1}(1)
        [f,x]=ecdf(squeeze(locs(i).center(end,j,:)));
        hh(i)=stairs(x,f,'color',cs(i,:));
        hold on
        %single component, so std should be sqrt(2Ddt)
        plot(x,normcdf(x,0,sqrt(2*kBT/(6*pi*params(i).eta*params(i).R)*summary(i).t_final(end))))
    end
    title(titles{j})
    xlim([-10,10])
    xlabel('Position (\mum)')
    ylabel('Cumulitive Density')
    legend(hh,['R=' num2str(params(1).R)],['R=' num2str(params(2).R)],...
        ['R=' num2str(params(3).R)],['R=' num2str(params(4).R)],...
        'location','northwest')
end
