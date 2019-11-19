// Prototypes

void initiallocations();
void initialbinding();
void initialnucleotide();
//helper helpers
void pickpointsphere();
void findMTdist();
void closestPointOnMT(double x,double y,double z,int MTnum);
void pointToMTdist(double x,double y,double z, int MTnum);
void makeRotationMatrix(double t0,double t1,double t2);
void rotateCargo();


// void pickpointsphere(){
//     //find random points on sphere for each motor according to
//     //http://mathworld.wolfram.com/SpherePointPicking.html
//
//     for(n=0;n<N[m];n++){
//         uu[n]=RAND;
//         vv[n]=RAND;
//     }
//
//     //convert random u's to random azimuths
//     for(n=0;n<N[m];n++)
//         az[n]=2*pi*uu[n];
//
//     //convert random v's to random elevations
//     //need -pi/2 to convert from Wolfram's convention of 0 to pi to
//     //Matlab's of -pi/2 to pi/2
//     for(n=0;n<N[m];n++)
//         el[n]=acos(2*vv[n]-1)-pi/2;
//
//     //generate cartesian coords from spherical ones
//     for(n=0;n<N[m];n++){
//         rcosel[n] = R*cos(el[n]);
//         x[n]=rcosel[n]*cos(az[n]);
//         y[n]=rcosel[n]*sin(az[n]);
//         z[n]=R*sin(el[n]);
//     }
// }


void pickpointsphere(){
    //find random point on the unit sphere
    //http://mathworld.wolfram.com/SpherePointPicking.html
    uu=RAND;
    vv=RAND;

    //convert random u's to random azimuths
    az=2*pi*uu;

    //convert random v's to random elevations
    //need -pi/2 to convert from Wolfram's convention of 0 to pi to
    //Matlab's of -pi/2 to pi/2
    el=acos(2*vv-1)-pi/2;

    //generate cartesian coords from spherical ones
    x=cos(el)*cos(az);
    y=cos(el)*sin(az);
    z=sin(el);
}

