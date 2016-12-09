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
    
    for runno=1:nruns
        
        run_name=[base_run_name '.' int2str(runno-1)];
        run([analysispath '/import_summary.m'])
        
        runs(runno).repeat=repeat;
        runs(runno).step = step;
        runs(runno).t_arr = t_arr;
        runs(runno).exit_cond = exit_cond;
        runs(runno).success = success;
        runs(runno).D_anchor = D_anchor;
        runs(runno).eps_0 = eps_0;
        runs(runno).pi_0 = pi_0;
        runs(runno).offset = offset;
        runs(runno).R = R;
        runs(runno).N1 = N1;
        runs(runno).F1 = F1;
        runs(runno).theta_c = theta_c;
        runs(runno).last_bound_center = last_bound_center;
        runs(runno).center_final = center_final;
        runs(runno).locs_final = locs_final;
        runs(runno).head_final = head_final;
    end
    
    clear runno    
    summaries_imported=true;
    
end