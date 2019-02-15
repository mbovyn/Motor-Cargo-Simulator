function h=plotCircle3D(center,normal,radius)

% source: https://www.mathworks.com/matlabcentral/fileexchange/26588-plot-circle-in-3d
% edited by Matt Bovyn

theta=0:0.01:2*pi;
v=null(normal);
points=repmat(center',1,size(theta,2))+radius*(v(:,1)*cos(theta)+v(:,2)*sin(theta));
h=plot3(points(1,:),points(2,:),points(3,:),'r-','LineWidth',2);

end