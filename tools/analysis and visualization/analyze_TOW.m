%% import data

run([analysispath '/import_params_and_multiple_summaries.m'])

%% Find TOW probability



for i=1:nruns
    
    Ns(i)=runs(i).N1(1,1);
    
    stayed_on=~(runs(i).exit_cond==1);
    TOWed=sum(runs(i).exit_cond(stayed_on)==12);
    passed=sum(runs(i).exit_cond(stayed_on)==8);
    
    fraction(i)=TOWed/(TOWed+passed);
    
    %SEM from 
    %http://stats.stackexchange.com/questions/29641/standard-error-for-the-mean-of-a-sample-of-binomial-random-variables
    
    SEM(i)=sqrt(fraction(i)*(1-fraction(i))/sum(stayed_on));
    
end

%%

errorbar(Ns,fraction,SEM,'.')

hold on 

experimental_SE=sqrt(experimental_fraction*(1-experimental_fraction)/experimental_n);

plot([Ns(1) Ns(end)],[experimental_fraction experimental_fraction],'k')
plot([Ns(1) Ns(end)],[experimental_fraction+experimental_SE experimental_fraction+experimental_SE],'k--')
plot([Ns(1) Ns(end)],[experimental_fraction-experimental_SE experimental_fraction-experimental_SE],'k--')

xlabel('Number of Motors on the Cargo')
ylabel('Fraction of Cargos that TOW')

legend('Simulated Fraction +/- Standard Error','Experimental Fraction','+/- Experimental Standard Error','Location','SouthEast')