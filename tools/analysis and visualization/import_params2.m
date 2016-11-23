%% Import data from text file.
% Script for importing data from the following text file:
%
%    /Users/Matt/Google Drive/Allard Lab/Motor Freedom Project/src/params3.txt
%
% To extend the code to different selected data or a different text file,
% generate a function instead of a script.

% Auto-generated by MATLAB on 2016/05/04 16:35:47

%% Initialize variables.
filename = [results_prefix '_params.txt'];
delimiter = ' ';
startRow = [11,13,15,16,17,23,25,27];
endRow = [11,13,15,16,17,23,25,27];

%% Format string for each line of text:
%   column2: double (%f)
%	column3: double (%f)
% For more information, see the TEXTSCAN documentation.
formatSpec = '%*s%f%f%*s%*s%*s%*s%*s%*s%*s%*s%*s%*s%*s%*s%[^\n\r]';

%% Open the text file.
fileID = fopen(filename,'r');

%% Read columns of data according to format string.
% This call is based on the structure of the file used to generate this
% code. If an error occurs for a different file, try regenerating the code
% from the Import Tool.
textscan(fileID, '%[^\n\r]', startRow(1)-1, 'WhiteSpace', '', 'ReturnOnError', false);
dataArray = textscan(fileID, formatSpec, endRow(1)-startRow(1)+1, 'Delimiter', delimiter, 'MultipleDelimsAsOne', true, 'ReturnOnError', false);
for block=2:length(startRow)
    frewind(fileID);
    textscan(fileID, '%[^\n\r]', startRow(block)-1, 'WhiteSpace', '', 'ReturnOnError', false);
    dataArrayBlock = textscan(fileID, formatSpec, endRow(block)-startRow(block)+1, 'Delimiter', delimiter, 'MultipleDelimsAsOne', true, 'ReturnOnError', false);
    for col=1:length(dataArray)
        dataArray{col} = [dataArray{col};dataArrayBlock{col}];
    end
end

%% Close the text file.
fclose(fileID);

%% Post processing for unimportable data.
% No unimportable data rules were applied during the import, so no post
% processing code is included. To generate code which works for
% unimportable data, select unimportable cells in a file and regenerate the
% script.

%% Allocate imported array to column variable names
raw_mat = [dataArray{1:end-1}];

N=raw_mat(1,:);
F_s=raw_mat(2,:);
eps_0=raw_mat(3,:);
pi_0=raw_mat(4,:);
v_f=raw_mat(5,:);
R_motor=raw_mat(6,:);
step_size=raw_mat(7,:);
D_m=raw_mat(8,:);

%% Clear temporary variables
clearvars raw_mat filename delimiter startRow endRow formatSpec fileID block dataArrayBlock col dataArray ans;