
%
if ~exist('ToWs_imported','var')
    
    base_run_name=run_name;
    if(~exist('runs','var'))
        runs=struct;
    end
    
    run_name00=[base_run_name '.' int2str(0) '.' int2str(0)];
    filename00 = [localpath '/' run_name00 '_ToW.txt'];
    run_name01=[base_run_name '.' int2str(0) '.' int2str(1)];
    filename01 = [localpath '/' run_name01 '_ToW.txt'];
    run_name10=[base_run_name '.' int2str(1) '.' int2str(0)];
    filename10 = [localpath '/' run_name10 '_ToW.txt'];
    run_name11=[base_run_name '.' int2str(1) '.' int2str(1)];
    filename11 = [localpath '/' run_name11 '_ToW.txt'];
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
            
            run([analysispath '/import_ToW.m'])
            
            for varname={'ToW_time' , ...
                        'F_ToW0' , ...
                        'F_ToW1' , ...
                        'F2_ToW0' , ...
                        'F2_ToW1', ...
                        'FMT_ToW0' , ...
                        'FMT_ToW1' , ...
                        'F2MT_ToW0', ...
                        'F2MT_ToW1', ...
                        'FH_ToW0' , ...
                        'FH_ToW1' , ...
                        'F2H_ToW0', ...
                        'F2H_ToW1' , ...
                        'Fteam_ToW0' , ...
                        'Fteam_ToW1' , ...
                        'FonMT_ToW00' , ...
                        'FonMT_ToW01' , ...
                        'FonMT_ToW10' , ...
                        'FonMT_ToW11' , ...
                        'FonOT_ToW0' , ...
                        'FonOT_ToW1' , ...
                        'n_ToW0' , ...
                        'n_ToW1' , ...
                        'off_count0' , ...
                        'off_count1' }

                runs(runno1,runno2).(varname{1})=eval(varname{1});
            
            end
            
        end
    end
    
    clear runno1 runno2 varname
    run_name=base_run_name;
    ToWs_imported=true;
    
end