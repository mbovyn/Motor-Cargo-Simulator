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
void countMTviolations(double MTviolationDist);

void setup_solve();
void evaluate_steric();
void calculate_forces();
void calculate_steric();
void set_brownian_forces_to_0();
void compute_next_locations();
void split_forces();

int sumforces();
double cross(double a0,double a1,double a2,double b0,double b1,double b2,int i);

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
    convert_loc_to_spherical(m,n);

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
    convert_loc_to_spherical(m,n);
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

    //force anchor back onto cargo surface
    //legacy version which used spherical conversions
    if(MotorDiffusion<3){
        for(m=0;m<2;m++){
            for(n=0;n<N[m];n++){
                for(i=0;i<3;i++){
                    prior_locs[m][n][i]=locs[m][n][i];
                }
                convert_loc_to_spherical(m,n);
                convert_loc_sph_to_cart();
                move_to_membrane_dist[m][n]=sqrt(
                    pow(prior_locs[m][n][0]-locs[m][n][0],2)+
                    pow(prior_locs[m][n][1]-locs[m][n][1],2)+
                    pow(prior_locs[m][n][1]-locs[m][n][1],2));
                if(move_to_membrane_dist[m][n]>.01){
                    printf("\n\n\nError! Anchor relocation moved type %dmotor%d it %lf microns on step %ld of repeat %d\n\n\n",m,n,move_to_membrane_dist[m][n],step,j);
                    graceful_exit=1;
                }
                //printf("\n\n\nError! Anchor relocation moved type %dmotor%d it %lf microns on step %ld\n\n\n",m,n,move_to_membrane_dist[m][n],step);

                if(verboseTF>4 && MotorDiffusion==8){
                    printf("stochastic, locs final is                         (%lf %lf %lf)\n",locs[m][n][0],locs[m][n][1],locs[m][n][2]);
                }
            }
        }
    }else if(MotorDiffusion>=3 && MotorDiffusion<10){
        //set next locations from solver to current locations
        //and put anchor location back on cargo surface

        double center_to_a_mag;

        nn=0;
        for(m=0;m<2;m++){
            for(n=0;n<N[m];n++){

                //magnitude of vector to calculated next anchor position (a1)
                center_to_a_mag=sqrt(pow(a1[nn][0]-center[0],2)+
                    pow(a1[nn][1]-center[1],2)+pow(a1[nn][2]-center[2],2));

                //check for too large movement
                if(fabs(center_to_a_mag-R)>.01){
                    printf("\n\n\nError! Anchor relocation moved type %dmotor%d it %lf microns on step %ld of repeat %d\n\n\n",m,n,center_to_a_mag,step,j);
                    printf("a1 is (%g,%g,%g), center is (%g,%g,%g)\n",a1[nn][0],a1[nn][1],a1[nn][2],center[0],center[1],center[2]);
                    graceful_exit=1;
                }
                //position on surface=R*(unit vector from c to a1)
                for(i=0;i<3;i++){
                    locs[m][n][i]=center[i]+R*((a1[nn][i]-center[i])/center_to_a_mag);
                }
                nn++;

                if(verboseTF>4 && MotorDiffusion==8){
                    printf("stochastic, locs final is                         (%lf %lf %lf)\n",locs[m][n][0],locs[m][n][1],locs[m][n][2]);
                }
            }
        }
    }else if(MotorDiffusion>=10){

        nn=0;
        for(m=0;m<2;m++){
            for(n=0;n<N[m];n++){

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
    if(verboseTF>3){
        printf("Cargo center at %g,%g,%g\n",center[0],center[1],center[2]);
        printf("Want to move center to %g,%g,%g\n",c1[0],c1[1],c1[2]);
        //for(i=0;i<2;i++){
        //    c1[i]=center[i];
        //}
        //printf("Want to move center to %g,%g,%g\n",c1[0],c1[1],c1[2]);
        //printf("Result should be 0,0,%g\n",center[2]-c1[2]);
    }

    //Sterics for MT
    if(PerfectSterics==2){

      //checked for conflicts with multiple MTs in getInputParams

      //If cargo is inside MT, move the edge up to the MT surface
      //pointToMTdist(center[0],center[1],center[2],0);
      //printf("\nold MTdist is %g\n", MTdist);
      pointToMTdist(c1[0],c1[1],c1[2],0);
      //printf("new MTdist-R is %g\n", MTdist-R);
      //printf("cVector is (%g,%g,%g), with mag %g\n",all3(cVector),mag(cVector) );

      if(MTdist<R){

          //Remove part of movement that is towards the MT

          dp=0;
          for(i=0;i<3;i++){
              dp+=(c1[i]-center[i])*cVector[i];
          }

          for(i=0;i<3;i++){
              c1[i]=c1[i]-(dp/mag(cVector))*(cVector[i]/(mag(cVector)));
              //printf("add to c1 is %g\n", -(dp/mag(cVector))*(cVector[i]/(mag(cVector))));
          }
          nn=0;
          for(m=0;m<2;m++){
              for(n=0;n<N[m];n++){
                  for(i=0;i<3;i++){
                      a1[nn][i]=a1[nn][i]-(dp/mag(cVector))*(cVector[i]/(mag(cVector)));
                      //printf("add to c1 is %g\n", -(dp/mag(cVector))*(cVector[i]/(mag(cVector))));
                  }
                  nn++;
              }
          }

      }

      //pointToMTdist(center[0],center[1],center[2],0);
      //if(R-MTdist>1E-12){
        //printf("Remaining overlap detected of %g\n",MTdist-R);
      //}

      //countMTviolations(magdiff(c1,center));
    }

    switch(CargoBehavior){

        case 1: //transfer all values

            //transfer cargo center
            for(i=0;i<3;i++){
                center[i]=c1[i];
            }

            update_motor_locations();

            break;

        case 2: //implement hard wall at z=0 with perfect sterics

            //transfer cargo center
            for(i=0;i<3;i++){
                center[i]=c1[i];
            }

            update_motor_locations();

            //if cargo is inside the wall
            if(c1[2]-R<0){

                //move cargo center so cargo is outside of surface
                center[2]=R;

                //move motors too
                nn=0;
                for(m=0;m<2;m++){
                    for(n=0;n<N[m];n++){

                        locs[m][n][2]=a1[nn][2]+(center[2]-c1[2]);
                        //printf("center z moved from %g to %g (%g), motor moved from %g to %g (%g)\n",c1[2],center[2],-c1[2]+center[2],a1[nn][2],locs[m][n][2],-a1[nn][2]+locs[m][n][2] );

                        nn++;

                    }
                }

                if(magdiff(c1,center)>.01){
                    printf("\n\nError: Surface sterics moved cargo more than 10nm\n" );
                    exit(4);
                }
            }

            break;

        default:
            printf("\n\nError: Bad value for CargoBehavior\n\n" );
            exit(4);
    }//finished CargoBehavior switch

    if(verboseTF>3){
        printf("Cargo center moved to %g,%g,%g\n",center[0],center[1],center[2]);
    }

    //transfer motor locations to syntax for rest of program
    //and force motors onto surface for free case
    //update_motor_locations();

    //Sterics for MT
    if(PerfectSterics==1){

      //checked for conflicts with multiple MTs in getInputParams

      //If cargo is inside MT, move the edge up to the MT surface
      pointToMTdist(center[0],center[1],center[2],0);



      if(MTdist<R){

          //unless the overlap is huge
          //if(R-MTdist>.01){
              //printf("Error: Cargo more than 10nm inside MT\n");
          //}

        //move the cargo out of the MT by exactly the right amount
        //printf("center z moved from (%g,%g,%g)",all3(center));
        for(i=0;i<3;i++){
          center[i]=center[i]-cVector[i]/MTdist*(R-MTdist);
        }
        //printf(" to (%g,%g,%g)\n",all3(center));
        //printf("cVector is (%g,%g,%g). Overlap is %g\n",all3(cVector),R-MTdist );


        //move motors too
        nn=0;
        for(m=0;m<2;m++){
            for(n=0;n<N[m];n++){
                //printf("motor z moved from %g",locs[m][n][2]);
                for(i=0;i<3;i++){
                  locs[m][n][i]=locs[m][n][i]-cVector[i]/MTdist*(R-MTdist);
                }
                //printf(" to %g\n",locs[m][n][2]);
                nn++;
            }
        }
      }

      //pointToMTdist(center[0],center[1],center[2],0);
      //if(R-MTdist>1E-12){
        //printf("Remaining overlap detected of %g\n",MTdist-R);
      //}

      countMTviolations(magdiff(c1,center));
    }

    //check for anchor off surface
    for(m=0;m<2;m++){
        for(n=0;n<N[m];n++){
            if(!graceful_exit
                && (sqrt( pow(locs[m][n][0]-center[0],2)+pow(locs[m][n][1]-center[1],2)+pow(locs[m][n][2]-center[2],2) ) > R+.005 ||
                 sqrt( pow(locs[m][n][0]-center[0],2)+pow(locs[m][n][1]-center[1],2)+pow(locs[m][n][2]-center[2],2) ) < R-.005)){
                printf("\n\n\nError! Anchor type%dmotor%d more than 5nm off surface!\nExiting gracefully at step %ld\n\n\n",m,n,step);
                graceful_exit=1;
            }
        }
    }

    //check for heads inside cargo
    for(m=0;m<2;m++){
        for(n=0;n<N[m];n++){
            if(!graceful_exit && (magdiff(head[m][n],center) < R-.01)){
                printf("\n\n\nError! Head of type%dmotor%d more than 10nm inside cargo!\nExiting gracefully at step %ld\n\n\n",m,n,step);
                graceful_exit=1;
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

    need_steric=0;

    for(k=0;k<n_MTs;k++){
        pointToMTdist(center[0],center[1],center[2],k);
        if(MTdist<R){
            //set that we need the steric spring so we know to use the smaller timestep
            need_steric=1;
        }
    }

    if(Surface && center[2]<R){
        need_steric=1;
    }

}

void countMTviolations(double MTviolationDist){

    if(MTviolationDist>.005){

        MTviolationCounter[k]++;
        if(verboseTF>2){
            printf("MT %d violation by %g at step %ld. Total violations: %d\n",k,MTviolationDist,step,MTviolationCounter[k]);
        }
        if(MTviolationCounter[k]>5){
            printf("\n\n\nError! MT %d more than 5nm inside cargo for 5 steps!\nExiting gracefully at step %ld\n\n\n",k,step);
            graceful_exit=1;
        }
    }else{
        MTviolationCounter[k]=0;
    }
}

void calculate_steric(){
    //set value of steric force
    //set if we need the steric spring timestep

    //initially set to 0
    for(i=0;i<3;i++){
        Fsteric[i]=0;
    }

    if(verboseTF>3){
        printf("The steric force was found to be:\n");
    }

    //find steric force for each MT
    for(k=0;k<n_MTs;k++){
        pointToMTdist(center[0],center[1],center[2],k);
        if(MTdist<R){
            if(MTdist==0){
                printf("\nError! Center-MT distance is 0. Steric force undefined.\n");
                exit(0);
            }
            //implement the steric force
            Fsterick[k][0]=-kcMT*(R*cVector[0]/MTdist - cVector[0]);
            Fsterick[k][1]=-kcMT*(R*cVector[1]/MTdist - cVector[1]);
            Fsterick[k][2]=-kcMT*(R*cVector[2]/MTdist - cVector[2]);

            countMTviolations(R-MTdist);

            MTdistk[k]=R-MTdist;

        }else{
            MTviolationCounter[k]=0;
            for(i=0;i<3;i++){
                Fsterick[k][i]=0;
            }
            MTdistk[k]=0;
        }

        if(verboseTF>4){
            printf("    MT %d: (%g,%g,%g)\n",
                k+1,Fsterick[k][0],Fsterick[k][1],Fsterick[k][2]);

        }

        //add up forces from each MT into one total steric force
        for(i=0;i<3;i++){
            Fsteric[i]+=Fsterick[k][i];
        }

    }// loop over MTs

    //Steric force from surface
    //only pushes up, engages when the lowest point on the bead is below 0 in z

    if(Surface==1 && center[2]<R){
        Fsteric_surf[0]=0;
        Fsteric_surf[1]=0;
        Fsteric_surf[2]=-kcMT*(center[2]-R);
        //printf("surface force is (%g, %g, %g)\n", Fsteric_surf[0],Fsteric_surf[1],Fsteric_surf[2]);

        //Total steric force
        for(i=0;i<3;i++){
            Fsteric[i]+=Fsteric_surf[i];
        }
    }

    if(verboseTF>3){
        printf("    Total: (%g,%g,%g)\n",
            Fsteric[0],Fsteric[1],Fsteric[2]);
    }

} //evaluate_steric

void calculate_forces() //finds force values for trap, steric, and splits motor forces to radial and tangential
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
            for(i=0;i<3;i++){
                Ftrap[i]=Fin[i];
            }
            break;
        case 3:
            //implement something here for an optical trap
            for(i=0;i<3;i++){
                Ftrap[i]=-Fin[i]*(center[i]-trap_center[i]);
            }
            //printf("Trap force is (%g,%g,%g)\n",Ftrap[0],Ftrap[1],Ftrap[2] );
            break;
        default:
            printf("\n\nError: Bad value for external_force\n\n");
            exit(4);
    }

    if(verboseTF>3){
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
            printf("\n\nError: Bad value for external_force\n\n");
            exit(4);
    }

    if(verboseTF>3){
        printf("The external torque on the cargo is: (%g,%g,%g)\n",
            TorqeExt[0],TorqeExt[1],TorqeExt[2]);
    }

    //split forces into radial and tangential components
    split_forces();

    //(legacy version of)
    //transform force vectors to spherical and split into radial and tangential
    // nn=0;
    // for(m=0;m<2;m++){
    //     for(n=0;n<N[m];n++){
    //         if(bound[m][n]){
    //
    //             convert_loc_to_spherical(m,n);
    //             convert_vec_to_sph(locs_sph[m][n][0],locs_sph[m][n][1],F_m_vec[m][n][0],F_m_vec[m][n][1],F_m_vec[m][n][2]);
    //
    //             convert_vec_to_cart(locs_sph[m][n][0],locs_sph[m][n][1],0,0,v_sph[2]);
    //             for(i=0;i<3;i++){
    //                 FmRadial[nn][i]=v_cart[i];
    //             }
    //             convert_vec_to_cart(locs_sph[m][n][0],locs_sph[m][n][1],v_sph[0],v_sph[1],0);
    //             for(i=0;i<3;i++){
    //                 FmTangential[nn][i]=v_cart[i];
    //             }
    //
    //             if(verboseTF>4){
    //                 printf("On type%dmotor%d\n",m,n);
    //                 printf("    force magnitude before solve is %g\n",F_m_mag[0][0]);
    //                 printf("    cartesian loc vector is (%g,%g,%g)\n",locs[m][n][0],locs[m][n][1],locs[m][n][2]);
    //                 printf("    spherical loc vector is (%g,%g)\n",locs_sph[m][n][0],locs_sph[m][n][1]);
    //                 printf("    cartesian force vector is (%g,%g,%g)\n",F_m_vec[m][n][0],F_m_vec[m][n][1],F_m_vec[m][n][2]);
    //                 printf("    spherical force vector is (%g,%g,%g)\n",v_sph[0],v_sph[1],v_sph[2]);
    //                 printf("    radial force vector is (%g,%g,%g)\n    tangential force vector is (%g,%g,%g)\n",FmRadial[nn][0],FmRadial[nn][1],FmRadial[nn][2],FmTangential[nn][0],FmTangential[nn][1],FmTangential[nn][0]);
    //             }
    //
    //
    //         }
    //         else{
    //             for(i=0;i<3;i++){
    //                 FmRadial[nn][i]=0;
    //                 FmTangential[nn][i]=0;
    //             }
    //         }
    //         nn++;
    //     }
    // }
}//end calculate forces

void split_forces(){

    //double loc_mag;
    double dotprod;

    nn=0;
    for(m=0;m<2;m++){
        for(n=0;n<N[m];n++){
            if(bound[m][n]){

                //find dot product of motor force with radial vector
                //(same as unit vector from center to anchor)
                //gives motor force in radial direction
                //loc_mag=sqrt(pow(locs[m][n][0]-center[0],2)+
                //    pow(locs[m][n][1]-center[1],2)+pow(locs[m][n][2]-center[2],2));
                dotprod=F_m_vec[m][n][0]*((locs[m][n][0]-center[0])/R)+
                    F_m_vec[m][n][1]*((locs[m][n][1]-center[1])/R)+
                    F_m_vec[m][n][2]*((locs[m][n][2]-center[2])/R);

                //then radial force has magnitude proportion*original magnitude
                //and is in radial direction
                //tangential force is difference between the two
                for(i=0;i<3;i++){
                    FmRadial[nn][i]=dotprod*((locs[m][n][i]-center[i])/R);
                    FmTangential[nn][i]=F_m_vec[m][n][i]-FmRadial[nn][i];
                }

                if(verboseTF>4){
                    printf("On type%dmotor%d\n",m,n);
                    printf("    head at (%g,%g,%g) and anchor at (%g,%g,%g)\n",all3(head[m][n]),all3(locs[m][n]) );
                    printf("    stretched by %g\n",magdiff(locs[m][n],head[m][n])-L[m] );
                    printf("    force magnitude before solve is %g\n",F_m_mag[m][n] );
                    printf("    cartesian loc vector is (%g,%g,%g)\n",all3(locs[m][n]) );
                    //printf("    spherical loc vector is (%g,%g)\n",locs_sph[m][n][0],locs_sph[m][n][1]);
                    printf("    cartesian force vector is (%g,%g,%g)\n",all3(F_m_vec[m][n]) );
                    //printf("    spherical force vector is (%g,%g,%g)\n",v_sph[0],v_sph[1],v_sph[2]);
                    printf("    fraction of motor force in radial direction is %g\n",dotprod/F_m_mag[m][n] );
                    printf("    radial force vector is (%g,%g,%g)\n    tangential force vector is (%g,%g,%g)\n",all3(FmRadial[nn]),all3(FmTangential[nn]) );
                }

            }else{
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
            if(verboseTF>3){
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

        case 8: //diffusing cluster

            //kinda hackey, will only work for binding
            //rotational diffusion only

            nn=0;
            //only generate one set of displacements
            generate_brownian_displacement_anchor();
            for(m=0;m<2;m++){
                for(n=0;n<N[m];n++){
                    for(i=0;i<3;i++){
                        Dba[nn][i]=brownian_displacement[i];
                    }
                    nn++;
                }
            }

            //generate_brownian_displacement_cargo();
            //for(i=0;i<3;i++){
            //    Dbc[i]=brownian_displacement[i];
            //}

            generate_brownian_displacement_rotation();
            for(i=0;i<3;i++){
                Rbc[i]=brownian_displacement[i];
            }

            stochastic_equations();
            break;

        case 9: //no cargo translational diffusion

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

        case 12: //bead equations, rotational diffusion only

            generate_brownian_displacement_rotation();
            for(i=0;i<3;i++){
                Rbc[i]=brownian_displacement[i];
            }

            bead_equations();
            break;

        default:
            printf("\n\nError: Bad Motor Diffusion type\n\n");
            exit(4);

    }

    if(MotorDiffusion<10){
        for(i=0;i<3;i++){
            omega[i]=theta1[i]-theta[i];
        }
    }

    //check for error states
    if(isnan(c1[0]) || isnan(c1[1]) || isnan(c1[2]) || isinf(c1[0])| isinf(c1[1]) || isinf(c1[2])){
        printf("\nError! new value of center is (%g,%g,%g) - shouldn't be nan or inf\n",c1[0],c1[1],c1[2]);
        graceful_exit=1;
    }

    //check that sum of forces is close to 0
    if(track_force_balance & (sumforces()>0)){
        printf("\nError! Sum of forces/torques != 0, code %d\nExiting gracefully at step %ld\n\n\n",sumforces(),step);
        graceful_exit=1;
    }

    if(dt_override>=0){
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
                > R*pi/5 ){
                printf("\n\n\nError! Motor number %ld moved too much one time step!\nExiting gracefully at step %ld\n\n\n",nn,step);
                graceful_exit=1;
            }
        }
    }

    if(verboseTF>4){
        printf("After solve, we have:\n");
        for(nn=0;nn<N[0]+N[1];nn++){
            printf("    For motor %ld",nn);
            printf(" change in motor location is (%g,%g,%g)\n",a1[nn][0]-a[nn][0],a1[nn][1]-a[nn][1],a1[nn][2]-a[nn][2] );
        }
        printf("\n    Change in cargo location is (%g,%g,%g)\n",c1[0]-c[0],c1[1]-c[1],c1[2]-c[2]);
        printf("    Change in cargo angle is (%g,%g,%g)\n",theta1[0]-theta[0],theta1[1]-theta[1],theta1[2]-theta[2]);
    }

} //compute_next_locations


int sumforces(){
//Sums all forces and torques, makes sure they balance
//returns 0 if they balance, >0 if they don't

//now acutally calculates F/dt, as divisions by dt were causing floating point issues

    //forces, excluding internal forces
    double fsum;
    //torques, excluding internal torques
    double tsum;

    //forces on anchor
    double msum;
    //forces on cargo (including internal forces)
    double cfsum;
    //torques on cargo (including torques from internal forces)
    double ctsum;

    //Tolerance for how far away from 0 is ok
    double tol=1E-12;

    //make seperate variable to hold drag on anchor since it's annoying to calculate
    double adrag[NMOTORSMAX][3];
    double abrownian[NMOTORSMAX][3];
    //calculate it here
    nn=0;
    for(m=0;m<2;m++){
        for(n=0;n<N[m];n++){
            for(i=0;i<3;i++){
                if(!(MotorDiffusion>=10) && (D_m[m]>1E-12)){
                    // adrag[nn][i]=(1/mu_m[m])*((c1[i]-c[i])/dt+
                    //     cross((theta1[0]-theta[0])/dt,(theta1[1]-theta[1])/dt,(theta1[2]-theta[2])/dt,a[nn][0]-c[0],a[nn][1]-c[1],a[nn][2]-c[2],i)
                    //     -(a1[nn][i]-a[nn][i])/dt);
                    adrag[nn][i]=(1/mu_m[m])*((c1[i]-c[i])+
                        cross((theta1[0]-theta[0]),(theta1[1]-theta[1]),(theta1[2]-theta[2]),a[nn][0]-c[0],a[nn][1]-c[1],a[nn][2]-c[2],i)
                        -(a1[nn][i]-a[nn][i]));
                }else{
                    adrag[nn][i]=NAN;
                    //if motor aren't free, return nan
                    //if D=0, return nan (model not well defined for D=0)
                    //nan fails all checks, so msum, cfsum and ctsum pass
                }
                //printf("adrag[%ld][%d]=%g\n",nn,i,adrag[nn][i] );


                abrownian[nn][i]=sqrt(2*kBT*(1/mu_m[m])*dt)*Dba[nn][i];
            }
            nn++;
        }
    }

    //in each dimension, sum forces
    for(i=0;i<3;i++){

        fsum=0;
        tsum=0;
        cfsum=0;
        ctsum=0;

        //printf("i=%d:\n",i );

        //External force and torque
        fsum+=Ftrap[i]*dt;
        cfsum+=Ftrap[i]*dt;
        //printf("    Ftrap is %g/dt\n",Ftrap[i]*dt );
        tsum+=TorqeExt[i]*dt;
        ctsum+=TorqeExt[i]*dt;
        //printf("    TorqueExt is %g/dt\n",TorqeExt[i]*dt );

        //Steric force
        fsum+=Fsteric[i]*dt;
        cfsum+=Fsteric[i]*dt;
        //printf("    Fsteric is %g/dt\n",Fsteric[i]*dt );

        //cargo drag force and torque
        fsum+=-(c1[i]-c[i])*(1/muCargoTranslation);
        cfsum+=-(c1[i]-c[i])*(1/muCargoTranslation);
        //printf("    Fdrag is %g/dt\n",-(c1[i]-c[i])*(1/muCargoTranslation) );
        tsum+=-(theta1[i]-theta[i])*(1/muCargoRotation);
        ctsum+=-(theta1[i]-theta[i])*(1/muCargoRotation);
        //printf("    Tdrag is %g/dt\n",-(theta1[i]-theta[i])*(1/muCargoRotation) );

        //for each motor
        nn=0;
        for(m=0;m<2;m++){
            for(n=0;n<N[m];n++){

                //motor force and torque
                fsum+=F_m_vec[m][n][i]*dt;
                //printf("    F_m_vec[%d][%d] is %g/dt\n",m,n,F_m_vec[m][n][i]*dt );
                tsum+=cross(locs[m][n][0]-center[0],locs[m][n][1]-center[1],locs[m][n][2]-center[2],F_m_vec[m][n][0]*dt,F_m_vec[m][n][1]*dt,F_m_vec[m][n][2]*dt,i);
                //printf("    Torque from F_m_vec[%d][%d] is %g/dt\n",m,n,cross(locs[m][n][0]-center[0],locs[m][n][1]-center[1],locs[m][n][2]-center[2],F_m_vec[m][n][0]*dt,F_m_vec[m][n][1]*dt,F_m_vec[m][n][2]*dt,i) );

                //radial force
                cfsum+=FmRadial[nn][i]*dt;
                //printf("    FmRadial[%ld] is %g/dt\n",nn,FmRadial[nn][i]*dt );
                //reaction to brownian force on anchor
                cfsum-=sqrt(2*kBT*(1/mu_m[m])*dt)*Dba[nn][i];
                //reaction to drag force on anchor
                cfsum-=adrag[nn][i];

                //torque from reaction to brownian force on anchor
                ctsum-=cross(a[nn][0]-c[0],a[nn][1]-c[1],a[nn][2]-c[2],abrownian[nn][0],abrownian[nn][1],abrownian[nn][2],i);
                //printf("    torque from brownian anchor is %g/dt\n",-cross(a[nn][0]-c[0],a[nn][1]-c[1],a[nn][2]-c[2],abrownian[nn][0],abrownian[nn][1],abrownian[nn][2],i) );
                //torque from reaction to drag force on anchor
                ctsum-=cross(a[nn][0]-c[0],a[nn][1]-c[1],a[nn][2]-c[2],adrag[nn][0],adrag[nn][1],adrag[nn][2],i);
                //printf("    torque from anchor drag is %g/dt\n",-cross(a[nn][0]-c[0],a[nn][1]-c[1],a[nn][2]-c[2],all3(adrag[nn]),i) );


                //on motor anchor

                msum=0;
                //motor force
                msum+=FmTangential[nn][i]*dt;
                //printf("    FmTangential[%ld] is %g/dt\n",nn,FmTangential[nn][i]*dt );
                //brownian force
                msum+=abrownian[nn][i];
                //printf("    brownian force on motor [%ld] is %g/dt\n",nn,abrownian[nn][i] );
                //drag force
                msum+=adrag[nn][i];
                //printf("    Drag on motor [%ld] is %g/dt\n",nn,adrag[nn][i] );

                //printf("    type%dmotor%d/number %ld, msum is %g\n",m,n,nn,msum );

                //check sum of forces on anchor. Return >0 if don't balance
                if(fabs(msum)>tol){
                    printf("type%dmotor%d/number %ld, dim %d\n",m,n,nn,i );
                    printf("    FmTangential[%ld] is %g/dt\n",nn,FmTangential[nn][i]*dt );
                    printf("    brownian force on motor [%ld] is %g/dt\n",nn,abrownian[nn][i] );
                    printf("    Drag on motor [%ld] is %g/dt\n",nn,adrag[nn][i] );
                    //printf("    added %g\n",(adrag[nn][i]+abrownian[nn][i]));
                    //printf("    dt is %g\n",dt);
                    printf("    msum is %g/dt\n",msum );
                    return 5;
                }


                nn++;
            }
        }

        //Brownian force and torque
        fsum+=sqrt(2*kBT*(1/muCargoTranslation)*dt)*Dbc[i];
        cfsum+=sqrt(2*kBT*(1/muCargoTranslation)*dt)*Dbc[i];
        //printf("    Fbrownian is %g/dt\n",sqrt(2*kBT*(1/muCargoTranslation)*dt)*Dbc[i] );
        //if(i==2)
        //    printf("    Fbrownian is %g\n",sqrt(2*kBT*(1/muCargoTranslation)*dt)*Dbc[i]/dt );
        tsum+=sqrt(2*kBT*(1/muCargoRotation)*dt)*Rbc[i];
        ctsum+=sqrt(2*kBT*(1/muCargoRotation)*dt)*Rbc[i];
        //printf("    Tbrownian is %g/dt\n",sqrt(2*kBT*(1/muCargoRotation)*dt)*Rbc[i] );

        //printf("    Fsum is %g/dt\n",fsum );
        //printf("    Tsum is %g/dt\n",tsum );
        //printf("    cfsum is %g/dt\n",cfsum );
        //printf("    ctsum is %g/dt\n",ctsum );
        //printf("\n");

        //Check sums. Return >0 if forces don't balance
        if(fabs(fsum)>tol){
            printf("dim %d\n",i );
            printf("    Fsum is %g/dt\n",fsum );
            return 1;
        }
        if(fabs(tsum)>tol){
            printf("dim %d\n",i );
            printf("    Tsum is %g/dt\n",tsum );
            return 2;
        }
        if(fabs(cfsum)>tol){
            printf("dim %d\n",i );
            printf("    cfsum is %g/dt\n",cfsum );
            return 3;
        }
        if(fabs(ctsum)>tol){
            printf("dim %d\n",i );
            printf("    ctsum is %g/dt\n",ctsum );
            return 4;
        }

    }

    return 0;
}

double cross(double a0,double a1,double a2,double b0,double b1,double b2,int i){

    if(i==0){
        return -a2*b1 + a1*b2;
    }else if(i==1){
        return a2*b0 - a0*b2;
    }else if(i==2){
        return -a1*b0 + a0*b1;
    }else{
        printf("\n\n\nError in cross, i is %d when it should be 0, 1, or 2\n\n\n",i);
        return NAN;
        graceful_exit=1;
    }
}
