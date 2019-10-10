function struct_out = transform_vars(struct_in,repeat)
%transform_vars Chooses a structure based on the dimensions of the
%data.

if sum(size(unique(repeat))~=size(repeat))
    
    fields=fieldnames(struct_in);
    for i=1:length(fields)
        if iscell(struct_in.(fields{i}))
            for j=1:length(struct_in.(fields{i}))
                struct_in.(fields{i}){j}=transform_var(struct_in.(fields{i}){j},repeat);
            end
        else
            struct_in.(fields{i})=transform_var(struct_in.(fields{i}),repeat);
        end
    end
    
end

struct_out=struct_in;

end

function out=transform_var(var,repeat)

    numts=zeros(1,max(repeat));

    for i=1:max(repeat)
        numts(i)=numel(find(repeat==i));
    end


    if max(numts)-min(numts)==0

        %if repeats have equal numbers of timesteps, output in 3D array
        out=reshape(var,[],size(var,2),max(repeat));

    else

        %output in a cell array
        out=cell(max(repeat),1);

        for i=1:max(repeat)

            temp=var(repmat(repeat==i,1,size(var,2)));
            out{i}=reshape(temp,[],size(var,2));

        end

    end

end