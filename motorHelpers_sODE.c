// Prototypes

void generate_rand_normal();
void convert_loc_sph_to_cart();
void convert_vec_to_cart(double az,double el,double v_az,double v_el,double v_r);
void convert_vec_to_sph(double az,double el,double v_x,double v_y,double v_z);

void generate_brownian_displacement_anchor();
void generate_brownian_displacement_cargo();
void generate_brownian_displacement_rotation();

void diffuse_sph_one_motor();

void cargobehavior();

void setup_solve();
void evaluate_steric();
void calculate_forces();
void set_brownian_forces_to_0();
void compute_next_locations();


void generate_rand_normal(){
    //generate random normal number by Box-Muller transform

    //start with 2 uniform(0,1) random numbers
    rand1=RAND;
    rand2=RAND;
    //tranform to normally distributed
    randn1=sqrt(-2*log(rand1))*cos(2*pi*rand2);
    randn2=sqrt(-2*log(rand1))*sin(2*pi*rand2);
}

void convert_loc_sph_to_cart(){
    //http://www.mathworks.com/help/matlab/ref/sph2cart.html

    locs[m][n][0]=R*cos(locs_sph[m][n][1])*cos(locs_sph[m][n][0])+center[0];
    locs[m][n][1]=R*cos(locs_sph[m][n][1])*sin(locs_sph[m][n][0])+center[1];
    locs[m][n][2]=R*sin(locs_sph[m][n][1])+center[2];
}

void convert_vec_to_cart(double az,double el,double v_az,double v_el,double v_r){
    //http://www.mathworks.com/help/phased/ref/sph2cartvec.html
    v_cart[0]=-sin(az)*v_az-sin(el)*cos(az)*v_el+cos(el)*cos(az)*v_r; //x
    v_cart[1]=cos(az)*v_az-sin(el)*sin(az)*v_el+cos(el)*sin(az)*v_r; //y
    v_cart[2]=cos(el)*v_el+sin(el)*v_r; //z
}

void convert_vec_to_sph(double az,double el,double v_x,double v_y,double v_z){
    v_sph[0]=-sin(az)*v_x+cos(az)*v_y; //az
    v_sph[1]=-sin(el)*cos(az)*v_x - sin(el)*sin(az)*v_y + cos(el)*v_z; //el
    v_sph[2]=cos(el)*cos(az)*v_x + cos(el)*sin(az)*v_y + sin(el)*v_z; //r
}

void generate_brownian_displacement_anchor(){
    //convert motor locations to spherical
    convert_loc_to_spherical();

    //find local cartesian vectors in plane tangent to sphere at anchor loc
    //use cartesian version of az and el vectors as vectors in plane
    convert_vec_to_cart(locs_sph[m][n][0],locs_sph[m][n][1],1,0,0);
    for(i=0;i<3;i++){
        u_hat[i]=v_cart[i];
        //printf("%f\n",u_hat[i]);
    }
    convert_vec_to_cart(locs_sph[m][n][0],locs_sph[m][n][1],0,1,0);
    for(i=0;i<3;i++){
        v_hat[i]=v_cart[i];
        //printf("%f\n",v_hat[i]);
    }

    //generate random vector in plane defined by u_hat and v_hat
    //first need 2 normally distributed random variables
    generate_rand_normal();
    //cartesian displacement vector is sum of two unit vectors weighted by
    //gaussian random variable

    for(i=0;i<3;i++){
        brownian_displacement[i]=randn1*u_hat[i]+randn2*v_hat[i];
    }
}

void generate_brownian_displacement_cargo(){

    generate_rand_normal();
    brownian_displacement[0]=randn1;
    brownian_displacement[1]=randn2;
    generate_rand_normal();
    brownian_displacement[2]=randn1;

    //that way doesn't work
    // pickpointsphere();
    // generate_rand_normal();
    //
    // brownian_displacement[0]=randn1*x;
    // brownian_displacement[1]=randn1*y;
    // brownian_displacement[2]=randn1*z;
}

