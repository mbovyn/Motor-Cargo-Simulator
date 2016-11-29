if ~exist('N','var')
    %2 entry parameters
    run([analysispath '/import_params2.m'])
    %1 entry parameters
    run([analysispath '/import_params.m'])
    %MT params
    run([analysispath '/import_MT_params.m'])
end

%take in the summary the simulation writes if we haven't yet
if ~exist('exit_cond','var')
    run([analysispath '/import_summary.m'])
end