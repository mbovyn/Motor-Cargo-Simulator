function [ h_motor,h_head,h_stalk ] = draw_motor( m,att,R_motor,loc,loc_head,varargin )
%UNTITLED3 Summary of this function goes here
%   Detailed explanation goes here

%plot motor
[xm,ym,zm]=sphere;
            
if isempty(att) || ~att

    h_motor=surf(...
        xm*R_motor+loc(1),...
        ym*R_motor+loc(2),...
        zm*R_motor+loc(3));

    set(h_motor,'EdgeColor','k');
    
    h_head=[];
    h_stalk=[];

elseif att

    h_motor=surf(...
        xm*.1*R_motor+loc(1),...
        ym*.1*R_motor+loc(2),...
        zm*.1*R_motor+loc(3));

%                 h_head=surf(...
%                     xm*2*R_MT+loc_head(n,1),...
%                     ym*2*R_MT+loc_head(n,2),...
%                     zm*2*R_MT+loc_head(n,3));

    h_head=surf(...
        xm*.02+loc_head(1),...
        ym*.02+loc_head(2),...
        zm*.02+loc_head(3));

    if m==1
        set(h_head,'EdgeColor','b');   
    elseif m==2
        set(h_head,'EdgeColor','r');
    else
       error('Error setting head edge color');
    end

    if m==1
        set(h_head,'FaceColor','b');
    elseif m==2
        set(h_head,'FaceColor','r');
    else
       error('Error setting head face color');
    end

    %plot a line connecting the two
    h_stalk=plot3([loc_head(1) loc(1)],...
    [loc_head(2) loc(2)],...
    [loc_head(3) loc(3)],'m','LineWidth',4);

%     if draw_detail==true
%         if stretch(n)==1
%             set(h_head,'EdgeColor','m');
%         end
%     end

else
     error('Something wrong with attachment status');
end



if m==1
    set(h_motor,'FaceColor','b');
elseif m==2
    set(h_motor,'FaceColor','r');
else
    error('Error setting anchor face color');
end

set(h_motor,'FaceAlpha',.5)
set(h_motor,'EdgeAlpha',.7)
            

% if any(strcmp('Color',varargin))
%     set(h,'FaceColor',varargin{find(strcmp('Color',varargin))+1});
% else
%     set(h,'FaceColor','y');
% end
% 
% if any(strcmp('Alpha',varargin))
%     set(h,'FaceAlpha',varargin{find(strcmp('Alpha',varargin))+1});
% else
%     set(h,'FaceAlpha',.4);
% end

end