void generate_brownian_displacement_rotation(){

    //make gaussian random variables
    generate_rand_normal();
    brownian_displacement[0]=randn1;
    brownian_displacement[1]=randn2;
    //make two more and use the first to find dz (other is wasted)
    generate_rand_normal();
    brownian_displacement[2]=randn1;

    //not sure that way actually works (seems to be too slow by factor of e)
    //instead, try picking a random unit vector with a gaussian magnitude

    // //pick a random point on the unit sphere
    // //same as picking randomly directed unit vector, then converting to cartesian
    // pickpointsphere();
    // //generate gaussian random variable
    // generate_rand_normal();
    // //set output to random spharical unit vector * gaussian random variable
    // brownian_displacement[0]=randn1*x;
    // brownian_displacement[1]=randn1*y;
    // brownian_displacement[2]=randn1*z;
}

void diffuse_sph_one_motor(){

    //generate brownian displacement vector
    generate_brownian_displacement_anchor();

    //move anchor by generated vector (will go off sphere surface)
    for(i=0;i<3;i++){
        locs[m][n][i]+=sqrt(4*D_m[m]*dt)*brownian_displacement[i];
    }

    if(verboseTF>4 && MotorDiffusion==8){
        printf("Legacy, locs update is     (%lf %lf %lf)\n",locs[0][0][0],locs[0][0][1],locs[0][0][2] );
    }

    //bring back to sphere surface by converting to spherical and back (fix R)
    convert_loc_to_spherical();
    convert_loc_sph_to_cart();

    if(verboseTF>4 && MotorDiffusion==8){
        printf("Legacy, locs final is                             (%lf %lf %lf)\n",locs[0][0][0],locs[0][0][1],locs[0][0][2] );
    }
}

// old version
// had problems near poles
// void diffuse_sph_one_motor(){
//     //convert motor locations to spherical
//     convert_loc_to_spherical();
//
//     // printf("%f\n",locs_sph[m][n][0]);
//     // printf("%f\n",locs_sph[m][n][1]);
//
//     lim=pi/2-acos(1/(.5*R)*sqrt(2*D_m[m]*dt)*3);
//
//     //if near pole, need to move out a bit so diffusion can work
//     if(locs_sph[m][n][1]>pi/2-lim){
//         locs_sph[m][n][1]=pi/2-lim;
//         locs_sph[m][n][0]=RAND*2*pi;
//         printf("Moved from top\n");
//     }
//     if(locs_sph[m][n][1]<-pi/2+lim){
//         locs_sph[m][n][1]=-pi/2+lim;
//         locs_sph[m][n][0]=RAND*2*pi;
//         printf("Moved from bottom\n");
//     }
//
//     // printf("%f\n",locs_sph[m][n][0]);
//     // printf("%f\n",locs_sph[m][n][1]);
//
//     //do diffusion in spherical
//     //first need normally distributed random variables
//     generate_rand_normal();
//     // printf("%f\n",randn1);
//     // printf("%f\n",randn2);
//     //not sure about this yet.
//     //scale change in az by cos(el) -- remember el goes from
//     //-pi/2 to pi/2
//     locs_sph[m][n][0]+=1/(R*cos(locs_sph[m][n][1]))*sqrt(2*D_m[m]*dt)*randn1;
//     locs_sph[m][n][1]+=1/R*sqrt(2*D_m[m]*dt)*randn2;
//
//     //correct if went out of bounds
//     if(locs_sph[m][n][0]>=2*pi){
//         //printf("hit1\n");
//         locs_sph[m][n][0]-=2*pi;
//     }
//     if(locs_sph[m][n][0]<0){
//         //printf("hit2\n");
//         locs_sph[m][n][0]+=2*pi;
//     }
//     if(locs_sph[m][n][1]<-pi/2){
//         //printf("hit3\n");
//         locs_sph[m][n][1]=-pi/2-(locs_sph[m][n][1]+pi/2);
//         if(locs_sph[m][n][0]<=pi){
//             locs_sph[m][n][0]+=pi;
//         }
//         else{
//             locs_sph[m][n][0]-=pi;
//         }
//     }
//     if(locs_sph[m][n][1]>pi/2){
//         //printf("hit4\n");
//         locs_sph[m][n][1]=pi/2-(locs_sph[m][n][1]-pi/2);
//         if(locs_sph[m][n][0]<=pi){
//             locs_sph[m][n][0]+=pi;
//         }
//         else{
//             locs_sph[m][n][0]-=pi;
//         }
//     }
//
//     convert_loc_sph_to_cart();
// }

