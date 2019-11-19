%bring in parameters and outputs for multiple runs

%take in the summary the simulation writes if we haven't yet
if exist('params','var')
    warning('Some data is alreday loaded, skipping load. ''clear'' to force load')
    return
end

[params,summary,locs,heads,forces,omega]=import_all_all(run_name,nruns,localpath);

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



%get parameters over several conditions, each with multiple runs
function [params,summary,locs,heads,forces,omega]=import_all_all(run_name,nruns,localpath)

    %determine if numbers of runs are the same between conditions
    differentsizes=0;
    for j=1:length(nruns)-1
        if ~isequal(nruns{j},nruns{j+1})
            differentsizes=1;
        end
    end

    %if only have one parameter sweeps (nruns is nx1 or 1xn) and number
    %of runs is the same between conditions, use simplified form
    %ex. params(runs,condition)
    if (sum([nruns{:}]==1)==length([nruns{:}])/2) && ~differentsizes

        for i=length(localpath):-1:1
            [params(:,i),summary(:,i),locs(:,i),heads(:,i),forces(:,i),omega(:,i)]= ...
                import_all(run_name{i},nruns{i},localpath{i});
        end

    %otherwise stack conditions in third dimension
    %(nruns is nxm or have different numbers of runs between conditions)
    %ex. params(runs(1),runs(2),condition)
    else

        %check that structure will be created with a large enough size in
        %each dimension to hold all conditions
        %right now this will happen if the larger one is input first
        %(checked by if statement)
        %Don't know how to handle mismatched sizes (ex. 6x4 and 7x3),
        %these currently break this
        [~,inds]=max(cell2mat(nruns'));
        if length(nruns)>1 && ~isequal(inds,[1,1])
            error(['Please order conditions with highest number of runs first', newline,...
                'This code needs to be rewritten for mismatched numbers of runs (ex. 6x4 and 7x5)'] );
        end

        for i=length(localpath):-1:1

            [params(1:nruns{i}(1),1:nruns{i}(2),i),...
            summary(1:nruns{i}(1),1:nruns{i}(2),i),...
            locs(1:nruns{i}(1),1:nruns{i}(2),i),...
            heads(1:nruns{i}(1),1:nruns{i}(2),i),...
            forces(1:nruns{i}(1),1:nruns{i}(2),i),...
            omega(1:nruns{i}(1),1:nruns{i}(2),i)]= ...
                import_all(run_name{i},nruns{i},localpath{i});

        end

    end

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
            [summary(runno1,runno2),status]=import_summary(params(runno1,runno2),localpath,run_name);
            if status>0
                disp(['in ' run_name])
            end

            %import locs
            if exist([localpath '/' run_name '_Center_and_Anchors.txt'],'file')
                locs(runno1,runno2)=import_locs(params(runno1,runno2),localpath,run_name);
            else
                locs(runno1,runno2)=struct('step',[],'t_arr',[],'center',[],'loc_rec',[]);
            end

            %import heads
            if exist([localpath '/' run_name '_Heads.txt'],'file')
                heads(runno1,runno2)=import_head(params(runno1,runno2),localpath,run_name);
            else
                heads(runno1,runno2)=struct('step',[],'t_arr',[],'bound',[],'head_rec',[]);
            end

            %import forces
            if exist([localpath '/' run_name '_Forces.txt'],'file')
                forces(runno1,runno2)=import_forces(params(runno1,runno2),localpath,run_name);
            else
                forces(runno1,runno2)=struct('step',[],'t_arr',[],...
                    'Fext',[],'Fsteric',[],'Fmag',[],'Fcart',[],'Fradial',[],'Ftangential',[]);
            end

            %import omega
            if exist([localpath '/' run_name '_Omega.txt'],'file')
                omega(runno1,runno2)=import_omega(localpath,run_name);
            else
                omega(runno1,runno2)=struct('step',[],'t_arr',[],'vector',[]);
            end


        end
    end

end
