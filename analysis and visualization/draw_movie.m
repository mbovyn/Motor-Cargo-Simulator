%% draws movie from data created by simulation

%want a white background behind the figure so it blends in with slide
set(0,'defaultfigurecolor','w')

%% import parameters and data

%take in parameters from the files read by the simulation
%only take it in if we haven't done it already
if ~exist('N','var')
    disp('Importing Parameters')
    %2 entry parameters
    run([analysispath '/import_params2.m'])
    %1 entry parameters
    run([analysispath '/import_params.m'])
    %MT params
    run([analysispath '/import_MT_params.m'])
end

%take in the summary the simulation writes if we haven't yet
if ~exist('exit_cond','var')

    disp('Importing Summary')

    run([analysispath '/import_summary.m'])

    if disp_theta_c==0
        theta_c=NaN;
    else
        theta_c=theta_c(1);
    end
end



%take in the location data written by the simulation
%only if it hasn't already been read in
if ~exist('loc_rec','var')

    run([analysispath '/import_locs.m'])

    %take in data on locations of heads if the file exists (sometimes we
    %need not write one)
    if exist([localpath '/' run_name '_Heads.txt'],'file')
        run([analysispath '/import_head.m'])
    else
        disp('No file to read heads from')
    end

end



%take in the force data written by the simulation
%only if we're going to use it and it hasn't already been read in
if draw_forces==true && ~exist('Fext','var')
    disp('Importing Forces')
    run([analysispath '/import_forces.m'])
end

%take in the data on the orientation change of the cargo
if ~exist('omega','var') && exist([localpath '/' run_name '_Omega.txt'],'file')

    disp('Importing Omega - Cargo Rotation')
    import_omega

    %can't simply add euler vectors to get cumulative rotation
    %need to convert them to rotation matricies, multiply them, then
    %convert back

    %first turn omega vector into normalized vector + magnitude (Euler
    %Vector)
    omega_mag=sqrt(sum(omega.*omega,2));
    EV=[omega(:,1)./omega_mag,omega(:,2)./omega_mag,omega(:,3)./omega_mag,omega_mag*180/pi];
    EV(isnan(EV))=0;
    %note first value written is 0 vector, so can't be normalized and ends
    %up NaNs

    %use function from matlab file exchange to convert to rotation
    %matricies
    rotmats=SpinCalc('EVtoDCM',EV,eps,0);
    %create a cumulative rotation matrix with 1 less entry (to exclude NaNs
    %from first omega)
    cumrotmats=zeros(size(rotmats)-[0,0,1]);
    %set first value to first real rotation
    cumrotmats(:,:,1)=rotmats(:,:,2);
    %do cumulative matrix product
    for i=2:size(cumrotmats,3)
        cumrotmats(:,:,i)=cumrotmats(:,:,i-1)*rotmats(:,:,i+1);
    end
    %find Cumulative Euler Vectors
    cumeuler=SpinCalc('DCMtoEV',cumrotmats,eps,0);

    %also tried to do this with quaternians, didn't work for some reason

%     quaternians=SpinCalc('EVtoQ',EV,eps,1);
%
%     cumquatprod=zeros(size(quaternians));
%     cumquatprod(1,:)=quaternians(1,:);
%     cumquatprod(2,:)=quaternians(2,:);
%     for i=3:size(quaternians,1)
%         cumquatprod(i,:)=quatmultiply(cumquatprod(i-1,:),quaternians(i,:));
%     end
%     cumeuler=SpinCalc('QtoEV',cumquatprod,eps,1);

end

%% set plot bounds

max_length=max(R_motor);

switch plot_box

    case 1 %cargo set at 0 and not moving

        xends=[-(R(1)+max_length) R(1)+max_length];
        yends=[-(R(1)+max_length) R(1)+max_length];
        zends=[-(R(1)+max_length+.02) R(1)+max_length];

    case 2 %outside of all points to be drawn

        xends=[min(center(:,1))-R(1)-max_length max(center(:,1))+R(1)+max_length];
        yends=[min(center(:,2))-R(1)-max_length max(center(:,2))+R(1)+max_length];
        zends=[min(center(:,3))-R(1)-max_length max(center(:,3))+R(1)+max_length];

    case 3 %tighter bounds than 2, motor circles may be cut off

        xends=[min(center(:,1))-R(1) max(center(:,1))+R(1)];
        yends=[min(center(:,2))-R(1) max(center(:,2))+R(1)];
        zends=[min(center(:,3))-R(1) max(center(:,3))+R(1)];

    case 4 % cargo centered