void update_motor_locations(){
    //set next locations from solver to current locations
    nn=0;
    for(m=0;m<2;m++){
        for(n=0;n<N[m];n++){
            //set anchor location of solver syntax (a) from syntax in rest
            //of program (locs)

            if(MotorDiffusion>2){
                for(i=0;i<3;i++){
                    locs[m][n][i]=a1[nn][i];
                }
                nn++;
            }
        }
    }
}

void cargobehavior()
{
    switch(CargoBehavior){

        case 1: //transfer all values

            update_motor_locations();

            //transfer cargo center
            for(i=0;i<3;i++){
                center[i]=c1[i];
            }

            break;

        case 2: //on rails - only move in x direction

            update_motor_locations();

            //transfer cargo center
            center[0]=c1[0];
            //center[1]=c1[1];
            //center[2]=c1[2];

            break;

        case 3: //stuck - cargo can't move at all

            update_motor_locations();

            //transfer cargo center
            //center[0]=c1[0];
            //center[1]=c1[1];
            //center[2]=c1[2];

            break;

        default:
            printf("bad value for CargoBehavior\n" );
    }//finished switch

    //force anchor back onto cargo surface
    for(m=0;m<2;m++){
        for(n=0;n<N[m];n++){
            convert_loc_to_spherical();
            convert_loc_sph_to_cart();
            if(verboseTF>4 && MotorDiffusion==8){
                printf("stochastic, locs final is                         (%lf %lf %lf)\n",locs[m][n][0],locs[m][n][1],locs[m][n][2]);
            }
        }
    }

} // finished cargobehavior

void setup_solve()
{
    //Need to give values to c, a, xiAnchor

    nn=0; //counter for how many motors there are total
    for(m=0;m<2;m++){
        for(n=0;n<N[m];n++){
            //set anchor location of solver syntax (a) from syntax in rest
            //of program (locs)

            for(i=0;i<3;i++){
                a[nn][i]=locs[m][n][i];
            }
            //set the drag coefficient according to motor identity
            muAnchor[nn]=mu_m[m];
            DAnchor[nn]=D_m[m];
            nn++;
        }
    }

    //current value of nn is the total number of motors
    total_motors=nn;

    //transfer center to c
    for(i=0;i<3;i++){
        c[i]=center[i];
    }
}

void evaluate_steric(){
    //set value of steric force
    //set if we need the steric spring timestep

    need_steric=0;

    //initially set to 0
    for(i=0;i<3;i++){
        Fsteric[i]=0;
    }

    if(verboseTF>4){
        printf("The steric force was found to be:\n");
    }

    //find steric force for each MT
    for(k=0;k<n_MTs;k++){
        pointToMTdist(center[0],center[1],center[2],k);
        if(MTdist<R){
            //implement the steric force
            Fsterick[0]=-kcMT*(R*cVector[0]/MTdist - cVector[0]);
            Fsterick[1]=-kcMT*(R*cVector[1]/MTdist - cVector[1]);
            Fsterick[2]=-kcMT*(R*cVector[2]/MTdist - cVector[2]);
            //set that we need the steric spring so we know to use the smaller timestep
            need_steric=1;

            if(MTdist < R-.005){

                MTviolationCounter[k]++;
                if(verboseTF>3){
                    printf("MT %d violation at step %ld. Total violations: %d\n",k,step,MTviolationCounter[k]);
                }
                if(MTviolationCounter[k]>5){
                    printf("\n\n\nError! MT %d more than 5nm inside cargo for 5 steps!\nExiting gracefully at step %ld\n\n\n",k,step);
                    graceful_exit=1;
                }
            }else{
                MTviolationCounter[k]=0;
            }

        }else{
            MTviolationCounter[k]=0;
            for(i=0;i<3;i++){
                Fsterick[i]=0;
            }
        }

        if(verboseTF>4){
            printf("    MT %d: (%g,%g,%g)\n",
                k+1,Fsterick[0],Fsterick[1],Fsterick[2]);

        }

        //add up forces from each MT into one total steric force
        for(i=0;i<3;i++){
            Fsteric[i]+=Fsterick[i];
        }

    }// loop over MTs

    if(verboseTF>4){
        printf("    Total: (%g,%g,%g)\n",
            Fsteric[0],Fsteric[1],Fsteric[2]);
    }

} //evaluate_steric

