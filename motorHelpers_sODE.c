// Prototypes

void diffusion();
void cargobehavior();
//helper helpers
void generate_rand_normal();
void convert_loc_sph_to_cart();
void diffuse_sph_one_motor();
void convert_vec_to_cart(double az,double el,double v_az,double v_el,double v_r);
int do_linalg();

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

    locs[m][n][0]=R*cos(locs_sph[m][n][1])*cos(locs_sph[m][n][0]);
    locs[m][n][1]=R*cos(locs_sph[m][n][1])*sin(locs_sph[m][n][0]);
    locs[m][n][2]=R*sin(locs_sph[m][n][1]);
}

void convert_vec_to_cart(double az,double el,double v_az,double v_el,double v_r){
    //http://www.mathworks.com/help/phased/ref/sph2cartvec.html
    v_cart[0]=-sin(az)*v_az-sin(el)*cos(az)*v_el+cos(el)*cos(az)*v_r;
    v_cart[1]=cos(az)*v_az-sin(el)*sin(az)*v_el+cos(el)*sin(az)*v_r;
    v_cart[2]=cos(el)*v_el+sin(el)*v_r;
}

void diffuse_sph_one_motor(){
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
    //then find distance moved in u and v directions
    du=sqrt(2*D_m[m]*dt)*randn1;
    dv=sqrt(2*D_m[m]*dt)*randn2;
    //convert move anchor by this vector (will go off sphere surface)
    for(i=0;i<3;i++){
        locs[m][n][i]+=du*u_hat[i]+dv*v_hat[i];
    }

    //bring back to sphere surface by converting to spherical and back (fix R)
    convert_loc_to_spherical();
    convert_loc_sph_to_cart();
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

void diffusion()
{
    switch (MotorDiffusion) {
        case 1: //diffuse all motors

            for(n=0;n<N[m];n++){
                diffuse_sph_one_motor();
            }

            break;

        case 2: //diffuse only motors that aren't bound

            for(n=0;n<N[m];n++){
                if(bound[m][n]==0){
                    diffuse_sph_one_motor();
                }
            }

            break;

        case 3: //don't diffuse motors

            //can just sit and do nothing
            break;

        default:
            printf("Bad Motor Diffusion type\n");

    }
} // finished

void cargobehavior()
{
} // finished

int do_linalg()
{
    double a_data[] = { 0.18, 0.60, 0.57, 0.96,
                      0.41, 0.24, 0.99, 0.58,
                      0.14, 0.30, 0.97, 0.66,
                      0.51, 0.13, 0.19, 0.85 };

  double b_data[] = { 1.0, 2.0, 3.0, 4.0 };

  gsl_matrix_view m
    = gsl_matrix_view_array (a_data, 4, 4);

  gsl_vector_view b
    = gsl_vector_view_array (b_data, 4);

  gsl_vector *x = gsl_vector_alloc (4);

  int s;

  gsl_permutation * p = gsl_permutation_alloc (4);

  gsl_linalg_LU_decomp (&m.matrix, p, &s);

  gsl_linalg_LU_solve (&m.matrix, p, &b.vector, x);

  printf ("x = \n");
  gsl_vector_fprintf (stdout, x, "%g");

  gsl_permutation_free (p);
  gsl_vector_free (x);
  return 0;
}
