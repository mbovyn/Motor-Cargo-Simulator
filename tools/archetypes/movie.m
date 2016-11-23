% Wrapper for the draw_movie script which creates a movie of the
% simulation output

%% file juggling

%set the name of the run here
run_name='demo';
%create prefix name with directory
results_prefix=[pwd '/' run_name];

%analysis file path
analysispath='/Users/Matt/project_code/Motor_Freedom/tools/analysis and visualization';

%% Movie setup

%what frames to display
start_frame=1;
frames=300; %number of skip_frames to go, not actual number of frames
skip_frames=800;

%whether or not to save a movie
SaveMPEG=false;
%SaveMPEG='demo_skip500';

%% frame setup

%whether or not to draw force vectors
draw_forces=false;
%whether or not to color code headss and necks
draw_detail=false;

%level of details to display
Diagnostics=1;

%title to display
titlestring=sprintf('Demonstration of Full Simulation, Fast Forward');

%number of points to draw on the surface of the cargo
n_cargo_surf=20;

%initial view angle
%init_view=[0 90];

%whether or not to draw the target circle for MFP visualizations
%set to NaN for don't draw
theta_c=NaN;

%option for choosing what the bounds of the plot are
%{
1: cargo set at 0 and not moving
2: outside of all points to be drawn
3: tighter bounds than 2, motor circles may be cut off
%}
plot_box=1;

%% create the movie

run([analysispath '/draw_movie.m'])