void calculate_forces()
{
    //set value of external force
    switch(external_force){
        case 1:
            for(i=0;i<3;i++){
                Ftrap[i]=0;
            }
            break;
        case 2:
            //external force given as input
            //values for Ftrap set when input, don't change them
            break;
        case 3:
            //implement something here for an optical trap
            break;
        default:
            printf("bad value for external_force\n");
            exit(0);
    }

    if(verboseTF>4){
        printf("The external force on the cargo is: (%g,%g,%g)\n",
            Ftrap[0],Ftrap[1],Ftrap[2]);
    }

    //deal with external torque
    switch(external_torque){
        case 1:
            for(i=0;i<3;i++){
                TorqeExt[i]=0;
            }
            break;
        case 2:
            //external force given as input
            //values for Ftrap set when input, don't change them
            break;
        default:
            printf("bad value for external_force\n");
            exit(0);
    }

    if(verboseTF>4){
        printf("The external torque on the cargo is: (%g,%g,%g)\n",
            TorqeExt[0],TorqeExt[1],TorqeExt[2]);
    }

    //transform force vectors to spherical and split into radial and tangential
    nn=0;
    for(m=0;m<2;m++){
        for(n=0;n<N[m];n++){
            if(bound[m][n]){

                convert_loc_to_spherical();
                convert_vec_to_sph(locs_sph[m][n][0],locs_sph[m][n][1],F_m_vec[m][n][0],F_m_vec[m][n][1],F_m_vec[m][n][2]);

                convert_vec_to_cart(locs_sph[m][n][0],locs_sph[m][n][1],0,0,v_sph[2]);
                for(i=0;i<3;i++){
                    FmRadial[nn][i]=v_cart[i];
                }
                convert_vec_to_cart(locs_sph[m][n][0],locs_sph[m][n][1],v_sph[0],v_sph[1],0);
                for(i=0;i<3;i++){
                    FmTangential[nn][i]=v_cart[i];
                }

                if(verboseTF>4){
                    printf("On type%dmotor%d\n",m,n);
                    printf("    force magnitude before solve is %g\n",F_m_mag[0][0]);
                    printf("    cartesian loc vector is (%g,%g,%g)\n",locs[m][n][0],locs[m][n][1],locs[m][n][2]);
                    printf("    spherical loc vector is (%g,%g)\n",locs_sph[m][n][0],locs_sph[m][n][1]);
                    printf("    cartesian force vector is (%g,%g,%g)\n",F_m_vec[m][n][0],F_m_vec[m][n][1],F_m_vec[m][n][2]);
                    printf("    spherical force vector is (%g,%g,%g)\n",v_sph[0],v_sph[1],v_sph[2]);
                    printf("    radial force vector is (%g,%g,%g)\n    tangential force vector is (%g,%g,%g)\n",FmRadial[nn][0],FmRadial[nn][1],FmRadial[nn][2],FmTangential[nn][0],FmTangential[nn][1],FmTangential[nn][0]);
                }


            }
            else{
                for(i=0;i<3;i++){
                    FmRadial[nn][i]=0;
                    FmTangential[nn][i]=0;
                }
            }
            nn++;
        }
    }
}