%         xends=[-(R+max_length) R+max_length];
%         yends=[-(R+max_length) R+max_length];
%         zends=[-(R+max_length+.02) R+max_length+.02];

    case 5 % only set y and z ends, leave x to be set in calling script

        yends=[min(center(:,2))-R(1) max(center(:,2))+R(1)];
        zends=[min(center(:,3))-R(1) max(center(:,3))+R(1)];

    case 6 %only follow in x

        yends=[min(center(:,2))-R(1) max(center(:,2))+R(1)];
        zends=[min(center(:,3))-R(1) max(center(:,3))+R(1)];

    otherwise

        error('Unusable key for plot bounds specified in plot_box')

end



% xends=[-(R+max_length) locs_final{1}{1}(1)+.2];
% zends=[-(R+max_length) R+max_length];

%xends=[-.15 .5];
% yends=[-.15 .15];
% zends=[-(R+max_length+z_MT_offset+.005) -(R+max_length+z_MT_offset+.005)+.3];


%% --------------------------------------------------------------------------
%calculate what we need from what was read in
%--------------------------------------------------------------------------

create_attach_rec

%% ------------------------------------------------------------------------
%plot
%--------------------------------------------------------------------------

%create a figure which we'll update


%if we want to save the MPEG
if SaveMPEG~=false

    fig=figure('Position', [150, 150, 700, 700]);

    M(frames)=struct('cdata',[],'colormap',[]);

    vidObj = VideoWriter([localpath '/' SaveMPEG],'MPEG-4');
    vidObj.FrameRate=12;
    vidObj.Quality=75;

    open(vidObj);

else

    fig=figure('Position', [150, 150, 700, 700]);

end

if ~exist('tan_scaling','var')

    %prepare to draw forces
    %scale forces on cargo to cargo radius
    %and forces on anchor to motor length
    if draw_forces==true

        disp('Creating force scaling')

        mags_ext=sqrt(sum(Fext.*Fext,2));
        ext_scaling=R(1)/max(mags_ext);

        mags_steric=sqrt(sum(Fsteric.*Fsteric,2));
        steric_scaling=R(1)/max(mags_steric);

        mags_tan=zeros(size(Ftangential{1}{1},1),N(1)+N(2));
        mags_rad=zeros(size(Fradial{1}{1},1),N(1)+N(2));

        for m=1:2
            for n=1:N(m)
                mags_tan(:,(m-1)*N(1)+n)=sqrt(sum(Ftangential{m}{n}.*Ftangential{m}{n},2));
                mags_rad(:,(m-1)*N(1)+n)=sqrt(sum(Fradial{m}{n}.*Fradial{m}{n},2));
            end
        end

        mags_tan=mags_tan(:);
        mags_rad=mags_rad(:);

        tan_scaling=R(1)/max(mags_tan);
        rad_scaling=R(1)/max(mags_rad);

        cargo_scaling=min([ext_scaling,steric_scaling,rad_scaling]);

        clear mags_ext mags_steric mags_tan mags_rad ...
            ext_scaling steric_scaling rad_scaling
    end

end

if isnan(skip_frames)
    skip_frames=ceil((size(loc_rec,2))/frames);
end

%find the final frame to draw from the given inputs
final_frame=min([start_frame+frames*skip_frames size(center,1)]);

if start_frame+frames*skip_frames > size(center,1)
    loop_ts=[start_frame:skip_frames:final_frame length(t_arr)];
else
    loop_ts=start_frame:skip_frames:final_frame;
end

