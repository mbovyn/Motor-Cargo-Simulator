function [ h ] = draw_cargo( center_x,center_y,center_z,R,n_points )
%UNTITLED3 Summary of this function goes here
%   Detailed explanation goes here

%plot vesicle
[xp,yp,zp]=ellipsoid(center_x,center_y,center_z,R,R,R,n_points);
h=surf(xp,yp,zp,'edgealpha',.3);
alpha(.2)
set(h,'FaceColor','y');

end