void set_brownian_forces_to_0(){


    for(nn=0;nn<N[0]+N[1];nn++){
        //generate_brownian_displacement_anchor();
        for(i=0;i<3;i++){
            Dba[nn][i]=0;
        }
    }

    //generate_brownian_displacement_cargo();
    for(i=0;i<3;i++){
        Dbc[i]=0;
    }

    //generate_brownian_displacement_rotation();
    for(i=0;i<3;i++){
        Rbc[i]=0;
    }
}

void compute_next_locations(){
    switch (MotorDiffusion) {
        case 1: //diffuse all motors by legacy function

            for(m=0;m<2;m++){
                for(n=0;n<N[m];n++){
                    diffuse_sph_one_motor();
                }
            }

            break;

        case 2: //diffuse only motors that aren't bound by legacy function

            for(m=0;m<2;m++){
                for(n=0;n<N[m];n++){
                    if(bound[m][n]==0){
                        diffuse_sph_one_motor();
                    }
                }
            }

            break;

        case 3: //don't diffuse anything, use deterministic equations

            //leave brownian forces set at 0, call stochastic equations
            stochastic_equations();
            break;

        case 4: //diffusion handled by full treatment with drag

            nn=0;
            for(m=0;m<2;m++){
                for(n=0;n<N[m];n++){
                    generate_brownian_displacement_anchor();
                    for(i=0;i<3;i++){
                        Dba[nn][i]=brownian_displacement[i];
                    }
                    nn++;
                }
            }

            generate_brownian_displacement_cargo();
            for(i=0;i<3;i++){
                Dbc[i]=brownian_displacement[i];
            }

            generate_brownian_displacement_rotation();
            for(i=0;i<3;i++){
                Rbc[i]=brownian_displacement[i];
            }

            stochastic_equations();
            break;

        case 5: //anchors diffuse, cargo translation and rotation set to 0

            //set_brownian_forces_to_0();

            nn=0;
            for(m=0;m<2;m++){
                for(n=0;n<N[m];n++){
                    generate_brownian_displacement_anchor();
                    for(i=0;i<3;i++){
                        Dba[nn][i]=brownian_displacement[i];
                    }
                    if(verboseTF>4){
                        printf("brownian displacements generated for motor are (%lf %lf %lf)\n",Dba[nn][0],Dba[nn][1],Dba[nn][2]);
                        printf("locs before solve are (%lf %lf %lf)\n",locs[0][0][0],locs[0][0][1],locs[0][0][2]);
                    }
                    nn++;
                }
            }


            stochastic_equations();
            if(verboseTF>4){
                printf("locs update is (%lf %lf %lf)\n",a1[0][0],a1[0][1],a1[0][2]);
            }
            break;

        case 6: //only cargo translational diffusion

            generate_brownian_displacement_cargo();
            for(i=0;i<3;i++){
                Dbc[i]=brownian_displacement[i];
            }

            stochastic_equations();
            break;

        case 7: //only cargo rotational diffusion

            generate_brownian_displacement_rotation();
            for(i=0;i<3;i++){
                Rbc[i]=brownian_displacement[i];
            }

            stochastic_equations();
            break;

        case 8: //testing for anchor diffusion

            //printf("At beginning, locs is (%lf %lf %lf)\n",locs[0][0][0],locs[0][0][1],locs[0][0][2] );


            for(m=0;m<2;m++){
                for(n=0;n<N[m];n++){
                    diffuse_sph_one_motor();
                }
            }



            for(nn=0;nn<N[0]+N[1];nn++){
                //generate_brownian_displacement_anchor();
                for(i=0;i<3;i++){
                    Dba[nn][i]=brownian_displacement[i];
                    // if(verboseTF>4){
                    //     printf("%lf ",Dba[nn][i]);
                    // }

                }
                printf("brownian displacements generated for motor are (%lf %lf %lf)\n",Dba[nn][0],Dba[nn][1],Dba[nn][2]);
            }

            stochastic_equations();

            if(verboseTF>4){
                printf("stochastic, locs update is (%lf %lf %lf)\n",a1[0][0],a1[0][1],a1[0][2] );
            }

            break;

        case 9: //no anchor diffusion

            generate_brownian_displacement_cargo();
            for(i=0;i<3;i++){
                Dbc[i]=brownian_displacement[i];
            }

            generate_brownian_displacement_rotation();
            for(i=0;i<3;i++){
                Rbc[i]=brownian_displacement[i];
            }

            stochastic_equations();
            break;

        case 10: //bead equations

            generate_brownian_displacement_cargo();
            for(i=0;i<3;i++){
                Dbc[i]=brownian_displacement[i];
            }

            generate_brownian_displacement_rotation();
            for(i=0;i<3;i++){
                Rbc[i]=brownian_displacement[i];
            }

            bead_equations();
            break;

        case 11: //bead equations, deterministic

            bead_equations();
            break;

        // case 12: //attempt to fix motor wandering
        //
        //     generate_brownian_displacement_cargo();
        //     for(i=0;i<3;i++){
        //         Dbc[i]=brownian_displacement[i];
        //     }
        //
        //     generate_brownian_displacement_rotation();
        //     for(i=0;i<3;i++){
        //         Rbc[i]=brownian_displacement[i];
        //     }
        //
        //     bead_equations();
        //
        //     nn=0;
        //     for(m=0;m<2;m++){
        //         for(n=0;n<N[m];n++){
        //             convert_loc_to_spherical();
        //             locs
        //             nn++;
        //         }
        //     }
        //
        //     break;

        default:
            printf("Bad Motor Diffusion type\n");
            exit(0);

    }

    for(i=0;i<3;i++){
        omega[i]=theta1[i]-theta[i];
    }

    //check for error states

    //cargo moving too far is a sign of instability
    if(sqrt( (c1[0]-c[0])*(c1[0]-c[0]) + (c1[1]-c[1])*(c1[1]-c[1]) + (c1[2]-c[2])*(c1[2]-c[2]) ) > R){
        printf("\n\n\nError! Cargo moved >R in one time step!\nExiting gracefully at step %ld\n\n\n",step);
        graceful_exit=1;
    }

    //if rotates greater than pi/5, tan(theta)-theta gets off by >.1
    //this means the difference in the local cartesian distance and distance on the circle is more than 10% off
    if(!graceful_exit && sqrt( (theta1[0]-theta[0])*(theta1[0]-theta[0]) + (theta1[1]-theta[1])*(theta1[1]-theta[1]) + (theta1[2]-theta[2])*(theta1[2]-theta[2]) )> pi/10 ){
            printf("\n\n\nError! Cargo rotated too much in one time step!\nExiting gracefully at step %ld\n\n\n",step);
            graceful_exit=1;
        }

    //if motors move on the cargo more than R*pi/5 radians, local cartesian approximation off by >10%
    for(nn=0;nn<N[0]+N[1];nn++){
        if(!graceful_exit
            && sqrt( (a1[nn][0]-a[nn][0]-(c1[0]-c[0]))*(a1[nn][0]-a[nn][0]-(c1[0]-c[0]))
            + (a1[nn][1]-a[nn][1]-(c1[1]-c[1]))*(a1[nn][1]-a[nn][1]-(c1[1]-c[1]))
            + (a1[nn][2]-a[nn][2]-(c1[2]-c[2]))*(a1[nn][2]-a[nn][2]-(c1[2]-c[2])) )
            > R*pi/10 ){
            printf("\n\n\nError! Motor number %ld moved too much one time step!\nExiting gracefully at step %ld\n\n\n",nn,step);
            graceful_exit=1;
        }
    }

    if(verboseTF>4){
        printf("After solve, we have:\n");
        for(nn=0;nn<N[0]+N[1];nn++){
            printf("    For motor %ld",nn);
            printf(" change in motor location is (%g,%g,%g)\n",a1[nn][0],a1[nn][1],a1[nn][2] );
        }
        printf("\n    Change in cargo location is (%g,%g,%g)\n",c1[0]-c[0],c1[1]-c[1],c1[2]-c[2]);
        printf("    Change in cargo angle is (%g,%g,%g)\n",theta1[0]-theta[0],theta1[1]-theta[1],theta1[2]-theta[2]);
    }

}
