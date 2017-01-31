//prototypes
void bead_equations();

void bead_equations(){
    switch(total_motors){
        case 1:
            c1[0] = c[0] + sqrt(2)*sqrt(DCargoTranslation)*sqrt(dt)*Dbc[0] + dt*muCargoTranslation*(Fsteric[0] + Ftrap[0] + FmRadial[0][0] + FmTangential[0][0]);

            c1[1] = c[1] + sqrt(2)*sqrt(DCargoTranslation)*sqrt(dt)*Dbc[1] + dt*muCargoTranslation*(Fsteric[1] + Ftrap[1] + FmRadial[0][1] + FmTangential[0][1]);

            c1[2] = c[2] + sqrt(2)*sqrt(DCargoTranslation)*sqrt(dt)*Dbc[2] + dt*muCargoTranslation*(Fsteric[2] + Ftrap[2] + FmRadial[0][2] + FmTangential[0][2]);

            theta1[0] = sqrt(2)*sqrt(DCargoRotation)*sqrt(dt)*Rbc[0] + theta[0] + dt*muCargoRotation*(TorqeExt[0] + c[2]*FmTangential[0][1] - a[0][2]*FmTangential[0][1] - c[1]*FmTangential[0][2] + a[0][1]*FmTangential[0][2]);

            theta1[1] = sqrt(2)*sqrt(DCargoRotation)*sqrt(dt)*Rbc[1] + theta[1] + dt*muCargoRotation*(TorqeExt[1] - c[2]*FmTangential[0][0] + a[0][2]*FmTangential[0][0] + c[0]*FmTangential[0][2] - a[0][0]*FmTangential[0][2]);

            theta1[2] = sqrt(2)*sqrt(DCargoRotation)*sqrt(dt)*Rbc[2] + theta[2] + dt*muCargoRotation*(TorqeExt[2] + c[1]*FmTangential[0][0] - a[0][1]*FmTangential[0][0] - c[0]*FmTangential[0][1] + a[0][0]*FmTangential[0][1]);

            omega[0] = theta1[0]-theta[0];
            omega[1] = theta1[1]-theta[1];
            omega[2] = theta1[2]-theta[2];

            if(sqrt(omega[0]*omega[0] + omega[1]*omega[1] + omega[2]*omega[2])<1E-12){

                a1[0][0] = -c[0] + c1[0] + a[0][0];

                a1[0][1] = -c[1] + c1[1] + a[0][1];

                a1[0][2] = -c[2] + c1[2] + a[0][2];

            }else{

                a1[0][0] = (-(c[0]*pow(omega[0],2)) + c1[0]*pow(omega[0],2) - c[1]*omega[0]*omega[1] + c1[0]*pow(omega[1],2) - c[2]*omega[0]*omega[2] + c1[0]*pow(omega[2],2) + pow(omega[0],2)*a[0][0] + omega[0]*omega[1]*a[0][1] + omega[0]*omega[2]*a[0][2] - sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))*sin(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)))*(c[2]*omega[1] - c[1]*omega[2] + omega[2]*a[0][1] - omega[1]*a[0][2]) + cos(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)))*(c[1]*omega[0]*omega[1] + c[2]*omega[0]*omega[2] - c[0]*(pow(omega[1],2) + pow(omega[2],2)) + pow(omega[1],2)*a[0][0] + pow(omega[2],2)*a[0][0] - omega[0]*omega[1]*a[0][1] - omega[0]*omega[2]*a[0][2]))/(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2));

                a1[0][1] = (c1[1]*pow(omega[0],2) - c[0]*omega[0]*omega[1] - c[1]*pow(omega[1],2) + c1[1]*pow(omega[1],2) - c[2]*omega[1]*omega[2] + c1[1]*pow(omega[2],2) + omega[0]*omega[1]*a[0][0] + pow(omega[1],2)*a[0][1] + omega[1]*omega[2]*a[0][2] + sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))*sin(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)))*(c[2]*omega[0] - c[0]*omega[2] + omega[2]*a[0][0] - omega[0]*a[0][2]) + cos(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)))*(c[0]*omega[0]*omega[1] + c[2]*omega[1]*omega[2] - c[1]*(pow(omega[0],2) + pow(omega[2],2)) - omega[0]*omega[1]*a[0][0] + pow(omega[0],2)*a[0][1] + pow(omega[2],2)*a[0][1] - omega[1]*omega[2]*a[0][2]))/(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2));

                a1[0][2] = (c1[2]*(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)) + ((-1 + cos(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))))*omega[0]*omega[2] + omega[1]*sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))*sin(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))))*(c[0] - a[0][0]) - 2*sin(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))/2.)*(cos(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))/2.)*omega[0]*sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)) + omega[1]*omega[2]*sin(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))/2.))*(c[1] - a[0][1]) - (cos(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)))*(pow(omega[0],2) + pow(omega[1],2)) + pow(omega[2],2))*(c[2] - a[0][2]))/(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2));

            }

            break;

        case 2:
            c1[0] = c[0] + sqrt(2)*sqrt(DCargoTranslation)*sqrt(dt)*Dbc[0] + dt*muCargoTranslation*(Fsteric[0] + Ftrap[0] + FmRadial[0][0] + FmRadial[1][0] + FmTangential[0][0] + FmTangential[1][0]);

            c1[1] = c[1] + sqrt(2)*sqrt(DCargoTranslation)*sqrt(dt)*Dbc[1] + dt*muCargoTranslation*(Fsteric[1] + Ftrap[1] + FmRadial[0][1] + FmRadial[1][1] + FmTangential[0][1] + FmTangential[1][1]);

            c1[2] = c[2] + sqrt(2)*sqrt(DCargoTranslation)*sqrt(dt)*Dbc[2] + dt*muCargoTranslation*(Fsteric[2] + Ftrap[2] + FmRadial[0][2] + FmRadial[1][2] + FmTangential[0][2] + FmTangential[1][2]);

            theta1[0] = sqrt(2)*sqrt(DCargoRotation)*sqrt(dt)*Rbc[0] + theta[0] + dt*muCargoRotation*(TorqeExt[0] - a[0][2]*FmTangential[0][1] - c[1]*FmTangential[0][2] + a[0][1]*FmTangential[0][2] - a[1][2]*FmTangential[1][1] + c[2]*(FmTangential[0][1] + FmTangential[1][1]) - c[1]*FmTangential[1][2] + a[1][1]*FmTangential[1][2]);

            theta1[1] = sqrt(2)*sqrt(DCargoRotation)*sqrt(dt)*Rbc[1] + theta[1] + dt*muCargoRotation*(TorqeExt[1] + a[0][2]*FmTangential[0][0] + c[0]*FmTangential[0][2] - a[0][0]*FmTangential[0][2] + a[1][2]*FmTangential[1][0] - c[2]*(FmTangential[0][0] + FmTangential[1][0]) + c[0]*FmTangential[1][2] - a[1][0]*FmTangential[1][2]);

            theta1[2] = sqrt(2)*sqrt(DCargoRotation)*sqrt(dt)*Rbc[2] + theta[2] + dt*muCargoRotation*(TorqeExt[2] - a[0][1]*FmTangential[0][0] - c[0]*FmTangential[0][1] + a[0][0]*FmTangential[0][1] - a[1][1]*FmTangential[1][0] + c[1]*(FmTangential[0][0] + FmTangential[1][0]) - c[0]*FmTangential[1][1] + a[1][0]*FmTangential[1][1]);

            omega[0] = theta1[0]-theta[0];
            omega[1] = theta1[1]-theta[1];
            omega[2] = theta1[2]-theta[2];

            if(sqrt(omega[0]*omega[0] + omega[1]*omega[1] + omega[2]*omega[2])<1E-12){

                a1[0][0] = -c[0] + c1[0] + a[0][0];

                a1[0][1] = -c[1] + c1[1] + a[0][1];

                a1[0][2] = -c[2] + c1[2] + a[0][2];

                a1[1][0] = -c[0] + c1[0] + a[1][0];

                a1[1][1] = -c[1] + c1[1] + a[1][1];

                a1[1][2] = -c[2] + c1[2] + a[1][2];

            }else{

                a1[0][0] = (-(c[0]*pow(omega[0],2)) + c1[0]*pow(omega[0],2) - c[1]*omega[0]*omega[1] + c1[0]*pow(omega[1],2) - c[2]*omega[0]*omega[2] + c1[0]*pow(omega[2],2) + pow(omega[0],2)*a[0][0] + omega[0]*omega[1]*a[0][1] + omega[0]*omega[2]*a[0][2] - sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))*sin(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)))*(c[2]*omega[1] - c[1]*omega[2] + omega[2]*a[0][1] - omega[1]*a[0][2]) + cos(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)))*(c[1]*omega[0]*omega[1] + c[2]*omega[0]*omega[2] - c[0]*(pow(omega[1],2) + pow(omega[2],2)) + pow(omega[1],2)*a[0][0] + pow(omega[2],2)*a[0][0] - omega[0]*omega[1]*a[0][1] - omega[0]*omega[2]*a[0][2]))/(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2));

                a1[0][1] = (c1[1]*pow(omega[0],2) - c[0]*omega[0]*omega[1] - c[1]*pow(omega[1],2) + c1[1]*pow(omega[1],2) - c[2]*omega[1]*omega[2] + c1[1]*pow(omega[2],2) + omega[0]*omega[1]*a[0][0] + pow(omega[1],2)*a[0][1] + omega[1]*omega[2]*a[0][2] + sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))*sin(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)))*(c[2]*omega[0] - c[0]*omega[2] + omega[2]*a[0][0] - omega[0]*a[0][2]) + cos(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)))*(c[0]*omega[0]*omega[1] + c[2]*omega[1]*omega[2] - c[1]*(pow(omega[0],2) + pow(omega[2],2)) - omega[0]*omega[1]*a[0][0] + pow(omega[0],2)*a[0][1] + pow(omega[2],2)*a[0][1] - omega[1]*omega[2]*a[0][2]))/(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2));

                a1[0][2] = (c1[2]*(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)) + ((-1 + cos(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))))*omega[0]*omega[2] + omega[1]*sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))*sin(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))))*(c[0] - a[0][0]) - 2*sin(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))/2.)*(cos(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))/2.)*omega[0]*sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)) + omega[1]*omega[2]*sin(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))/2.))*(c[1] - a[0][1]) - (cos(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)))*(pow(omega[0],2) + pow(omega[1],2)) + pow(omega[2],2))*(c[2] - a[0][2]))/(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2));

                a1[1][0] = (-(c[0]*pow(omega[0],2)) + c1[0]*pow(omega[0],2) - c[1]*omega[0]*omega[1] + c1[0]*pow(omega[1],2) - c[2]*omega[0]*omega[2] + c1[0]*pow(omega[2],2) + pow(omega[0],2)*a[1][0] + omega[0]*omega[1]*a[1][1] + omega[0]*omega[2]*a[1][2] - sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))*sin(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)))*(c[2]*omega[1] - c[1]*omega[2] + omega[2]*a[1][1] - omega[1]*a[1][2]) + cos(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)))*(c[1]*omega[0]*omega[1] + c[2]*omega[0]*omega[2] - c[0]*(pow(omega[1],2) + pow(omega[2],2)) + pow(omega[1],2)*a[1][0] + pow(omega[2],2)*a[1][0] - omega[0]*omega[1]*a[1][1] - omega[0]*omega[2]*a[1][2]))/(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2));

                a1[1][1] = (c1[1]*pow(omega[0],2) - c[0]*omega[0]*omega[1] - c[1]*pow(omega[1],2) + c1[1]*pow(omega[1],2) - c[2]*omega[1]*omega[2] + c1[1]*pow(omega[2],2) + omega[0]*omega[1]*a[1][0] + pow(omega[1],2)*a[1][1] + omega[1]*omega[2]*a[1][2] + sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))*sin(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)))*(c[2]*omega[0] - c[0]*omega[2] + omega[2]*a[1][0] - omega[0]*a[1][2]) + cos(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)))*(c[0]*omega[0]*omega[1] + c[2]*omega[1]*omega[2] - c[1]*(pow(omega[0],2) + pow(omega[2],2)) - omega[0]*omega[1]*a[1][0] + pow(omega[0],2)*a[1][1] + pow(omega[2],2)*a[1][1] - omega[1]*omega[2]*a[1][2]))/(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2));

                a1[1][2] = (c1[2]*(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)) + ((-1 + cos(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))))*omega[0]*omega[2] + omega[1]*sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))*sin(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))))*(c[0] - a[1][0]) - 2*sin(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))/2.)*(cos(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))/2.)*omega[0]*sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)) + omega[1]*omega[2]*sin(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))/2.))*(c[1] - a[1][1]) - (cos(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)))*(pow(omega[0],2) + pow(omega[1],2)) + pow(omega[2],2))*(c[2] - a[1][2]))/(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2));

            }

            break;

        case 3:
            c1[0] = c[0] + sqrt(2)*sqrt(DCargoTranslation)*sqrt(dt)*Dbc[0] + dt*muCargoTranslation*(Fsteric[0] + Ftrap[0] + FmRadial[0][0] + FmRadial[1][0] + FmRadial[2][0] + FmTangential[0][0] + FmTangential[1][0] + FmTangential[2][0]);

            c1[1] = c[1] + sqrt(2)*sqrt(DCargoTranslation)*sqrt(dt)*Dbc[1] + dt*muCargoTranslation*(Fsteric[1] + Ftrap[1] + FmRadial[0][1] + FmRadial[1][1] + FmRadial[2][1] + FmTangential[0][1] + FmTangential[1][1] + FmTangential[2][1]);

            c1[2] = c[2] + sqrt(2)*sqrt(DCargoTranslation)*sqrt(dt)*Dbc[2] + dt*muCargoTranslation*(Fsteric[2] + Ftrap[2] + FmRadial[0][2] + FmRadial[1][2] + FmRadial[2][2] + FmTangential[0][2] + FmTangential[1][2] + FmTangential[2][2]);

            theta1[0] = sqrt(2)*sqrt(DCargoRotation)*sqrt(dt)*Rbc[0] + theta[0] + dt*muCargoRotation*(TorqeExt[0] - a[0][2]*FmTangential[0][1] - c[1]*FmTangential[0][2] + a[0][1]*FmTangential[0][2] - a[1][2]*FmTangential[1][1] - c[1]*FmTangential[1][2] + a[1][1]*FmTangential[1][2] - a[2][2]*FmTangential[2][1] + c[2]*(FmTangential[0][1] + FmTangential[1][1] + FmTangential[2][1]) - c[1]*FmTangential[2][2] + a[2][1]*FmTangential[2][2]);

            theta1[1] = sqrt(2)*sqrt(DCargoRotation)*sqrt(dt)*Rbc[1] + theta[1] + dt*muCargoRotation*(TorqeExt[1] + a[0][2]*FmTangential[0][0] + c[0]*FmTangential[0][2] - a[0][0]*FmTangential[0][2] + a[1][2]*FmTangential[1][0] + c[0]*FmTangential[1][2] - a[1][0]*FmTangential[1][2] + a[2][2]*FmTangential[2][0] - c[2]*(FmTangential[0][0] + FmTangential[1][0] + FmTangential[2][0]) + c[0]*FmTangential[2][2] - a[2][0]*FmTangential[2][2]);

            theta1[2] = sqrt(2)*sqrt(DCargoRotation)*sqrt(dt)*Rbc[2] + theta[2] + dt*muCargoRotation*(TorqeExt[2] - a[0][1]*FmTangential[0][0] - c[0]*FmTangential[0][1] + a[0][0]*FmTangential[0][1] - a[1][1]*FmTangential[1][0] - c[0]*FmTangential[1][1] + a[1][0]*FmTangential[1][1] - a[2][1]*FmTangential[2][0] + c[1]*(FmTangential[0][0] + FmTangential[1][0] + FmTangential[2][0]) - c[0]*FmTangential[2][1] + a[2][0]*FmTangential[2][1]);

            omega[0] = theta1[0]-theta[0];
            omega[1] = theta1[1]-theta[1];
            omega[2] = theta1[2]-theta[2];

            if(sqrt(omega[0]*omega[0] + omega[1]*omega[1] + omega[2]*omega[2])<1E-12){

                a1[0][0] = -c[0] + c1[0] + a[0][0];

                a1[0][1] = -c[1] + c1[1] + a[0][1];

                a1[0][2] = -c[2] + c1[2] + a[0][2];

                a1[1][0] = -c[0] + c1[0] + a[1][0];

                a1[1][1] = -c[1] + c1[1] + a[1][1];

                a1[1][2] = -c[2] + c1[2] + a[1][2];

                a1[2][0] = -c[0] + c1[0] + a[2][0];

                a1[2][1] = -c[1] + c1[1] + a[2][1];

                a1[2][2] = -c[2] + c1[2] + a[2][2];

            }else{

                a1[0][0] = (-(c[0]*pow(omega[0],2)) + c1[0]*pow(omega[0],2) - c[1]*omega[0]*omega[1] + c1[0]*pow(omega[1],2) - c[2]*omega[0]*omega[2] + c1[0]*pow(omega[2],2) + pow(omega[0],2)*a[0][0] + omega[0]*omega[1]*a[0][1] + omega[0]*omega[2]*a[0][2] - sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))*sin(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)))*(c[2]*omega[1] - c[1]*omega[2] + omega[2]*a[0][1] - omega[1]*a[0][2]) + cos(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)))*(c[1]*omega[0]*omega[1] + c[2]*omega[0]*omega[2] - c[0]*(pow(omega[1],2) + pow(omega[2],2)) + pow(omega[1],2)*a[0][0] + pow(omega[2],2)*a[0][0] - omega[0]*omega[1]*a[0][1] - omega[0]*omega[2]*a[0][2]))/(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2));

                a1[0][1] = (c1[1]*pow(omega[0],2) - c[0]*omega[0]*omega[1] - c[1]*pow(omega[1],2) + c1[1]*pow(omega[1],2) - c[2]*omega[1]*omega[2] + c1[1]*pow(omega[2],2) + omega[0]*omega[1]*a[0][0] + pow(omega[1],2)*a[0][1] + omega[1]*omega[2]*a[0][2] + sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))*sin(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)))*(c[2]*omega[0] - c[0]*omega[2] + omega[2]*a[0][0] - omega[0]*a[0][2]) + cos(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)))*(c[0]*omega[0]*omega[1] + c[2]*omega[1]*omega[2] - c[1]*(pow(omega[0],2) + pow(omega[2],2)) - omega[0]*omega[1]*a[0][0] + pow(omega[0],2)*a[0][1] + pow(omega[2],2)*a[0][1] - omega[1]*omega[2]*a[0][2]))/(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2));

                a1[0][2] = (c1[2]*(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)) + ((-1 + cos(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))))*omega[0]*omega[2] + omega[1]*sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))*sin(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))))*(c[0] - a[0][0]) - 2*sin(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))/2.)*(cos(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))/2.)*omega[0]*sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)) + omega[1]*omega[2]*sin(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))/2.))*(c[1] - a[0][1]) - (cos(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)))*(pow(omega[0],2) + pow(omega[1],2)) + pow(omega[2],2))*(c[2] - a[0][2]))/(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2));

                a1[1][0] = (-(c[0]*pow(omega[0],2)) + c1[0]*pow(omega[0],2) - c[1]*omega[0]*omega[1] + c1[0]*pow(omega[1],2) - c[2]*omega[0]*omega[2] + c1[0]*pow(omega[2],2) + pow(omega[0],2)*a[1][0] + omega[0]*omega[1]*a[1][1] + omega[0]*omega[2]*a[1][2] - sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))*sin(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)))*(c[2]*omega[1] - c[1]*omega[2] + omega[2]*a[1][1] - omega[1]*a[1][2]) + cos(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)))*(c[1]*omega[0]*omega[1] + c[2]*omega[0]*omega[2] - c[0]*(pow(omega[1],2) + pow(omega[2],2)) + pow(omega[1],2)*a[1][0] + pow(omega[2],2)*a[1][0] - omega[0]*omega[1]*a[1][1] - omega[0]*omega[2]*a[1][2]))/(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2));

                a1[1][1] = (c1[1]*pow(omega[0],2) - c[0]*omega[0]*omega[1] - c[1]*pow(omega[1],2) + c1[1]*pow(omega[1],2) - c[2]*omega[1]*omega[2] + c1[1]*pow(omega[2],2) + omega[0]*omega[1]*a[1][0] + pow(omega[1],2)*a[1][1] + omega[1]*omega[2]*a[1][2] + sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))*sin(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)))*(c[2]*omega[0] - c[0]*omega[2] + omega[2]*a[1][0] - omega[0]*a[1][2]) + cos(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)))*(c[0]*omega[0]*omega[1] + c[2]*omega[1]*omega[2] - c[1]*(pow(omega[0],2) + pow(omega[2],2)) - omega[0]*omega[1]*a[1][0] + pow(omega[0],2)*a[1][1] + pow(omega[2],2)*a[1][1] - omega[1]*omega[2]*a[1][2]))/(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2));

                a1[1][2] = (c1[2]*(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)) + ((-1 + cos(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))))*omega[0]*omega[2] + omega[1]*sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))*sin(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))))*(c[0] - a[1][0]) - 2*sin(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))/2.)*(cos(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))/2.)*omega[0]*sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)) + omega[1]*omega[2]*sin(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))/2.))*(c[1] - a[1][1]) - (cos(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)))*(pow(omega[0],2) + pow(omega[1],2)) + pow(omega[2],2))*(c[2] - a[1][2]))/(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2));

                a1[2][0] = (-(c[0]*pow(omega[0],2)) + c1[0]*pow(omega[0],2) - c[1]*omega[0]*omega[1] + c1[0]*pow(omega[1],2) - c[2]*omega[0]*omega[2] + c1[0]*pow(omega[2],2) + pow(omega[0],2)*a[2][0] + omega[0]*omega[1]*a[2][1] + omega[0]*omega[2]*a[2][2] - sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))*sin(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)))*(c[2]*omega[1] - c[1]*omega[2] + omega[2]*a[2][1] - omega[1]*a[2][2]) + cos(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)))*(c[1]*omega[0]*omega[1] + c[2]*omega[0]*omega[2] - c[0]*(pow(omega[1],2) + pow(omega[2],2)) + pow(omega[1],2)*a[2][0] + pow(omega[2],2)*a[2][0] - omega[0]*omega[1]*a[2][1] - omega[0]*omega[2]*a[2][2]))/(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2));

                a1[2][1] = (c1[1]*pow(omega[0],2) - c[0]*omega[0]*omega[1] - c[1]*pow(omega[1],2) + c1[1]*pow(omega[1],2) - c[2]*omega[1]*omega[2] + c1[1]*pow(omega[2],2) + omega[0]*omega[1]*a[2][0] + pow(omega[1],2)*a[2][1] + omega[1]*omega[2]*a[2][2] + sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))*sin(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)))*(c[2]*omega[0] - c[0]*omega[2] + omega[2]*a[2][0] - omega[0]*a[2][2]) + cos(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)))*(c[0]*omega[0]*omega[1] + c[2]*omega[1]*omega[2] - c[1]*(pow(omega[0],2) + pow(omega[2],2)) - omega[0]*omega[1]*a[2][0] + pow(omega[0],2)*a[2][1] + pow(omega[2],2)*a[2][1] - omega[1]*omega[2]*a[2][2]))/(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2));

                a1[2][2] = (c1[2]*(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)) + ((-1 + cos(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))))*omega[0]*omega[2] + omega[1]*sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))*sin(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))))*(c[0] - a[2][0]) - 2*sin(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))/2.)*(cos(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))/2.)*omega[0]*sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)) + omega[1]*omega[2]*sin(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))/2.))*(c[1] - a[2][1]) - (cos(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)))*(pow(omega[0],2) + pow(omega[1],2)) + pow(omega[2],2))*(c[2] - a[2][2]))/(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2));

            }

            break;

        case 4:
            c1[0] = c[0] + sqrt(2)*sqrt(DCargoTranslation)*sqrt(dt)*Dbc[0] + dt*muCargoTranslation*(Fsteric[0] + Ftrap[0] + FmRadial[0][0] + FmRadial[1][0] + FmRadial[2][0] + FmRadial[3][0] + FmTangential[0][0] + FmTangential[1][0] + FmTangential[2][0] + FmTangential[3][0]);

            c1[1] = c[1] + sqrt(2)*sqrt(DCargoTranslation)*sqrt(dt)*Dbc[1] + dt*muCargoTranslation*(Fsteric[1] + Ftrap[1] + FmRadial[0][1] + FmRadial[1][1] + FmRadial[2][1] + FmRadial[3][1] + FmTangential[0][1] + FmTangential[1][1] + FmTangential[2][1] + FmTangential[3][1]);

            c1[2] = c[2] + sqrt(2)*sqrt(DCargoTranslation)*sqrt(dt)*Dbc[2] + dt*muCargoTranslation*(Fsteric[2] + Ftrap[2] + FmRadial[0][2] + FmRadial[1][2] + FmRadial[2][2] + FmRadial[3][2] + FmTangential[0][2] + FmTangential[1][2] + FmTangential[2][2] + FmTangential[3][2]);

            theta1[0] = sqrt(2)*sqrt(DCargoRotation)*sqrt(dt)*Rbc[0] + theta[0] + dt*muCargoRotation*(TorqeExt[0] - a[0][2]*FmTangential[0][1] - c[1]*FmTangential[0][2] + a[0][1]*FmTangential[0][2] - a[1][2]*FmTangential[1][1] - c[1]*FmTangential[1][2] + a[1][1]*FmTangential[1][2] - a[2][2]*FmTangential[2][1] - c[1]*FmTangential[2][2] + a[2][1]*FmTangential[2][2] - a[3][2]*FmTangential[3][1] + c[2]*(FmTangential[0][1] + FmTangential[1][1] + FmTangential[2][1] + FmTangential[3][1]) - c[1]*FmTangential[3][2] + a[3][1]*FmTangential[3][2]);

            theta1[1] = sqrt(2)*sqrt(DCargoRotation)*sqrt(dt)*Rbc[1] + theta[1] + dt*muCargoRotation*(TorqeExt[1] + a[0][2]*FmTangential[0][0] + c[0]*FmTangential[0][2] - a[0][0]*FmTangential[0][2] + a[1][2]*FmTangential[1][0] + c[0]*FmTangential[1][2] - a[1][0]*FmTangential[1][2] + a[2][2]*FmTangential[2][0] + c[0]*FmTangential[2][2] - a[2][0]*FmTangential[2][2] + a[3][2]*FmTangential[3][0] - c[2]*(FmTangential[0][0] + FmTangential[1][0] + FmTangential[2][0] + FmTangential[3][0]) + c[0]*FmTangential[3][2] - a[3][0]*FmTangential[3][2]);

            theta1[2] = sqrt(2)*sqrt(DCargoRotation)*sqrt(dt)*Rbc[2] + theta[2] + dt*muCargoRotation*(TorqeExt[2] - a[0][1]*FmTangential[0][0] - c[0]*FmTangential[0][1] + a[0][0]*FmTangential[0][1] - a[1][1]*FmTangential[1][0] - c[0]*FmTangential[1][1] + a[1][0]*FmTangential[1][1] - a[2][1]*FmTangential[2][0] - c[0]*FmTangential[2][1] + a[2][0]*FmTangential[2][1] - a[3][1]*FmTangential[3][0] + c[1]*(FmTangential[0][0] + FmTangential[1][0] + FmTangential[2][0] + FmTangential[3][0]) - c[0]*FmTangential[3][1] + a[3][0]*FmTangential[3][1]);

            omega[0] = theta1[0]-theta[0];
            omega[1] = theta1[1]-theta[1];
            omega[2] = theta1[2]-theta[2];

            if(sqrt(omega[0]*omega[0] + omega[1]*omega[1] + omega[2]*omega[2])<1E-12){

                a1[0][0] = -c[0] + c1[0] + a[0][0];

                a1[0][1] = -c[1] + c1[1] + a[0][1];

                a1[0][2] = -c[2] + c1[2] + a[0][2];

                a1[1][0] = -c[0] + c1[0] + a[1][0];

                a1[1][1] = -c[1] + c1[1] + a[1][1];

                a1[1][2] = -c[2] + c1[2] + a[1][2];

                a1[2][0] = -c[0] + c1[0] + a[2][0];

                a1[2][1] = -c[1] + c1[1] + a[2][1];

                a1[2][2] = -c[2] + c1[2] + a[2][2];

                a1[3][0] = -c[0] + c1[0] + a[3][0];

                a1[3][1] = -c[1] + c1[1] + a[3][1];

                a1[3][2] = -c[2] + c1[2] + a[3][2];

            }else{

                a1[0][0] = (-(c[0]*pow(omega[0],2)) + c1[0]*pow(omega[0],2) - c[1]*omega[0]*omega[1] + c1[0]*pow(omega[1],2) - c[2]*omega[0]*omega[2] + c1[0]*pow(omega[2],2) + pow(omega[0],2)*a[0][0] + omega[0]*omega[1]*a[0][1] + omega[0]*omega[2]*a[0][2] - sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))*sin(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)))*(c[2]*omega[1] - c[1]*omega[2] + omega[2]*a[0][1] - omega[1]*a[0][2]) + cos(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)))*(c[1]*omega[0]*omega[1] + c[2]*omega[0]*omega[2] - c[0]*(pow(omega[1],2) + pow(omega[2],2)) + pow(omega[1],2)*a[0][0] + pow(omega[2],2)*a[0][0] - omega[0]*omega[1]*a[0][1] - omega[0]*omega[2]*a[0][2]))/(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2));

                a1[0][1] = (c1[1]*pow(omega[0],2) - c[0]*omega[0]*omega[1] - c[1]*pow(omega[1],2) + c1[1]*pow(omega[1],2) - c[2]*omega[1]*omega[2] + c1[1]*pow(omega[2],2) + omega[0]*omega[1]*a[0][0] + pow(omega[1],2)*a[0][1] + omega[1]*omega[2]*a[0][2] + sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))*sin(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)))*(c[2]*omega[0] - c[0]*omega[2] + omega[2]*a[0][0] - omega[0]*a[0][2]) + cos(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)))*(c[0]*omega[0]*omega[1] + c[2]*omega[1]*omega[2] - c[1]*(pow(omega[0],2) + pow(omega[2],2)) - omega[0]*omega[1]*a[0][0] + pow(omega[0],2)*a[0][1] + pow(omega[2],2)*a[0][1] - omega[1]*omega[2]*a[0][2]))/(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2));

                a1[0][2] = (c1[2]*(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)) + ((-1 + cos(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))))*omega[0]*omega[2] + omega[1]*sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))*sin(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))))*(c[0] - a[0][0]) - 2*sin(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))/2.)*(cos(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))/2.)*omega[0]*sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)) + omega[1]*omega[2]*sin(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))/2.))*(c[1] - a[0][1]) - (cos(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)))*(pow(omega[0],2) + pow(omega[1],2)) + pow(omega[2],2))*(c[2] - a[0][2]))/(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2));

                a1[1][0] = (-(c[0]*pow(omega[0],2)) + c1[0]*pow(omega[0],2) - c[1]*omega[0]*omega[1] + c1[0]*pow(omega[1],2) - c[2]*omega[0]*omega[2] + c1[0]*pow(omega[2],2) + pow(omega[0],2)*a[1][0] + omega[0]*omega[1]*a[1][1] + omega[0]*omega[2]*a[1][2] - sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))*sin(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)))*(c[2]*omega[1] - c[1]*omega[2] + omega[2]*a[1][1] - omega[1]*a[1][2]) + cos(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)))*(c[1]*omega[0]*omega[1] + c[2]*omega[0]*omega[2] - c[0]*(pow(omega[1],2) + pow(omega[2],2)) + pow(omega[1],2)*a[1][0] + pow(omega[2],2)*a[1][0] - omega[0]*omega[1]*a[1][1] - omega[0]*omega[2]*a[1][2]))/(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2));

                a1[1][1] = (c1[1]*pow(omega[0],2) - c[0]*omega[0]*omega[1] - c[1]*pow(omega[1],2) + c1[1]*pow(omega[1],2) - c[2]*omega[1]*omega[2] + c1[1]*pow(omega[2],2) + omega[0]*omega[1]*a[1][0] + pow(omega[1],2)*a[1][1] + omega[1]*omega[2]*a[1][2] + sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))*sin(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)))*(c[2]*omega[0] - c[0]*omega[2] + omega[2]*a[1][0] - omega[0]*a[1][2]) + cos(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)))*(c[0]*omega[0]*omega[1] + c[2]*omega[1]*omega[2] - c[1]*(pow(omega[0],2) + pow(omega[2],2)) - omega[0]*omega[1]*a[1][0] + pow(omega[0],2)*a[1][1] + pow(omega[2],2)*a[1][1] - omega[1]*omega[2]*a[1][2]))/(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2));

                a1[1][2] = (c1[2]*(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)) + ((-1 + cos(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))))*omega[0]*omega[2] + omega[1]*sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))*sin(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))))*(c[0] - a[1][0]) - 2*sin(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))/2.)*(cos(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))/2.)*omega[0]*sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)) + omega[1]*omega[2]*sin(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))/2.))*(c[1] - a[1][1]) - (cos(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)))*(pow(omega[0],2) + pow(omega[1],2)) + pow(omega[2],2))*(c[2] - a[1][2]))/(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2));

                a1[2][0] = (-(c[0]*pow(omega[0],2)) + c1[0]*pow(omega[0],2) - c[1]*omega[0]*omega[1] + c1[0]*pow(omega[1],2) - c[2]*omega[0]*omega[2] + c1[0]*pow(omega[2],2) + pow(omega[0],2)*a[2][0] + omega[0]*omega[1]*a[2][1] + omega[0]*omega[2]*a[2][2] - sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))*sin(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)))*(c[2]*omega[1] - c[1]*omega[2] + omega[2]*a[2][1] - omega[1]*a[2][2]) + cos(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)))*(c[1]*omega[0]*omega[1] + c[2]*omega[0]*omega[2] - c[0]*(pow(omega[1],2) + pow(omega[2],2)) + pow(omega[1],2)*a[2][0] + pow(omega[2],2)*a[2][0] - omega[0]*omega[1]*a[2][1] - omega[0]*omega[2]*a[2][2]))/(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2));

                a1[2][1] = (c1[1]*pow(omega[0],2) - c[0]*omega[0]*omega[1] - c[1]*pow(omega[1],2) + c1[1]*pow(omega[1],2) - c[2]*omega[1]*omega[2] + c1[1]*pow(omega[2],2) + omega[0]*omega[1]*a[2][0] + pow(omega[1],2)*a[2][1] + omega[1]*omega[2]*a[2][2] + sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))*sin(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)))*(c[2]*omega[0] - c[0]*omega[2] + omega[2]*a[2][0] - omega[0]*a[2][2]) + cos(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)))*(c[0]*omega[0]*omega[1] + c[2]*omega[1]*omega[2] - c[1]*(pow(omega[0],2) + pow(omega[2],2)) - omega[0]*omega[1]*a[2][0] + pow(omega[0],2)*a[2][1] + pow(omega[2],2)*a[2][1] - omega[1]*omega[2]*a[2][2]))/(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2));

                a1[2][2] = (c1[2]*(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)) + ((-1 + cos(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))))*omega[0]*omega[2] + omega[1]*sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))*sin(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))))*(c[0] - a[2][0]) - 2*sin(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))/2.)*(cos(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))/2.)*omega[0]*sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)) + omega[1]*omega[2]*sin(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))/2.))*(c[1] - a[2][1]) - (cos(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)))*(pow(omega[0],2) + pow(omega[1],2)) + pow(omega[2],2))*(c[2] - a[2][2]))/(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2));

                a1[3][0] = (-(c[0]*pow(omega[0],2)) + c1[0]*pow(omega[0],2) - c[1]*omega[0]*omega[1] + c1[0]*pow(omega[1],2) - c[2]*omega[0]*omega[2] + c1[0]*pow(omega[2],2) + pow(omega[0],2)*a[3][0] + omega[0]*omega[1]*a[3][1] + omega[0]*omega[2]*a[3][2] - sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))*sin(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)))*(c[2]*omega[1] - c[1]*omega[2] + omega[2]*a[3][1] - omega[1]*a[3][2]) + cos(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)))*(c[1]*omega[0]*omega[1] + c[2]*omega[0]*omega[2] - c[0]*(pow(omega[1],2) + pow(omega[2],2)) + pow(omega[1],2)*a[3][0] + pow(omega[2],2)*a[3][0] - omega[0]*omega[1]*a[3][1] - omega[0]*omega[2]*a[3][2]))/(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2));

                a1[3][1] = (c1[1]*pow(omega[0],2) - c[0]*omega[0]*omega[1] - c[1]*pow(omega[1],2) + c1[1]*pow(omega[1],2) - c[2]*omega[1]*omega[2] + c1[1]*pow(omega[2],2) + omega[0]*omega[1]*a[3][0] + pow(omega[1],2)*a[3][1] + omega[1]*omega[2]*a[3][2] + sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))*sin(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)))*(c[2]*omega[0] - c[0]*omega[2] + omega[2]*a[3][0] - omega[0]*a[3][2]) + cos(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)))*(c[0]*omega[0]*omega[1] + c[2]*omega[1]*omega[2] - c[1]*(pow(omega[0],2) + pow(omega[2],2)) - omega[0]*omega[1]*a[3][0] + pow(omega[0],2)*a[3][1] + pow(omega[2],2)*a[3][1] - omega[1]*omega[2]*a[3][2]))/(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2));

                a1[3][2] = (c1[2]*(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)) + ((-1 + cos(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))))*omega[0]*omega[2] + omega[1]*sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))*sin(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))))*(c[0] - a[3][0]) - 2*sin(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))/2.)*(cos(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))/2.)*omega[0]*sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)) + omega[1]*omega[2]*sin(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))/2.))*(c[1] - a[3][1]) - (cos(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)))*(pow(omega[0],2) + pow(omega[1],2)) + pow(omega[2],2))*(c[2] - a[3][2]))/(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2));

            }

            break;

        case 5:
            c1[0] = c[0] + sqrt(2)*sqrt(DCargoTranslation)*sqrt(dt)*Dbc[0] + dt*muCargoTranslation*(Fsteric[0] + Ftrap[0] + FmRadial[0][0] + FmRadial[1][0] + FmRadial[2][0] + FmRadial[3][0] + FmRadial[4][0] + FmTangential[0][0] + FmTangential[1][0] + FmTangential[2][0] + FmTangential[3][0] + FmTangential[4][0]);

            c1[1] = c[1] + sqrt(2)*sqrt(DCargoTranslation)*sqrt(dt)*Dbc[1] + dt*muCargoTranslation*(Fsteric[1] + Ftrap[1] + FmRadial[0][1] + FmRadial[1][1] + FmRadial[2][1] + FmRadial[3][1] + FmRadial[4][1] + FmTangential[0][1] + FmTangential[1][1] + FmTangential[2][1] + FmTangential[3][1] + FmTangential[4][1]);

            c1[2] = c[2] + sqrt(2)*sqrt(DCargoTranslation)*sqrt(dt)*Dbc[2] + dt*muCargoTranslation*(Fsteric[2] + Ftrap[2] + FmRadial[0][2] + FmRadial[1][2] + FmRadial[2][2] + FmRadial[3][2] + FmRadial[4][2] + FmTangential[0][2] + FmTangential[1][2] + FmTangential[2][2] + FmTangential[3][2] + FmTangential[4][2]);

            theta1[0] = sqrt(2)*sqrt(DCargoRotation)*sqrt(dt)*Rbc[0] + theta[0] + dt*muCargoRotation*(TorqeExt[0] - a[0][2]*FmTangential[0][1] - c[1]*FmTangential[0][2] + a[0][1]*FmTangential[0][2] - a[1][2]*FmTangential[1][1] - c[1]*FmTangential[1][2] + a[1][1]*FmTangential[1][2] - a[2][2]*FmTangential[2][1] - c[1]*FmTangential[2][2] + a[2][1]*FmTangential[2][2] - a[3][2]*FmTangential[3][1] - c[1]*FmTangential[3][2] + a[3][1]*FmTangential[3][2] - a[4][2]*FmTangential[4][1] + c[2]*(FmTangential[0][1] + FmTangential[1][1] + FmTangential[2][1] + FmTangential[3][1] + FmTangential[4][1]) - c[1]*FmTangential[4][2] + a[4][1]*FmTangential[4][2]);

            theta1[1] = sqrt(2)*sqrt(DCargoRotation)*sqrt(dt)*Rbc[1] + theta[1] + dt*muCargoRotation*(TorqeExt[1] + a[0][2]*FmTangential[0][0] + c[0]*FmTangential[0][2] - a[0][0]*FmTangential[0][2] + a[1][2]*FmTangential[1][0] + c[0]*FmTangential[1][2] - a[1][0]*FmTangential[1][2] + a[2][2]*FmTangential[2][0] + c[0]*FmTangential[2][2] - a[2][0]*FmTangential[2][2] + a[3][2]*FmTangential[3][0] + c[0]*FmTangential[3][2] - a[3][0]*FmTangential[3][2] + a[4][2]*FmTangential[4][0] - c[2]*(FmTangential[0][0] + FmTangential[1][0] + FmTangential[2][0] + FmTangential[3][0] + FmTangential[4][0]) + c[0]*FmTangential[4][2] - a[4][0]*FmTangential[4][2]);

            theta1[2] = sqrt(2)*sqrt(DCargoRotation)*sqrt(dt)*Rbc[2] + theta[2] + dt*muCargoRotation*(TorqeExt[2] - a[0][1]*FmTangential[0][0] - c[0]*FmTangential[0][1] + a[0][0]*FmTangential[0][1] - a[1][1]*FmTangential[1][0] - c[0]*FmTangential[1][1] + a[1][0]*FmTangential[1][1] - a[2][1]*FmTangential[2][0] - c[0]*FmTangential[2][1] + a[2][0]*FmTangential[2][1] - a[3][1]*FmTangential[3][0] - c[0]*FmTangential[3][1] + a[3][0]*FmTangential[3][1] - a[4][1]*FmTangential[4][0] + c[1]*(FmTangential[0][0] + FmTangential[1][0] + FmTangential[2][0] + FmTangential[3][0] + FmTangential[4][0]) - c[0]*FmTangential[4][1] + a[4][0]*FmTangential[4][1]);

            omega[0] = theta1[0]-theta[0];
            omega[1] = theta1[1]-theta[1];
            omega[2] = theta1[2]-theta[2];

            if(sqrt(omega[0]*omega[0] + omega[1]*omega[1] + omega[2]*omega[2])<1E-12){

                a1[0][0] = -c[0] + c1[0] + a[0][0];

                a1[0][1] = -c[1] + c1[1] + a[0][1];

                a1[0][2] = -c[2] + c1[2] + a[0][2];

                a1[1][0] = -c[0] + c1[0] + a[1][0];

                a1[1][1] = -c[1] + c1[1] + a[1][1];

                a1[1][2] = -c[2] + c1[2] + a[1][2];

                a1[2][0] = -c[0] + c1[0] + a[2][0];

                a1[2][1] = -c[1] + c1[1] + a[2][1];

                a1[2][2] = -c[2] + c1[2] + a[2][2];

                a1[3][0] = -c[0] + c1[0] + a[3][0];

                a1[3][1] = -c[1] + c1[1] + a[3][1];

                a1[3][2] = -c[2] + c1[2] + a[3][2];

                a1[4][0] = -c[0] + c1[0] + a[4][0];

                a1[4][1] = -c[1] + c1[1] + a[4][1];

                a1[4][2] = -c[2] + c1[2] + a[4][2];

            }else{

                a1[0][0] = (-(c[0]*pow(omega[0],2)) + c1[0]*pow(omega[0],2) - c[1]*omega[0]*omega[1] + c1[0]*pow(omega[1],2) - c[2]*omega[0]*omega[2] + c1[0]*pow(omega[2],2) + pow(omega[0],2)*a[0][0] + omega[0]*omega[1]*a[0][1] + omega[0]*omega[2]*a[0][2] - sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))*sin(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)))*(c[2]*omega[1] - c[1]*omega[2] + omega[2]*a[0][1] - omega[1]*a[0][2]) + cos(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)))*(c[1]*omega[0]*omega[1] + c[2]*omega[0]*omega[2] - c[0]*(pow(omega[1],2) + pow(omega[2],2)) + pow(omega[1],2)*a[0][0] + pow(omega[2],2)*a[0][0] - omega[0]*omega[1]*a[0][1] - omega[0]*omega[2]*a[0][2]))/(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2));

                a1[0][1] = (c1[1]*pow(omega[0],2) - c[0]*omega[0]*omega[1] - c[1]*pow(omega[1],2) + c1[1]*pow(omega[1],2) - c[2]*omega[1]*omega[2] + c1[1]*pow(omega[2],2) + omega[0]*omega[1]*a[0][0] + pow(omega[1],2)*a[0][1] + omega[1]*omega[2]*a[0][2] + sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))*sin(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)))*(c[2]*omega[0] - c[0]*omega[2] + omega[2]*a[0][0] - omega[0]*a[0][2]) + cos(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)))*(c[0]*omega[0]*omega[1] + c[2]*omega[1]*omega[2] - c[1]*(pow(omega[0],2) + pow(omega[2],2)) - omega[0]*omega[1]*a[0][0] + pow(omega[0],2)*a[0][1] + pow(omega[2],2)*a[0][1] - omega[1]*omega[2]*a[0][2]))/(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2));

                a1[0][2] = (c1[2]*(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)) + ((-1 + cos(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))))*omega[0]*omega[2] + omega[1]*sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))*sin(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))))*(c[0] - a[0][0]) - 2*sin(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))/2.)*(cos(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))/2.)*omega[0]*sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)) + omega[1]*omega[2]*sin(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))/2.))*(c[1] - a[0][1]) - (cos(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)))*(pow(omega[0],2) + pow(omega[1],2)) + pow(omega[2],2))*(c[2] - a[0][2]))/(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2));

                a1[1][0] = (-(c[0]*pow(omega[0],2)) + c1[0]*pow(omega[0],2) - c[1]*omega[0]*omega[1] + c1[0]*pow(omega[1],2) - c[2]*omega[0]*omega[2] + c1[0]*pow(omega[2],2) + pow(omega[0],2)*a[1][0] + omega[0]*omega[1]*a[1][1] + omega[0]*omega[2]*a[1][2] - sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))*sin(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)))*(c[2]*omega[1] - c[1]*omega[2] + omega[2]*a[1][1] - omega[1]*a[1][2]) + cos(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)))*(c[1]*omega[0]*omega[1] + c[2]*omega[0]*omega[2] - c[0]*(pow(omega[1],2) + pow(omega[2],2)) + pow(omega[1],2)*a[1][0] + pow(omega[2],2)*a[1][0] - omega[0]*omega[1]*a[1][1] - omega[0]*omega[2]*a[1][2]))/(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2));

                a1[1][1] = (c1[1]*pow(omega[0],2) - c[0]*omega[0]*omega[1] - c[1]*pow(omega[1],2) + c1[1]*pow(omega[1],2) - c[2]*omega[1]*omega[2] + c1[1]*pow(omega[2],2) + omega[0]*omega[1]*a[1][0] + pow(omega[1],2)*a[1][1] + omega[1]*omega[2]*a[1][2] + sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))*sin(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)))*(c[2]*omega[0] - c[0]*omega[2] + omega[2]*a[1][0] - omega[0]*a[1][2]) + cos(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)))*(c[0]*omega[0]*omega[1] + c[2]*omega[1]*omega[2] - c[1]*(pow(omega[0],2) + pow(omega[2],2)) - omega[0]*omega[1]*a[1][0] + pow(omega[0],2)*a[1][1] + pow(omega[2],2)*a[1][1] - omega[1]*omega[2]*a[1][2]))/(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2));

                a1[1][2] = (c1[2]*(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)) + ((-1 + cos(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))))*omega[0]*omega[2] + omega[1]*sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))*sin(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))))*(c[0] - a[1][0]) - 2*sin(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))/2.)*(cos(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))/2.)*omega[0]*sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)) + omega[1]*omega[2]*sin(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))/2.))*(c[1] - a[1][1]) - (cos(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)))*(pow(omega[0],2) + pow(omega[1],2)) + pow(omega[2],2))*(c[2] - a[1][2]))/(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2));

                a1[2][0] = (-(c[0]*pow(omega[0],2)) + c1[0]*pow(omega[0],2) - c[1]*omega[0]*omega[1] + c1[0]*pow(omega[1],2) - c[2]*omega[0]*omega[2] + c1[0]*pow(omega[2],2) + pow(omega[0],2)*a[2][0] + omega[0]*omega[1]*a[2][1] + omega[0]*omega[2]*a[2][2] - sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))*sin(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)))*(c[2]*omega[1] - c[1]*omega[2] + omega[2]*a[2][1] - omega[1]*a[2][2]) + cos(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)))*(c[1]*omega[0]*omega[1] + c[2]*omega[0]*omega[2] - c[0]*(pow(omega[1],2) + pow(omega[2],2)) + pow(omega[1],2)*a[2][0] + pow(omega[2],2)*a[2][0] - omega[0]*omega[1]*a[2][1] - omega[0]*omega[2]*a[2][2]))/(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2));

                a1[2][1] = (c1[1]*pow(omega[0],2) - c[0]*omega[0]*omega[1] - c[1]*pow(omega[1],2) + c1[1]*pow(omega[1],2) - c[2]*omega[1]*omega[2] + c1[1]*pow(omega[2],2) + omega[0]*omega[1]*a[2][0] + pow(omega[1],2)*a[2][1] + omega[1]*omega[2]*a[2][2] + sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))*sin(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)))*(c[2]*omega[0] - c[0]*omega[2] + omega[2]*a[2][0] - omega[0]*a[2][2]) + cos(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)))*(c[0]*omega[0]*omega[1] + c[2]*omega[1]*omega[2] - c[1]*(pow(omega[0],2) + pow(omega[2],2)) - omega[0]*omega[1]*a[2][0] + pow(omega[0],2)*a[2][1] + pow(omega[2],2)*a[2][1] - omega[1]*omega[2]*a[2][2]))/(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2));

                a1[2][2] = (c1[2]*(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)) + ((-1 + cos(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))))*omega[0]*omega[2] + omega[1]*sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))*sin(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))))*(c[0] - a[2][0]) - 2*sin(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))/2.)*(cos(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))/2.)*omega[0]*sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)) + omega[1]*omega[2]*sin(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))/2.))*(c[1] - a[2][1]) - (cos(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)))*(pow(omega[0],2) + pow(omega[1],2)) + pow(omega[2],2))*(c[2] - a[2][2]))/(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2));

                a1[3][0] = (-(c[0]*pow(omega[0],2)) + c1[0]*pow(omega[0],2) - c[1]*omega[0]*omega[1] + c1[0]*pow(omega[1],2) - c[2]*omega[0]*omega[2] + c1[0]*pow(omega[2],2) + pow(omega[0],2)*a[3][0] + omega[0]*omega[1]*a[3][1] + omega[0]*omega[2]*a[3][2] - sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))*sin(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)))*(c[2]*omega[1] - c[1]*omega[2] + omega[2]*a[3][1] - omega[1]*a[3][2]) + cos(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)))*(c[1]*omega[0]*omega[1] + c[2]*omega[0]*omega[2] - c[0]*(pow(omega[1],2) + pow(omega[2],2)) + pow(omega[1],2)*a[3][0] + pow(omega[2],2)*a[3][0] - omega[0]*omega[1]*a[3][1] - omega[0]*omega[2]*a[3][2]))/(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2));

                a1[3][1] = (c1[1]*pow(omega[0],2) - c[0]*omega[0]*omega[1] - c[1]*pow(omega[1],2) + c1[1]*pow(omega[1],2) - c[2]*omega[1]*omega[2] + c1[1]*pow(omega[2],2) + omega[0]*omega[1]*a[3][0] + pow(omega[1],2)*a[3][1] + omega[1]*omega[2]*a[3][2] + sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))*sin(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)))*(c[2]*omega[0] - c[0]*omega[2] + omega[2]*a[3][0] - omega[0]*a[3][2]) + cos(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)))*(c[0]*omega[0]*omega[1] + c[2]*omega[1]*omega[2] - c[1]*(pow(omega[0],2) + pow(omega[2],2)) - omega[0]*omega[1]*a[3][0] + pow(omega[0],2)*a[3][1] + pow(omega[2],2)*a[3][1] - omega[1]*omega[2]*a[3][2]))/(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2));

                a1[3][2] = (c1[2]*(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)) + ((-1 + cos(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))))*omega[0]*omega[2] + omega[1]*sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))*sin(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))))*(c[0] - a[3][0]) - 2*sin(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))/2.)*(cos(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))/2.)*omega[0]*sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)) + omega[1]*omega[2]*sin(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))/2.))*(c[1] - a[3][1]) - (cos(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)))*(pow(omega[0],2) + pow(omega[1],2)) + pow(omega[2],2))*(c[2] - a[3][2]))/(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2));

                a1[4][0] = (-(c[0]*pow(omega[0],2)) + c1[0]*pow(omega[0],2) - c[1]*omega[0]*omega[1] + c1[0]*pow(omega[1],2) - c[2]*omega[0]*omega[2] + c1[0]*pow(omega[2],2) + pow(omega[0],2)*a[4][0] + omega[0]*omega[1]*a[4][1] + omega[0]*omega[2]*a[4][2] - sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))*sin(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)))*(c[2]*omega[1] - c[1]*omega[2] + omega[2]*a[4][1] - omega[1]*a[4][2]) + cos(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)))*(c[1]*omega[0]*omega[1] + c[2]*omega[0]*omega[2] - c[0]*(pow(omega[1],2) + pow(omega[2],2)) + pow(omega[1],2)*a[4][0] + pow(omega[2],2)*a[4][0] - omega[0]*omega[1]*a[4][1] - omega[0]*omega[2]*a[4][2]))/(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2));

                a1[4][1] = (c1[1]*pow(omega[0],2) - c[0]*omega[0]*omega[1] - c[1]*pow(omega[1],2) + c1[1]*pow(omega[1],2) - c[2]*omega[1]*omega[2] + c1[1]*pow(omega[2],2) + omega[0]*omega[1]*a[4][0] + pow(omega[1],2)*a[4][1] + omega[1]*omega[2]*a[4][2] + sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))*sin(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)))*(c[2]*omega[0] - c[0]*omega[2] + omega[2]*a[4][0] - omega[0]*a[4][2]) + cos(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)))*(c[0]*omega[0]*omega[1] + c[2]*omega[1]*omega[2] - c[1]*(pow(omega[0],2) + pow(omega[2],2)) - omega[0]*omega[1]*a[4][0] + pow(omega[0],2)*a[4][1] + pow(omega[2],2)*a[4][1] - omega[1]*omega[2]*a[4][2]))/(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2));

                a1[4][2] = (c1[2]*(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)) + ((-1 + cos(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))))*omega[0]*omega[2] + omega[1]*sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))*sin(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))))*(c[0] - a[4][0]) - 2*sin(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))/2.)*(cos(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))/2.)*omega[0]*sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)) + omega[1]*omega[2]*sin(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))/2.))*(c[1] - a[4][1]) - (cos(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)))*(pow(omega[0],2) + pow(omega[1],2)) + pow(omega[2],2))*(c[2] - a[4][2]))/(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2));

            }

            break;

        case 6:
            c1[0] = c[0] + sqrt(2)*sqrt(DCargoTranslation)*sqrt(dt)*Dbc[0] + dt*muCargoTranslation*(Fsteric[0] + Ftrap[0] + FmRadial[0][0] + FmRadial[1][0] + FmRadial[2][0] + FmRadial[3][0] + FmRadial[4][0] + FmRadial[5][0] + FmTangential[0][0] + FmTangential[1][0] + FmTangential[2][0] + FmTangential[3][0] + FmTangential[4][0] + FmTangential[5][0]);

            c1[1] = c[1] + sqrt(2)*sqrt(DCargoTranslation)*sqrt(dt)*Dbc[1] + dt*muCargoTranslation*(Fsteric[1] + Ftrap[1] + FmRadial[0][1] + FmRadial[1][1] + FmRadial[2][1] + FmRadial[3][1] + FmRadial[4][1] + FmRadial[5][1] + FmTangential[0][1] + FmTangential[1][1] + FmTangential[2][1] + FmTangential[3][1] + FmTangential[4][1] + FmTangential[5][1]);

            c1[2] = c[2] + sqrt(2)*sqrt(DCargoTranslation)*sqrt(dt)*Dbc[2] + dt*muCargoTranslation*(Fsteric[2] + Ftrap[2] + FmRadial[0][2] + FmRadial[1][2] + FmRadial[2][2] + FmRadial[3][2] + FmRadial[4][2] + FmRadial[5][2] + FmTangential[0][2] + FmTangential[1][2] + FmTangential[2][2] + FmTangential[3][2] + FmTangential[4][2] + FmTangential[5][2]);

            theta1[0] = sqrt(2)*sqrt(DCargoRotation)*sqrt(dt)*Rbc[0] + theta[0] + dt*muCargoRotation*(TorqeExt[0] - a[0][2]*FmTangential[0][1] - c[1]*FmTangential[0][2] + a[0][1]*FmTangential[0][2] - a[1][2]*FmTangential[1][1] - c[1]*FmTangential[1][2] + a[1][1]*FmTangential[1][2] - a[2][2]*FmTangential[2][1] - c[1]*FmTangential[2][2] + a[2][1]*FmTangential[2][2] - a[3][2]*FmTangential[3][1] - c[1]*FmTangential[3][2] + a[3][1]*FmTangential[3][2] - a[4][2]*FmTangential[4][1] - c[1]*FmTangential[4][2] + a[4][1]*FmTangential[4][2] - a[5][2]*FmTangential[5][1] + c[2]*(FmTangential[0][1] + FmTangential[1][1] + FmTangential[2][1] + FmTangential[3][1] + FmTangential[4][1] + FmTangential[5][1]) - c[1]*FmTangential[5][2] + a[5][1]*FmTangential[5][2]);

            theta1[1] = sqrt(2)*sqrt(DCargoRotation)*sqrt(dt)*Rbc[1] + theta[1] + dt*muCargoRotation*(TorqeExt[1] + a[0][2]*FmTangential[0][0] + c[0]*FmTangential[0][2] - a[0][0]*FmTangential[0][2] + a[1][2]*FmTangential[1][0] + c[0]*FmTangential[1][2] - a[1][0]*FmTangential[1][2] + a[2][2]*FmTangential[2][0] + c[0]*FmTangential[2][2] - a[2][0]*FmTangential[2][2] + a[3][2]*FmTangential[3][0] + c[0]*FmTangential[3][2] - a[3][0]*FmTangential[3][2] + a[4][2]*FmTangential[4][0] + c[0]*FmTangential[4][2] - a[4][0]*FmTangential[4][2] + a[5][2]*FmTangential[5][0] - c[2]*(FmTangential[0][0] + FmTangential[1][0] + FmTangential[2][0] + FmTangential[3][0] + FmTangential[4][0] + FmTangential[5][0]) + c[0]*FmTangential[5][2] - a[5][0]*FmTangential[5][2]);

            theta1[2] = sqrt(2)*sqrt(DCargoRotation)*sqrt(dt)*Rbc[2] + theta[2] + dt*muCargoRotation*(TorqeExt[2] - a[0][1]*FmTangential[0][0] - c[0]*FmTangential[0][1] + a[0][0]*FmTangential[0][1] - a[1][1]*FmTangential[1][0] - c[0]*FmTangential[1][1] + a[1][0]*FmTangential[1][1] - a[2][1]*FmTangential[2][0] - c[0]*FmTangential[2][1] + a[2][0]*FmTangential[2][1] - a[3][1]*FmTangential[3][0] - c[0]*FmTangential[3][1] + a[3][0]*FmTangential[3][1] - a[4][1]*FmTangential[4][0] - c[0]*FmTangential[4][1] + a[4][0]*FmTangential[4][1] - a[5][1]*FmTangential[5][0] + c[1]*(FmTangential[0][0] + FmTangential[1][0] + FmTangential[2][0] + FmTangential[3][0] + FmTangential[4][0] + FmTangential[5][0]) - c[0]*FmTangential[5][1] + a[5][0]*FmTangential[5][1]);

            omega[0] = theta1[0]-theta[0];
            omega[1] = theta1[1]-theta[1];
            omega[2] = theta1[2]-theta[2];

            if(sqrt(omega[0]*omega[0] + omega[1]*omega[1] + omega[2]*omega[2])<1E-12){

                a1[0][0] = -c[0] + c1[0] + a[0][0];

                a1[0][1] = -c[1] + c1[1] + a[0][1];

                a1[0][2] = -c[2] + c1[2] + a[0][2];

                a1[1][0] = -c[0] + c1[0] + a[1][0];

                a1[1][1] = -c[1] + c1[1] + a[1][1];

                a1[1][2] = -c[2] + c1[2] + a[1][2];

                a1[2][0] = -c[0] + c1[0] + a[2][0];

                a1[2][1] = -c[1] + c1[1] + a[2][1];

                a1[2][2] = -c[2] + c1[2] + a[2][2];

                a1[3][0] = -c[0] + c1[0] + a[3][0];

                a1[3][1] = -c[1] + c1[1] + a[3][1];

                a1[3][2] = -c[2] + c1[2] + a[3][2];

                a1[4][0] = -c[0] + c1[0] + a[4][0];

                a1[4][1] = -c[1] + c1[1] + a[4][1];

                a1[4][2] = -c[2] + c1[2] + a[4][2];

                a1[5][0] = -c[0] + c1[0] + a[5][0];

                a1[5][1] = -c[1] + c1[1] + a[5][1];

                a1[5][2] = -c[2] + c1[2] + a[5][2];

            }else{

                a1[0][0] = (-(c[0]*pow(omega[0],2)) + c1[0]*pow(omega[0],2) - c[1]*omega[0]*omega[1] + c1[0]*pow(omega[1],2) - c[2]*omega[0]*omega[2] + c1[0]*pow(omega[2],2) + pow(omega[0],2)*a[0][0] + omega[0]*omega[1]*a[0][1] + omega[0]*omega[2]*a[0][2] - sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))*sin(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)))*(c[2]*omega[1] - c[1]*omega[2] + omega[2]*a[0][1] - omega[1]*a[0][2]) + cos(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)))*(c[1]*omega[0]*omega[1] + c[2]*omega[0]*omega[2] - c[0]*(pow(omega[1],2) + pow(omega[2],2)) + pow(omega[1],2)*a[0][0] + pow(omega[2],2)*a[0][0] - omega[0]*omega[1]*a[0][1] - omega[0]*omega[2]*a[0][2]))/(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2));

                a1[0][1] = (c1[1]*pow(omega[0],2) - c[0]*omega[0]*omega[1] - c[1]*pow(omega[1],2) + c1[1]*pow(omega[1],2) - c[2]*omega[1]*omega[2] + c1[1]*pow(omega[2],2) + omega[0]*omega[1]*a[0][0] + pow(omega[1],2)*a[0][1] + omega[1]*omega[2]*a[0][2] + sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))*sin(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)))*(c[2]*omega[0] - c[0]*omega[2] + omega[2]*a[0][0] - omega[0]*a[0][2]) + cos(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)))*(c[0]*omega[0]*omega[1] + c[2]*omega[1]*omega[2] - c[1]*(pow(omega[0],2) + pow(omega[2],2)) - omega[0]*omega[1]*a[0][0] + pow(omega[0],2)*a[0][1] + pow(omega[2],2)*a[0][1] - omega[1]*omega[2]*a[0][2]))/(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2));

                a1[0][2] = (c1[2]*(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)) + ((-1 + cos(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))))*omega[0]*omega[2] + omega[1]*sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))*sin(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))))*(c[0] - a[0][0]) - 2*sin(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))/2.)*(cos(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))/2.)*omega[0]*sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)) + omega[1]*omega[2]*sin(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))/2.))*(c[1] - a[0][1]) - (cos(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)))*(pow(omega[0],2) + pow(omega[1],2)) + pow(omega[2],2))*(c[2] - a[0][2]))/(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2));

                a1[1][0] = (-(c[0]*pow(omega[0],2)) + c1[0]*pow(omega[0],2) - c[1]*omega[0]*omega[1] + c1[0]*pow(omega[1],2) - c[2]*omega[0]*omega[2] + c1[0]*pow(omega[2],2) + pow(omega[0],2)*a[1][0] + omega[0]*omega[1]*a[1][1] + omega[0]*omega[2]*a[1][2] - sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))*sin(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)))*(c[2]*omega[1] - c[1]*omega[2] + omega[2]*a[1][1] - omega[1]*a[1][2]) + cos(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)))*(c[1]*omega[0]*omega[1] + c[2]*omega[0]*omega[2] - c[0]*(pow(omega[1],2) + pow(omega[2],2)) + pow(omega[1],2)*a[1][0] + pow(omega[2],2)*a[1][0] - omega[0]*omega[1]*a[1][1] - omega[0]*omega[2]*a[1][2]))/(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2));

                a1[1][1] = (c1[1]*pow(omega[0],2) - c[0]*omega[0]*omega[1] - c[1]*pow(omega[1],2) + c1[1]*pow(omega[1],2) - c[2]*omega[1]*omega[2] + c1[1]*pow(omega[2],2) + omega[0]*omega[1]*a[1][0] + pow(omega[1],2)*a[1][1] + omega[1]*omega[2]*a[1][2] + sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))*sin(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)))*(c[2]*omega[0] - c[0]*omega[2] + omega[2]*a[1][0] - omega[0]*a[1][2]) + cos(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)))*(c[0]*omega[0]*omega[1] + c[2]*omega[1]*omega[2] - c[1]*(pow(omega[0],2) + pow(omega[2],2)) - omega[0]*omega[1]*a[1][0] + pow(omega[0],2)*a[1][1] + pow(omega[2],2)*a[1][1] - omega[1]*omega[2]*a[1][2]))/(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2));

                a1[1][2] = (c1[2]*(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)) + ((-1 + cos(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))))*omega[0]*omega[2] + omega[1]*sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))*sin(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))))*(c[0] - a[1][0]) - 2*sin(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))/2.)*(cos(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))/2.)*omega[0]*sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)) + omega[1]*omega[2]*sin(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))/2.))*(c[1] - a[1][1]) - (cos(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)))*(pow(omega[0],2) + pow(omega[1],2)) + pow(omega[2],2))*(c[2] - a[1][2]))/(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2));

                a1[2][0] = (-(c[0]*pow(omega[0],2)) + c1[0]*pow(omega[0],2) - c[1]*omega[0]*omega[1] + c1[0]*pow(omega[1],2) - c[2]*omega[0]*omega[2] + c1[0]*pow(omega[2],2) + pow(omega[0],2)*a[2][0] + omega[0]*omega[1]*a[2][1] + omega[0]*omega[2]*a[2][2] - sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))*sin(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)))*(c[2]*omega[1] - c[1]*omega[2] + omega[2]*a[2][1] - omega[1]*a[2][2]) + cos(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)))*(c[1]*omega[0]*omega[1] + c[2]*omega[0]*omega[2] - c[0]*(pow(omega[1],2) + pow(omega[2],2)) + pow(omega[1],2)*a[2][0] + pow(omega[2],2)*a[2][0] - omega[0]*omega[1]*a[2][1] - omega[0]*omega[2]*a[2][2]))/(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2));

                a1[2][1] = (c1[1]*pow(omega[0],2) - c[0]*omega[0]*omega[1] - c[1]*pow(omega[1],2) + c1[1]*pow(omega[1],2) - c[2]*omega[1]*omega[2] + c1[1]*pow(omega[2],2) + omega[0]*omega[1]*a[2][0] + pow(omega[1],2)*a[2][1] + omega[1]*omega[2]*a[2][2] + sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))*sin(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)))*(c[2]*omega[0] - c[0]*omega[2] + omega[2]*a[2][0] - omega[0]*a[2][2]) + cos(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)))*(c[0]*omega[0]*omega[1] + c[2]*omega[1]*omega[2] - c[1]*(pow(omega[0],2) + pow(omega[2],2)) - omega[0]*omega[1]*a[2][0] + pow(omega[0],2)*a[2][1] + pow(omega[2],2)*a[2][1] - omega[1]*omega[2]*a[2][2]))/(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2));

                a1[2][2] = (c1[2]*(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)) + ((-1 + cos(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))))*omega[0]*omega[2] + omega[1]*sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))*sin(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))))*(c[0] - a[2][0]) - 2*sin(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))/2.)*(cos(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))/2.)*omega[0]*sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)) + omega[1]*omega[2]*sin(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))/2.))*(c[1] - a[2][1]) - (cos(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)))*(pow(omega[0],2) + pow(omega[1],2)) + pow(omega[2],2))*(c[2] - a[2][2]))/(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2));

                a1[3][0] = (-(c[0]*pow(omega[0],2)) + c1[0]*pow(omega[0],2) - c[1]*omega[0]*omega[1] + c1[0]*pow(omega[1],2) - c[2]*omega[0]*omega[2] + c1[0]*pow(omega[2],2) + pow(omega[0],2)*a[3][0] + omega[0]*omega[1]*a[3][1] + omega[0]*omega[2]*a[3][2] - sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))*sin(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)))*(c[2]*omega[1] - c[1]*omega[2] + omega[2]*a[3][1] - omega[1]*a[3][2]) + cos(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)))*(c[1]*omega[0]*omega[1] + c[2]*omega[0]*omega[2] - c[0]*(pow(omega[1],2) + pow(omega[2],2)) + pow(omega[1],2)*a[3][0] + pow(omega[2],2)*a[3][0] - omega[0]*omega[1]*a[3][1] - omega[0]*omega[2]*a[3][2]))/(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2));

                a1[3][1] = (c1[1]*pow(omega[0],2) - c[0]*omega[0]*omega[1] - c[1]*pow(omega[1],2) + c1[1]*pow(omega[1],2) - c[2]*omega[1]*omega[2] + c1[1]*pow(omega[2],2) + omega[0]*omega[1]*a[3][0] + pow(omega[1],2)*a[3][1] + omega[1]*omega[2]*a[3][2] + sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))*sin(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)))*(c[2]*omega[0] - c[0]*omega[2] + omega[2]*a[3][0] - omega[0]*a[3][2]) + cos(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)))*(c[0]*omega[0]*omega[1] + c[2]*omega[1]*omega[2] - c[1]*(pow(omega[0],2) + pow(omega[2],2)) - omega[0]*omega[1]*a[3][0] + pow(omega[0],2)*a[3][1] + pow(omega[2],2)*a[3][1] - omega[1]*omega[2]*a[3][2]))/(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2));

                a1[3][2] = (c1[2]*(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)) + ((-1 + cos(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))))*omega[0]*omega[2] + omega[1]*sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))*sin(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))))*(c[0] - a[3][0]) - 2*sin(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))/2.)*(cos(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))/2.)*omega[0]*sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)) + omega[1]*omega[2]*sin(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))/2.))*(c[1] - a[3][1]) - (cos(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)))*(pow(omega[0],2) + pow(omega[1],2)) + pow(omega[2],2))*(c[2] - a[3][2]))/(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2));

                a1[4][0] = (-(c[0]*pow(omega[0],2)) + c1[0]*pow(omega[0],2) - c[1]*omega[0]*omega[1] + c1[0]*pow(omega[1],2) - c[2]*omega[0]*omega[2] + c1[0]*pow(omega[2],2) + pow(omega[0],2)*a[4][0] + omega[0]*omega[1]*a[4][1] + omega[0]*omega[2]*a[4][2] - sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))*sin(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)))*(c[2]*omega[1] - c[1]*omega[2] + omega[2]*a[4][1] - omega[1]*a[4][2]) + cos(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)))*(c[1]*omega[0]*omega[1] + c[2]*omega[0]*omega[2] - c[0]*(pow(omega[1],2) + pow(omega[2],2)) + pow(omega[1],2)*a[4][0] + pow(omega[2],2)*a[4][0] - omega[0]*omega[1]*a[4][1] - omega[0]*omega[2]*a[4][2]))/(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2));

                a1[4][1] = (c1[1]*pow(omega[0],2) - c[0]*omega[0]*omega[1] - c[1]*pow(omega[1],2) + c1[1]*pow(omega[1],2) - c[2]*omega[1]*omega[2] + c1[1]*pow(omega[2],2) + omega[0]*omega[1]*a[4][0] + pow(omega[1],2)*a[4][1] + omega[1]*omega[2]*a[4][2] + sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))*sin(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)))*(c[2]*omega[0] - c[0]*omega[2] + omega[2]*a[4][0] - omega[0]*a[4][2]) + cos(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)))*(c[0]*omega[0]*omega[1] + c[2]*omega[1]*omega[2] - c[1]*(pow(omega[0],2) + pow(omega[2],2)) - omega[0]*omega[1]*a[4][0] + pow(omega[0],2)*a[4][1] + pow(omega[2],2)*a[4][1] - omega[1]*omega[2]*a[4][2]))/(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2));

                a1[4][2] = (c1[2]*(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)) + ((-1 + cos(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))))*omega[0]*omega[2] + omega[1]*sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))*sin(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))))*(c[0] - a[4][0]) - 2*sin(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))/2.)*(cos(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))/2.)*omega[0]*sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)) + omega[1]*omega[2]*sin(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))/2.))*(c[1] - a[4][1]) - (cos(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)))*(pow(omega[0],2) + pow(omega[1],2)) + pow(omega[2],2))*(c[2] - a[4][2]))/(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2));

                a1[5][0] = (-(c[0]*pow(omega[0],2)) + c1[0]*pow(omega[0],2) - c[1]*omega[0]*omega[1] + c1[0]*pow(omega[1],2) - c[2]*omega[0]*omega[2] + c1[0]*pow(omega[2],2) + pow(omega[0],2)*a[5][0] + omega[0]*omega[1]*a[5][1] + omega[0]*omega[2]*a[5][2] - sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))*sin(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)))*(c[2]*omega[1] - c[1]*omega[2] + omega[2]*a[5][1] - omega[1]*a[5][2]) + cos(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)))*(c[1]*omega[0]*omega[1] + c[2]*omega[0]*omega[2] - c[0]*(pow(omega[1],2) + pow(omega[2],2)) + pow(omega[1],2)*a[5][0] + pow(omega[2],2)*a[5][0] - omega[0]*omega[1]*a[5][1] - omega[0]*omega[2]*a[5][2]))/(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2));

                a1[5][1] = (c1[1]*pow(omega[0],2) - c[0]*omega[0]*omega[1] - c[1]*pow(omega[1],2) + c1[1]*pow(omega[1],2) - c[2]*omega[1]*omega[2] + c1[1]*pow(omega[2],2) + omega[0]*omega[1]*a[5][0] + pow(omega[1],2)*a[5][1] + omega[1]*omega[2]*a[5][2] + sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))*sin(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)))*(c[2]*omega[0] - c[0]*omega[2] + omega[2]*a[5][0] - omega[0]*a[5][2]) + cos(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)))*(c[0]*omega[0]*omega[1] + c[2]*omega[1]*omega[2] - c[1]*(pow(omega[0],2) + pow(omega[2],2)) - omega[0]*omega[1]*a[5][0] + pow(omega[0],2)*a[5][1] + pow(omega[2],2)*a[5][1] - omega[1]*omega[2]*a[5][2]))/(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2));

                a1[5][2] = (c1[2]*(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)) + ((-1 + cos(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))))*omega[0]*omega[2] + omega[1]*sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))*sin(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))))*(c[0] - a[5][0]) - 2*sin(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))/2.)*(cos(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))/2.)*omega[0]*sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)) + omega[1]*omega[2]*sin(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))/2.))*(c[1] - a[5][1]) - (cos(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)))*(pow(omega[0],2) + pow(omega[1],2)) + pow(omega[2],2))*(c[2] - a[5][2]))/(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2));

            }

            break;

        case 7:
            c1[0] = c[0] + sqrt(2)*sqrt(DCargoTranslation)*sqrt(dt)*Dbc[0] + dt*muCargoTranslation*(Fsteric[0] + Ftrap[0] + FmRadial[0][0] + FmRadial[1][0] + FmRadial[2][0] + FmRadial[3][0] + FmRadial[4][0] + FmRadial[5][0] + FmRadial[6][0] + FmTangential[0][0] + FmTangential[1][0] + FmTangential[2][0] + FmTangential[3][0] + FmTangential[4][0] + FmTangential[5][0] + FmTangential[6][0]);

            c1[1] = c[1] + sqrt(2)*sqrt(DCargoTranslation)*sqrt(dt)*Dbc[1] + dt*muCargoTranslation*(Fsteric[1] + Ftrap[1] + FmRadial[0][1] + FmRadial[1][1] + FmRadial[2][1] + FmRadial[3][1] + FmRadial[4][1] + FmRadial[5][1] + FmRadial[6][1] + FmTangential[0][1] + FmTangential[1][1] + FmTangential[2][1] + FmTangential[3][1] + FmTangential[4][1] + FmTangential[5][1] + FmTangential[6][1]);

            c1[2] = c[2] + sqrt(2)*sqrt(DCargoTranslation)*sqrt(dt)*Dbc[2] + dt*muCargoTranslation*(Fsteric[2] + Ftrap[2] + FmRadial[0][2] + FmRadial[1][2] + FmRadial[2][2] + FmRadial[3][2] + FmRadial[4][2] + FmRadial[5][2] + FmRadial[6][2] + FmTangential[0][2] + FmTangential[1][2] + FmTangential[2][2] + FmTangential[3][2] + FmTangential[4][2] + FmTangential[5][2] + FmTangential[6][2]);

            theta1[0] = sqrt(2)*sqrt(DCargoRotation)*sqrt(dt)*Rbc[0] + theta[0] + dt*muCargoRotation*(TorqeExt[0] - a[0][2]*FmTangential[0][1] - c[1]*FmTangential[0][2] + a[0][1]*FmTangential[0][2] - a[1][2]*FmTangential[1][1] - c[1]*FmTangential[1][2] + a[1][1]*FmTangential[1][2] - a[2][2]*FmTangential[2][1] - c[1]*FmTangential[2][2] + a[2][1]*FmTangential[2][2] - a[3][2]*FmTangential[3][1] - c[1]*FmTangential[3][2] + a[3][1]*FmTangential[3][2] - a[4][2]*FmTangential[4][1] - c[1]*FmTangential[4][2] + a[4][1]*FmTangential[4][2] - a[5][2]*FmTangential[5][1] - c[1]*FmTangential[5][2] + a[5][1]*FmTangential[5][2] - a[6][2]*FmTangential[6][1] + c[2]*(FmTangential[0][1] + FmTangential[1][1] + FmTangential[2][1] + FmTangential[3][1] + FmTangential[4][1] + FmTangential[5][1] + FmTangential[6][1]) - c[1]*FmTangential[6][2] + a[6][1]*FmTangential[6][2]);

            theta1[1] = sqrt(2)*sqrt(DCargoRotation)*sqrt(dt)*Rbc[1] + theta[1] + dt*muCargoRotation*(TorqeExt[1] + a[0][2]*FmTangential[0][0] + c[0]*FmTangential[0][2] - a[0][0]*FmTangential[0][2] + a[1][2]*FmTangential[1][0] + c[0]*FmTangential[1][2] - a[1][0]*FmTangential[1][2] + a[2][2]*FmTangential[2][0] + c[0]*FmTangential[2][2] - a[2][0]*FmTangential[2][2] + a[3][2]*FmTangential[3][0] + c[0]*FmTangential[3][2] - a[3][0]*FmTangential[3][2] + a[4][2]*FmTangential[4][0] + c[0]*FmTangential[4][2] - a[4][0]*FmTangential[4][2] + a[5][2]*FmTangential[5][0] + c[0]*FmTangential[5][2] - a[5][0]*FmTangential[5][2] + a[6][2]*FmTangential[6][0] - c[2]*(FmTangential[0][0] + FmTangential[1][0] + FmTangential[2][0] + FmTangential[3][0] + FmTangential[4][0] + FmTangential[5][0] + FmTangential[6][0]) + c[0]*FmTangential[6][2] - a[6][0]*FmTangential[6][2]);

            theta1[2] = sqrt(2)*sqrt(DCargoRotation)*sqrt(dt)*Rbc[2] + theta[2] + dt*muCargoRotation*(TorqeExt[2] - a[0][1]*FmTangential[0][0] - c[0]*FmTangential[0][1] + a[0][0]*FmTangential[0][1] - a[1][1]*FmTangential[1][0] - c[0]*FmTangential[1][1] + a[1][0]*FmTangential[1][1] - a[2][1]*FmTangential[2][0] - c[0]*FmTangential[2][1] + a[2][0]*FmTangential[2][1] - a[3][1]*FmTangential[3][0] - c[0]*FmTangential[3][1] + a[3][0]*FmTangential[3][1] - a[4][1]*FmTangential[4][0] - c[0]*FmTangential[4][1] + a[4][0]*FmTangential[4][1] - a[5][1]*FmTangential[5][0] - c[0]*FmTangential[5][1] + a[5][0]*FmTangential[5][1] - a[6][1]*FmTangential[6][0] + c[1]*(FmTangential[0][0] + FmTangential[1][0] + FmTangential[2][0] + FmTangential[3][0] + FmTangential[4][0] + FmTangential[5][0] + FmTangential[6][0]) - c[0]*FmTangential[6][1] + a[6][0]*FmTangential[6][1]);

            omega[0] = theta1[0]-theta[0];
            omega[1] = theta1[1]-theta[1];
            omega[2] = theta1[2]-theta[2];

            if(sqrt(omega[0]*omega[0] + omega[1]*omega[1] + omega[2]*omega[2])<1E-12){

                a1[0][0] = -c[0] + c1[0] + a[0][0];

                a1[0][1] = -c[1] + c1[1] + a[0][1];

                a1[0][2] = -c[2] + c1[2] + a[0][2];

                a1[1][0] = -c[0] + c1[0] + a[1][0];

                a1[1][1] = -c[1] + c1[1] + a[1][1];

                a1[1][2] = -c[2] + c1[2] + a[1][2];

                a1[2][0] = -c[0] + c1[0] + a[2][0];

                a1[2][1] = -c[1] + c1[1] + a[2][1];

                a1[2][2] = -c[2] + c1[2] + a[2][2];

                a1[3][0] = -c[0] + c1[0] + a[3][0];

                a1[3][1] = -c[1] + c1[1] + a[3][1];

                a1[3][2] = -c[2] + c1[2] + a[3][2];

                a1[4][0] = -c[0] + c1[0] + a[4][0];

                a1[4][1] = -c[1] + c1[1] + a[4][1];

                a1[4][2] = -c[2] + c1[2] + a[4][2];

                a1[5][0] = -c[0] + c1[0] + a[5][0];

                a1[5][1] = -c[1] + c1[1] + a[5][1];

                a1[5][2] = -c[2] + c1[2] + a[5][2];

                a1[6][0] = -c[0] + c1[0] + a[6][0];

                a1[6][1] = -c[1] + c1[1] + a[6][1];

                a1[6][2] = -c[2] + c1[2] + a[6][2];

            }else{

                a1[0][0] = (-(c[0]*pow(omega[0],2)) + c1[0]*pow(omega[0],2) - c[1]*omega[0]*omega[1] + c1[0]*pow(omega[1],2) - c[2]*omega[0]*omega[2] + c1[0]*pow(omega[2],2) + pow(omega[0],2)*a[0][0] + omega[0]*omega[1]*a[0][1] + omega[0]*omega[2]*a[0][2] - sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))*sin(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)))*(c[2]*omega[1] - c[1]*omega[2] + omega[2]*a[0][1] - omega[1]*a[0][2]) + cos(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)))*(c[1]*omega[0]*omega[1] + c[2]*omega[0]*omega[2] - c[0]*(pow(omega[1],2) + pow(omega[2],2)) + pow(omega[1],2)*a[0][0] + pow(omega[2],2)*a[0][0] - omega[0]*omega[1]*a[0][1] - omega[0]*omega[2]*a[0][2]))/(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2));

                a1[0][1] = (c1[1]*pow(omega[0],2) - c[0]*omega[0]*omega[1] - c[1]*pow(omega[1],2) + c1[1]*pow(omega[1],2) - c[2]*omega[1]*omega[2] + c1[1]*pow(omega[2],2) + omega[0]*omega[1]*a[0][0] + pow(omega[1],2)*a[0][1] + omega[1]*omega[2]*a[0][2] + sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))*sin(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)))*(c[2]*omega[0] - c[0]*omega[2] + omega[2]*a[0][0] - omega[0]*a[0][2]) + cos(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)))*(c[0]*omega[0]*omega[1] + c[2]*omega[1]*omega[2] - c[1]*(pow(omega[0],2) + pow(omega[2],2)) - omega[0]*omega[1]*a[0][0] + pow(omega[0],2)*a[0][1] + pow(omega[2],2)*a[0][1] - omega[1]*omega[2]*a[0][2]))/(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2));

                a1[0][2] = (c1[2]*(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)) + ((-1 + cos(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))))*omega[0]*omega[2] + omega[1]*sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))*sin(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))))*(c[0] - a[0][0]) - 2*sin(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))/2.)*(cos(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))/2.)*omega[0]*sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)) + omega[1]*omega[2]*sin(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))/2.))*(c[1] - a[0][1]) - (cos(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)))*(pow(omega[0],2) + pow(omega[1],2)) + pow(omega[2],2))*(c[2] - a[0][2]))/(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2));

                a1[1][0] = (-(c[0]*pow(omega[0],2)) + c1[0]*pow(omega[0],2) - c[1]*omega[0]*omega[1] + c1[0]*pow(omega[1],2) - c[2]*omega[0]*omega[2] + c1[0]*pow(omega[2],2) + pow(omega[0],2)*a[1][0] + omega[0]*omega[1]*a[1][1] + omega[0]*omega[2]*a[1][2] - sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))*sin(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)))*(c[2]*omega[1] - c[1]*omega[2] + omega[2]*a[1][1] - omega[1]*a[1][2]) + cos(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)))*(c[1]*omega[0]*omega[1] + c[2]*omega[0]*omega[2] - c[0]*(pow(omega[1],2) + pow(omega[2],2)) + pow(omega[1],2)*a[1][0] + pow(omega[2],2)*a[1][0] - omega[0]*omega[1]*a[1][1] - omega[0]*omega[2]*a[1][2]))/(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2));

                a1[1][1] = (c1[1]*pow(omega[0],2) - c[0]*omega[0]*omega[1] - c[1]*pow(omega[1],2) + c1[1]*pow(omega[1],2) - c[2]*omega[1]*omega[2] + c1[1]*pow(omega[2],2) + omega[0]*omega[1]*a[1][0] + pow(omega[1],2)*a[1][1] + omega[1]*omega[2]*a[1][2] + sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))*sin(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)))*(c[2]*omega[0] - c[0]*omega[2] + omega[2]*a[1][0] - omega[0]*a[1][2]) + cos(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)))*(c[0]*omega[0]*omega[1] + c[2]*omega[1]*omega[2] - c[1]*(pow(omega[0],2) + pow(omega[2],2)) - omega[0]*omega[1]*a[1][0] + pow(omega[0],2)*a[1][1] + pow(omega[2],2)*a[1][1] - omega[1]*omega[2]*a[1][2]))/(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2));

                a1[1][2] = (c1[2]*(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)) + ((-1 + cos(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))))*omega[0]*omega[2] + omega[1]*sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))*sin(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))))*(c[0] - a[1][0]) - 2*sin(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))/2.)*(cos(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))/2.)*omega[0]*sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)) + omega[1]*omega[2]*sin(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))/2.))*(c[1] - a[1][1]) - (cos(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)))*(pow(omega[0],2) + pow(omega[1],2)) + pow(omega[2],2))*(c[2] - a[1][2]))/(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2));

                a1[2][0] = (-(c[0]*pow(omega[0],2)) + c1[0]*pow(omega[0],2) - c[1]*omega[0]*omega[1] + c1[0]*pow(omega[1],2) - c[2]*omega[0]*omega[2] + c1[0]*pow(omega[2],2) + pow(omega[0],2)*a[2][0] + omega[0]*omega[1]*a[2][1] + omega[0]*omega[2]*a[2][2] - sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))*sin(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)))*(c[2]*omega[1] - c[1]*omega[2] + omega[2]*a[2][1] - omega[1]*a[2][2]) + cos(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)))*(c[1]*omega[0]*omega[1] + c[2]*omega[0]*omega[2] - c[0]*(pow(omega[1],2) + pow(omega[2],2)) + pow(omega[1],2)*a[2][0] + pow(omega[2],2)*a[2][0] - omega[0]*omega[1]*a[2][1] - omega[0]*omega[2]*a[2][2]))/(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2));

                a1[2][1] = (c1[1]*pow(omega[0],2) - c[0]*omega[0]*omega[1] - c[1]*pow(omega[1],2) + c1[1]*pow(omega[1],2) - c[2]*omega[1]*omega[2] + c1[1]*pow(omega[2],2) + omega[0]*omega[1]*a[2][0] + pow(omega[1],2)*a[2][1] + omega[1]*omega[2]*a[2][2] + sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))*sin(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)))*(c[2]*omega[0] - c[0]*omega[2] + omega[2]*a[2][0] - omega[0]*a[2][2]) + cos(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)))*(c[0]*omega[0]*omega[1] + c[2]*omega[1]*omega[2] - c[1]*(pow(omega[0],2) + pow(omega[2],2)) - omega[0]*omega[1]*a[2][0] + pow(omega[0],2)*a[2][1] + pow(omega[2],2)*a[2][1] - omega[1]*omega[2]*a[2][2]))/(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2));

                a1[2][2] = (c1[2]*(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)) + ((-1 + cos(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))))*omega[0]*omega[2] + omega[1]*sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))*sin(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))))*(c[0] - a[2][0]) - 2*sin(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))/2.)*(cos(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))/2.)*omega[0]*sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)) + omega[1]*omega[2]*sin(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))/2.))*(c[1] - a[2][1]) - (cos(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)))*(pow(omega[0],2) + pow(omega[1],2)) + pow(omega[2],2))*(c[2] - a[2][2]))/(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2));

                a1[3][0] = (-(c[0]*pow(omega[0],2)) + c1[0]*pow(omega[0],2) - c[1]*omega[0]*omega[1] + c1[0]*pow(omega[1],2) - c[2]*omega[0]*omega[2] + c1[0]*pow(omega[2],2) + pow(omega[0],2)*a[3][0] + omega[0]*omega[1]*a[3][1] + omega[0]*omega[2]*a[3][2] - sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))*sin(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)))*(c[2]*omega[1] - c[1]*omega[2] + omega[2]*a[3][1] - omega[1]*a[3][2]) + cos(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)))*(c[1]*omega[0]*omega[1] + c[2]*omega[0]*omega[2] - c[0]*(pow(omega[1],2) + pow(omega[2],2)) + pow(omega[1],2)*a[3][0] + pow(omega[2],2)*a[3][0] - omega[0]*omega[1]*a[3][1] - omega[0]*omega[2]*a[3][2]))/(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2));

                a1[3][1] = (c1[1]*pow(omega[0],2) - c[0]*omega[0]*omega[1] - c[1]*pow(omega[1],2) + c1[1]*pow(omega[1],2) - c[2]*omega[1]*omega[2] + c1[1]*pow(omega[2],2) + omega[0]*omega[1]*a[3][0] + pow(omega[1],2)*a[3][1] + omega[1]*omega[2]*a[3][2] + sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))*sin(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)))*(c[2]*omega[0] - c[0]*omega[2] + omega[2]*a[3][0] - omega[0]*a[3][2]) + cos(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)))*(c[0]*omega[0]*omega[1] + c[2]*omega[1]*omega[2] - c[1]*(pow(omega[0],2) + pow(omega[2],2)) - omega[0]*omega[1]*a[3][0] + pow(omega[0],2)*a[3][1] + pow(omega[2],2)*a[3][1] - omega[1]*omega[2]*a[3][2]))/(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2));

                a1[3][2] = (c1[2]*(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)) + ((-1 + cos(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))))*omega[0]*omega[2] + omega[1]*sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))*sin(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))))*(c[0] - a[3][0]) - 2*sin(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))/2.)*(cos(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))/2.)*omega[0]*sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)) + omega[1]*omega[2]*sin(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))/2.))*(c[1] - a[3][1]) - (cos(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)))*(pow(omega[0],2) + pow(omega[1],2)) + pow(omega[2],2))*(c[2] - a[3][2]))/(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2));

                a1[4][0] = (-(c[0]*pow(omega[0],2)) + c1[0]*pow(omega[0],2) - c[1]*omega[0]*omega[1] + c1[0]*pow(omega[1],2) - c[2]*omega[0]*omega[2] + c1[0]*pow(omega[2],2) + pow(omega[0],2)*a[4][0] + omega[0]*omega[1]*a[4][1] + omega[0]*omega[2]*a[4][2] - sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))*sin(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)))*(c[2]*omega[1] - c[1]*omega[2] + omega[2]*a[4][1] - omega[1]*a[4][2]) + cos(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)))*(c[1]*omega[0]*omega[1] + c[2]*omega[0]*omega[2] - c[0]*(pow(omega[1],2) + pow(omega[2],2)) + pow(omega[1],2)*a[4][0] + pow(omega[2],2)*a[4][0] - omega[0]*omega[1]*a[4][1] - omega[0]*omega[2]*a[4][2]))/(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2));

                a1[4][1] = (c1[1]*pow(omega[0],2) - c[0]*omega[0]*omega[1] - c[1]*pow(omega[1],2) + c1[1]*pow(omega[1],2) - c[2]*omega[1]*omega[2] + c1[1]*pow(omega[2],2) + omega[0]*omega[1]*a[4][0] + pow(omega[1],2)*a[4][1] + omega[1]*omega[2]*a[4][2] + sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))*sin(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)))*(c[2]*omega[0] - c[0]*omega[2] + omega[2]*a[4][0] - omega[0]*a[4][2]) + cos(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)))*(c[0]*omega[0]*omega[1] + c[2]*omega[1]*omega[2] - c[1]*(pow(omega[0],2) + pow(omega[2],2)) - omega[0]*omega[1]*a[4][0] + pow(omega[0],2)*a[4][1] + pow(omega[2],2)*a[4][1] - omega[1]*omega[2]*a[4][2]))/(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2));

                a1[4][2] = (c1[2]*(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)) + ((-1 + cos(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))))*omega[0]*omega[2] + omega[1]*sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))*sin(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))))*(c[0] - a[4][0]) - 2*sin(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))/2.)*(cos(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))/2.)*omega[0]*sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)) + omega[1]*omega[2]*sin(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))/2.))*(c[1] - a[4][1]) - (cos(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)))*(pow(omega[0],2) + pow(omega[1],2)) + pow(omega[2],2))*(c[2] - a[4][2]))/(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2));

                a1[5][0] = (-(c[0]*pow(omega[0],2)) + c1[0]*pow(omega[0],2) - c[1]*omega[0]*omega[1] + c1[0]*pow(omega[1],2) - c[2]*omega[0]*omega[2] + c1[0]*pow(omega[2],2) + pow(omega[0],2)*a[5][0] + omega[0]*omega[1]*a[5][1] + omega[0]*omega[2]*a[5][2] - sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))*sin(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)))*(c[2]*omega[1] - c[1]*omega[2] + omega[2]*a[5][1] - omega[1]*a[5][2]) + cos(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)))*(c[1]*omega[0]*omega[1] + c[2]*omega[0]*omega[2] - c[0]*(pow(omega[1],2) + pow(omega[2],2)) + pow(omega[1],2)*a[5][0] + pow(omega[2],2)*a[5][0] - omega[0]*omega[1]*a[5][1] - omega[0]*omega[2]*a[5][2]))/(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2));

                a1[5][1] = (c1[1]*pow(omega[0],2) - c[0]*omega[0]*omega[1] - c[1]*pow(omega[1],2) + c1[1]*pow(omega[1],2) - c[2]*omega[1]*omega[2] + c1[1]*pow(omega[2],2) + omega[0]*omega[1]*a[5][0] + pow(omega[1],2)*a[5][1] + omega[1]*omega[2]*a[5][2] + sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))*sin(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)))*(c[2]*omega[0] - c[0]*omega[2] + omega[2]*a[5][0] - omega[0]*a[5][2]) + cos(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)))*(c[0]*omega[0]*omega[1] + c[2]*omega[1]*omega[2] - c[1]*(pow(omega[0],2) + pow(omega[2],2)) - omega[0]*omega[1]*a[5][0] + pow(omega[0],2)*a[5][1] + pow(omega[2],2)*a[5][1] - omega[1]*omega[2]*a[5][2]))/(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2));

                a1[5][2] = (c1[2]*(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)) + ((-1 + cos(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))))*omega[0]*omega[2] + omega[1]*sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))*sin(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))))*(c[0] - a[5][0]) - 2*sin(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))/2.)*(cos(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))/2.)*omega[0]*sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)) + omega[1]*omega[2]*sin(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))/2.))*(c[1] - a[5][1]) - (cos(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)))*(pow(omega[0],2) + pow(omega[1],2)) + pow(omega[2],2))*(c[2] - a[5][2]))/(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2));

                a1[6][0] = (-(c[0]*pow(omega[0],2)) + c1[0]*pow(omega[0],2) - c[1]*omega[0]*omega[1] + c1[0]*pow(omega[1],2) - c[2]*omega[0]*omega[2] + c1[0]*pow(omega[2],2) + pow(omega[0],2)*a[6][0] + omega[0]*omega[1]*a[6][1] + omega[0]*omega[2]*a[6][2] - sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))*sin(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)))*(c[2]*omega[1] - c[1]*omega[2] + omega[2]*a[6][1] - omega[1]*a[6][2]) + cos(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)))*(c[1]*omega[0]*omega[1] + c[2]*omega[0]*omega[2] - c[0]*(pow(omega[1],2) + pow(omega[2],2)) + pow(omega[1],2)*a[6][0] + pow(omega[2],2)*a[6][0] - omega[0]*omega[1]*a[6][1] - omega[0]*omega[2]*a[6][2]))/(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2));

                a1[6][1] = (c1[1]*pow(omega[0],2) - c[0]*omega[0]*omega[1] - c[1]*pow(omega[1],2) + c1[1]*pow(omega[1],2) - c[2]*omega[1]*omega[2] + c1[1]*pow(omega[2],2) + omega[0]*omega[1]*a[6][0] + pow(omega[1],2)*a[6][1] + omega[1]*omega[2]*a[6][2] + sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))*sin(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)))*(c[2]*omega[0] - c[0]*omega[2] + omega[2]*a[6][0] - omega[0]*a[6][2]) + cos(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)))*(c[0]*omega[0]*omega[1] + c[2]*omega[1]*omega[2] - c[1]*(pow(omega[0],2) + pow(omega[2],2)) - omega[0]*omega[1]*a[6][0] + pow(omega[0],2)*a[6][1] + pow(omega[2],2)*a[6][1] - omega[1]*omega[2]*a[6][2]))/(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2));

                a1[6][2] = (c1[2]*(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)) + ((-1 + cos(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))))*omega[0]*omega[2] + omega[1]*sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))*sin(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))))*(c[0] - a[6][0]) - 2*sin(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))/2.)*(cos(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))/2.)*omega[0]*sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)) + omega[1]*omega[2]*sin(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))/2.))*(c[1] - a[6][1]) - (cos(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)))*(pow(omega[0],2) + pow(omega[1],2)) + pow(omega[2],2))*(c[2] - a[6][2]))/(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2));

            }

            break;

        case 8:
            c1[0] = c[0] + sqrt(2)*sqrt(DCargoTranslation)*sqrt(dt)*Dbc[0] + dt*muCargoTranslation*(Fsteric[0] + Ftrap[0] + FmRadial[0][0] + FmRadial[1][0] + FmRadial[2][0] + FmRadial[3][0] + FmRadial[4][0] + FmRadial[5][0] + FmRadial[6][0] + FmRadial[7][0] + FmTangential[0][0] + FmTangential[1][0] + FmTangential[2][0] + FmTangential[3][0] + FmTangential[4][0] + FmTangential[5][0] + FmTangential[6][0] + FmTangential[7][0]);

            c1[1] = c[1] + sqrt(2)*sqrt(DCargoTranslation)*sqrt(dt)*Dbc[1] + dt*muCargoTranslation*(Fsteric[1] + Ftrap[1] + FmRadial[0][1] + FmRadial[1][1] + FmRadial[2][1] + FmRadial[3][1] + FmRadial[4][1] + FmRadial[5][1] + FmRadial[6][1] + FmRadial[7][1] + FmTangential[0][1] + FmTangential[1][1] + FmTangential[2][1] + FmTangential[3][1] + FmTangential[4][1] + FmTangential[5][1] + FmTangential[6][1] + FmTangential[7][1]);

            c1[2] = c[2] + sqrt(2)*sqrt(DCargoTranslation)*sqrt(dt)*Dbc[2] + dt*muCargoTranslation*(Fsteric[2] + Ftrap[2] + FmRadial[0][2] + FmRadial[1][2] + FmRadial[2][2] + FmRadial[3][2] + FmRadial[4][2] + FmRadial[5][2] + FmRadial[6][2] + FmRadial[7][2] + FmTangential[0][2] + FmTangential[1][2] + FmTangential[2][2] + FmTangential[3][2] + FmTangential[4][2] + FmTangential[5][2] + FmTangential[6][2] + FmTangential[7][2]);

            theta1[0] = sqrt(2)*sqrt(DCargoRotation)*sqrt(dt)*Rbc[0] + theta[0] + dt*muCargoRotation*(TorqeExt[0] - a[0][2]*FmTangential[0][1] - c[1]*FmTangential[0][2] + a[0][1]*FmTangential[0][2] - a[1][2]*FmTangential[1][1] - c[1]*FmTangential[1][2] + a[1][1]*FmTangential[1][2] - a[2][2]*FmTangential[2][1] - c[1]*FmTangential[2][2] + a[2][1]*FmTangential[2][2] - a[3][2]*FmTangential[3][1] - c[1]*FmTangential[3][2] + a[3][1]*FmTangential[3][2] - a[4][2]*FmTangential[4][1] - c[1]*FmTangential[4][2] + a[4][1]*FmTangential[4][2] - a[5][2]*FmTangential[5][1] - c[1]*FmTangential[5][2] + a[5][1]*FmTangential[5][2] - a[6][2]*FmTangential[6][1] - c[1]*FmTangential[6][2] + a[6][1]*FmTangential[6][2] - a[7][2]*FmTangential[7][1] + c[2]*(FmTangential[0][1] + FmTangential[1][1] + FmTangential[2][1] + FmTangential[3][1] + FmTangential[4][1] + FmTangential[5][1] + FmTangential[6][1] + FmTangential[7][1]) - c[1]*FmTangential[7][2] + a[7][1]*FmTangential[7][2]);

            theta1[1] = sqrt(2)*sqrt(DCargoRotation)*sqrt(dt)*Rbc[1] + theta[1] + dt*muCargoRotation*(TorqeExt[1] + a[0][2]*FmTangential[0][0] + c[0]*FmTangential[0][2] - a[0][0]*FmTangential[0][2] + a[1][2]*FmTangential[1][0] + c[0]*FmTangential[1][2] - a[1][0]*FmTangential[1][2] + a[2][2]*FmTangential[2][0] + c[0]*FmTangential[2][2] - a[2][0]*FmTangential[2][2] + a[3][2]*FmTangential[3][0] + c[0]*FmTangential[3][2] - a[3][0]*FmTangential[3][2] + a[4][2]*FmTangential[4][0] + c[0]*FmTangential[4][2] - a[4][0]*FmTangential[4][2] + a[5][2]*FmTangential[5][0] + c[0]*FmTangential[5][2] - a[5][0]*FmTangential[5][2] + a[6][2]*FmTangential[6][0] + c[0]*FmTangential[6][2] - a[6][0]*FmTangential[6][2] + a[7][2]*FmTangential[7][0] - c[2]*(FmTangential[0][0] + FmTangential[1][0] + FmTangential[2][0] + FmTangential[3][0] + FmTangential[4][0] + FmTangential[5][0] + FmTangential[6][0] + FmTangential[7][0]) + c[0]*FmTangential[7][2] - a[7][0]*FmTangential[7][2]);

            theta1[2] = sqrt(2)*sqrt(DCargoRotation)*sqrt(dt)*Rbc[2] + theta[2] + dt*muCargoRotation*(TorqeExt[2] - a[0][1]*FmTangential[0][0] - c[0]*FmTangential[0][1] + a[0][0]*FmTangential[0][1] - a[1][1]*FmTangential[1][0] - c[0]*FmTangential[1][1] + a[1][0]*FmTangential[1][1] - a[2][1]*FmTangential[2][0] - c[0]*FmTangential[2][1] + a[2][0]*FmTangential[2][1] - a[3][1]*FmTangential[3][0] - c[0]*FmTangential[3][1] + a[3][0]*FmTangential[3][1] - a[4][1]*FmTangential[4][0] - c[0]*FmTangential[4][1] + a[4][0]*FmTangential[4][1] - a[5][1]*FmTangential[5][0] - c[0]*FmTangential[5][1] + a[5][0]*FmTangential[5][1] - a[6][1]*FmTangential[6][0] - c[0]*FmTangential[6][1] + a[6][0]*FmTangential[6][1] - a[7][1]*FmTangential[7][0] + c[1]*(FmTangential[0][0] + FmTangential[1][0] + FmTangential[2][0] + FmTangential[3][0] + FmTangential[4][0] + FmTangential[5][0] + FmTangential[6][0] + FmTangential[7][0]) - c[0]*FmTangential[7][1] + a[7][0]*FmTangential[7][1]);

            omega[0] = theta1[0]-theta[0];
            omega[1] = theta1[1]-theta[1];
            omega[2] = theta1[2]-theta[2];

            if(sqrt(omega[0]*omega[0] + omega[1]*omega[1] + omega[2]*omega[2])<1E-12){

                a1[0][0] = -c[0] + c1[0] + a[0][0];

                a1[0][1] = -c[1] + c1[1] + a[0][1];

                a1[0][2] = -c[2] + c1[2] + a[0][2];

                a1[1][0] = -c[0] + c1[0] + a[1][0];

                a1[1][1] = -c[1] + c1[1] + a[1][1];

                a1[1][2] = -c[2] + c1[2] + a[1][2];

                a1[2][0] = -c[0] + c1[0] + a[2][0];

                a1[2][1] = -c[1] + c1[1] + a[2][1];

                a1[2][2] = -c[2] + c1[2] + a[2][2];

                a1[3][0] = -c[0] + c1[0] + a[3][0];

                a1[3][1] = -c[1] + c1[1] + a[3][1];

                a1[3][2] = -c[2] + c1[2] + a[3][2];

                a1[4][0] = -c[0] + c1[0] + a[4][0];

                a1[4][1] = -c[1] + c1[1] + a[4][1];

                a1[4][2] = -c[2] + c1[2] + a[4][2];

                a1[5][0] = -c[0] + c1[0] + a[5][0];

                a1[5][1] = -c[1] + c1[1] + a[5][1];

                a1[5][2] = -c[2] + c1[2] + a[5][2];

                a1[6][0] = -c[0] + c1[0] + a[6][0];

                a1[6][1] = -c[1] + c1[1] + a[6][1];

                a1[6][2] = -c[2] + c1[2] + a[6][2];

                a1[7][0] = -c[0] + c1[0] + a[7][0];

                a1[7][1] = -c[1] + c1[1] + a[7][1];

                a1[7][2] = -c[2] + c1[2] + a[7][2];

            }else{

                a1[0][0] = (-(c[0]*pow(omega[0],2)) + c1[0]*pow(omega[0],2) - c[1]*omega[0]*omega[1] + c1[0]*pow(omega[1],2) - c[2]*omega[0]*omega[2] + c1[0]*pow(omega[2],2) + pow(omega[0],2)*a[0][0] + omega[0]*omega[1]*a[0][1] + omega[0]*omega[2]*a[0][2] - sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))*sin(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)))*(c[2]*omega[1] - c[1]*omega[2] + omega[2]*a[0][1] - omega[1]*a[0][2]) + cos(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)))*(c[1]*omega[0]*omega[1] + c[2]*omega[0]*omega[2] - c[0]*(pow(omega[1],2) + pow(omega[2],2)) + pow(omega[1],2)*a[0][0] + pow(omega[2],2)*a[0][0] - omega[0]*omega[1]*a[0][1] - omega[0]*omega[2]*a[0][2]))/(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2));

                a1[0][1] = (c1[1]*pow(omega[0],2) - c[0]*omega[0]*omega[1] - c[1]*pow(omega[1],2) + c1[1]*pow(omega[1],2) - c[2]*omega[1]*omega[2] + c1[1]*pow(omega[2],2) + omega[0]*omega[1]*a[0][0] + pow(omega[1],2)*a[0][1] + omega[1]*omega[2]*a[0][2] + sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))*sin(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)))*(c[2]*omega[0] - c[0]*omega[2] + omega[2]*a[0][0] - omega[0]*a[0][2]) + cos(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)))*(c[0]*omega[0]*omega[1] + c[2]*omega[1]*omega[2] - c[1]*(pow(omega[0],2) + pow(omega[2],2)) - omega[0]*omega[1]*a[0][0] + pow(omega[0],2)*a[0][1] + pow(omega[2],2)*a[0][1] - omega[1]*omega[2]*a[0][2]))/(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2));

                a1[0][2] = (c1[2]*(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)) + ((-1 + cos(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))))*omega[0]*omega[2] + omega[1]*sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))*sin(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))))*(c[0] - a[0][0]) - 2*sin(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))/2.)*(cos(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))/2.)*omega[0]*sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)) + omega[1]*omega[2]*sin(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))/2.))*(c[1] - a[0][1]) - (cos(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)))*(pow(omega[0],2) + pow(omega[1],2)) + pow(omega[2],2))*(c[2] - a[0][2]))/(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2));

                a1[1][0] = (-(c[0]*pow(omega[0],2)) + c1[0]*pow(omega[0],2) - c[1]*omega[0]*omega[1] + c1[0]*pow(omega[1],2) - c[2]*omega[0]*omega[2] + c1[0]*pow(omega[2],2) + pow(omega[0],2)*a[1][0] + omega[0]*omega[1]*a[1][1] + omega[0]*omega[2]*a[1][2] - sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))*sin(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)))*(c[2]*omega[1] - c[1]*omega[2] + omega[2]*a[1][1] - omega[1]*a[1][2]) + cos(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)))*(c[1]*omega[0]*omega[1] + c[2]*omega[0]*omega[2] - c[0]*(pow(omega[1],2) + pow(omega[2],2)) + pow(omega[1],2)*a[1][0] + pow(omega[2],2)*a[1][0] - omega[0]*omega[1]*a[1][1] - omega[0]*omega[2]*a[1][2]))/(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2));

                a1[1][1] = (c1[1]*pow(omega[0],2) - c[0]*omega[0]*omega[1] - c[1]*pow(omega[1],2) + c1[1]*pow(omega[1],2) - c[2]*omega[1]*omega[2] + c1[1]*pow(omega[2],2) + omega[0]*omega[1]*a[1][0] + pow(omega[1],2)*a[1][1] + omega[1]*omega[2]*a[1][2] + sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))*sin(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)))*(c[2]*omega[0] - c[0]*omega[2] + omega[2]*a[1][0] - omega[0]*a[1][2]) + cos(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)))*(c[0]*omega[0]*omega[1] + c[2]*omega[1]*omega[2] - c[1]*(pow(omega[0],2) + pow(omega[2],2)) - omega[0]*omega[1]*a[1][0] + pow(omega[0],2)*a[1][1] + pow(omega[2],2)*a[1][1] - omega[1]*omega[2]*a[1][2]))/(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2));

                a1[1][2] = (c1[2]*(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)) + ((-1 + cos(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))))*omega[0]*omega[2] + omega[1]*sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))*sin(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))))*(c[0] - a[1][0]) - 2*sin(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))/2.)*(cos(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))/2.)*omega[0]*sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)) + omega[1]*omega[2]*sin(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))/2.))*(c[1] - a[1][1]) - (cos(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)))*(pow(omega[0],2) + pow(omega[1],2)) + pow(omega[2],2))*(c[2] - a[1][2]))/(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2));

                a1[2][0] = (-(c[0]*pow(omega[0],2)) + c1[0]*pow(omega[0],2) - c[1]*omega[0]*omega[1] + c1[0]*pow(omega[1],2) - c[2]*omega[0]*omega[2] + c1[0]*pow(omega[2],2) + pow(omega[0],2)*a[2][0] + omega[0]*omega[1]*a[2][1] + omega[0]*omega[2]*a[2][2] - sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))*sin(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)))*(c[2]*omega[1] - c[1]*omega[2] + omega[2]*a[2][1] - omega[1]*a[2][2]) + cos(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)))*(c[1]*omega[0]*omega[1] + c[2]*omega[0]*omega[2] - c[0]*(pow(omega[1],2) + pow(omega[2],2)) + pow(omega[1],2)*a[2][0] + pow(omega[2],2)*a[2][0] - omega[0]*omega[1]*a[2][1] - omega[0]*omega[2]*a[2][2]))/(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2));

                a1[2][1] = (c1[1]*pow(omega[0],2) - c[0]*omega[0]*omega[1] - c[1]*pow(omega[1],2) + c1[1]*pow(omega[1],2) - c[2]*omega[1]*omega[2] + c1[1]*pow(omega[2],2) + omega[0]*omega[1]*a[2][0] + pow(omega[1],2)*a[2][1] + omega[1]*omega[2]*a[2][2] + sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))*sin(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)))*(c[2]*omega[0] - c[0]*omega[2] + omega[2]*a[2][0] - omega[0]*a[2][2]) + cos(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)))*(c[0]*omega[0]*omega[1] + c[2]*omega[1]*omega[2] - c[1]*(pow(omega[0],2) + pow(omega[2],2)) - omega[0]*omega[1]*a[2][0] + pow(omega[0],2)*a[2][1] + pow(omega[2],2)*a[2][1] - omega[1]*omega[2]*a[2][2]))/(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2));

                a1[2][2] = (c1[2]*(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)) + ((-1 + cos(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))))*omega[0]*omega[2] + omega[1]*sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))*sin(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))))*(c[0] - a[2][0]) - 2*sin(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))/2.)*(cos(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))/2.)*omega[0]*sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)) + omega[1]*omega[2]*sin(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))/2.))*(c[1] - a[2][1]) - (cos(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)))*(pow(omega[0],2) + pow(omega[1],2)) + pow(omega[2],2))*(c[2] - a[2][2]))/(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2));

                a1[3][0] = (-(c[0]*pow(omega[0],2)) + c1[0]*pow(omega[0],2) - c[1]*omega[0]*omega[1] + c1[0]*pow(omega[1],2) - c[2]*omega[0]*omega[2] + c1[0]*pow(omega[2],2) + pow(omega[0],2)*a[3][0] + omega[0]*omega[1]*a[3][1] + omega[0]*omega[2]*a[3][2] - sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))*sin(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)))*(c[2]*omega[1] - c[1]*omega[2] + omega[2]*a[3][1] - omega[1]*a[3][2]) + cos(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)))*(c[1]*omega[0]*omega[1] + c[2]*omega[0]*omega[2] - c[0]*(pow(omega[1],2) + pow(omega[2],2)) + pow(omega[1],2)*a[3][0] + pow(omega[2],2)*a[3][0] - omega[0]*omega[1]*a[3][1] - omega[0]*omega[2]*a[3][2]))/(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2));

                a1[3][1] = (c1[1]*pow(omega[0],2) - c[0]*omega[0]*omega[1] - c[1]*pow(omega[1],2) + c1[1]*pow(omega[1],2) - c[2]*omega[1]*omega[2] + c1[1]*pow(omega[2],2) + omega[0]*omega[1]*a[3][0] + pow(omega[1],2)*a[3][1] + omega[1]*omega[2]*a[3][2] + sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))*sin(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)))*(c[2]*omega[0] - c[0]*omega[2] + omega[2]*a[3][0] - omega[0]*a[3][2]) + cos(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)))*(c[0]*omega[0]*omega[1] + c[2]*omega[1]*omega[2] - c[1]*(pow(omega[0],2) + pow(omega[2],2)) - omega[0]*omega[1]*a[3][0] + pow(omega[0],2)*a[3][1] + pow(omega[2],2)*a[3][1] - omega[1]*omega[2]*a[3][2]))/(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2));

                a1[3][2] = (c1[2]*(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)) + ((-1 + cos(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))))*omega[0]*omega[2] + omega[1]*sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))*sin(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))))*(c[0] - a[3][0]) - 2*sin(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))/2.)*(cos(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))/2.)*omega[0]*sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)) + omega[1]*omega[2]*sin(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))/2.))*(c[1] - a[3][1]) - (cos(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)))*(pow(omega[0],2) + pow(omega[1],2)) + pow(omega[2],2))*(c[2] - a[3][2]))/(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2));

                a1[4][0] = (-(c[0]*pow(omega[0],2)) + c1[0]*pow(omega[0],2) - c[1]*omega[0]*omega[1] + c1[0]*pow(omega[1],2) - c[2]*omega[0]*omega[2] + c1[0]*pow(omega[2],2) + pow(omega[0],2)*a[4][0] + omega[0]*omega[1]*a[4][1] + omega[0]*omega[2]*a[4][2] - sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))*sin(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)))*(c[2]*omega[1] - c[1]*omega[2] + omega[2]*a[4][1] - omega[1]*a[4][2]) + cos(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)))*(c[1]*omega[0]*omega[1] + c[2]*omega[0]*omega[2] - c[0]*(pow(omega[1],2) + pow(omega[2],2)) + pow(omega[1],2)*a[4][0] + pow(omega[2],2)*a[4][0] - omega[0]*omega[1]*a[4][1] - omega[0]*omega[2]*a[4][2]))/(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2));

                a1[4][1] = (c1[1]*pow(omega[0],2) - c[0]*omega[0]*omega[1] - c[1]*pow(omega[1],2) + c1[1]*pow(omega[1],2) - c[2]*omega[1]*omega[2] + c1[1]*pow(omega[2],2) + omega[0]*omega[1]*a[4][0] + pow(omega[1],2)*a[4][1] + omega[1]*omega[2]*a[4][2] + sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))*sin(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)))*(c[2]*omega[0] - c[0]*omega[2] + omega[2]*a[4][0] - omega[0]*a[4][2]) + cos(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)))*(c[0]*omega[0]*omega[1] + c[2]*omega[1]*omega[2] - c[1]*(pow(omega[0],2) + pow(omega[2],2)) - omega[0]*omega[1]*a[4][0] + pow(omega[0],2)*a[4][1] + pow(omega[2],2)*a[4][1] - omega[1]*omega[2]*a[4][2]))/(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2));

                a1[4][2] = (c1[2]*(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)) + ((-1 + cos(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))))*omega[0]*omega[2] + omega[1]*sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))*sin(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))))*(c[0] - a[4][0]) - 2*sin(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))/2.)*(cos(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))/2.)*omega[0]*sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)) + omega[1]*omega[2]*sin(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))/2.))*(c[1] - a[4][1]) - (cos(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)))*(pow(omega[0],2) + pow(omega[1],2)) + pow(omega[2],2))*(c[2] - a[4][2]))/(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2));

                a1[5][0] = (-(c[0]*pow(omega[0],2)) + c1[0]*pow(omega[0],2) - c[1]*omega[0]*omega[1] + c1[0]*pow(omega[1],2) - c[2]*omega[0]*omega[2] + c1[0]*pow(omega[2],2) + pow(omega[0],2)*a[5][0] + omega[0]*omega[1]*a[5][1] + omega[0]*omega[2]*a[5][2] - sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))*sin(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)))*(c[2]*omega[1] - c[1]*omega[2] + omega[2]*a[5][1] - omega[1]*a[5][2]) + cos(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)))*(c[1]*omega[0]*omega[1] + c[2]*omega[0]*omega[2] - c[0]*(pow(omega[1],2) + pow(omega[2],2)) + pow(omega[1],2)*a[5][0] + pow(omega[2],2)*a[5][0] - omega[0]*omega[1]*a[5][1] - omega[0]*omega[2]*a[5][2]))/(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2));

                a1[5][1] = (c1[1]*pow(omega[0],2) - c[0]*omega[0]*omega[1] - c[1]*pow(omega[1],2) + c1[1]*pow(omega[1],2) - c[2]*omega[1]*omega[2] + c1[1]*pow(omega[2],2) + omega[0]*omega[1]*a[5][0] + pow(omega[1],2)*a[5][1] + omega[1]*omega[2]*a[5][2] + sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))*sin(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)))*(c[2]*omega[0] - c[0]*omega[2] + omega[2]*a[5][0] - omega[0]*a[5][2]) + cos(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)))*(c[0]*omega[0]*omega[1] + c[2]*omega[1]*omega[2] - c[1]*(pow(omega[0],2) + pow(omega[2],2)) - omega[0]*omega[1]*a[5][0] + pow(omega[0],2)*a[5][1] + pow(omega[2],2)*a[5][1] - omega[1]*omega[2]*a[5][2]))/(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2));

                a1[5][2] = (c1[2]*(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)) + ((-1 + cos(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))))*omega[0]*omega[2] + omega[1]*sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))*sin(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))))*(c[0] - a[5][0]) - 2*sin(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))/2.)*(cos(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))/2.)*omega[0]*sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)) + omega[1]*omega[2]*sin(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))/2.))*(c[1] - a[5][1]) - (cos(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)))*(pow(omega[0],2) + pow(omega[1],2)) + pow(omega[2],2))*(c[2] - a[5][2]))/(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2));

                a1[6][0] = (-(c[0]*pow(omega[0],2)) + c1[0]*pow(omega[0],2) - c[1]*omega[0]*omega[1] + c1[0]*pow(omega[1],2) - c[2]*omega[0]*omega[2] + c1[0]*pow(omega[2],2) + pow(omega[0],2)*a[6][0] + omega[0]*omega[1]*a[6][1] + omega[0]*omega[2]*a[6][2] - sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))*sin(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)))*(c[2]*omega[1] - c[1]*omega[2] + omega[2]*a[6][1] - omega[1]*a[6][2]) + cos(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)))*(c[1]*omega[0]*omega[1] + c[2]*omega[0]*omega[2] - c[0]*(pow(omega[1],2) + pow(omega[2],2)) + pow(omega[1],2)*a[6][0] + pow(omega[2],2)*a[6][0] - omega[0]*omega[1]*a[6][1] - omega[0]*omega[2]*a[6][2]))/(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2));

                a1[6][1] = (c1[1]*pow(omega[0],2) - c[0]*omega[0]*omega[1] - c[1]*pow(omega[1],2) + c1[1]*pow(omega[1],2) - c[2]*omega[1]*omega[2] + c1[1]*pow(omega[2],2) + omega[0]*omega[1]*a[6][0] + pow(omega[1],2)*a[6][1] + omega[1]*omega[2]*a[6][2] + sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))*sin(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)))*(c[2]*omega[0] - c[0]*omega[2] + omega[2]*a[6][0] - omega[0]*a[6][2]) + cos(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)))*(c[0]*omega[0]*omega[1] + c[2]*omega[1]*omega[2] - c[1]*(pow(omega[0],2) + pow(omega[2],2)) - omega[0]*omega[1]*a[6][0] + pow(omega[0],2)*a[6][1] + pow(omega[2],2)*a[6][1] - omega[1]*omega[2]*a[6][2]))/(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2));

                a1[6][2] = (c1[2]*(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)) + ((-1 + cos(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))))*omega[0]*omega[2] + omega[1]*sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))*sin(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))))*(c[0] - a[6][0]) - 2*sin(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))/2.)*(cos(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))/2.)*omega[0]*sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)) + omega[1]*omega[2]*sin(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))/2.))*(c[1] - a[6][1]) - (cos(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)))*(pow(omega[0],2) + pow(omega[1],2)) + pow(omega[2],2))*(c[2] - a[6][2]))/(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2));

                a1[7][0] = (-(c[0]*pow(omega[0],2)) + c1[0]*pow(omega[0],2) - c[1]*omega[0]*omega[1] + c1[0]*pow(omega[1],2) - c[2]*omega[0]*omega[2] + c1[0]*pow(omega[2],2) + pow(omega[0],2)*a[7][0] + omega[0]*omega[1]*a[7][1] + omega[0]*omega[2]*a[7][2] - sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))*sin(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)))*(c[2]*omega[1] - c[1]*omega[2] + omega[2]*a[7][1] - omega[1]*a[7][2]) + cos(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)))*(c[1]*omega[0]*omega[1] + c[2]*omega[0]*omega[2] - c[0]*(pow(omega[1],2) + pow(omega[2],2)) + pow(omega[1],2)*a[7][0] + pow(omega[2],2)*a[7][0] - omega[0]*omega[1]*a[7][1] - omega[0]*omega[2]*a[7][2]))/(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2));

                a1[7][1] = (c1[1]*pow(omega[0],2) - c[0]*omega[0]*omega[1] - c[1]*pow(omega[1],2) + c1[1]*pow(omega[1],2) - c[2]*omega[1]*omega[2] + c1[1]*pow(omega[2],2) + omega[0]*omega[1]*a[7][0] + pow(omega[1],2)*a[7][1] + omega[1]*omega[2]*a[7][2] + sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))*sin(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)))*(c[2]*omega[0] - c[0]*omega[2] + omega[2]*a[7][0] - omega[0]*a[7][2]) + cos(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)))*(c[0]*omega[0]*omega[1] + c[2]*omega[1]*omega[2] - c[1]*(pow(omega[0],2) + pow(omega[2],2)) - omega[0]*omega[1]*a[7][0] + pow(omega[0],2)*a[7][1] + pow(omega[2],2)*a[7][1] - omega[1]*omega[2]*a[7][2]))/(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2));

                a1[7][2] = (c1[2]*(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)) + ((-1 + cos(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))))*omega[0]*omega[2] + omega[1]*sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))*sin(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))))*(c[0] - a[7][0]) - 2*sin(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))/2.)*(cos(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))/2.)*omega[0]*sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)) + omega[1]*omega[2]*sin(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))/2.))*(c[1] - a[7][1]) - (cos(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)))*(pow(omega[0],2) + pow(omega[1],2)) + pow(omega[2],2))*(c[2] - a[7][2]))/(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2));

            }

            break;

        case 9:
            c1[0] = c[0] + sqrt(2)*sqrt(DCargoTranslation)*sqrt(dt)*Dbc[0] + dt*muCargoTranslation*(Fsteric[0] + Ftrap[0] + FmRadial[0][0] + FmRadial[1][0] + FmRadial[2][0] + FmRadial[3][0] + FmRadial[4][0] + FmRadial[5][0] + FmRadial[6][0] + FmRadial[7][0] + FmRadial[8][0] + FmTangential[0][0] + FmTangential[1][0] + FmTangential[2][0] + FmTangential[3][0] + FmTangential[4][0] + FmTangential[5][0] + FmTangential[6][0] + FmTangential[7][0] + FmTangential[8][0]);

            c1[1] = c[1] + sqrt(2)*sqrt(DCargoTranslation)*sqrt(dt)*Dbc[1] + dt*muCargoTranslation*(Fsteric[1] + Ftrap[1] + FmRadial[0][1] + FmRadial[1][1] + FmRadial[2][1] + FmRadial[3][1] + FmRadial[4][1] + FmRadial[5][1] + FmRadial[6][1] + FmRadial[7][1] + FmRadial[8][1] + FmTangential[0][1] + FmTangential[1][1] + FmTangential[2][1] + FmTangential[3][1] + FmTangential[4][1] + FmTangential[5][1] + FmTangential[6][1] + FmTangential[7][1] + FmTangential[8][1]);

            c1[2] = c[2] + sqrt(2)*sqrt(DCargoTranslation)*sqrt(dt)*Dbc[2] + dt*muCargoTranslation*(Fsteric[2] + Ftrap[2] + FmRadial[0][2] + FmRadial[1][2] + FmRadial[2][2] + FmRadial[3][2] + FmRadial[4][2] + FmRadial[5][2] + FmRadial[6][2] + FmRadial[7][2] + FmRadial[8][2] + FmTangential[0][2] + FmTangential[1][2] + FmTangential[2][2] + FmTangential[3][2] + FmTangential[4][2] + FmTangential[5][2] + FmTangential[6][2] + FmTangential[7][2] + FmTangential[8][2]);

            theta1[0] = sqrt(2)*sqrt(DCargoRotation)*sqrt(dt)*Rbc[0] + theta[0] + dt*muCargoRotation*(TorqeExt[0] - a[0][2]*FmTangential[0][1] - c[1]*FmTangential[0][2] + a[0][1]*FmTangential[0][2] - a[1][2]*FmTangential[1][1] - c[1]*FmTangential[1][2] + a[1][1]*FmTangential[1][2] - a[2][2]*FmTangential[2][1] - c[1]*FmTangential[2][2] + a[2][1]*FmTangential[2][2] - a[3][2]*FmTangential[3][1] - c[1]*FmTangential[3][2] + a[3][1]*FmTangential[3][2] - a[4][2]*FmTangential[4][1] - c[1]*FmTangential[4][2] + a[4][1]*FmTangential[4][2] - a[5][2]*FmTangential[5][1] - c[1]*FmTangential[5][2] + a[5][1]*FmTangential[5][2] - a[6][2]*FmTangential[6][1] - c[1]*FmTangential[6][2] + a[6][1]*FmTangential[6][2] - a[7][2]*FmTangential[7][1] - c[1]*FmTangential[7][2] + a[7][1]*FmTangential[7][2] - a[8][2]*FmTangential[8][1] + c[2]*(FmTangential[0][1] + FmTangential[1][1] + FmTangential[2][1] + FmTangential[3][1] + FmTangential[4][1] + FmTangential[5][1] + FmTangential[6][1] + FmTangential[7][1] + FmTangential[8][1]) - c[1]*FmTangential[8][2] + a[8][1]*FmTangential[8][2]);

            theta1[1] = sqrt(2)*sqrt(DCargoRotation)*sqrt(dt)*Rbc[1] + theta[1] + dt*muCargoRotation*(TorqeExt[1] + a[0][2]*FmTangential[0][0] + c[0]*FmTangential[0][2] - a[0][0]*FmTangential[0][2] + a[1][2]*FmTangential[1][0] + c[0]*FmTangential[1][2] - a[1][0]*FmTangential[1][2] + a[2][2]*FmTangential[2][0] + c[0]*FmTangential[2][2] - a[2][0]*FmTangential[2][2] + a[3][2]*FmTangential[3][0] + c[0]*FmTangential[3][2] - a[3][0]*FmTangential[3][2] + a[4][2]*FmTangential[4][0] + c[0]*FmTangential[4][2] - a[4][0]*FmTangential[4][2] + a[5][2]*FmTangential[5][0] + c[0]*FmTangential[5][2] - a[5][0]*FmTangential[5][2] + a[6][2]*FmTangential[6][0] + c[0]*FmTangential[6][2] - a[6][0]*FmTangential[6][2] + a[7][2]*FmTangential[7][0] + c[0]*FmTangential[7][2] - a[7][0]*FmTangential[7][2] + a[8][2]*FmTangential[8][0] - c[2]*(FmTangential[0][0] + FmTangential[1][0] + FmTangential[2][0] + FmTangential[3][0] + FmTangential[4][0] + FmTangential[5][0] + FmTangential[6][0] + FmTangential[7][0] + FmTangential[8][0]) + c[0]*FmTangential[8][2] - a[8][0]*FmTangential[8][2]);

            theta1[2] = sqrt(2)*sqrt(DCargoRotation)*sqrt(dt)*Rbc[2] + theta[2] + dt*muCargoRotation*(TorqeExt[2] - a[0][1]*FmTangential[0][0] - c[0]*FmTangential[0][1] + a[0][0]*FmTangential[0][1] - a[1][1]*FmTangential[1][0] - c[0]*FmTangential[1][1] + a[1][0]*FmTangential[1][1] - a[2][1]*FmTangential[2][0] - c[0]*FmTangential[2][1] + a[2][0]*FmTangential[2][1] - a[3][1]*FmTangential[3][0] - c[0]*FmTangential[3][1] + a[3][0]*FmTangential[3][1] - a[4][1]*FmTangential[4][0] - c[0]*FmTangential[4][1] + a[4][0]*FmTangential[4][1] - a[5][1]*FmTangential[5][0] - c[0]*FmTangential[5][1] + a[5][0]*FmTangential[5][1] - a[6][1]*FmTangential[6][0] - c[0]*FmTangential[6][1] + a[6][0]*FmTangential[6][1] - a[7][1]*FmTangential[7][0] - c[0]*FmTangential[7][1] + a[7][0]*FmTangential[7][1] - a[8][1]*FmTangential[8][0] + c[1]*(FmTangential[0][0] + FmTangential[1][0] + FmTangential[2][0] + FmTangential[3][0] + FmTangential[4][0] + FmTangential[5][0] + FmTangential[6][0] + FmTangential[7][0] + FmTangential[8][0]) - c[0]*FmTangential[8][1] + a[8][0]*FmTangential[8][1]);

            omega[0] = theta1[0]-theta[0];
            omega[1] = theta1[1]-theta[1];
            omega[2] = theta1[2]-theta[2];

            if(sqrt(omega[0]*omega[0] + omega[1]*omega[1] + omega[2]*omega[2])<1E-12){

                a1[0][0] = -c[0] + c1[0] + a[0][0];

                a1[0][1] = -c[1] + c1[1] + a[0][1];

                a1[0][2] = -c[2] + c1[2] + a[0][2];

                a1[1][0] = -c[0] + c1[0] + a[1][0];

                a1[1][1] = -c[1] + c1[1] + a[1][1];

                a1[1][2] = -c[2] + c1[2] + a[1][2];

                a1[2][0] = -c[0] + c1[0] + a[2][0];

                a1[2][1] = -c[1] + c1[1] + a[2][1];

                a1[2][2] = -c[2] + c1[2] + a[2][2];

                a1[3][0] = -c[0] + c1[0] + a[3][0];

                a1[3][1] = -c[1] + c1[1] + a[3][1];

                a1[3][2] = -c[2] + c1[2] + a[3][2];

                a1[4][0] = -c[0] + c1[0] + a[4][0];

                a1[4][1] = -c[1] + c1[1] + a[4][1];

                a1[4][2] = -c[2] + c1[2] + a[4][2];

                a1[5][0] = -c[0] + c1[0] + a[5][0];

                a1[5][1] = -c[1] + c1[1] + a[5][1];

                a1[5][2] = -c[2] + c1[2] + a[5][2];

                a1[6][0] = -c[0] + c1[0] + a[6][0];

                a1[6][1] = -c[1] + c1[1] + a[6][1];

                a1[6][2] = -c[2] + c1[2] + a[6][2];

                a1[7][0] = -c[0] + c1[0] + a[7][0];

                a1[7][1] = -c[1] + c1[1] + a[7][1];

                a1[7][2] = -c[2] + c1[2] + a[7][2];

                a1[8][0] = -c[0] + c1[0] + a[8][0];

                a1[8][1] = -c[1] + c1[1] + a[8][1];

                a1[8][2] = -c[2] + c1[2] + a[8][2];

            }else{

                a1[0][0] = (-(c[0]*pow(omega[0],2)) + c1[0]*pow(omega[0],2) - c[1]*omega[0]*omega[1] + c1[0]*pow(omega[1],2) - c[2]*omega[0]*omega[2] + c1[0]*pow(omega[2],2) + pow(omega[0],2)*a[0][0] + omega[0]*omega[1]*a[0][1] + omega[0]*omega[2]*a[0][2] - sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))*sin(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)))*(c[2]*omega[1] - c[1]*omega[2] + omega[2]*a[0][1] - omega[1]*a[0][2]) + cos(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)))*(c[1]*omega[0]*omega[1] + c[2]*omega[0]*omega[2] - c[0]*(pow(omega[1],2) + pow(omega[2],2)) + pow(omega[1],2)*a[0][0] + pow(omega[2],2)*a[0][0] - omega[0]*omega[1]*a[0][1] - omega[0]*omega[2]*a[0][2]))/(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2));

                a1[0][1] = (c1[1]*pow(omega[0],2) - c[0]*omega[0]*omega[1] - c[1]*pow(omega[1],2) + c1[1]*pow(omega[1],2) - c[2]*omega[1]*omega[2] + c1[1]*pow(omega[2],2) + omega[0]*omega[1]*a[0][0] + pow(omega[1],2)*a[0][1] + omega[1]*omega[2]*a[0][2] + sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))*sin(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)))*(c[2]*omega[0] - c[0]*omega[2] + omega[2]*a[0][0] - omega[0]*a[0][2]) + cos(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)))*(c[0]*omega[0]*omega[1] + c[2]*omega[1]*omega[2] - c[1]*(pow(omega[0],2) + pow(omega[2],2)) - omega[0]*omega[1]*a[0][0] + pow(omega[0],2)*a[0][1] + pow(omega[2],2)*a[0][1] - omega[1]*omega[2]*a[0][2]))/(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2));

                a1[0][2] = (c1[2]*(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)) + ((-1 + cos(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))))*omega[0]*omega[2] + omega[1]*sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))*sin(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))))*(c[0] - a[0][0]) - 2*sin(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))/2.)*(cos(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))/2.)*omega[0]*sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)) + omega[1]*omega[2]*sin(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))/2.))*(c[1] - a[0][1]) - (cos(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)))*(pow(omega[0],2) + pow(omega[1],2)) + pow(omega[2],2))*(c[2] - a[0][2]))/(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2));

                a1[1][0] = (-(c[0]*pow(omega[0],2)) + c1[0]*pow(omega[0],2) - c[1]*omega[0]*omega[1] + c1[0]*pow(omega[1],2) - c[2]*omega[0]*omega[2] + c1[0]*pow(omega[2],2) + pow(omega[0],2)*a[1][0] + omega[0]*omega[1]*a[1][1] + omega[0]*omega[2]*a[1][2] - sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))*sin(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)))*(c[2]*omega[1] - c[1]*omega[2] + omega[2]*a[1][1] - omega[1]*a[1][2]) + cos(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)))*(c[1]*omega[0]*omega[1] + c[2]*omega[0]*omega[2] - c[0]*(pow(omega[1],2) + pow(omega[2],2)) + pow(omega[1],2)*a[1][0] + pow(omega[2],2)*a[1][0] - omega[0]*omega[1]*a[1][1] - omega[0]*omega[2]*a[1][2]))/(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2));

                a1[1][1] = (c1[1]*pow(omega[0],2) - c[0]*omega[0]*omega[1] - c[1]*pow(omega[1],2) + c1[1]*pow(omega[1],2) - c[2]*omega[1]*omega[2] + c1[1]*pow(omega[2],2) + omega[0]*omega[1]*a[1][0] + pow(omega[1],2)*a[1][1] + omega[1]*omega[2]*a[1][2] + sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))*sin(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)))*(c[2]*omega[0] - c[0]*omega[2] + omega[2]*a[1][0] - omega[0]*a[1][2]) + cos(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)))*(c[0]*omega[0]*omega[1] + c[2]*omega[1]*omega[2] - c[1]*(pow(omega[0],2) + pow(omega[2],2)) - omega[0]*omega[1]*a[1][0] + pow(omega[0],2)*a[1][1] + pow(omega[2],2)*a[1][1] - omega[1]*omega[2]*a[1][2]))/(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2));

                a1[1][2] = (c1[2]*(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)) + ((-1 + cos(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))))*omega[0]*omega[2] + omega[1]*sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))*sin(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))))*(c[0] - a[1][0]) - 2*sin(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))/2.)*(cos(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))/2.)*omega[0]*sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)) + omega[1]*omega[2]*sin(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))/2.))*(c[1] - a[1][1]) - (cos(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)))*(pow(omega[0],2) + pow(omega[1],2)) + pow(omega[2],2))*(c[2] - a[1][2]))/(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2));

                a1[2][0] = (-(c[0]*pow(omega[0],2)) + c1[0]*pow(omega[0],2) - c[1]*omega[0]*omega[1] + c1[0]*pow(omega[1],2) - c[2]*omega[0]*omega[2] + c1[0]*pow(omega[2],2) + pow(omega[0],2)*a[2][0] + omega[0]*omega[1]*a[2][1] + omega[0]*omega[2]*a[2][2] - sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))*sin(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)))*(c[2]*omega[1] - c[1]*omega[2] + omega[2]*a[2][1] - omega[1]*a[2][2]) + cos(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)))*(c[1]*omega[0]*omega[1] + c[2]*omega[0]*omega[2] - c[0]*(pow(omega[1],2) + pow(omega[2],2)) + pow(omega[1],2)*a[2][0] + pow(omega[2],2)*a[2][0] - omega[0]*omega[1]*a[2][1] - omega[0]*omega[2]*a[2][2]))/(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2));

                a1[2][1] = (c1[1]*pow(omega[0],2) - c[0]*omega[0]*omega[1] - c[1]*pow(omega[1],2) + c1[1]*pow(omega[1],2) - c[2]*omega[1]*omega[2] + c1[1]*pow(omega[2],2) + omega[0]*omega[1]*a[2][0] + pow(omega[1],2)*a[2][1] + omega[1]*omega[2]*a[2][2] + sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))*sin(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)))*(c[2]*omega[0] - c[0]*omega[2] + omega[2]*a[2][0] - omega[0]*a[2][2]) + cos(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)))*(c[0]*omega[0]*omega[1] + c[2]*omega[1]*omega[2] - c[1]*(pow(omega[0],2) + pow(omega[2],2)) - omega[0]*omega[1]*a[2][0] + pow(omega[0],2)*a[2][1] + pow(omega[2],2)*a[2][1] - omega[1]*omega[2]*a[2][2]))/(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2));

                a1[2][2] = (c1[2]*(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)) + ((-1 + cos(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))))*omega[0]*omega[2] + omega[1]*sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))*sin(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))))*(c[0] - a[2][0]) - 2*sin(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))/2.)*(cos(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))/2.)*omega[0]*sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)) + omega[1]*omega[2]*sin(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))/2.))*(c[1] - a[2][1]) - (cos(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)))*(pow(omega[0],2) + pow(omega[1],2)) + pow(omega[2],2))*(c[2] - a[2][2]))/(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2));

                a1[3][0] = (-(c[0]*pow(omega[0],2)) + c1[0]*pow(omega[0],2) - c[1]*omega[0]*omega[1] + c1[0]*pow(omega[1],2) - c[2]*omega[0]*omega[2] + c1[0]*pow(omega[2],2) + pow(omega[0],2)*a[3][0] + omega[0]*omega[1]*a[3][1] + omega[0]*omega[2]*a[3][2] - sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))*sin(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)))*(c[2]*omega[1] - c[1]*omega[2] + omega[2]*a[3][1] - omega[1]*a[3][2]) + cos(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)))*(c[1]*omega[0]*omega[1] + c[2]*omega[0]*omega[2] - c[0]*(pow(omega[1],2) + pow(omega[2],2)) + pow(omega[1],2)*a[3][0] + pow(omega[2],2)*a[3][0] - omega[0]*omega[1]*a[3][1] - omega[0]*omega[2]*a[3][2]))/(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2));

                a1[3][1] = (c1[1]*pow(omega[0],2) - c[0]*omega[0]*omega[1] - c[1]*pow(omega[1],2) + c1[1]*pow(omega[1],2) - c[2]*omega[1]*omega[2] + c1[1]*pow(omega[2],2) + omega[0]*omega[1]*a[3][0] + pow(omega[1],2)*a[3][1] + omega[1]*omega[2]*a[3][2] + sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))*sin(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)))*(c[2]*omega[0] - c[0]*omega[2] + omega[2]*a[3][0] - omega[0]*a[3][2]) + cos(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)))*(c[0]*omega[0]*omega[1] + c[2]*omega[1]*omega[2] - c[1]*(pow(omega[0],2) + pow(omega[2],2)) - omega[0]*omega[1]*a[3][0] + pow(omega[0],2)*a[3][1] + pow(omega[2],2)*a[3][1] - omega[1]*omega[2]*a[3][2]))/(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2));

                a1[3][2] = (c1[2]*(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)) + ((-1 + cos(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))))*omega[0]*omega[2] + omega[1]*sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))*sin(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))))*(c[0] - a[3][0]) - 2*sin(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))/2.)*(cos(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))/2.)*omega[0]*sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)) + omega[1]*omega[2]*sin(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))/2.))*(c[1] - a[3][1]) - (cos(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)))*(pow(omega[0],2) + pow(omega[1],2)) + pow(omega[2],2))*(c[2] - a[3][2]))/(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2));

                a1[4][0] = (-(c[0]*pow(omega[0],2)) + c1[0]*pow(omega[0],2) - c[1]*omega[0]*omega[1] + c1[0]*pow(omega[1],2) - c[2]*omega[0]*omega[2] + c1[0]*pow(omega[2],2) + pow(omega[0],2)*a[4][0] + omega[0]*omega[1]*a[4][1] + omega[0]*omega[2]*a[4][2] - sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))*sin(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)))*(c[2]*omega[1] - c[1]*omega[2] + omega[2]*a[4][1] - omega[1]*a[4][2]) + cos(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)))*(c[1]*omega[0]*omega[1] + c[2]*omega[0]*omega[2] - c[0]*(pow(omega[1],2) + pow(omega[2],2)) + pow(omega[1],2)*a[4][0] + pow(omega[2],2)*a[4][0] - omega[0]*omega[1]*a[4][1] - omega[0]*omega[2]*a[4][2]))/(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2));

                a1[4][1] = (c1[1]*pow(omega[0],2) - c[0]*omega[0]*omega[1] - c[1]*pow(omega[1],2) + c1[1]*pow(omega[1],2) - c[2]*omega[1]*omega[2] + c1[1]*pow(omega[2],2) + omega[0]*omega[1]*a[4][0] + pow(omega[1],2)*a[4][1] + omega[1]*omega[2]*a[4][2] + sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))*sin(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)))*(c[2]*omega[0] - c[0]*omega[2] + omega[2]*a[4][0] - omega[0]*a[4][2]) + cos(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)))*(c[0]*omega[0]*omega[1] + c[2]*omega[1]*omega[2] - c[1]*(pow(omega[0],2) + pow(omega[2],2)) - omega[0]*omega[1]*a[4][0] + pow(omega[0],2)*a[4][1] + pow(omega[2],2)*a[4][1] - omega[1]*omega[2]*a[4][2]))/(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2));

                a1[4][2] = (c1[2]*(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)) + ((-1 + cos(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))))*omega[0]*omega[2] + omega[1]*sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))*sin(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))))*(c[0] - a[4][0]) - 2*sin(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))/2.)*(cos(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))/2.)*omega[0]*sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)) + omega[1]*omega[2]*sin(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))/2.))*(c[1] - a[4][1]) - (cos(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)))*(pow(omega[0],2) + pow(omega[1],2)) + pow(omega[2],2))*(c[2] - a[4][2]))/(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2));

                a1[5][0] = (-(c[0]*pow(omega[0],2)) + c1[0]*pow(omega[0],2) - c[1]*omega[0]*omega[1] + c1[0]*pow(omega[1],2) - c[2]*omega[0]*omega[2] + c1[0]*pow(omega[2],2) + pow(omega[0],2)*a[5][0] + omega[0]*omega[1]*a[5][1] + omega[0]*omega[2]*a[5][2] - sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))*sin(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)))*(c[2]*omega[1] - c[1]*omega[2] + omega[2]*a[5][1] - omega[1]*a[5][2]) + cos(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)))*(c[1]*omega[0]*omega[1] + c[2]*omega[0]*omega[2] - c[0]*(pow(omega[1],2) + pow(omega[2],2)) + pow(omega[1],2)*a[5][0] + pow(omega[2],2)*a[5][0] - omega[0]*omega[1]*a[5][1] - omega[0]*omega[2]*a[5][2]))/(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2));

                a1[5][1] = (c1[1]*pow(omega[0],2) - c[0]*omega[0]*omega[1] - c[1]*pow(omega[1],2) + c1[1]*pow(omega[1],2) - c[2]*omega[1]*omega[2] + c1[1]*pow(omega[2],2) + omega[0]*omega[1]*a[5][0] + pow(omega[1],2)*a[5][1] + omega[1]*omega[2]*a[5][2] + sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))*sin(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)))*(c[2]*omega[0] - c[0]*omega[2] + omega[2]*a[5][0] - omega[0]*a[5][2]) + cos(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)))*(c[0]*omega[0]*omega[1] + c[2]*omega[1]*omega[2] - c[1]*(pow(omega[0],2) + pow(omega[2],2)) - omega[0]*omega[1]*a[5][0] + pow(omega[0],2)*a[5][1] + pow(omega[2],2)*a[5][1] - omega[1]*omega[2]*a[5][2]))/(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2));

                a1[5][2] = (c1[2]*(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)) + ((-1 + cos(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))))*omega[0]*omega[2] + omega[1]*sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))*sin(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))))*(c[0] - a[5][0]) - 2*sin(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))/2.)*(cos(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))/2.)*omega[0]*sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)) + omega[1]*omega[2]*sin(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))/2.))*(c[1] - a[5][1]) - (cos(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)))*(pow(omega[0],2) + pow(omega[1],2)) + pow(omega[2],2))*(c[2] - a[5][2]))/(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2));

                a1[6][0] = (-(c[0]*pow(omega[0],2)) + c1[0]*pow(omega[0],2) - c[1]*omega[0]*omega[1] + c1[0]*pow(omega[1],2) - c[2]*omega[0]*omega[2] + c1[0]*pow(omega[2],2) + pow(omega[0],2)*a[6][0] + omega[0]*omega[1]*a[6][1] + omega[0]*omega[2]*a[6][2] - sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))*sin(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)))*(c[2]*omega[1] - c[1]*omega[2] + omega[2]*a[6][1] - omega[1]*a[6][2]) + cos(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)))*(c[1]*omega[0]*omega[1] + c[2]*omega[0]*omega[2] - c[0]*(pow(omega[1],2) + pow(omega[2],2)) + pow(omega[1],2)*a[6][0] + pow(omega[2],2)*a[6][0] - omega[0]*omega[1]*a[6][1] - omega[0]*omega[2]*a[6][2]))/(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2));

                a1[6][1] = (c1[1]*pow(omega[0],2) - c[0]*omega[0]*omega[1] - c[1]*pow(omega[1],2) + c1[1]*pow(omega[1],2) - c[2]*omega[1]*omega[2] + c1[1]*pow(omega[2],2) + omega[0]*omega[1]*a[6][0] + pow(omega[1],2)*a[6][1] + omega[1]*omega[2]*a[6][2] + sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))*sin(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)))*(c[2]*omega[0] - c[0]*omega[2] + omega[2]*a[6][0] - omega[0]*a[6][2]) + cos(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)))*(c[0]*omega[0]*omega[1] + c[2]*omega[1]*omega[2] - c[1]*(pow(omega[0],2) + pow(omega[2],2)) - omega[0]*omega[1]*a[6][0] + pow(omega[0],2)*a[6][1] + pow(omega[2],2)*a[6][1] - omega[1]*omega[2]*a[6][2]))/(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2));

                a1[6][2] = (c1[2]*(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)) + ((-1 + cos(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))))*omega[0]*omega[2] + omega[1]*sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))*sin(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))))*(c[0] - a[6][0]) - 2*sin(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))/2.)*(cos(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))/2.)*omega[0]*sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)) + omega[1]*omega[2]*sin(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))/2.))*(c[1] - a[6][1]) - (cos(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)))*(pow(omega[0],2) + pow(omega[1],2)) + pow(omega[2],2))*(c[2] - a[6][2]))/(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2));

                a1[7][0] = (-(c[0]*pow(omega[0],2)) + c1[0]*pow(omega[0],2) - c[1]*omega[0]*omega[1] + c1[0]*pow(omega[1],2) - c[2]*omega[0]*omega[2] + c1[0]*pow(omega[2],2) + pow(omega[0],2)*a[7][0] + omega[0]*omega[1]*a[7][1] + omega[0]*omega[2]*a[7][2] - sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))*sin(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)))*(c[2]*omega[1] - c[1]*omega[2] + omega[2]*a[7][1] - omega[1]*a[7][2]) + cos(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)))*(c[1]*omega[0]*omega[1] + c[2]*omega[0]*omega[2] - c[0]*(pow(omega[1],2) + pow(omega[2],2)) + pow(omega[1],2)*a[7][0] + pow(omega[2],2)*a[7][0] - omega[0]*omega[1]*a[7][1] - omega[0]*omega[2]*a[7][2]))/(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2));

                a1[7][1] = (c1[1]*pow(omega[0],2) - c[0]*omega[0]*omega[1] - c[1]*pow(omega[1],2) + c1[1]*pow(omega[1],2) - c[2]*omega[1]*omega[2] + c1[1]*pow(omega[2],2) + omega[0]*omega[1]*a[7][0] + pow(omega[1],2)*a[7][1] + omega[1]*omega[2]*a[7][2] + sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))*sin(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)))*(c[2]*omega[0] - c[0]*omega[2] + omega[2]*a[7][0] - omega[0]*a[7][2]) + cos(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)))*(c[0]*omega[0]*omega[1] + c[2]*omega[1]*omega[2] - c[1]*(pow(omega[0],2) + pow(omega[2],2)) - omega[0]*omega[1]*a[7][0] + pow(omega[0],2)*a[7][1] + pow(omega[2],2)*a[7][1] - omega[1]*omega[2]*a[7][2]))/(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2));

                a1[7][2] = (c1[2]*(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)) + ((-1 + cos(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))))*omega[0]*omega[2] + omega[1]*sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))*sin(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))))*(c[0] - a[7][0]) - 2*sin(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))/2.)*(cos(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))/2.)*omega[0]*sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)) + omega[1]*omega[2]*sin(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))/2.))*(c[1] - a[7][1]) - (cos(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)))*(pow(omega[0],2) + pow(omega[1],2)) + pow(omega[2],2))*(c[2] - a[7][2]))/(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2));

                a1[8][0] = (-(c[0]*pow(omega[0],2)) + c1[0]*pow(omega[0],2) - c[1]*omega[0]*omega[1] + c1[0]*pow(omega[1],2) - c[2]*omega[0]*omega[2] + c1[0]*pow(omega[2],2) + pow(omega[0],2)*a[8][0] + omega[0]*omega[1]*a[8][1] + omega[0]*omega[2]*a[8][2] - sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))*sin(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)))*(c[2]*omega[1] - c[1]*omega[2] + omega[2]*a[8][1] - omega[1]*a[8][2]) + cos(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)))*(c[1]*omega[0]*omega[1] + c[2]*omega[0]*omega[2] - c[0]*(pow(omega[1],2) + pow(omega[2],2)) + pow(omega[1],2)*a[8][0] + pow(omega[2],2)*a[8][0] - omega[0]*omega[1]*a[8][1] - omega[0]*omega[2]*a[8][2]))/(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2));

                a1[8][1] = (c1[1]*pow(omega[0],2) - c[0]*omega[0]*omega[1] - c[1]*pow(omega[1],2) + c1[1]*pow(omega[1],2) - c[2]*omega[1]*omega[2] + c1[1]*pow(omega[2],2) + omega[0]*omega[1]*a[8][0] + pow(omega[1],2)*a[8][1] + omega[1]*omega[2]*a[8][2] + sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))*sin(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)))*(c[2]*omega[0] - c[0]*omega[2] + omega[2]*a[8][0] - omega[0]*a[8][2]) + cos(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)))*(c[0]*omega[0]*omega[1] + c[2]*omega[1]*omega[2] - c[1]*(pow(omega[0],2) + pow(omega[2],2)) - omega[0]*omega[1]*a[8][0] + pow(omega[0],2)*a[8][1] + pow(omega[2],2)*a[8][1] - omega[1]*omega[2]*a[8][2]))/(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2));

                a1[8][2] = (c1[2]*(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)) + ((-1 + cos(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))))*omega[0]*omega[2] + omega[1]*sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))*sin(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))))*(c[0] - a[8][0]) - 2*sin(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))/2.)*(cos(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))/2.)*omega[0]*sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)) + omega[1]*omega[2]*sin(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))/2.))*(c[1] - a[8][1]) - (cos(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)))*(pow(omega[0],2) + pow(omega[1],2)) + pow(omega[2],2))*(c[2] - a[8][2]))/(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2));

            }

            break;

        case 10:
            c1[0] = c[0] + sqrt(2)*sqrt(DCargoTranslation)*sqrt(dt)*Dbc[0] + dt*muCargoTranslation*(Fsteric[0] + Ftrap[0] + FmRadial[0][0] + FmRadial[1][0] + FmRadial[2][0] + FmRadial[3][0] + FmRadial[4][0] + FmRadial[5][0] + FmRadial[6][0] + FmRadial[7][0] + FmRadial[8][0] + FmRadial[9][0] + FmTangential[0][0] + FmTangential[1][0] + FmTangential[2][0] + FmTangential[3][0] + FmTangential[4][0] + FmTangential[5][0] + FmTangential[6][0] + FmTangential[7][0] + FmTangential[8][0] + FmTangential[9][0]);

            c1[1] = c[1] + sqrt(2)*sqrt(DCargoTranslation)*sqrt(dt)*Dbc[1] + dt*muCargoTranslation*(Fsteric[1] + Ftrap[1] + FmRadial[0][1] + FmRadial[1][1] + FmRadial[2][1] + FmRadial[3][1] + FmRadial[4][1] + FmRadial[5][1] + FmRadial[6][1] + FmRadial[7][1] + FmRadial[8][1] + FmRadial[9][1] + FmTangential[0][1] + FmTangential[1][1] + FmTangential[2][1] + FmTangential[3][1] + FmTangential[4][1] + FmTangential[5][1] + FmTangential[6][1] + FmTangential[7][1] + FmTangential[8][1] + FmTangential[9][1]);

            c1[2] = c[2] + sqrt(2)*sqrt(DCargoTranslation)*sqrt(dt)*Dbc[2] + dt*muCargoTranslation*(Fsteric[2] + Ftrap[2] + FmRadial[0][2] + FmRadial[1][2] + FmRadial[2][2] + FmRadial[3][2] + FmRadial[4][2] + FmRadial[5][2] + FmRadial[6][2] + FmRadial[7][2] + FmRadial[8][2] + FmRadial[9][2] + FmTangential[0][2] + FmTangential[1][2] + FmTangential[2][2] + FmTangential[3][2] + FmTangential[4][2] + FmTangential[5][2] + FmTangential[6][2] + FmTangential[7][2] + FmTangential[8][2] + FmTangential[9][2]);

            theta1[0] = sqrt(2)*sqrt(DCargoRotation)*sqrt(dt)*Rbc[0] + theta[0] + dt*muCargoRotation*(TorqeExt[0] - a[0][2]*FmTangential[0][1] - c[1]*FmTangential[0][2] + a[0][1]*FmTangential[0][2] - a[1][2]*FmTangential[1][1] - c[1]*FmTangential[1][2] + a[1][1]*FmTangential[1][2] - a[2][2]*FmTangential[2][1] - c[1]*FmTangential[2][2] + a[2][1]*FmTangential[2][2] - a[3][2]*FmTangential[3][1] - c[1]*FmTangential[3][2] + a[3][1]*FmTangential[3][2] - a[4][2]*FmTangential[4][1] - c[1]*FmTangential[4][2] + a[4][1]*FmTangential[4][2] - a[5][2]*FmTangential[5][1] - c[1]*FmTangential[5][2] + a[5][1]*FmTangential[5][2] - a[6][2]*FmTangential[6][1] - c[1]*FmTangential[6][2] + a[6][1]*FmTangential[6][2] - a[7][2]*FmTangential[7][1] - c[1]*FmTangential[7][2] + a[7][1]*FmTangential[7][2] - a[8][2]*FmTangential[8][1] - c[1]*FmTangential[8][2] + a[8][1]*FmTangential[8][2] - a[9][2]*FmTangential[9][1] + c[2]*(FmTangential[0][1] + FmTangential[1][1] + FmTangential[2][1] + FmTangential[3][1] + FmTangential[4][1] + FmTangential[5][1] + FmTangential[6][1] + FmTangential[7][1] + FmTangential[8][1] + FmTangential[9][1]) - c[1]*FmTangential[9][2] + a[9][1]*FmTangential[9][2]);

            theta1[1] = sqrt(2)*sqrt(DCargoRotation)*sqrt(dt)*Rbc[1] + theta[1] + dt*muCargoRotation*(TorqeExt[1] + a[0][2]*FmTangential[0][0] + c[0]*FmTangential[0][2] - a[0][0]*FmTangential[0][2] + a[1][2]*FmTangential[1][0] + c[0]*FmTangential[1][2] - a[1][0]*FmTangential[1][2] + a[2][2]*FmTangential[2][0] + c[0]*FmTangential[2][2] - a[2][0]*FmTangential[2][2] + a[3][2]*FmTangential[3][0] + c[0]*FmTangential[3][2] - a[3][0]*FmTangential[3][2] + a[4][2]*FmTangential[4][0] + c[0]*FmTangential[4][2] - a[4][0]*FmTangential[4][2] + a[5][2]*FmTangential[5][0] + c[0]*FmTangential[5][2] - a[5][0]*FmTangential[5][2] + a[6][2]*FmTangential[6][0] + c[0]*FmTangential[6][2] - a[6][0]*FmTangential[6][2] + a[7][2]*FmTangential[7][0] + c[0]*FmTangential[7][2] - a[7][0]*FmTangential[7][2] + a[8][2]*FmTangential[8][0] + c[0]*FmTangential[8][2] - a[8][0]*FmTangential[8][2] + a[9][2]*FmTangential[9][0] - c[2]*(FmTangential[0][0] + FmTangential[1][0] + FmTangential[2][0] + FmTangential[3][0] + FmTangential[4][0] + FmTangential[5][0] + FmTangential[6][0] + FmTangential[7][0] + FmTangential[8][0] + FmTangential[9][0]) + c[0]*FmTangential[9][2] - a[9][0]*FmTangential[9][2]);

            theta1[2] = sqrt(2)*sqrt(DCargoRotation)*sqrt(dt)*Rbc[2] + theta[2] + dt*muCargoRotation*(TorqeExt[2] - a[0][1]*FmTangential[0][0] - c[0]*FmTangential[0][1] + a[0][0]*FmTangential[0][1] - a[1][1]*FmTangential[1][0] - c[0]*FmTangential[1][1] + a[1][0]*FmTangential[1][1] - a[2][1]*FmTangential[2][0] - c[0]*FmTangential[2][1] + a[2][0]*FmTangential[2][1] - a[3][1]*FmTangential[3][0] - c[0]*FmTangential[3][1] + a[3][0]*FmTangential[3][1] - a[4][1]*FmTangential[4][0] - c[0]*FmTangential[4][1] + a[4][0]*FmTangential[4][1] - a[5][1]*FmTangential[5][0] - c[0]*FmTangential[5][1] + a[5][0]*FmTangential[5][1] - a[6][1]*FmTangential[6][0] - c[0]*FmTangential[6][1] + a[6][0]*FmTangential[6][1] - a[7][1]*FmTangential[7][0] - c[0]*FmTangential[7][1] + a[7][0]*FmTangential[7][1] - a[8][1]*FmTangential[8][0] - c[0]*FmTangential[8][1] + a[8][0]*FmTangential[8][1] - a[9][1]*FmTangential[9][0] + c[1]*(FmTangential[0][0] + FmTangential[1][0] + FmTangential[2][0] + FmTangential[3][0] + FmTangential[4][0] + FmTangential[5][0] + FmTangential[6][0] + FmTangential[7][0] + FmTangential[8][0] + FmTangential[9][0]) - c[0]*FmTangential[9][1] + a[9][0]*FmTangential[9][1]);

            omega[0] = theta1[0]-theta[0];
            omega[1] = theta1[1]-theta[1];
            omega[2] = theta1[2]-theta[2];

            if(sqrt(omega[0]*omega[0] + omega[1]*omega[1] + omega[2]*omega[2])<1E-12){

                a1[0][0] = -c[0] + c1[0] + a[0][0];

                a1[0][1] = -c[1] + c1[1] + a[0][1];

                a1[0][2] = -c[2] + c1[2] + a[0][2];

                a1[1][0] = -c[0] + c1[0] + a[1][0];

                a1[1][1] = -c[1] + c1[1] + a[1][1];

                a1[1][2] = -c[2] + c1[2] + a[1][2];

                a1[2][0] = -c[0] + c1[0] + a[2][0];

                a1[2][1] = -c[1] + c1[1] + a[2][1];

                a1[2][2] = -c[2] + c1[2] + a[2][2];

                a1[3][0] = -c[0] + c1[0] + a[3][0];

                a1[3][1] = -c[1] + c1[1] + a[3][1];

                a1[3][2] = -c[2] + c1[2] + a[3][2];

                a1[4][0] = -c[0] + c1[0] + a[4][0];

                a1[4][1] = -c[1] + c1[1] + a[4][1];

                a1[4][2] = -c[2] + c1[2] + a[4][2];

                a1[5][0] = -c[0] + c1[0] + a[5][0];

                a1[5][1] = -c[1] + c1[1] + a[5][1];

                a1[5][2] = -c[2] + c1[2] + a[5][2];

                a1[6][0] = -c[0] + c1[0] + a[6][0];

                a1[6][1] = -c[1] + c1[1] + a[6][1];

                a1[6][2] = -c[2] + c1[2] + a[6][2];

                a1[7][0] = -c[0] + c1[0] + a[7][0];

                a1[7][1] = -c[1] + c1[1] + a[7][1];

                a1[7][2] = -c[2] + c1[2] + a[7][2];

                a1[8][0] = -c[0] + c1[0] + a[8][0];

                a1[8][1] = -c[1] + c1[1] + a[8][1];

                a1[8][2] = -c[2] + c1[2] + a[8][2];

                a1[9][0] = -c[0] + c1[0] + a[9][0];

                a1[9][1] = -c[1] + c1[1] + a[9][1];

                a1[9][2] = -c[2] + c1[2] + a[9][2];

            }else{

                a1[0][0] = (-(c[0]*pow(omega[0],2)) + c1[0]*pow(omega[0],2) - c[1]*omega[0]*omega[1] + c1[0]*pow(omega[1],2) - c[2]*omega[0]*omega[2] + c1[0]*pow(omega[2],2) + pow(omega[0],2)*a[0][0] + omega[0]*omega[1]*a[0][1] + omega[0]*omega[2]*a[0][2] - sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))*sin(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)))*(c[2]*omega[1] - c[1]*omega[2] + omega[2]*a[0][1] - omega[1]*a[0][2]) + cos(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)))*(c[1]*omega[0]*omega[1] + c[2]*omega[0]*omega[2] - c[0]*(pow(omega[1],2) + pow(omega[2],2)) + pow(omega[1],2)*a[0][0] + pow(omega[2],2)*a[0][0] - omega[0]*omega[1]*a[0][1] - omega[0]*omega[2]*a[0][2]))/(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2));

                a1[0][1] = (c1[1]*pow(omega[0],2) - c[0]*omega[0]*omega[1] - c[1]*pow(omega[1],2) + c1[1]*pow(omega[1],2) - c[2]*omega[1]*omega[2] + c1[1]*pow(omega[2],2) + omega[0]*omega[1]*a[0][0] + pow(omega[1],2)*a[0][1] + omega[1]*omega[2]*a[0][2] + sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))*sin(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)))*(c[2]*omega[0] - c[0]*omega[2] + omega[2]*a[0][0] - omega[0]*a[0][2]) + cos(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)))*(c[0]*omega[0]*omega[1] + c[2]*omega[1]*omega[2] - c[1]*(pow(omega[0],2) + pow(omega[2],2)) - omega[0]*omega[1]*a[0][0] + pow(omega[0],2)*a[0][1] + pow(omega[2],2)*a[0][1] - omega[1]*omega[2]*a[0][2]))/(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2));

                a1[0][2] = (c1[2]*(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)) + ((-1 + cos(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))))*omega[0]*omega[2] + omega[1]*sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))*sin(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))))*(c[0] - a[0][0]) - 2*sin(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))/2.)*(cos(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))/2.)*omega[0]*sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)) + omega[1]*omega[2]*sin(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))/2.))*(c[1] - a[0][1]) - (cos(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)))*(pow(omega[0],2) + pow(omega[1],2)) + pow(omega[2],2))*(c[2] - a[0][2]))/(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2));

                a1[1][0] = (-(c[0]*pow(omega[0],2)) + c1[0]*pow(omega[0],2) - c[1]*omega[0]*omega[1] + c1[0]*pow(omega[1],2) - c[2]*omega[0]*omega[2] + c1[0]*pow(omega[2],2) + pow(omega[0],2)*a[1][0] + omega[0]*omega[1]*a[1][1] + omega[0]*omega[2]*a[1][2] - sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))*sin(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)))*(c[2]*omega[1] - c[1]*omega[2] + omega[2]*a[1][1] - omega[1]*a[1][2]) + cos(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)))*(c[1]*omega[0]*omega[1] + c[2]*omega[0]*omega[2] - c[0]*(pow(omega[1],2) + pow(omega[2],2)) + pow(omega[1],2)*a[1][0] + pow(omega[2],2)*a[1][0] - omega[0]*omega[1]*a[1][1] - omega[0]*omega[2]*a[1][2]))/(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2));

                a1[1][1] = (c1[1]*pow(omega[0],2) - c[0]*omega[0]*omega[1] - c[1]*pow(omega[1],2) + c1[1]*pow(omega[1],2) - c[2]*omega[1]*omega[2] + c1[1]*pow(omega[2],2) + omega[0]*omega[1]*a[1][0] + pow(omega[1],2)*a[1][1] + omega[1]*omega[2]*a[1][2] + sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))*sin(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)))*(c[2]*omega[0] - c[0]*omega[2] + omega[2]*a[1][0] - omega[0]*a[1][2]) + cos(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)))*(c[0]*omega[0]*omega[1] + c[2]*omega[1]*omega[2] - c[1]*(pow(omega[0],2) + pow(omega[2],2)) - omega[0]*omega[1]*a[1][0] + pow(omega[0],2)*a[1][1] + pow(omega[2],2)*a[1][1] - omega[1]*omega[2]*a[1][2]))/(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2));

                a1[1][2] = (c1[2]*(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)) + ((-1 + cos(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))))*omega[0]*omega[2] + omega[1]*sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))*sin(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))))*(c[0] - a[1][0]) - 2*sin(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))/2.)*(cos(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))/2.)*omega[0]*sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)) + omega[1]*omega[2]*sin(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))/2.))*(c[1] - a[1][1]) - (cos(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)))*(pow(omega[0],2) + pow(omega[1],2)) + pow(omega[2],2))*(c[2] - a[1][2]))/(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2));

                a1[2][0] = (-(c[0]*pow(omega[0],2)) + c1[0]*pow(omega[0],2) - c[1]*omega[0]*omega[1] + c1[0]*pow(omega[1],2) - c[2]*omega[0]*omega[2] + c1[0]*pow(omega[2],2) + pow(omega[0],2)*a[2][0] + omega[0]*omega[1]*a[2][1] + omega[0]*omega[2]*a[2][2] - sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))*sin(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)))*(c[2]*omega[1] - c[1]*omega[2] + omega[2]*a[2][1] - omega[1]*a[2][2]) + cos(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)))*(c[1]*omega[0]*omega[1] + c[2]*omega[0]*omega[2] - c[0]*(pow(omega[1],2) + pow(omega[2],2)) + pow(omega[1],2)*a[2][0] + pow(omega[2],2)*a[2][0] - omega[0]*omega[1]*a[2][1] - omega[0]*omega[2]*a[2][2]))/(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2));

                a1[2][1] = (c1[1]*pow(omega[0],2) - c[0]*omega[0]*omega[1] - c[1]*pow(omega[1],2) + c1[1]*pow(omega[1],2) - c[2]*omega[1]*omega[2] + c1[1]*pow(omega[2],2) + omega[0]*omega[1]*a[2][0] + pow(omega[1],2)*a[2][1] + omega[1]*omega[2]*a[2][2] + sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))*sin(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)))*(c[2]*omega[0] - c[0]*omega[2] + omega[2]*a[2][0] - omega[0]*a[2][2]) + cos(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)))*(c[0]*omega[0]*omega[1] + c[2]*omega[1]*omega[2] - c[1]*(pow(omega[0],2) + pow(omega[2],2)) - omega[0]*omega[1]*a[2][0] + pow(omega[0],2)*a[2][1] + pow(omega[2],2)*a[2][1] - omega[1]*omega[2]*a[2][2]))/(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2));

                a1[2][2] = (c1[2]*(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)) + ((-1 + cos(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))))*omega[0]*omega[2] + omega[1]*sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))*sin(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))))*(c[0] - a[2][0]) - 2*sin(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))/2.)*(cos(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))/2.)*omega[0]*sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)) + omega[1]*omega[2]*sin(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))/2.))*(c[1] - a[2][1]) - (cos(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)))*(pow(omega[0],2) + pow(omega[1],2)) + pow(omega[2],2))*(c[2] - a[2][2]))/(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2));

                a1[3][0] = (-(c[0]*pow(omega[0],2)) + c1[0]*pow(omega[0],2) - c[1]*omega[0]*omega[1] + c1[0]*pow(omega[1],2) - c[2]*omega[0]*omega[2] + c1[0]*pow(omega[2],2) + pow(omega[0],2)*a[3][0] + omega[0]*omega[1]*a[3][1] + omega[0]*omega[2]*a[3][2] - sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))*sin(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)))*(c[2]*omega[1] - c[1]*omega[2] + omega[2]*a[3][1] - omega[1]*a[3][2]) + cos(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)))*(c[1]*omega[0]*omega[1] + c[2]*omega[0]*omega[2] - c[0]*(pow(omega[1],2) + pow(omega[2],2)) + pow(omega[1],2)*a[3][0] + pow(omega[2],2)*a[3][0] - omega[0]*omega[1]*a[3][1] - omega[0]*omega[2]*a[3][2]))/(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2));

                a1[3][1] = (c1[1]*pow(omega[0],2) - c[0]*omega[0]*omega[1] - c[1]*pow(omega[1],2) + c1[1]*pow(omega[1],2) - c[2]*omega[1]*omega[2] + c1[1]*pow(omega[2],2) + omega[0]*omega[1]*a[3][0] + pow(omega[1],2)*a[3][1] + omega[1]*omega[2]*a[3][2] + sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))*sin(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)))*(c[2]*omega[0] - c[0]*omega[2] + omega[2]*a[3][0] - omega[0]*a[3][2]) + cos(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)))*(c[0]*omega[0]*omega[1] + c[2]*omega[1]*omega[2] - c[1]*(pow(omega[0],2) + pow(omega[2],2)) - omega[0]*omega[1]*a[3][0] + pow(omega[0],2)*a[3][1] + pow(omega[2],2)*a[3][1] - omega[1]*omega[2]*a[3][2]))/(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2));

                a1[3][2] = (c1[2]*(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)) + ((-1 + cos(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))))*omega[0]*omega[2] + omega[1]*sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))*sin(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))))*(c[0] - a[3][0]) - 2*sin(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))/2.)*(cos(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))/2.)*omega[0]*sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)) + omega[1]*omega[2]*sin(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))/2.))*(c[1] - a[3][1]) - (cos(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)))*(pow(omega[0],2) + pow(omega[1],2)) + pow(omega[2],2))*(c[2] - a[3][2]))/(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2));

                a1[4][0] = (-(c[0]*pow(omega[0],2)) + c1[0]*pow(omega[0],2) - c[1]*omega[0]*omega[1] + c1[0]*pow(omega[1],2) - c[2]*omega[0]*omega[2] + c1[0]*pow(omega[2],2) + pow(omega[0],2)*a[4][0] + omega[0]*omega[1]*a[4][1] + omega[0]*omega[2]*a[4][2] - sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))*sin(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)))*(c[2]*omega[1] - c[1]*omega[2] + omega[2]*a[4][1] - omega[1]*a[4][2]) + cos(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)))*(c[1]*omega[0]*omega[1] + c[2]*omega[0]*omega[2] - c[0]*(pow(omega[1],2) + pow(omega[2],2)) + pow(omega[1],2)*a[4][0] + pow(omega[2],2)*a[4][0] - omega[0]*omega[1]*a[4][1] - omega[0]*omega[2]*a[4][2]))/(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2));

                a1[4][1] = (c1[1]*pow(omega[0],2) - c[0]*omega[0]*omega[1] - c[1]*pow(omega[1],2) + c1[1]*pow(omega[1],2) - c[2]*omega[1]*omega[2] + c1[1]*pow(omega[2],2) + omega[0]*omega[1]*a[4][0] + pow(omega[1],2)*a[4][1] + omega[1]*omega[2]*a[4][2] + sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))*sin(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)))*(c[2]*omega[0] - c[0]*omega[2] + omega[2]*a[4][0] - omega[0]*a[4][2]) + cos(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)))*(c[0]*omega[0]*omega[1] + c[2]*omega[1]*omega[2] - c[1]*(pow(omega[0],2) + pow(omega[2],2)) - omega[0]*omega[1]*a[4][0] + pow(omega[0],2)*a[4][1] + pow(omega[2],2)*a[4][1] - omega[1]*omega[2]*a[4][2]))/(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2));

                a1[4][2] = (c1[2]*(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)) + ((-1 + cos(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))))*omega[0]*omega[2] + omega[1]*sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))*sin(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))))*(c[0] - a[4][0]) - 2*sin(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))/2.)*(cos(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))/2.)*omega[0]*sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)) + omega[1]*omega[2]*sin(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))/2.))*(c[1] - a[4][1]) - (cos(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)))*(pow(omega[0],2) + pow(omega[1],2)) + pow(omega[2],2))*(c[2] - a[4][2]))/(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2));

                a1[5][0] = (-(c[0]*pow(omega[0],2)) + c1[0]*pow(omega[0],2) - c[1]*omega[0]*omega[1] + c1[0]*pow(omega[1],2) - c[2]*omega[0]*omega[2] + c1[0]*pow(omega[2],2) + pow(omega[0],2)*a[5][0] + omega[0]*omega[1]*a[5][1] + omega[0]*omega[2]*a[5][2] - sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))*sin(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)))*(c[2]*omega[1] - c[1]*omega[2] + omega[2]*a[5][1] - omega[1]*a[5][2]) + cos(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)))*(c[1]*omega[0]*omega[1] + c[2]*omega[0]*omega[2] - c[0]*(pow(omega[1],2) + pow(omega[2],2)) + pow(omega[1],2)*a[5][0] + pow(omega[2],2)*a[5][0] - omega[0]*omega[1]*a[5][1] - omega[0]*omega[2]*a[5][2]))/(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2));

                a1[5][1] = (c1[1]*pow(omega[0],2) - c[0]*omega[0]*omega[1] - c[1]*pow(omega[1],2) + c1[1]*pow(omega[1],2) - c[2]*omega[1]*omega[2] + c1[1]*pow(omega[2],2) + omega[0]*omega[1]*a[5][0] + pow(omega[1],2)*a[5][1] + omega[1]*omega[2]*a[5][2] + sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))*sin(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)))*(c[2]*omega[0] - c[0]*omega[2] + omega[2]*a[5][0] - omega[0]*a[5][2]) + cos(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)))*(c[0]*omega[0]*omega[1] + c[2]*omega[1]*omega[2] - c[1]*(pow(omega[0],2) + pow(omega[2],2)) - omega[0]*omega[1]*a[5][0] + pow(omega[0],2)*a[5][1] + pow(omega[2],2)*a[5][1] - omega[1]*omega[2]*a[5][2]))/(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2));

                a1[5][2] = (c1[2]*(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)) + ((-1 + cos(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))))*omega[0]*omega[2] + omega[1]*sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))*sin(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))))*(c[0] - a[5][0]) - 2*sin(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))/2.)*(cos(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))/2.)*omega[0]*sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)) + omega[1]*omega[2]*sin(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))/2.))*(c[1] - a[5][1]) - (cos(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)))*(pow(omega[0],2) + pow(omega[1],2)) + pow(omega[2],2))*(c[2] - a[5][2]))/(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2));

                a1[6][0] = (-(c[0]*pow(omega[0],2)) + c1[0]*pow(omega[0],2) - c[1]*omega[0]*omega[1] + c1[0]*pow(omega[1],2) - c[2]*omega[0]*omega[2] + c1[0]*pow(omega[2],2) + pow(omega[0],2)*a[6][0] + omega[0]*omega[1]*a[6][1] + omega[0]*omega[2]*a[6][2] - sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))*sin(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)))*(c[2]*omega[1] - c[1]*omega[2] + omega[2]*a[6][1] - omega[1]*a[6][2]) + cos(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)))*(c[1]*omega[0]*omega[1] + c[2]*omega[0]*omega[2] - c[0]*(pow(omega[1],2) + pow(omega[2],2)) + pow(omega[1],2)*a[6][0] + pow(omega[2],2)*a[6][0] - omega[0]*omega[1]*a[6][1] - omega[0]*omega[2]*a[6][2]))/(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2));

                a1[6][1] = (c1[1]*pow(omega[0],2) - c[0]*omega[0]*omega[1] - c[1]*pow(omega[1],2) + c1[1]*pow(omega[1],2) - c[2]*omega[1]*omega[2] + c1[1]*pow(omega[2],2) + omega[0]*omega[1]*a[6][0] + pow(omega[1],2)*a[6][1] + omega[1]*omega[2]*a[6][2] + sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))*sin(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)))*(c[2]*omega[0] - c[0]*omega[2] + omega[2]*a[6][0] - omega[0]*a[6][2]) + cos(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)))*(c[0]*omega[0]*omega[1] + c[2]*omega[1]*omega[2] - c[1]*(pow(omega[0],2) + pow(omega[2],2)) - omega[0]*omega[1]*a[6][0] + pow(omega[0],2)*a[6][1] + pow(omega[2],2)*a[6][1] - omega[1]*omega[2]*a[6][2]))/(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2));

                a1[6][2] = (c1[2]*(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)) + ((-1 + cos(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))))*omega[0]*omega[2] + omega[1]*sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))*sin(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))))*(c[0] - a[6][0]) - 2*sin(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))/2.)*(cos(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))/2.)*omega[0]*sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)) + omega[1]*omega[2]*sin(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))/2.))*(c[1] - a[6][1]) - (cos(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)))*(pow(omega[0],2) + pow(omega[1],2)) + pow(omega[2],2))*(c[2] - a[6][2]))/(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2));

                a1[7][0] = (-(c[0]*pow(omega[0],2)) + c1[0]*pow(omega[0],2) - c[1]*omega[0]*omega[1] + c1[0]*pow(omega[1],2) - c[2]*omega[0]*omega[2] + c1[0]*pow(omega[2],2) + pow(omega[0],2)*a[7][0] + omega[0]*omega[1]*a[7][1] + omega[0]*omega[2]*a[7][2] - sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))*sin(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)))*(c[2]*omega[1] - c[1]*omega[2] + omega[2]*a[7][1] - omega[1]*a[7][2]) + cos(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)))*(c[1]*omega[0]*omega[1] + c[2]*omega[0]*omega[2] - c[0]*(pow(omega[1],2) + pow(omega[2],2)) + pow(omega[1],2)*a[7][0] + pow(omega[2],2)*a[7][0] - omega[0]*omega[1]*a[7][1] - omega[0]*omega[2]*a[7][2]))/(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2));

                a1[7][1] = (c1[1]*pow(omega[0],2) - c[0]*omega[0]*omega[1] - c[1]*pow(omega[1],2) + c1[1]*pow(omega[1],2) - c[2]*omega[1]*omega[2] + c1[1]*pow(omega[2],2) + omega[0]*omega[1]*a[7][0] + pow(omega[1],2)*a[7][1] + omega[1]*omega[2]*a[7][2] + sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))*sin(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)))*(c[2]*omega[0] - c[0]*omega[2] + omega[2]*a[7][0] - omega[0]*a[7][2]) + cos(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)))*(c[0]*omega[0]*omega[1] + c[2]*omega[1]*omega[2] - c[1]*(pow(omega[0],2) + pow(omega[2],2)) - omega[0]*omega[1]*a[7][0] + pow(omega[0],2)*a[7][1] + pow(omega[2],2)*a[7][1] - omega[1]*omega[2]*a[7][2]))/(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2));

                a1[7][2] = (c1[2]*(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)) + ((-1 + cos(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))))*omega[0]*omega[2] + omega[1]*sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))*sin(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))))*(c[0] - a[7][0]) - 2*sin(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))/2.)*(cos(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))/2.)*omega[0]*sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)) + omega[1]*omega[2]*sin(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))/2.))*(c[1] - a[7][1]) - (cos(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)))*(pow(omega[0],2) + pow(omega[1],2)) + pow(omega[2],2))*(c[2] - a[7][2]))/(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2));

                a1[8][0] = (-(c[0]*pow(omega[0],2)) + c1[0]*pow(omega[0],2) - c[1]*omega[0]*omega[1] + c1[0]*pow(omega[1],2) - c[2]*omega[0]*omega[2] + c1[0]*pow(omega[2],2) + pow(omega[0],2)*a[8][0] + omega[0]*omega[1]*a[8][1] + omega[0]*omega[2]*a[8][2] - sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))*sin(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)))*(c[2]*omega[1] - c[1]*omega[2] + omega[2]*a[8][1] - omega[1]*a[8][2]) + cos(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)))*(c[1]*omega[0]*omega[1] + c[2]*omega[0]*omega[2] - c[0]*(pow(omega[1],2) + pow(omega[2],2)) + pow(omega[1],2)*a[8][0] + pow(omega[2],2)*a[8][0] - omega[0]*omega[1]*a[8][1] - omega[0]*omega[2]*a[8][2]))/(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2));

                a1[8][1] = (c1[1]*pow(omega[0],2) - c[0]*omega[0]*omega[1] - c[1]*pow(omega[1],2) + c1[1]*pow(omega[1],2) - c[2]*omega[1]*omega[2] + c1[1]*pow(omega[2],2) + omega[0]*omega[1]*a[8][0] + pow(omega[1],2)*a[8][1] + omega[1]*omega[2]*a[8][2] + sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))*sin(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)))*(c[2]*omega[0] - c[0]*omega[2] + omega[2]*a[8][0] - omega[0]*a[8][2]) + cos(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)))*(c[0]*omega[0]*omega[1] + c[2]*omega[1]*omega[2] - c[1]*(pow(omega[0],2) + pow(omega[2],2)) - omega[0]*omega[1]*a[8][0] + pow(omega[0],2)*a[8][1] + pow(omega[2],2)*a[8][1] - omega[1]*omega[2]*a[8][2]))/(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2));

                a1[8][2] = (c1[2]*(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)) + ((-1 + cos(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))))*omega[0]*omega[2] + omega[1]*sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))*sin(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))))*(c[0] - a[8][0]) - 2*sin(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))/2.)*(cos(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))/2.)*omega[0]*sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)) + omega[1]*omega[2]*sin(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))/2.))*(c[1] - a[8][1]) - (cos(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)))*(pow(omega[0],2) + pow(omega[1],2)) + pow(omega[2],2))*(c[2] - a[8][2]))/(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2));

                a1[9][0] = (-(c[0]*pow(omega[0],2)) + c1[0]*pow(omega[0],2) - c[1]*omega[0]*omega[1] + c1[0]*pow(omega[1],2) - c[2]*omega[0]*omega[2] + c1[0]*pow(omega[2],2) + pow(omega[0],2)*a[9][0] + omega[0]*omega[1]*a[9][1] + omega[0]*omega[2]*a[9][2] - sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))*sin(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)))*(c[2]*omega[1] - c[1]*omega[2] + omega[2]*a[9][1] - omega[1]*a[9][2]) + cos(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)))*(c[1]*omega[0]*omega[1] + c[2]*omega[0]*omega[2] - c[0]*(pow(omega[1],2) + pow(omega[2],2)) + pow(omega[1],2)*a[9][0] + pow(omega[2],2)*a[9][0] - omega[0]*omega[1]*a[9][1] - omega[0]*omega[2]*a[9][2]))/(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2));

                a1[9][1] = (c1[1]*pow(omega[0],2) - c[0]*omega[0]*omega[1] - c[1]*pow(omega[1],2) + c1[1]*pow(omega[1],2) - c[2]*omega[1]*omega[2] + c1[1]*pow(omega[2],2) + omega[0]*omega[1]*a[9][0] + pow(omega[1],2)*a[9][1] + omega[1]*omega[2]*a[9][2] + sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))*sin(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)))*(c[2]*omega[0] - c[0]*omega[2] + omega[2]*a[9][0] - omega[0]*a[9][2]) + cos(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)))*(c[0]*omega[0]*omega[1] + c[2]*omega[1]*omega[2] - c[1]*(pow(omega[0],2) + pow(omega[2],2)) - omega[0]*omega[1]*a[9][0] + pow(omega[0],2)*a[9][1] + pow(omega[2],2)*a[9][1] - omega[1]*omega[2]*a[9][2]))/(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2));

                a1[9][2] = (c1[2]*(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)) + ((-1 + cos(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))))*omega[0]*omega[2] + omega[1]*sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))*sin(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))))*(c[0] - a[9][0]) - 2*sin(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))/2.)*(cos(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))/2.)*omega[0]*sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)) + omega[1]*omega[2]*sin(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2))/2.))*(c[1] - a[9][1]) - (cos(sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2)))*(pow(omega[0],2) + pow(omega[1],2)) + pow(omega[2],2))*(c[2] - a[9][2]))/(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2));

            }

            break;

        default:
            printf("Bad value for total_motors\n");
            exit(0);
    }
}