void initiallocations(){

    //uses only parameters to generate initial locations
    //sets locs

    if(verboseTF>2){
        printf("Setting initial locations with case %d\n",InitialLocations);
    }
    switch(InitialLocations){

        case 2:

            //set random initial locations, adjust for center of cargo
            for (m=0;m<2;m++){
                for(n=0;n<N[m];n++){
                    pickpointsphere();
                    for(i=0;i<3;i++){
                        if(i==0)
                            initlocs[m][n][i]=x*R+center[i];
                        if(i==1)
                            initlocs[m][n][i]=y*R+center[i];
                        if(i==2)
                            initlocs[m][n][i]=z*R+center[i];
                        }
                }
            }
            break;

        case 3:
            //initial locations set to the top of the sphere
            for (m=0;m<2;m++){
                for(n=0;n<N[m];n++){
                  initlocs[m][n][0]=center[0];
                  initlocs[m][n][1]=center[1];
                  initlocs[m][n][2]=R+center[2];
                }
            }
            break;

        case 4:
            //initial locations set to the bottom of the sphere
            for (m=0;m<2;m++){
                for(n=0;n<N[m];n++){
                    initlocs[m][n][0]=center[0];
                    initlocs[m][n][1]=center[1];
                    initlocs[m][n][2]=-R+center[2];
                }
            }
            break;

        case 5:
            //random initial conditions with cargo rotated so that type0motor0 is on top
            for (m=0;m<2;m++){
                for(n=0;n<N[m];n++){
                    pickpointsphere();
                    initlocs[m][n][0]=x*R+center[0];
                    initlocs[m][n][1]=y*R+center[1];
                    initlocs[m][n][2]=z*R+center[2];
                }
            }

            if(verboseTF>3){
                printf("Before rotation,initial locations are chosen as:\n");
                for (m=0;m<2;m++){
                    for(n=0;n<N[m];n++){
                        printf("    type%dmotor%d: (%g,%g,%g)\n",m,n,initlocs[m][n][0],initlocs[m][n][1],initlocs[m][n][2] );
                    }
                }
            }

            m=0;
            n=0;
            makeRotationMatrix(0,0,1);

            if(verboseTF>3){
                printf("The rotation matrix that was found is:\n");
                printf("    %+E %+E %+E\n        %+E %+E %+E\n        %+E %+E %+E\n",
                    rotmat[0],rotmat[1],rotmat[2],
                    rotmat[3],rotmat[4],rotmat[5],
                    rotmat[6],rotmat[7],rotmat[8]);
            }

            rotateCargo();

            break;

        case 6: //random initial locations, rotated so motor with most close neighbors is on top

            //pick random locations for each of the motors
            for (m=0;m<2;m++){
                for(n=0;n<N[m];n++){
                    pickpointsphere();
                    initlocs[m][n][0]=x*R+center[0];
                    initlocs[m][n][1]=y*R+center[1];
                    initlocs[m][n][2]=z*R+center[2];
                }
            }

            //for each motor (of the first type), find out how many neighbors
            //it has that can also bind
            m=0;
            for(n=0;n<N[m];n++){
                can_also_bind[n]=0;
                //for each other motor, find if the distance is less than the
                //max distance for a motor to also bind
                for(n2=0;n2<N[m];n2++){
                    //make sure it doens't count itself
                    if(n2!=n){
                        if(sqrt(pow(initlocs[m][n][0]-initlocs[m][n2][0],2)
                                +pow(initlocs[m][n][1]-initlocs[m][n2][1],2)
                                +pow(initlocs[m][n][2]-initlocs[m][n2][2],2)) //distance to motor
                            //< 2*R*sqrt((L[m]*(L[m] + 2*R))/pow(L[m] + R,2))     )//geometry calculation 1 in anchor to anchor distance for simultaneous binding.nb
                            < (sqrt(2)*L[m]*R)/sqrt(L[m]*(L[m] + R))     )         //geometry calculation 2 in anchor to anchor distance for simultaneous binding.nb
                        can_also_bind[n]++;
                    }
                }
                //printf("motor %d has %d neighbors that can bind\n",n,can_also_bind[n]);
            }

            //find out which motor has the most neighbors that can also bind
            most_neighbors=0;
            for(n=1;n<N[m];n++){
                if(can_also_bind[n]>can_also_bind[most_neighbors]){
                    most_neighbors=n;
                }
            }

            //printf("motor %d has the most neighbors\n",most_neighbors);

            //rotate motor with most neighbors that can bind to the top
            m=0;
            n=most_neighbors;
            makeRotationMatrix(0,0,1);
            rotateCargo();

            break;

        case 7: //start at a defined angle along the x axis
            for (m=0;m<2;m++){
                for(n=0;n<N[m];n++){
                    if(InitAngle<=90 && InitAngle>=-90){
                        initlocs[m][n][0]=center[0]+R*cos(pi/180*InitAngle)*cos(0);
                        initlocs[m][n][1]=center[1]+R*cos(pi/180*InitAngle)*sin(0);
                        initlocs[m][n][2]=center[2]+R*sin(pi/180*InitAngle);
                    } else if((InitAngle>90 && InitAngle<=180) ||
                              (InitAngle<-90 && InitAngle>=-180)){
                        initlocs[m][n][0]=center[0]+R*cos(pi/180*InitAngle)*cos(0);
                        initlocs[m][n][1]=center[1]+R*cos(pi/180*InitAngle)*sin(0);
                        initlocs[m][n][2]=center[2]+R*sin(pi/180*InitAngle);
                    } else {
                        printf("\n\nError: %g is not a valid initial angle\n(-180 to 180 accepted)\n\n", InitAngle);
                        exit(4);
                    }
                }
            }

            break;

        case 8: //rotate so type0motor0 is on bottom

            for (m=0;m<2;m++){
                for(n=0;n<N[m];n++){
                    pickpointsphere();
                    initlocs[m][n][0]=x*R+center[0];
                    initlocs[m][n][1]=y*R+center[1];
                    initlocs[m][n][2]=z*R+center[2];
                }
            }

            if(verboseTF>3){
                printf("    Before rotation,initial locations are chosen as:\n");
                for (m=0;m<2;m++){
                    for(n=0;n<N[m];n++){
                        printf("        type%dmotor%d: (%g,%g,%g)\n",m,n,initlocs[m][n][0],initlocs[m][n][1],initlocs[m][n][2] );
                    }
                }
            }

            m=0;
            n=0;
            makeRotationMatrix(0,0,-1);

            if(verboseTF>3){
                printf("    The rotation matrix that was found is:\n");
                printf("        %+E %+E %+E\n        %+E %+E %+E\n        %+E %+E %+E\n",
                    rotmat[0],rotmat[1],rotmat[2],
                    rotmat[3],rotmat[4],rotmat[5],
                    rotmat[6],rotmat[7],rotmat[8]);
            }

            rotateCargo();

            break;

        case 9: //pick one random spot and put all motors there

            //random initial location
            pickpointsphere();
            //place all motors there
            for (m=0;m<2;m++){
                for(n=0;n<N[m];n++){
                    initlocs[m][n][0]=x*R+center[0];
                    initlocs[m][n][1]=y*R+center[1];
                    initlocs[m][n][2]=z*R+center[2];
                }
            }

            break;

        default:
            printf("\n\nError: Not a valid initial location type\n\n");
            exit(4);
    }//switch

    // if(verboseTF>2){
    //     printf("Initial locations finally:\n");
    //     for (m=0;m<2;m++){
    //         for(n=0;n<N[m];n++){
    //             printf("    type%dmotor%d: (%g,%g,%g)\n",m,n,initlocs[m][n][0],initlocs[m][n][1],initlocs[m][n][2] );
    //         }
    //     }
    // }

    //if passed the setting to have one of the motors on the bottom
    if(SetAtBottom){
        //if passed 1, want to attach for m=0 (kinesin)
        //if passed 2, attach for m=1 (dynein)
        if(SetAtBottom==1){
            initlocs[0][0][0]=center[0];
            initlocs[0][0][1]=center[1];
            initlocs[0][0][2]=center[2]-R;
        }
        if(SetAtBottom==2){
            initlocs[1][0][0]=center[0];
            initlocs[1][0][1]=center[1];
            initlocs[1][0][2]=center[2]-R;
        }
        if(SetAtBottom==3){
            initlocs[0][0][0]=center[0];
            initlocs[0][0][1]=center[1];
            initlocs[0][0][2]=center[2]+R;
        }
        if(SetAtBottom==4){
            initlocs[1][0][0]=center[0];
            initlocs[1][0][1]=center[1];
            initlocs[1][0][2]=center[2]+R;
        }
    }//set at bottom

    //set the generated initial locations to the current location
    for (m=0;m<2;m++){
        for(n=0;n<N[m];n++){
            //printf("%d %f %f %f\n",m,initlocs[n][0],initlocs[n][1],initlocs[n][2]);
            for(i=0;i<3;i++){
                locs[m][n][i]=initlocs[m][n][i];
            }
        }
    }
} // finished initiallocations

