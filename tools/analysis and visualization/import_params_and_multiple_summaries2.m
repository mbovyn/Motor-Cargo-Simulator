if ~exist('params_imported','var')
    %2 entry parameters
    run([analysispath '/import_params2.m'])
    %1 entry parameters
    run([analysispath '/import_params.m'])
    %MT params
    run([analysispath '/import_MT_params.m'])
    
    params_imported=true;
end

%take in the summary the simulation writes if we haven't yet
if ~exist('summaries_imported','var')
    
    base_run_name=run_name;
    runs=struct;
    
    for runno1=1:nruns(1)
        
        for runno2=1:nruns(2)
        
            run_name=[base_run_name '.' int2str(runno1) '.' int2str(runno2)];
            run([analysispath '/import_summary.m'])

            runs(runno1,runno2).repeat=repeat;
            runs(runno1,runno2).step = step;
            runs(runno1,runno2).t_arr = t_arr;
            runs(runno1,runno2).exit_cond = exit_cond;
            runs(runno1,runno2).success = success;
            runs(runno1,runno2).D_anchor = D_anchor;
            runs(runno1,runno2).eps_0 = eps_0;
            runs(runno1,runno2).pi_0 = pi_0;
            runs(runno1,runno2).offset = offset;
            runs(runno1,runno2).R = R;
            runs(runno1,runno2).N1 = N1;
            runs(runno1,runno2).F1 = F1;
            runs(runno1,runno2).theta_c = theta_c;
            runs(runno1,runno2).last_bound_center = last_bound_center;
            runs(runno1,runno2).center_final = center_final;
            runs(runno1,runno2).locs_final = locs_final;
            runs(runno1,runno2).head_final = head_final;
            runs(runno1,runno2).MTvec=MTvec{2};
            runs(runno1,runno2).ToW_time=ToW_time;
            
        end
    end
    
    clear runno1 runno2
    summaries_imported=true;
    
end