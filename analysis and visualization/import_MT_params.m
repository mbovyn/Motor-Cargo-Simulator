function params=import_MT_params(params,localpath,run_name)
%% Import data from text file.
% Script for importing data from the following text file:
%
%    /Users/Matt/Google Drive/project_data/Motor_Freedom_data/multiMT_test/test_MT_params.txt
%
% To extend the code to different selected data or a different text file,
% generate a function instead of a script.

% Auto-generated by MATLAB on 2016/11/22 17:30:43

%% Initialize variables.
if exist('param_name','var')
    filename = [localpath '/' param_name '_MT_params.txt'];
else
    filename = [localpath '/' run_name '_MT_params.txt'];
end
delimiter = {' ','(',')'};
startRow = 5;

%% Read columns of data as text:
% For more information, see the TEXTSCAN documentation.
formatSpec = '%s%s%s%s%s%s%s%[^\n\r]';

%% Open the text file.
fileID = fopen(filename,'r');

%% Read columns of data according to the format.
% This call is based on the structure of the file used to generate this
% code. If an error occurs for a different file, try regenerating the code
% from the Import Tool.
textscan(fileID, '%[^\n\r]', startRow-1, 'WhiteSpace', '', 'ReturnOnError', false, 'EndOfLine', '\r\n');
dataArray = textscan(fileID, formatSpec, 'Delimiter', delimiter, 'MultipleDelimsAsOne', true, 'ReturnOnError', false);

%% Close the text file.
fclose(fileID);

%% Convert the contents of columns containing numeric text to numbers.
% Replace non-numeric text with NaN.
raw = repmat({''},length(dataArray{1}),length(dataArray)-1);
for col=1:length(dataArray)-1
    raw(1:length(dataArray{col}),col) = dataArray{col};
end
numericData = NaN(size(dataArray{1},1),size(dataArray,2));

for col=[1,2,3,4,5,6,7]
    % Converts text in the input cell array to numbers. Replaced non-numeric
    % text with NaN.
    rawData = dataArray{col};
    for row=1:size(rawData, 1);
        % Create a regular expression to detect and remove non-numeric prefixes and
        % suffixes.
        regexstr = '(?<prefix>.*?)(?<numbers>([-]*(\d+[\,]*)+[\.]{0,1}\d*[eEdD]{0,1}[-+]*\d*[i]{0,1})|([-]*(\d+[\,]*)*[\.]{1,1}\d+[eEdD]{0,1}[-+]*\d*[i]{0,1}))(?<suffix>.*)';
        try
            result = regexp(rawData{row}, regexstr, 'names');
            numbers = result.numbers;
            
            % Detected commas in non-thousand locations.
            invalidThousandsSeparator = false;
            if any(numbers==',');
                thousandsRegExp = '^\d+?(\,\d{3})*\.{0,1}\d*$';
                if isempty(regexp(numbers, thousandsRegExp, 'once'));
                    numbers = NaN;
                    invalidThousandsSeparator = true;
                end
            end
            % Convert numeric text to numbers.
            if ~invalidThousandsSeparator;
                numbers = textscan(strrep(numbers, ',', ''), '%f');
                numericData(row, col) = numbers{1};
                raw{row, col} = numbers{1};
            end
        catch me
        end
    end
end


%% Allocate imported array to column variable names

%MTparams=struct;
%MTparams.n_MTs=params.n_MTs;

ptx = cell2mat(raw(:, 1));
pty = cell2mat(raw(:, 2));
ptz = cell2mat(raw(:, 3));
vecx = cell2mat(raw(:, 4));
vecy = cell2mat(raw(:, 5));
vecz = cell2mat(raw(:, 6));
params.R_MT = cell2mat(raw(:, 7));

params.MTpt=zeros(params.n_MTs,3)';
params.MTvec=zeros(params.n_MTs,3)';

for i=1:params.n_MTs
    params.MTpt(:,i)=[ptx(i) pty(i) ptz(i)]';
    params.MTvec(:,i)=[vecx(i) vecy(i) vecz(i)]';
end

%% Clear temporary variables
%clearvars filename delimiter startRow formatSpec fileID dataArray ans raw col numericData rawData row regexstr result numbers invalidThousandsSeparator thousandsRegExp me;
%clearvars ptx pty ptz vecx vecy vecz importi;
end