void makeRotationMatrix(double t0,double t1,double t2){
    rotmat[0] = -((pow(t1*(center[0] - initlocs[m][n][0]) + t0*(-center[1] + initlocs[m][n][1]),2) - R*(R - t1*center[1] - t2*center[2] + t0*(-center[0] + initlocs[m][n][0]) + t1*initlocs[m][n][1] + t2*initlocs[m][n][2]) + pow(t2*(center[0] - initlocs[m][n][0]) + t0*(-center[2] + initlocs[m][n][2]),2))/(R*(R - t1*center[1] - t2*center[2] + t0*(-center[0] + initlocs[m][n][0]) + t1*initlocs[m][n][1] + t2*initlocs[m][n][2])));
    rotmat[1] = (t1*center[0] - t0*center[1] - t1*initlocs[m][n][0] + t0*initlocs[m][n][1] + ((t2*(-center[1] + initlocs[m][n][1]) + t1*(center[2] - initlocs[m][n][2]))*(t2*(center[0] - initlocs[m][n][0]) + t0*(-center[2] + initlocs[m][n][2])))/(R - t1*center[1] - t2*center[2] + t0*(-center[0] + initlocs[m][n][0]) + t1*initlocs[m][n][1] + t2*initlocs[m][n][2]))/R;
    rotmat[2] = (t2*center[0] - t0*center[2] - t2*initlocs[m][n][0] + t0*initlocs[m][n][2] - ((t1*(center[0] - initlocs[m][n][0]) + t0*(-center[1] + initlocs[m][n][1]))*(t2*(-center[1] + initlocs[m][n][1]) + t1*(center[2] - initlocs[m][n][2])))/(R - t1*center[1] - t2*center[2] + t0*(-center[0] + initlocs[m][n][0]) + t1*initlocs[m][n][1] + t2*initlocs[m][n][2]))/R;
    rotmat[3] = (-(t1*center[0]) + t0*center[1] + t1*initlocs[m][n][0] - t0*initlocs[m][n][1] + ((t2*(-center[1] + initlocs[m][n][1]) + t1*(center[2] - initlocs[m][n][2]))*(t2*(center[0] - initlocs[m][n][0]) + t0*(-center[2] + initlocs[m][n][2])))/(R - t1*center[1] - t2*center[2] + t0*(-center[0] + initlocs[m][n][0]) + t1*initlocs[m][n][1] + t2*initlocs[m][n][2]))/R;
    rotmat[4] = (pow(R,2) - (pow(t0,2) + pow(t2,2))*pow(center[1] - initlocs[m][n][1],2) + 2*t1*(center[1] - initlocs[m][n][1])*(t0*(center[0] - initlocs[m][n][0]) + t2*(center[2] - initlocs[m][n][2])) + R*(-(t1*center[1]) - t2*center[2] + t0*(-center[0] + initlocs[m][n][0]) + t1*initlocs[m][n][1] + t2*initlocs[m][n][2]) - pow(t1,2)*(pow(center[0],2) + pow(center[2],2) - 2*center[0]*initlocs[m][n][0] + pow(initlocs[m][n][0],2) - 2*center[2]*initlocs[m][n][2] + pow(initlocs[m][n][2],2)))/(R*(R - t1*center[1] - t2*center[2] + t0*(-center[0] + initlocs[m][n][0]) + t1*initlocs[m][n][1] + t2*initlocs[m][n][2]));
    rotmat[5] = (t2*center[1] - t1*center[2] - t2*initlocs[m][n][1] + t1*initlocs[m][n][2] - ((t1*(center[0] - initlocs[m][n][0]) + t0*(-center[1] + initlocs[m][n][1]))*(t2*(center[0] - initlocs[m][n][0]) + t0*(-center[2] + initlocs[m][n][2])))/(R - t1*center[1] - t2*center[2] + t0*(-center[0] + initlocs[m][n][0]) + t1*initlocs[m][n][1] + t2*initlocs[m][n][2]))/R;
    rotmat[6] = (-(t2*center[0]) + t0*center[2] + t2*initlocs[m][n][0] - t0*initlocs[m][n][2] - ((t1*(center[0] - initlocs[m][n][0]) + t0*(-center[1] + initlocs[m][n][1]))*(t2*(-center[1] + initlocs[m][n][1]) + t1*(center[2] - initlocs[m][n][2])))/(R - t1*center[1] - t2*center[2] + t0*(-center[0] + initlocs[m][n][0]) + t1*initlocs[m][n][1] + t2*initlocs[m][n][2]))/R;
    rotmat[7] = (-(t2*center[1]) + t1*center[2] + t2*initlocs[m][n][1] - t1*initlocs[m][n][2] - ((t1*(center[0] - initlocs[m][n][0]) + t0*(-center[1] + initlocs[m][n][1]))*(t2*(center[0] - initlocs[m][n][0]) + t0*(-center[2] + initlocs[m][n][2])))/(R - t1*center[1] - t2*center[2] + t0*(-center[0] + initlocs[m][n][0]) + t1*initlocs[m][n][1] + t2*initlocs[m][n][2]))/R;
    rotmat[8] = (pow(R,2) - pow(t2,2)*(pow(center[0],2) + pow(center[1],2) - 2*center[0]*initlocs[m][n][0] + pow(initlocs[m][n][0],2) - 2*center[1]*initlocs[m][n][1] + pow(initlocs[m][n][1],2)) + 2*t2*(t0*(center[0] - initlocs[m][n][0]) + t1*(center[1] - initlocs[m][n][1]))*(center[2] - initlocs[m][n][2]) - (pow(t0,2) + pow(t1,2))*pow(center[2] - initlocs[m][n][2],2) + R*(-(t1*center[1]) - t2*center[2] + t0*(-center[0] + initlocs[m][n][0]) + t1*initlocs[m][n][1] + t2*initlocs[m][n][2]))/(R*(R - t1*center[1] - t2*center[2] + t0*(-center[0] + initlocs[m][n][0]) + t1*initlocs[m][n][1] + t2*initlocs[m][n][2]));
}

