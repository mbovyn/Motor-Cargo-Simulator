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

        run([analysispath '/set_summary_vars.m'])
        for varname=summary_vars
            runs(runno).(varname{1})=transpose(eval(varname{1}));
        end
        runs(runno).MTvec=MTvec{2};

    end

    clear runno
    summaries_imported=true;

end