%% loop over each frame we want to draw
for t=loop_ts
    %% plot vesicle

    if exist('makeFig','var')
        h = draw_cargo(center(t,1),center(t,2),center(t,3),R(1),n_cargo_surf,'Color','w','Alpha',1);

        h.FaceLighting = 'gouraud';
        h.AmbientStrength = 0.3;
        h.DiffuseStrength = 0.8;
        h.SpecularStrength = 0.3;
        h.SpecularExponent = 25;
        h.BackFaceLighting = 'unlit';

    else

        h = draw_cargo(center(t,1),center(t,2),center(t,3),R(1),n_cargo_surf,'Alpha',1);

    end

    if exist('omega','var')
        if(t>1)
            rotate(h,[cumeuler(t-1,1) cumeuler(t-1,2) cumeuler(t-1,3)],cumeuler(t-1,4),[center(t,1),center(t,2),center(t,3)])
        end
    end

    %% initial axis properites
    hold on

    %% motor anchors and heads
    for m=1:2

        %access location information from this time step
        loc=loc_rec{m,t};
        loc_head=head_rec{m,t};
        att=attach_rec{m,t};

        if draw_detail==true
            stretch=stretch_rec{m,t};
        end

        %plot a sphere for each motor
        for n=1:N(m)

            [ h_motor,h_head,h_stalk ] = draw_motor( ...
                m,att(n),R_motor(m),loc(n,:),loc_head(n,:)...
                );

            if exist('makeFig','var')

                if ~att(n)
                    set(h_motor,'FaceColor',[0 .6 0]);
                    set(h_motor,'FaceAlpha',.8)
                    set(h_motor,'EdgeAlpha',0)

                    h_motor.FaceLighting = 'gouraud';
                    h_motor.AmbientStrength = 0.5;
                    h_motor.DiffuseStrength = 0.8;
                    h_motor.SpecularStrength = 0.3;
                    h_motor.SpecularExponent = 25;
                    h_motor.BackFaceLighting = 'unlit';
                else

                    set(h_motor,'EdgeColor','none');
                    %set(h_motor,'EdgeAlpha',1);
                    if bound{m}(t,n)==1
                        set(h_motor,'FaceColor','c');
                    elseif bound{m}(t,n)==2
                        set(h_motor,'FaceColor','m');
                    else
                        error('motor Not bound to 1 or 2')
                    end

                    set(h_head,'EdgeColor','none');
                    if bound{m}(t,n)==1
                        set(h_head,'FaceColor','c');
                    elseif bound{m}(t,n)==2
                        set(h_head,'FaceColor','m');
                    else
                        error('Head Not bound to 1 or 2')
                    end

                    set(h_stalk,'LineWidth',2);
                    if bound{m}(t,n)==1
                        set(h_stalk,'Color','c');
                    elseif bound{m}(t,n)==2
                        set(h_stalk,'Color','m');
                    else
                        error('Neck Not bound to 1 or 2')
                    end

                    h_motor.FaceLighting = 'gouraud';
                    h_motor.AmbientStrength = 0.5;
                    h_motor.DiffuseStrength = 0.8;
                    h_motor.SpecularStrength = 0.3;
                    h_motor.SpecularExponent = 25;
                    h_motor.BackFaceLighting = 'unlit';

                    h_head.FaceLighting = 'gouraud';
                    h_head.AmbientStrength = 0.5;
                    h_head.DiffuseStrength = 0.8;
                    h_head.SpecularStrength = 0.3;
                    h_head.SpecularExponent = 25;
                    h_head.BackFaceLighting = 'unlit';
                end
            end

            if Diagnostics>1
                text(loc(n,1),...
                    loc(n,2),...
                    loc(n,3)+1.1*R_motor(m),sprintf('%d\n',n)...
                    ,'FontWeight','bold'...
                    ,'HorizontalAlignment','center');
            end

            if draw_forces==true

                %for the radial force on the anchor
                f=Ftangential{m}{n}(t,:)*tan_scaling;
                plot3([loc(n,1),loc(n,1)+f(1)],...
                    [loc(n,2),loc(n,2)+f(2)],...
                    [loc(n,3),loc(n,3)+f(3)],'linewidth',3)

                ct=center(t,:);

                %for tangential force
                f=Fradial{m}{n}(t,:)*cargo_scaling;
                plot3([ct(1) ct(1)+f(1)],...
                    [ct(2) ct(2)+f(2)],...
                    [ct(3) ct(3)+f(3)],...
                    'm','LineWidth',6)

            end
        end
    end

    %% if have force vectors, plot out the forces acting on the cargo
    if draw_forces==true

        ct=center(t,:);

        %for external force
        f=Fext(t,:)*cargo_scaling;
        plot3([ct(1) ct(1)+f(1)],...
            [ct(2) ct(2)+f(2)],...
            [ct(3) ct(3)+f(3)],...
            'k','LineWidth',6)

        %for the steric force from the MT
        f=Fsteric(t,:)*cargo_scaling;
        plot3([ct(1) ct(1)+f(1)],...
            [ct(2) ct(2)+f(2)],...
            [ct(3) ct(3)+f(3)],...
            'g','LineWidth',6)

    end

    %% extra display items

    %plot a ring to indicate the location of the critical angle
    %for visualizing mean first passage time test
    if ~isnan(theta_c)
        %plot a circle on the sphere where theta_c is
        circle_center=[center(t,1) center(t,2) center(t,3)+R*sin(theta_c)];
        plotCircle3D(circle_center,[0 0 1],R*cos(theta_c))
    end

    %     if p.Results.Diagnostics==true
    % %     if ~isempty(cargo_loc) && t>start_frame
    % %         if cargo_v(t)>0
    % %             status='Kinesin (blue) winning, moving (+)';
    % %         elseif cargo_v(t)<0
    % %             status='Dynein (red) winning, moving (-)';
    % %         else
    % %             status='Not moving';
    % %         end
    % %
    % %         text(0,0,.7,status,'HorizontalAlignment','center')
    % %     end
    %     end

    %% plot labels

    if Diagnostics>1
        title(sprintf([titlestring '\n Frame ' sprintf('%d',t) ', t=' sprintf('%0.5f',t_arr(t))]))
    elseif Diagnostics>0
        %display current frame
        %text(.4,-.4,.4,['Frame ' num2str(t)])
        %display current simulation time
        %text(-.4,.4,.4,['t=' num2str(t_arr(t))])

        title(sprintf([titlestring '\n t=' sprintf('%0.3f',t_arr(t)) ' s']))
    else
        title(titlestring)
    end

    xlabel('x (\mum)')
    ylabel('y (\mum)')
    zlabel('z (\mum)')


    %% axis and view properties

    if t==start_frame && exist('init_view','var')
        view(init_view(1),init_view(2));
    end

