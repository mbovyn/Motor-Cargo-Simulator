for i=1:nruns(1)
    for j=1:nruns(2)
        
        stayed_on=runs(i,j).exit_cond==12 | runs(i,j).exit_cond==8;
        
        TOWed{k}(i,j)=sum(runs(i,j).exit_cond(stayed_on)==12);
        passed{k}(i,j)=sum(runs(i,j).exit_cond(stayed_on)==8);
        
        %fraction{1}(i,j)=TOWed{1}(i,j)/sum(stayed_on);
        %SEM{1}(i,j)=sqrt(fraction{1}(i,j)*(1-fraction{1}(i,j))/sum(stayed_on{1}(i,j)));
        
        pi_0_axis{k}(i,j)=runs(i,j).pi_0(1);
        N_axis{k}(i,j)=runs(i,j).N1(1);
    
    end
end