void rotateCargo(){
    for (m=0;m<2;m++){
        for(n=0;n<N[m];n++){
            initlocsnew[m][n][0] = center[0] + rotmat[0]*(-center[0] + initlocs[m][n][0]) + rotmat[1]*(-center[1] + initlocs[m][n][1]) + rotmat[2]*(-center[2] + initlocs[m][n][2]);
            initlocsnew[m][n][1] = center[1] + rotmat[3]*(-center[0] + initlocs[m][n][0]) + rotmat[4]*(-center[1] + initlocs[m][n][1]) + rotmat[5]*(-center[2] + initlocs[m][n][2]);
            initlocsnew[m][n][2] = center[2] + rotmat[6]*(-center[0] + initlocs[m][n][0]) + rotmat[7]*(-center[1] + initlocs[m][n][1]) + rotmat[8]*(-center[2] + initlocs[m][n][2]);

            for(i=0;i<3;i++){
                initlocs[m][n][i]=initlocsnew[m][n][i];
            }
        }
    }
}

void vecToClosestPointOnMT(double x,double y,double z, int MTnum){
    //from mathematica file
    cVector[0] = (-x + MTpoint[MTnum][0] - MTvec[MTnum][0]*((-x + MTpoint[MTnum][0])*MTvec[MTnum][0] + (-y + MTpoint[MTnum][1])*MTvec[MTnum][1] + (-z + MTpoint[MTnum][2])*MTvec[MTnum][2]))*(1 - R_MT[MTnum]/sqrt(pow(x - MTpoint[MTnum][0] + MTvec[MTnum][0]*((-x + MTpoint[MTnum][0])*MTvec[MTnum][0] + (-y + MTpoint[MTnum][1])*MTvec[MTnum][1] + (-z + MTpoint[MTnum][2])*MTvec[MTnum][2]),2) + pow(y - MTpoint[MTnum][1] + MTvec[MTnum][1]*((-x + MTpoint[MTnum][0])*MTvec[MTnum][0] + (-y + MTpoint[MTnum][1])*MTvec[MTnum][1] + (-z + MTpoint[MTnum][2])*MTvec[MTnum][2]),2) + pow(z - MTpoint[MTnum][2] + MTvec[MTnum][2]*((-x + MTpoint[MTnum][0])*MTvec[MTnum][0] + (-y + MTpoint[MTnum][1])*MTvec[MTnum][1] + (-z + MTpoint[MTnum][2])*MTvec[MTnum][2]),2)));
    cVector[1] = (-y + MTpoint[MTnum][1] - MTvec[MTnum][1]*((-x + MTpoint[MTnum][0])*MTvec[MTnum][0] + (-y + MTpoint[MTnum][1])*MTvec[MTnum][1] + (-z + MTpoint[MTnum][2])*MTvec[MTnum][2]))*(1 - R_MT[MTnum]/sqrt(pow(x - MTpoint[MTnum][0] + MTvec[MTnum][0]*((-x + MTpoint[MTnum][0])*MTvec[MTnum][0] + (-y + MTpoint[MTnum][1])*MTvec[MTnum][1] + (-z + MTpoint[MTnum][2])*MTvec[MTnum][2]),2) + pow(y - MTpoint[MTnum][1] + MTvec[MTnum][1]*((-x + MTpoint[MTnum][0])*MTvec[MTnum][0] + (-y + MTpoint[MTnum][1])*MTvec[MTnum][1] + (-z + MTpoint[MTnum][2])*MTvec[MTnum][2]),2) + pow(z - MTpoint[MTnum][2] + MTvec[MTnum][2]*((-x + MTpoint[MTnum][0])*MTvec[MTnum][0] + (-y + MTpoint[MTnum][1])*MTvec[MTnum][1] + (-z + MTpoint[MTnum][2])*MTvec[MTnum][2]),2)));
    cVector[2] = (-z + MTpoint[MTnum][2] - MTvec[MTnum][2]*((-x + MTpoint[MTnum][0])*MTvec[MTnum][0] + (-y + MTpoint[MTnum][1])*MTvec[MTnum][1] + (-z + MTpoint[MTnum][2])*MTvec[MTnum][2]))*(1 - R_MT[MTnum]/sqrt(pow(x - MTpoint[MTnum][0] + MTvec[MTnum][0]*((-x + MTpoint[MTnum][0])*MTvec[MTnum][0] + (-y + MTpoint[MTnum][1])*MTvec[MTnum][1] + (-z + MTpoint[MTnum][2])*MTvec[MTnum][2]),2) + pow(y - MTpoint[MTnum][1] + MTvec[MTnum][1]*((-x + MTpoint[MTnum][0])*MTvec[MTnum][0] + (-y + MTpoint[MTnum][1])*MTvec[MTnum][1] + (-z + MTpoint[MTnum][2])*MTvec[MTnum][2]),2) + pow(z - MTpoint[MTnum][2] + MTvec[MTnum][2]*((-x + MTpoint[MTnum][0])*MTvec[MTnum][0] + (-y + MTpoint[MTnum][1])*MTvec[MTnum][1] + (-z + MTpoint[MTnum][2])*MTvec[MTnum][2]),2)));

    // printf("Vec from (%g,%g,%g) to MT%d at (%g,%g,%g): (%g,%g,%g)\n",
    // x,y,z,MTnum,MTpoint[MTnum][0],MTpoint[MTnum][1],MTpoint[MTnum][2],cVector[0],cVector[1],cVector[2]);
}

