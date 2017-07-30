%possible exit conditions are:
% 1: detach before intersection
% 8: exit ToW zone on primary MT (pass)
% 9: exit ToW zone on crossing MT (switch)
% 13: detach after intersection on primary MT (pass)
% 14: detach after intersection on crossing MT (switch)

%ToW given by TOW_time>0 (numerically TOW_time>.1)

theta=zeros(nruns(1),nruns(2));

towed=cell(nruns(1),nruns(2));
switched=cell(nruns(1),nruns(2));
stayed_on=cell(nruns(1),nruns(2));
fell_off=cell(nruns(1),nruns(2));
discarded=cell(nruns(1),nruns(2));

n_stayed_on=zeros(nruns(1),nruns(2));
n_ToWed=zeros(nruns(1),nruns(2));
p_ToW=zeros(nruns(1),nruns(2));
p_switch=zeros(nruns(1),nruns(2));
p_switchToW=zeros(nruns(1),nruns(2));

SE_ToW=zeros(nruns(1),nruns(2));
SE_switch=zeros(nruns(1),nruns(2));
SE_switchToW=zeros(nruns(1),nruns(2));

run([analysispath '/import_multiple_ToWs.m'])

for i=1:nruns(1)
    for j=1:nruns(2)
        
        %find the angle between the MTs from their unit vectors
        %(first MT always set to [1 0 0] unit vector, second MTvec only one
        %passed out)
        theta(i,j)=180-acosd(dot(runs(i,j).MTvec(1,:),[1 0 0]));
        
        valid=runs(i,j).exit_cond>0;

        %ToW if
        %ToW status or switch
        towed{i,j}=valid & ( ...
            (success==1)' ...
            ...(runs(i,j).ToW_time>.25)' ...
            ...runs(i,j).ToWs'>0 ...
            | runs(i,j).exit_cond==9 ...
            | runs(i,j).exit_cond==14 ...
            );
        %passed{i,j}=runs(i,j).exit_cond==8 | runs(i,j).exit_cond==13;
        switched{i,j}=runs(i,j).exit_cond==9 | runs(i,j).exit_cond==14;

        %was a valid run if have any of the listed exit conditions
        stayed_on{i,j}=runs(i,j).exit_cond==9 | runs(i,j).exit_cond==8 | ...
            runs(i,j).exit_cond==13 | runs(i,j).exit_cond==14;
        fell_off{i,j}=runs(i,j).exit_cond==1;
        discarded{i,j}=~fell_off{i,j} & ~stayed_on{i,j};

        %find probability of ToW, switch, switch | ToW
        n_stayed_on(i,j)=sum(stayed_on{i,j});
        n_ToWed(i,j)=sum(towed{i,j} & stayed_on{i,j});
        p_ToW(i,j)=n_ToWed(i,j)/n_stayed_on(i,j);
        p_switch(i,j)=sum(switched{i,j} & stayed_on{i,j})/n_stayed_on(i,j);
        p_switchToW(i,j)=sum(towed{i,j} & switched{i,j} & stayed_on{i,j})/sum(towed{i,j});

        %SEM from 
        %http://stats.stackexchange.com/questions/29641/standard-error-for-the-mean-of-a-sample-of-binomial-random-variables
        SE_ToW(i,j)=sqrt(p_ToW(i,j)*(1-p_ToW(i,j))/n_stayed_on(i,j));
        SE_switch(i,j)=sqrt(p_switch(i,j)*(1-p_switch(i,j))/n_stayed_on(i,j));
        SE_switchToW(i,j)=sqrt(p_switchToW(i,j)*(1-p_switchToW(i,j))/n_ToWed(i,j));
        
        %bernoulli trial variance is np(1-p)
        %var_ToW(i,j)=n_stayed_on(i,j)*p_ToW(i,j)*(1-p_ToW(i,j));
        %var_switch(i,j)=n_stayed_on(i,j)*p_switch(i,j)*(1-p_switch(i,j));
        %var_switchToW(i,j)=n_ToWed(i,j)*p_switchToW(i,j)*(1-p_switchToW(i,j));
    
        %record parameters
        pi_0_axis(i,j)=runs(i,j).pi_0(1);
        N_axis(i,j)=runs(i,j).N1(1);
    
    end
end