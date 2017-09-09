%% Import data from text file.
% Script for importing data from the following text file:
%
%    /Users/Matt/Google Drive/project_data/Motor_Freedom_data/numerical_tests/anchor_drag.0_Summary.txt
%
% To extend the code to different selected data or a different text file,
% generate a function instead of a script.

% Auto-generated by MATLAB on 2016/10/21 10:54:06

%% Initialize variables.
filename = [localpath '/' run_name '_Summary.txt'];

if ~exist(filename,'file')
    error([filename ' doesnt exist!'])
end
delimiter = ' ';
startRow = 2;

%% Format for each line of text:
%   column1: double (%f)
%	column2: double (%f)
%   column3: double (%f)
%	column4: double (%f)
%   column5: double (%f)
%	column6: double (%f)
%   column7: double (%f)
%	column8: double (%f)
%   column9: double (%f)
%	column10: double (%f)
%   column11: double (%f)
%	column12: double (%f)
% For more information, see the TEXTSCAN documentation.
%formatSpec = '%f%f%f%f%f%f%f%f%f%f%f%f%f%f%f%f%[^\n\r]';

num=20;

%piece1=repmat('%f',1,num+3+2*3*(N(1)+N(2)));
piece1=repmat('%f',1,num);
piece2='%[^\n\r]';

formatSpec=strcat(piece1,piece2);

%% Open the text file.
fileID = fopen(filename,'r');

%% Read columns of data according to the format.
% This call is based on the structure of the file used to generate this
% code. If an error occurs for a different file, try regenerating the code
% from the Import Tool.
dataArray2 = textscan(fileID, formatSpec, 'Delimiter', delimiter, 'MultipleDelimsAsOne', true, 'HeaderLines' ,startRow-1, 'ReturnOnError', false, 'EndOfLine', '\r\n');

N1 = dataArray2{:,11};

fclose(fileID);

fileID = fopen(filename,'r');

piece1=repmat('%f',1,num+3+2*3*(N1(1)+N(2))+(N1(1)+N(2)));
piece2='%[^\n\r]';

formatSpec=strcat(piece1,piece2);

%% second time

dataArray = textscan(fileID, formatSpec, 'Delimiter', delimiter, 'MultipleDelimsAsOne', true, 'HeaderLines' ,startRow-1, 'ReturnOnError', false, 'EndOfLine', '\r\n');

%% Close the text file.
fclose(fileID);

%% Allocate imported array to column variable names

% for importi=1:num
%     dataArray{:,importi}=dataArray{:,importi}(~isnan(dataArray{:,importi}));
% end

repeat = dataArray{:,1};
step = dataArray{:, 2};
t_final = dataArray{:, 3};
exit_cond = dataArray{:, 4};
success = dataArray{:,5};
success=logical(success);
D_anchor = dataArray{:, 6};
eps_0 = dataArray{:, 7};
pi_0 = dataArray{:, 8};
offset = dataArray{:, 9};
R = dataArray{:,10};
N1 = dataArray{:,11};
F1 = dataArray{:,12};
theta_c = dataArray{:,13};

MTvec{2}=[dataArray{:,14} dataArray{:,15} dataArray{:,16}];

ToW_time = dataArray{:,17};

last_bound_center = [dataArray{:, num-2} dataArray{:, num-1} dataArray{:, num}];

center_final = [dataArray{:, num+1} dataArray{:, num+2} dataArray{:, num+3}];
% type0motor0_x = dataArray{:, 10};
% type0motor0_y = dataArray{:, 11};
% type0motor0_z = dataArray{:, 12};

N(1)=N1(1);

locs_final=cell(2,1);
locs_final{1}=cell(N(1),1);
locs_final{2}=cell(N(2),2);

for m=1:2
    for n=1:N(m)
        if m==1
            column=num+4+(n-1)*3;
        else
            column=num+4+N(1)*3+(n-1)*3;
        end
        locs_final{m}{n}=[dataArray{:,column:column+2}];
    end
end

last_locs_col=num+4+3*(N(1)+N(2))-1;

head_final=cell(2,1);
head_final{1}=cell(N(1),1);
head_final{2}=cell(N(2),2);

for m=1:2
    for n=1:N(m)
        if m==1
            column=last_locs_col+1+(n-1)*3;
        else
            column=last_locs_col+1+N(1)*3+(n-1)*3;
        end
        head_final{m}{n}=[dataArray{:,column:column+2}];
    end
end

last_head_col=num+4+3*(N(1)+N(2))-1+ 3*(N(1)+N(2));

bound_final=cell(2,1);
bound_final{1}=cell(N(1),1);
bound_final{2}=cell(N(2),2);

for m=1:2
    for n=1:N(m)
        if m==1
            column=last_head_col+1+(n-1);
        else
            column=last_head_col+1+N(1)+(n-1);
        end
        bound_final{m}{n}=[dataArray{:,column}];
    end
end


%% Clear temporary variables
clearvars filename delimiter startRow formatSpec fileID dataArray ans num importi;