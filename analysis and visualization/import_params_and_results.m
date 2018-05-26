%bring in parameters and outputs for multiple runs

%take in the summary the simulation writes if we haven't yet

if exist('params','var')
    return
end

[params,summary,locs,heads,forces,omega]=import_all(run_name,nruns,localpath);


if isempty(fieldnames(locs))
    clearvars locs
end
if isempty(fieldnames(heads))
    clearvars heads
end
if isempty(fieldnames(forces))
    clearvars forces
end
if isempty(fieldnames(omega))
    clearvars omega
end

function [params,summary,locs,heads,forces,omega]=import_all(run_name,nruns,localpath)

    base_run_name=run_name;

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
    
    %structs are dumb, so make the last one first to avoid growing it
    %https://blogs.mathworks.com/loren/2008/02/01/structure-initialization/
    for runno1=nruns(1):-1:1
        for runno2=nruns(2):-1:1

            if strcmp(format,'00')
                run_name=[base_run_name '.' int2str(runno1-1) '.' int2str(runno2-1)];
            elseif strcmp(format,'01')
                run_name=[base_run_name '.' int2str(runno1-1) '.' int2str(runno2)];
            elseif strcmp(format,'10')
                run_name=[base_run_name '.' int2str(runno1) '.' int2str(runno2-1)];
            elseif strcmp(format,'11')
                run_name=[base_run_name '.' int2str(runno1) '.' int2str(runno2)];
            end

            %import parameters
            params(runno1,runno2)=import_params(localpath,run_name);
            params(runno1,runno2)=import_MT_params(params(runno1,runno2),localpath,run_name);

            %import summary
            summary(runno1,runno2)=import_summary(params(runno1,runno2),localpath,run_name);
            
            %import locs
            if exist([localpath '/' run_name '_Center_and_Anchors.txt'],'file')
                locs(runno1,runno2)=import_locs(params(runno1,runno2),localpath,run_name);
            else
                locs(runno1,runno2)=struct;
            end
            
            %import heads
            if exist([localpath '/' run_name '_Heads.txt'],'file')
                heads(runno1,runno2)=import_head(params(runno1,runno2),localpath,run_name);
            else
                heads(runno1,runno2)=struct;
            end
            
            %import forces
            if exist([localpath '/' run_name '_Forces.txt'],'file')
                forces(runno1,runno2)=import_forces(params(runno1,runno2),localpath,run_name);
            else
                forces(runno1,runno2)=struct;
            end
            
            %import omega
            if exist([localpath '/' run_name '_Omega.txt'],'file')
                omega(runno1,runno2)=import_omega(localpath,run_name);
            else
                omega(runno1,runno2)=struct;
            end


        end
    end

end