void pointToMTdist(double x,double y,double z, int MTnum){
    vecToClosestPointOnMT(x,y,z,MTnum);
    MTdist = sqrt(pow(cVector[0],2) + pow(cVector[1],2) + pow(cVector[2],2));

    // printf("Distance from (%g,%g,%g) to MT%d at (%g,%g,%g): %g\n",
    // x,y,z,MTnum,MTpoint[MTnum][0],MTpoint[MTnum][1],MTpoint[MTnum][2],MTdist);
}

void findMTdist(){
    //Find out if each motor is close enough to bind to the MT
    //sets bind_possible
    for(n=0;n<N[m];n++){
        if(bound[m][n]==0){

            //for each MT, find the distance from the anchor
            for(k=0;k<n_MTs;k++){
                // printf("Calling pointtoMTdist from findMTdist\n");
                pointToMTdist(locs[m][n][0],locs[m][n][1],locs[m][n][2],k);

                //prevent binding through the cargo
                //if dot product of vector from anchor to MT and vector from
                // center to anchor is <0, vector from anchor to MT points inside
                // the cargo
                if(((cVector[0]*(locs[m][n][0]-center[0])+
                    cVector[1]*(locs[m][n][1]-center[1])+
                    cVector[2]*(locs[m][n][2]-center[2])) < 0) &&
                   (mag(cVector)>.001)){

                    //printf("\ndist is %g, line dist is %g, step %ld of repeat %d\n",((pi - 2*acos((center[0]*cVector[0] + center[1]*cVector[1] + center[2]*cVector[2] - cVector[0]*locs[m][n][0] - cVector[1]*locs[m][n][1] - cVector[2]*locs[m][n][2])/sqrt((pow(cVector[0],2) + pow(cVector[1],2) + pow(cVector[2],2))*(pow(center[0] - locs[m][n][0],2) + pow(center[1] - locs[m][n][1],2) + pow(center[2] - locs[m][n][2],2)))) - 2*acos((-(center[0]*cVector[0]) + pow(cVector[0],2) - center[1]*cVector[1] + pow(cVector[1],2) - center[2]*cVector[2] + pow(cVector[2],2) + cVector[0]*locs[m][n][0] + cVector[1]*locs[m][n][1] + cVector[2]*locs[m][n][2])/sqrt((pow(cVector[0],2) + pow(cVector[1],2) + pow(cVector[2],2))*(pow(-center[0] + cVector[0] + locs[m][n][0],2) + pow(-center[1] + cVector[1] + locs[m][n][1],2) + pow(-center[2] + cVector[2] + locs[m][n][2],2)))) + 2*asin(sqrt((pow(center[0] - locs[m][n][0],2) + pow(center[1] - locs[m][n][1],2) + pow(center[2] - locs[m][n][2],2))/(pow(-center[0] + cVector[0] + locs[m][n][0],2) + pow(-center[1] + cVector[1] + locs[m][n][1],2) + pow(-center[2] + cVector[2] + locs[m][n][2],2)))))*sqrt(pow(center[0] - locs[m][n][0],2) + pow(center[1] - locs[m][n][1],2) + pow(center[2] - locs[m][n][2],2)))/2. + sqrt(-2*center[0]*cVector[0] + pow(cVector[0],2) - 2*center[1]*cVector[1] + pow(cVector[1],2) - 2*center[2]*cVector[2] + pow(cVector[2],2) + 2*cVector[0]*locs[m][n][0] + 2*cVector[1]*locs[m][n][1] + 2*cVector[2]*locs[m][n][2]),anchorMTdist[m][n][k],step,j);

                    //unless the rest length is long enough to go around the surface of the sphere and reach that point
                    //(see findDistanceSphere.nb)
                    dist_around_cargo=((pi - 2*acos((center[0]*cVector[0] + center[1]*cVector[1] + center[2]*cVector[2] - cVector[0]*locs[m][n][0] - cVector[1]*locs[m][n][1] - cVector[2]*locs[m][n][2])/sqrt((pow(cVector[0],2) + pow(cVector[1],2) + pow(cVector[2],2))*(pow(center[0] - locs[m][n][0],2) + pow(center[1] - locs[m][n][1],2) + pow(center[2] - locs[m][n][2],2)))) - 2*acos((-(center[0]*cVector[0]) + pow(cVector[0],2) - center[1]*cVector[1] + pow(cVector[1],2) - center[2]*cVector[2] + pow(cVector[2],2) + cVector[0]*locs[m][n][0] + cVector[1]*locs[m][n][1] + cVector[2]*locs[m][n][2])/sqrt((pow(cVector[0],2) + pow(cVector[1],2) + pow(cVector[2],2))*(pow(-center[0] + cVector[0] + locs[m][n][0],2) + pow(-center[1] + cVector[1] + locs[m][n][1],2) + pow(-center[2] + cVector[2] + locs[m][n][2],2)))) + 2*asin(sqrt((pow(center[0] - locs[m][n][0],2) + pow(center[1] - locs[m][n][1],2) + pow(center[2] - locs[m][n][2],2))/(pow(-center[0] + cVector[0] + locs[m][n][0],2) + pow(-center[1] + cVector[1] + locs[m][n][1],2) + pow(-center[2] + cVector[2] + locs[m][n][2],2)))))*sqrt(pow(center[0] - locs[m][n][0],2) + pow(center[1] - locs[m][n][1],2) + pow(center[2] - locs[m][n][2],2)))/2. + sqrt(-2*center[0]*cVector[0] + pow(cVector[0],2) - 2*center[1]*cVector[1] + pow(cVector[1],2) - 2*center[2]*cVector[2] + pow(cVector[2],2) + 2*cVector[0]*locs[m][n][0] + 2*cVector[1]*locs[m][n][1] + 2*cVector[2]*locs[m][n][2]);

                    if(dist_around_cargo < max_motor_reach[m]){
                        bind_possible[m][n][k]=1;
                        //printf("Bind possible is %d at step %ld\n",bind_possible[m][n][k],step);
                    }else{
                        bind_possible[m][n][k]=0;
                    }

                    anchorMTdist[m][n][k]=dist_around_cargo;

                }else{
                    bind_possible[m][n][k]=1;
                    anchorMTdist[m][n][k]=MTdist;
                }


                //often, only want to bind if MT is closer than motor is long
                if (anchorMTdist[m][n][k]<=L[m] && bind_possible[m][n][k]==1) {
                    within_L[m][n][k]=1;
                }else{
                    within_L[m][n][k]=0;
                }
                //printf("for type%dmotor%d dist is %f, bind_possible is %d\n",m,n,anchorMTdist[m][n][k],bind_possible[m][n][k]);
            }

        }else{
            for(k=0;k<n_MTs;k++){
                bind_possible[m][n][k]=0;
            }
        }
    }
}

