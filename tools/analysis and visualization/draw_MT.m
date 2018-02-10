function [ h_cyl,h_cap1,h_cap2 ] = draw_MT( xends,yends,zends,MTpt,MTvec,R_MT,varargin )
%draw_MT Draw Microtubule for movie
%   Detailed explanation goes here

    %vector from MTpt to pass each plane defining the cube
    v1=[max(xends) max(yends) max(zends)]-MTpt;
    v2=[min(xends) min(yends) min(zends)]-MTpt;

    %multipliers of MTvec to pass each plane
    n1=v1./MTvec;
    n2=v2./MTvec;

    %MT exits cube when it passes the closest plane
    %find smallest multiplier
    [~,I1]=min(abs(n1));
    [~,I2]=min(abs(n2));

    %end locations are MTvec*smallest multiplier
    end2=MTpt+MTvec.*n1(I1);
    end1=MTpt+MTvec.*n2(I2);

    if any(strcmp('Color',varargin))
        c=varargin{find(strcmp('Color',varargin))+1};
    else
        c='g';
    end

    if any(strcmp('FaceAlpha',varargin))
        fa=varargin{find(strcmp('FaceAlpha',varargin))+1};
    else
        fa=.5;
    end

    if any(strcmp('EdgeAlpha',varargin))
        ea=varargin{find(strcmp('EdgeAlpha',varargin))+1};
    else
        ea=.3;
    end

    [h_cyl,h_cap1,h_cap2]=Cylinder(end1,end2,R_MT,20,c,0,ea,fa);

    if ~any(strcmp('EndLabelsOff',varargin))
        text(end2(1)+.02*MTvec(1),end2(2)+.02*MTvec(2),end2(3)+.02*MTvec(3)...
            ,'(+)','FontWeight','bold'...
            ,'HorizontalAlignment','center','FontSize',16 ...
            ...%,'VerticalAlignment','bottom')
            ,'VerticalAlignment','middle')
        text(end1(1)-.02*MTvec(1),end1(2)-.02*MTvec(2),end1(3)-.02*MTvec(3)...
            ,'(-)','FontWeight','bold'...
            ,'FontSize',16 ...
            ...%,'HorizontalAlignment','right','VerticalAlignment','bottom')
            ,'HorizontalAlignment','center','VerticalAlignment','middle')
    end

end
