function [ h ] = draw_cargo( center_x,center_y,center_z,R,n_points,varargin )
%UNTITLED3 Summary of this function goes here
%   Detailed explanation goes here

%plot vesicle
[xp,yp,zp]=ellipsoid(center_x,center_y,center_z,R,R,R,n_points);
h=surf(xp,yp,zp,'edgealpha',.5);

if any(strcmp('Color',varargin))
    set(h,'FaceColor',varargin{find(strcmp('Color',varargin))+1});
else
    set(h,'FaceColor','y');
end

if any(strcmp('Alpha',varargin))
    set(h,'FaceAlpha',varargin{find(strcmp('Alpha',varargin))+1});
else
    set(h,'FaceAlpha',.4);
end

end

