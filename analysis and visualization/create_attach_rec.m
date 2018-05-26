if ~exist('attach_rec','var')
    
    disp('Creating attach_rec')

    if ~exist('head_rec','var')
        head_rec=cell(size(locs.loc_rec));
    end

    %attached status (head loc = NAN if not attached)
    attach_rec=cell(size(head_rec));
    for i=1:size(head_rec,2)
        if ~isempty(head_rec{1,i})
            attach_rec{1,i}=~isnan(head_rec{1,i}(:,1));
        else
            %attach_rec{2,i}=false;
        end

        if ~isempty(head_rec{2,i})
            attach_rec{2,i}=~isnan(head_rec{2,i}(:,1));
        else
            %attach_rec{2,i}=false;
        end
    end
    
end