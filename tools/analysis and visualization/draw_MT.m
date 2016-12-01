function [ h_cyl,h_cap1,h_cap2 ] = draw_MT( xends,yends,zends,MTpt,MTvec,R_MT )
%UNTITLED4 Summary of this function goes here
%   Detailed explanation goes here
        
    n1(1)=(xends(1)-MTpt(1))/MTvec(1);
    n2(1)=(xends(2)-MTpt(1))/MTvec(1);
    n1(2)=(yends(1)-MTpt(2))/MTvec(2);
    n2(2)=(yends(2)-MTpt(2))/MTvec(2);
    n1(3)=(zends(1)-MTpt(3))/MTvec(3);
    n2(3)=(zends(2)-MTpt(3))/MTvec(3);

    end1=MTpt-MTvec.*min(abs(n1));
    end2=MTpt+MTvec.*min(abs(n2));

    [h_cyl,h_cap1,h_cap2]=Cylinder(end1,end2,R_MT,20,'g',0,.3);

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
