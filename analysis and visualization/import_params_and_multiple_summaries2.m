%this version brings in parameters from 2D sweeps

if ~exist('params_imported','var') && ~exist('param_file_sweep','var')
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

    run_name00=[base_run_name '.' int2str(0) '.' int2str(0)];
    filename00 = [localpath '/' run_name00 '_Summary.txt'];
    run_name01=[base_run_name '.' int2str(0) '.' int2str(1)];
    filename01 = [localpath '/' run_name01 '_Summary.txt'];
    run_name10=[base_run_name '.' int2str(1) '.' int2str(0)];
    filename10 = [localpath '/' run_name10 '_Summary.txt'];
    run_name11=[base_run_name '.' int2str(1) '.' int2str(1)];
    filename11 = [localpath '/' run_name11 '_Summary.txt'];
    if exist(filename00,'file')
        format='00';
    elseif exist(filename01,'file')
        format='01';
    elseif exist(filename10,'file')
        format='10';
    elseif exist(filename11,'file')
        format='11';
    else
        error(['Unable to find file matching any format of ' filename00])
    end

    for runno1=1:nruns(1)

        for runno2=1:nruns(2)

            if strcmp(format,'00')
                run_name=[base_run_name '.' int2str(runno1-1) '.' int2str(runno2-1)];
            elseif strcmp(format,'01')
                run_name=[base_run_name '.' int2str(runno1-1) '.' int2str(runno2)];
            elseif strcmp(format,'10')
                run_name=[base_run_name '.' int2str(runno1) '.' int2str(runno2-1)];
            elseif strcmp(format,'11')
                run_name=[base_run_name '.' int2str(runno1) '.' int2str(runno2)];
            end

            if exist('param_file_sweep','var') && ~exist('params_imported','var')
                run([analysispath '/import_params2.m'])
                run([analysispath '/import_params.m'])
                run([analysispath '/import_MT_params.m'])
            end

            for varname={'N' , ...
                        'F_s' , ...
                        'eps_0' , ...
                        'pi_0' , ...
                        'v_f', ...
                        'R_motor' , ...
                        'step_size' , ...
                        'D_m', ...
                        'R', ...
                        'eta',...
                        'n_MTs',...
                        'R_MT' , ...
                        'MTpt' , ...
                        'MTvec' }

                runs(runno1,runno2).(varname{1})=transpose(eval(varname{1}));

            end

            run([analysispath '/import_summary.m'])

            run([analysispath '/set_summary_vars.m'])
            for varname=summary_vars
                runs(runno1,runno2).(varname{1})=transpose(eval(varname{1}));
            end
            runs(runno1,runno2).MTvec=MTvec{2};

        end
    end

    clear runno1 runno2
    run_name=base_run_name;
    summaries_imported=true;

end