%     if ~isnan(theta_c)
%         %set view angle
%         view(0,0)
%     end

    if t>start_frame
        view(az,el)
    end

    axis equal
    set(gca,'color',[.95 .95 .95])

    if plot_box==4

        xends=[center(t,1)-(R(1)+max_length) center(t,1)+R(1)+max_length];
        yends=[center(t,2)-(R(1)+max_length) center(t,2)+R(1)+max_length];
        zends=[center(t,3)-(R(1)+max_length+.02) center(t,3)+R(1)+max_length+.02];

    elseif plot_box==6

        %thing1=[ max([t-50 1]) min([t+50 length(ts)]) ]
        xends=[mean(center(max([t-50 1]):min([t+50 length(t_arr)]),1))-(R(1)+max_length) ...
            mean(center(max([t-50 1]):min([t+50 length(t_arr)]),1))+R(1)+max_length];

        %xends

    end

    axis([xends(1) xends(2) yends(1) yends(2) zends(1) zends(2)]);

        %% MTs


    if exist('makeFig','var')

        [ h_cyl,h_cap1,h_cap2 ] = draw_MT( xends,yends,zends,...
            MTpt{1},MTvec{1},R_MT(1),...
            'Color',[0 0 .6],'FaceAlpha',1,'EdgeAlpha',0,'EndLabelsOff');
        [ h_cyl,h_cap1,h_cap2 ] = draw_MT( xends,yends,zends,...
            MTpt{2},MTvec{2},R_MT(2),...
            'Color',[.6 0 0],'FaceAlpha',1,'EdgeAlpha',0,'EndLabelsOff');
    else

            for i=1:n_MTs
                [ h_cyl,h_cap1,h_cap2 ] = draw_MT( ...
                    xends,yends,zends,MTpt{i},MTvec{i},R_MT(i) );
            end
    end

    if exist('draw_sep_dist_line','var')

        plot3([MTpt{1}(1) MTpt{2}(1)],...
            [MTpt{1}(2) MTpt{2}(2)],...
            [MTpt{1}(3) MTpt{2}(3)],'k-.','LineWidth',2)

    end

    %% lighting
    if exist('makeFig','var')
        if exist('lights','var')
            lightangle(lights(1),lights(2))
        else
            lightangle(120,30)
        end
    end

    %% draw and save, prepare for next frame

    drawnow

    [az,el]=view;

    if SaveMPEG~=false

        M(t)=getframe(fig);

        writeVideo(vidObj,M(t));

    end

    hold off

end


% close the video file
if SaveMPEG~=false
    close(vidObj);
end