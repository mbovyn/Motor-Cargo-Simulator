for i=1:nruns(1)
    for j=1:nruns(2)
        
        theta(i,j)=180-acosd(dot(runs(i,j).MTvec(1,:),[1 0 0]));

        %towed{j,i}=runs(i).success==1;
        towed{i,j}=runs(i,j).success==1 | runs(i).exit_cond==9 | runs(i).exit_cond==14;

        stayed_on{j,i}=runs(i).exit_cond==9 | runs(i).exit_cond==8 | runs(i).exit_cond==13 | runs(i).exit_cond==14;
        discarded{j}(i)=sum(~stayed_on{j,i});

        towandstay{j,i}=towed{j,i} & stayed_on{j,i};

        TOWed{j}(i)=sum(towandstay{j,i});
        passed{j}(i)=sum( ~towed{j,i} & stayed_on{j,i} );

        fraction{j}(i)=TOWed{j}(i)/sum(stayed_on{j,i});

        %SEM from 
        %http://stats.stackexchange.com/questions/29641/standard-error-for-the-mean-of-a-sample-of-binomial-random-variables

        SEM{j}(i)=sqrt(fraction{j}(i)*(1-fraction{j}(i))/sum(stayed_on{j,i}));
        
        stayed_on=runs(i,j).exit_cond==12 | runs(i,j).exit_cond==8;
        
        TOWed{k}(i,j)=sum(runs(i,j).exit_cond(stayed_on)==12);
        passed{k}(i,j)=sum(runs(i,j).exit_cond(stayed_on)==8);
        
        %fraction{1}(i,j)=TOWed{1}(i,j)/sum(stayed_on);
        %SEM{1}(i,j)=sqrt(fraction{1}(i,j)*(1-fraction{1}(i,j))/sum(stayed_on{1}(i,j)));
        
        pi_0_axis{k}(i,j)=runs(i,j).pi_0(1);
        N_axis{k}(i,j)=runs(i,j).N1(1);
    
    end
end