void initialbinding(){

    if(verboseTF>2){
        printf("Setting initial binding with case %d\n",InitialBinding);
    }

    //Set no motors to be bound before we start (need this for findMTdist)
    for(m=0;m<2;m++){
        for(n=0;n<N[m];n++){
            bound[m][n]=0;
        }
    }

    switch (InitialBinding) {
        case 1: //Bind all in range

            for(m=0;m<2;m++){
                //call the function that find the distance from each motor to the MT
                findMTdist();

                //set bound status to mirror capture possibility
                for(n=0;n<N[m];n++){
                    for(k=0;k<n_MTs;k++){
                        //set bound to MT number
                        if(!bound[m][n]){
                            bound[m][n]=(k+1)*within_L[m][n][k];
                        }
                        //Note: this will always bind the motor to the first MT if there are multiple MTs in range
                    }
                }
            }

            break;

        case 2: //Bind only one kinesin to 1st MT

            for(m=0;m<2;m++){
                //find the distance from each anchor to the MT
                findMTdist();

                //attach the one kinesin
                if(m==0){
                    done=0;

                    if(InitialLocations==6){
                        if(within_L[m][most_neighbors][0]){
                            bound[m][most_neighbors]=1;
                            done=1;
                        }
                        if(!done){
                            printf("\n\n\n Error: Wasn't able to bind motor with most neighbors\n\n\n");
                            exit(4);
                        }
                    }else{

                        //loop through motors to assign binding status
                        for(n=0;n<N[m];n++){
                            //of the motors for which capture is possible, attach only one
                            if(within_L[m][n][0]){
                                if(done==0){
                                    bound[m][n]=1;
                                    done=1;
                                }
                                //all others don't attach
                                else{
                                    bound[m][n]=0;
                                }
                            }
                            else{
                                bound[m][n]=0;
                            }
                        }
                    }

                    //stop if one wasn't able to bind
                    if(done==0){
                        printf("\n\n\nError: Wasn't able to bind motor as requested\n");
                        printf("Center was (%g,%g,%g)\n",center[0],center[1],center[2]);
                        printf("InitialLocations was %d\n",InitialLocations);
                        printf("Anchor locations and dist to MT0 were:\n");
                        for(m=0;m<2;m++){
                            for(n=0;n<N[m];n++){
                                printf("    type%dmotor%d: (%g,%g,%g) and %g, marked %d %d\n",m,n,all3(locs[m][n]),anchorMTdist[m][n][0],within_L[m][n][0],bind_possible[m][n][0] );
                            }
                        }
                        printf("\n\n");
                        if(j==0){
                            exit(4);
                        } else {
                            graceful_exit=1;
                        }

                    }
                }
            }

            break;

        case 3: //don't bind any motors

            for(m=0;m<2;m++){
                //set none bound if we don't want any motors initially bound
                for(n=0;n<N[m];n++){
                    bound[m][n]=0;
                }
            }

            break;

        case 4: //Bind only one dyn

            for(m=0;m<2;m++){
                //find the distance from each anchor to the MT
                findMTdist();

                //attach the one dyn
                if(m==1){
                    done=0;
                    //loop through motors to assign binding status
                    for(n=0;n<N[m];n++){
                        //of the motors for which capture is possible, attach only one
                        if(within_L[m][n][0]){
                            if(done==0){
                                bound[m][n]=1;
                                done=1;
                            }
                            //all others don't attach
                            else{
                                bound[m][n]=0;
                            }
                        }
                        else{
                            bound[m][n]=0;
                        }
                    }

                    //stop if one wasn't able to bind
                    if(done==0){
                        printf("\n\n\n Error: Wasn't able to bind motor as requested\n\n\n");
                        exit(4);
                    }
                }
            }

            break;

        case 5: //force bind all motors

            for(m=0;m<2;m++){
                findMTdist();

                //loop through motors to assign binding status
                for(n=0;n<N[m];n++){
                    bound[m][n]=1;
                }
            }

            break;

        default:
            printf("\n\nError: Not a valid initial binding type\n\n");
            exit(4);
    }

    //set head locations to reflect binding status

    //when motors attach they then have a defined head location
    //this sets the heads directly below the anchor (same x position)
    //should later change to projection from center of cargo?
    // if(verboseTF>2)
    //     printf("Bound status:\n");

    for(m=0;m<2;m++){
        for(n=0;n<N[m];n++){

            // if(verboseTF>2){
            //     printf("    type%dmotor%d: %d\n",m,n,bound[m][n]);
            // }

            if(bound[m][n]){
                // printf("Calling closestPoint from head setting\n");
                closestPointOnMT(locs[m][n][0],locs[m][n][1],locs[m][n][2],bound[m][n]-1);
                //printf("cVector is \n", );
                for(i=0;i<3;i++){
                    head[m][n][i]=cPoint[i];
                }
            }
            else{
                head[m][n][0]=NAN;
                head[m][n][1]=NAN;
                head[m][n][2]=NAN;
            }
        }
    }



    if (bound[0][0] && initial_head){
        closestPointOnMT(locs[0][0][0],locs[0][0][1],locs[0][0][2],bound[0][0]-1);
        if(verboseTF>2){
            printf("InitialHead specified, adding %g to x part of (%g,%g,%g)\n",initial_head,cPoint[0],cPoint[1],cPoint[2]);
        }
        head[0][0][0]=cPoint[0]+initial_head;
        head[0][0][1]=cPoint[1];
        head[0][0][2]=cPoint[2];
    } else if(bound[1][0] && initial_head) {
        closestPointOnMT(locs[1][0][0],locs[1][0][1],locs[1][0][2],bound[1][0]-1);
        head[1][0][0]=cPoint[0]+initial_head;
        head[1][0][1]=cPoint[1];
        head[1][0][2]=cPoint[2];
    }

    // if(verboseTF>2)
    //     printf("Head location:\n");
    // for(m=0;m<2;m++){
    //     for(n=0;n<N[m];n++){
    //         printf("    type%dmotor%d: (%g,%g,%g)\n",m,n,head[m][n][0],head[m][n][1],head[m][n][2] );
    //     }
    // }
}//end initial binding

