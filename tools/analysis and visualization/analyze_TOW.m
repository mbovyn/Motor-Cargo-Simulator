%% file juggling

%set the name of the run here
run_name='TOW_fraction';

%% Import Data

run([analysispath '/import_params_and_multiple_summaries.m'])

%% Find TOW probability

for i=1:nruns
    
    Ns(i)=runs(i).N1(1,1);
    
    stayed_on=runs(i).exit_cond==12 | runs(i).exit_cond==8;
    sum(stayed_on)
    TOWed=sum(runs(i).exit_cond(stayed_on)==12);
    passed=sum(runs(i).exit_cond(stayed_on)==8);
    
    fraction(i)=TOWed/sum(stayed_on);
    
    %SEM from 
    %http://stats.stackexchange.com/questions/29641/standard-error-for-the-mean-of-a-sample-of-binomial-random-variables
    
    SEM(i)=sqrt(fraction(i)*(1-fraction(i))/sum(stayed_on));
    
end

%%

errorbar(Ns,fraction,SEM,'.')

hold on

if exist('mult','var')
    lims=[6 52];
else
    lims=[Ns(1)-2 Ns(end)+2];
end

if exist('experimental_fraction','var')
    experimental_SE=sqrt(experimental_fraction*(1-experimental_fraction)/experimental_n);
    experimental_CI=1.96*sqrt(experimental_fraction*(1-experimental_fraction)/experimental_n);

    plot(lims,[experimental_fraction experimental_fraction],'k')
    plot(lims,[experimental_fraction+experimental_SE experimental_fraction+experimental_SE],'k--')
    h=plot(lims,[experimental_fraction-experimental_SE experimental_fraction-experimental_SE],'k--');
    set(get(get(h,'Annotation'),'LegendInformation'),'IconDisplayStyle','off');
    
    plot(lims,[experimental_fraction+experimental_CI experimental_fraction+experimental_CI],'k:')
    h=plot(lims,[experimental_fraction-experimental_CI experimental_fraction-experimental_CI],'k:');
    set(get(get(h,'Annotation'),'LegendInformation'),'IconDisplayStyle','off');
end

if (exist('makesubfigure','var') && ~exist('mult','var') ) || exist('lastone','var')
    
    if exist('makesubfigure','var') && strcmp(makesubfigure,'full')
    
        xlabel('Number of Motors on the Cargo')
        ylabel('Fraction of Cargos that TOW')
        legend('Simulated','Experiment','Location','NorthWest')
    
    end
    
    axis([lims(1) lims(2) 0 1])
    title(titlestr)
    
    set(gca,'FontSize',10);

    fig = gcf;
    fig.PaperUnits = 'inches';
    fig.PaperPosition = [0 0 3.25 2.75];
    fig.PaperSize = [3.25 2.57];
    
elseif exist('mult','var')
    
else
    
    axis([lims(1) lims(2) 0 1])
    title(titlestr)
    
    xlabel('Number of Motors on the Cargo')
    ylabel('Fraction of Cargos that TOW')
    title(titlestr)
    legend('Simulated +/- Standard Error','Experiment','+/- Experiment Standard Error','Location','NorthWest')
    
end