void closestPointOnMT(double x,double y,double z,int MTnum){
    //find the closest point on the MT to the point given
    vecToClosestPointOnMT(x,y,z,MTnum);
    cPoint[0] = x + cVector[0];
    cPoint[1] = y + cVector[1];
    cPoint[2] = z + cVector[2];

    // printf("Point from (%g,%g,%g) closest to MT%d at (%g,%g,%g): (%g,%g,%g)\n",
    // x,y,z,MTnum,MTpoint[MTnum][0],MTpoint[MTnum][1],MTpoint[MTnum][2],cPoint[0],cPoint[1],cPoint[2]);
}

void initialnucleotide(){

    if(verboseTF>2){
        printf("setting initial nucleotide with case %d\n",InitialNucleotideBehavior);
    }

    switch (InitialNucleotideBehavior) {
        case 1: //all start ready

            for(m=0;m<2;m++){
                for(n=0;n<N[m];n++){
                    nuc_ready[n][m]=1;
                }
            }
            break;

        case 2: //all start not ready

            for(m=0;m<2;m++){
                for(n=0;n<N[m];n++){
                    nuc_ready[n][m]=0;
                }
            }
            break;

        default:
            printf("\n\nError: Invalid Initial Nucleotide Behavior setting\n\n");
            exit(4);
    }
}//finished initialnucleotide
