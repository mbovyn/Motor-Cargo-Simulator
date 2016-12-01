//prototypes
void bead_equations();

void bead_equations(){
    switch(total_motors){
        case 0:
            c1[0] = c[0] + sqrt(2)*sqrt(DCargoTranslation)*sqrt(dt)*Dbc[0] + dt*muCargoTranslation*(Fsteric[0] + Ftrap[0]);

            c1[1] = c[1] + sqrt(2)*sqrt(DCargoTranslation)*sqrt(dt)*Dbc[1] + dt*muCargoTranslation*(Fsteric[1] + Ftrap[1]);

            c1[2] = c[2] + sqrt(2)*sqrt(DCargoTranslation)*sqrt(dt)*Dbc[2] + dt*muCargoTranslation*(Fsteric[2] + Ftrap[2]);

            theta1[0] = sqrt(2)*sqrt(DCargoRotation)*sqrt(dt)*Rbc[0] + theta[0] + dt*muCargoRotation*TorqeExt[0];

            theta1[1] = sqrt(2)*sqrt(DCargoRotation)*sqrt(dt)*Rbc[1] + theta[1] + dt*muCargoRotation*TorqeExt[1];

            theta1[2] = sqrt(2)*sqrt(DCargoRotation)*sqrt(dt)*Rbc[2] + theta[2] + dt*muCargoRotation*TorqeExt[2];

            break;

        case 1:
            c1[0] = c[0] + sqrt(2)*sqrt(DCargoTranslation)*sqrt(dt)*Dbc[0] + dt*muCargoTranslation*(Fsteric[0] + Ftrap[0] + FmRadial[0][0] + FmTangential[0][0]);

            c1[1] = c[1] + sqrt(2)*sqrt(DCargoTranslation)*sqrt(dt)*Dbc[1] + dt*muCargoTranslation*(Fsteric[1] + Ftrap[1] + FmRadial[0][1] + FmTangential[0][1]);

            c1[2] = c[2] + sqrt(2)*sqrt(DCargoTranslation)*sqrt(dt)*Dbc[2] + dt*muCargoTranslation*(Fsteric[2] + Ftrap[2] + FmRadial[0][2] + FmTangential[0][2]);

            theta1[0] = sqrt(2)*sqrt(DCargoRotation)*sqrt(dt)*Rbc[0] + theta[0] + dt*muCargoRotation*(TorqeExt[0] + c[2]*FmTangential[0][1] - a[0][2]*FmTangential[0][1] - c[1]*FmTangential[0][2] + a[0][1]*FmTangential[0][2]);

            theta1[1] = sqrt(2)*sqrt(DCargoRotation)*sqrt(dt)*Rbc[1] + theta[1] + dt*muCargoRotation*(TorqeExt[1] - c[2]*FmTangential[0][0] + a[0][2]*FmTangential[0][0] + c[0]*FmTangential[0][2] - a[0][0]*FmTangential[0][2]);

            theta1[2] = sqrt(2)*sqrt(DCargoRotation)*sqrt(dt)*Rbc[2] + theta[2] + dt*muCargoRotation*(TorqeExt[2] + c[1]*FmTangential[0][0] - a[0][1]*FmTangential[0][0] - c[0]*FmTangential[0][1] + a[0][0]*FmTangential[0][1]);

            a1[0][0] = -c[0] + c1[0] + c[2]*theta[1] - c[1]*theta[2] - c[2]*theta1[1] + c[1]*theta1[2] + a[0][0] + theta[2]*a[0][1] - theta1[2]*a[0][1] - theta[1]*a[0][2] + theta1[1]*a[0][2];

            a1[0][1] = -c[1] + c1[1] - c[2]*theta[0] + c[0]*theta[2] + c[2]*theta1[0] - c[0]*theta1[2] - theta[2]*a[0][0] + theta1[2]*a[0][0] + a[0][1] + theta[0]*a[0][2] - theta1[0]*a[0][2];

            a1[0][2] = -c[2] + c1[2] + c[1]*theta[0] - c[0]*theta[1] - c[1]*theta1[0] + c[0]*theta1[1] + theta[1]*a[0][0] - theta1[1]*a[0][0] - theta[0]*a[0][1] + theta1[0]*a[0][1] + a[0][2];

            break;

        case 2:
            c1[0] = c[0] + sqrt(2)*sqrt(DCargoTranslation)*sqrt(dt)*Dbc[0] + dt*muCargoTranslation*(Fsteric[0] + Ftrap[0] + FmRadial[0][0] + FmRadial[1][0] + FmTangential[0][0] + FmTangential[1][0]);

            c1[1] = c[1] + sqrt(2)*sqrt(DCargoTranslation)*sqrt(dt)*Dbc[1] + dt*muCargoTranslation*(Fsteric[1] + Ftrap[1] + FmRadial[0][1] + FmRadial[1][1] + FmTangential[0][1] + FmTangential[1][1]);

            c1[2] = c[2] + sqrt(2)*sqrt(DCargoTranslation)*sqrt(dt)*Dbc[2] + dt*muCargoTranslation*(Fsteric[2] + Ftrap[2] + FmRadial[0][2] + FmRadial[1][2] + FmTangential[0][2] + FmTangential[1][2]);

            theta1[0] = sqrt(2)*sqrt(DCargoRotation)*sqrt(dt)*Rbc[0] + theta[0] + dt*muCargoRotation*(TorqeExt[0] - a[0][2]*FmTangential[0][1] - c[1]*FmTangential[0][2] + a[0][1]*FmTangential[0][2] - a[1][2]*FmTangential[1][1] + c[2]*(FmTangential[0][1] + FmTangential[1][1]) - c[1]*FmTangential[1][2] + a[1][1]*FmTangential[1][2]);

            theta1[1] = sqrt(2)*sqrt(DCargoRotation)*sqrt(dt)*Rbc[1] + theta[1] + dt*muCargoRotation*(TorqeExt[1] + a[0][2]*FmTangential[0][0] + c[0]*FmTangential[0][2] - a[0][0]*FmTangential[0][2] + a[1][2]*FmTangential[1][0] - c[2]*(FmTangential[0][0] + FmTangential[1][0]) + c[0]*FmTangential[1][2] - a[1][0]*FmTangential[1][2]);

            theta1[2] = sqrt(2)*sqrt(DCargoRotation)*sqrt(dt)*Rbc[2] + theta[2] + dt*muCargoRotation*(TorqeExt[2] - a[0][1]*FmTangential[0][0] - c[0]*FmTangential[0][1] + a[0][0]*FmTangential[0][1] - a[1][1]*FmTangential[1][0] + c[1]*(FmTangential[0][0] + FmTangential[1][0]) - c[0]*FmTangential[1][1] + a[1][0]*FmTangential[1][1]);

            a1[0][0] = -c[0] + c1[0] + c[2]*theta[1] - c[1]*theta[2] - c[2]*theta1[1] + c[1]*theta1[2] + a[0][0] + theta[2]*a[0][1] - theta1[2]*a[0][1] - theta[1]*a[0][2] + theta1[1]*a[0][2];

            a1[0][1] = -c[1] + c1[1] - c[2]*theta[0] + c[0]*theta[2] + c[2]*theta1[0] - c[0]*theta1[2] - theta[2]*a[0][0] + theta1[2]*a[0][0] + a[0][1] + theta[0]*a[0][2] - theta1[0]*a[0][2];

            a1[0][2] = -c[2] + c1[2] + c[1]*theta[0] - c[0]*theta[1] - c[1]*theta1[0] + c[0]*theta1[1] + theta[1]*a[0][0] - theta1[1]*a[0][0] - theta[0]*a[0][1] + theta1[0]*a[0][1] + a[0][2];

            a1[1][0] = -c[0] + c1[0] + c[2]*theta[1] - c[1]*theta[2] - c[2]*theta1[1] + c[1]*theta1[2] + a[1][0] + theta[2]*a[1][1] - theta1[2]*a[1][1] - theta[1]*a[1][2] + theta1[1]*a[1][2];

            a1[1][1] = -c[1] + c1[1] - c[2]*theta[0] + c[0]*theta[2] + c[2]*theta1[0] - c[0]*theta1[2] - theta[2]*a[1][0] + theta1[2]*a[1][0] + a[1][1] + theta[0]*a[1][2] - theta1[0]*a[1][2];

            a1[1][2] = -c[2] + c1[2] + c[1]*theta[0] - c[0]*theta[1] - c[1]*theta1[0] + c[0]*theta1[1] + theta[1]*a[1][0] - theta1[1]*a[1][0] - theta[0]*a[1][1] + theta1[0]*a[1][1] + a[1][2];

            break;

        case 3:
            c1[0] = c[0] + sqrt(2)*sqrt(DCargoTranslation)*sqrt(dt)*Dbc[0] + dt*muCargoTranslation*(Fsteric[0] + Ftrap[0] + FmRadial[0][0] + FmRadial[1][0] + FmRadial[2][0] + FmTangential[0][0] + FmTangential[1][0] + FmTangential[2][0]);

            c1[1] = c[1] + sqrt(2)*sqrt(DCargoTranslation)*sqrt(dt)*Dbc[1] + dt*muCargoTranslation*(Fsteric[1] + Ftrap[1] + FmRadial[0][1] + FmRadial[1][1] + FmRadial[2][1] + FmTangential[0][1] + FmTangential[1][1] + FmTangential[2][1]);

            c1[2] = c[2] + sqrt(2)*sqrt(DCargoTranslation)*sqrt(dt)*Dbc[2] + dt*muCargoTranslation*(Fsteric[2] + Ftrap[2] + FmRadial[0][2] + FmRadial[1][2] + FmRadial[2][2] + FmTangential[0][2] + FmTangential[1][2] + FmTangential[2][2]);

            theta1[0] = sqrt(2)*sqrt(DCargoRotation)*sqrt(dt)*Rbc[0] + theta[0] + dt*muCargoRotation*(TorqeExt[0] - a[0][2]*FmTangential[0][1] - c[1]*FmTangential[0][2] + a[0][1]*FmTangential[0][2] - a[1][2]*FmTangential[1][1] - c[1]*FmTangential[1][2] + a[1][1]*FmTangential[1][2] - a[2][2]*FmTangential[2][1] + c[2]*(FmTangential[0][1] + FmTangential[1][1] + FmTangential[2][1]) - c[1]*FmTangential[2][2] + a[2][1]*FmTangential[2][2]);

            theta1[1] = sqrt(2)*sqrt(DCargoRotation)*sqrt(dt)*Rbc[1] + theta[1] + dt*muCargoRotation*(TorqeExt[1] + a[0][2]*FmTangential[0][0] + c[0]*FmTangential[0][2] - a[0][0]*FmTangential[0][2] + a[1][2]*FmTangential[1][0] + c[0]*FmTangential[1][2] - a[1][0]*FmTangential[1][2] + a[2][2]*FmTangential[2][0] - c[2]*(FmTangential[0][0] + FmTangential[1][0] + FmTangential[2][0]) + c[0]*FmTangential[2][2] - a[2][0]*FmTangential[2][2]);

            theta1[2] = sqrt(2)*sqrt(DCargoRotation)*sqrt(dt)*Rbc[2] + theta[2] + dt*muCargoRotation*(TorqeExt[2] - a[0][1]*FmTangential[0][0] - c[0]*FmTangential[0][1] + a[0][0]*FmTangential[0][1] - a[1][1]*FmTangential[1][0] - c[0]*FmTangential[1][1] + a[1][0]*FmTangential[1][1] - a[2][1]*FmTangential[2][0] + c[1]*(FmTangential[0][0] + FmTangential[1][0] + FmTangential[2][0]) - c[0]*FmTangential[2][1] + a[2][0]*FmTangential[2][1]);

            a1[0][0] = -c[0] + c1[0] + c[2]*theta[1] - c[1]*theta[2] - c[2]*theta1[1] + c[1]*theta1[2] + a[0][0] + theta[2]*a[0][1] - theta1[2]*a[0][1] - theta[1]*a[0][2] + theta1[1]*a[0][2];

            a1[0][1] = -c[1] + c1[1] - c[2]*theta[0] + c[0]*theta[2] + c[2]*theta1[0] - c[0]*theta1[2] - theta[2]*a[0][0] + theta1[2]*a[0][0] + a[0][1] + theta[0]*a[0][2] - theta1[0]*a[0][2];

            a1[0][2] = -c[2] + c1[2] + c[1]*theta[0] - c[0]*theta[1] - c[1]*theta1[0] + c[0]*theta1[1] + theta[1]*a[0][0] - theta1[1]*a[0][0] - theta[0]*a[0][1] + theta1[0]*a[0][1] + a[0][2];

            a1[1][0] = -c[0] + c1[0] + c[2]*theta[1] - c[1]*theta[2] - c[2]*theta1[1] + c[1]*theta1[2] + a[1][0] + theta[2]*a[1][1] - theta1[2]*a[1][1] - theta[1]*a[1][2] + theta1[1]*a[1][2];

            a1[1][1] = -c[1] + c1[1] - c[2]*theta[0] + c[0]*theta[2] + c[2]*theta1[0] - c[0]*theta1[2] - theta[2]*a[1][0] + theta1[2]*a[1][0] + a[1][1] + theta[0]*a[1][2] - theta1[0]*a[1][2];

            a1[1][2] = -c[2] + c1[2] + c[1]*theta[0] - c[0]*theta[1] - c[1]*theta1[0] + c[0]*theta1[1] + theta[1]*a[1][0] - theta1[1]*a[1][0] - theta[0]*a[1][1] + theta1[0]*a[1][1] + a[1][2];

            a1[2][0] = -c[0] + c1[0] + c[2]*theta[1] - c[1]*theta[2] - c[2]*theta1[1] + c[1]*theta1[2] + a[2][0] + theta[2]*a[2][1] - theta1[2]*a[2][1] - theta[1]*a[2][2] + theta1[1]*a[2][2];

            a1[2][1] = -c[1] + c1[1] - c[2]*theta[0] + c[0]*theta[2] + c[2]*theta1[0] - c[0]*theta1[2] - theta[2]*a[2][0] + theta1[2]*a[2][0] + a[2][1] + theta[0]*a[2][2] - theta1[0]*a[2][2];

            a1[2][2] = -c[2] + c1[2] + c[1]*theta[0] - c[0]*theta[1] - c[1]*theta1[0] + c[0]*theta1[1] + theta[1]*a[2][0] - theta1[1]*a[2][0] - theta[0]*a[2][1] + theta1[0]*a[2][1] + a[2][2];

            break;

        case 4:
            c1[0] = c[0] + sqrt(2)*sqrt(DCargoTranslation)*sqrt(dt)*Dbc[0] + dt*muCargoTranslation*(Fsteric[0] + Ftrap[0] + FmRadial[0][0] + FmRadial[1][0] + FmRadial[2][0] + FmRadial[3][0] + FmTangential[0][0] + FmTangential[1][0] + FmTangential[2][0] + FmTangential[3][0]);

            c1[1] = c[1] + sqrt(2)*sqrt(DCargoTranslation)*sqrt(dt)*Dbc[1] + dt*muCargoTranslation*(Fsteric[1] + Ftrap[1] + FmRadial[0][1] + FmRadial[1][1] + FmRadial[2][1] + FmRadial[3][1] + FmTangential[0][1] + FmTangential[1][1] + FmTangential[2][1] + FmTangential[3][1]);

            c1[2] = c[2] + sqrt(2)*sqrt(DCargoTranslation)*sqrt(dt)*Dbc[2] + dt*muCargoTranslation*(Fsteric[2] + Ftrap[2] + FmRadial[0][2] + FmRadial[1][2] + FmRadial[2][2] + FmRadial[3][2] + FmTangential[0][2] + FmTangential[1][2] + FmTangential[2][2] + FmTangential[3][2]);

            theta1[0] = sqrt(2)*sqrt(DCargoRotation)*sqrt(dt)*Rbc[0] + theta[0] + dt*muCargoRotation*(TorqeExt[0] - a[0][2]*FmTangential[0][1] - c[1]*FmTangential[0][2] + a[0][1]*FmTangential[0][2] - a[1][2]*FmTangential[1][1] - c[1]*FmTangential[1][2] + a[1][1]*FmTangential[1][2] - a[2][2]*FmTangential[2][1] - c[1]*FmTangential[2][2] + a[2][1]*FmTangential[2][2] - a[3][2]*FmTangential[3][1] + c[2]*(FmTangential[0][1] + FmTangential[1][1] + FmTangential[2][1] + FmTangential[3][1]) - c[1]*FmTangential[3][2] + a[3][1]*FmTangential[3][2]);

            theta1[1] = sqrt(2)*sqrt(DCargoRotation)*sqrt(dt)*Rbc[1] + theta[1] + dt*muCargoRotation*(TorqeExt[1] + a[0][2]*FmTangential[0][0] + c[0]*FmTangential[0][2] - a[0][0]*FmTangential[0][2] + a[1][2]*FmTangential[1][0] + c[0]*FmTangential[1][2] - a[1][0]*FmTangential[1][2] + a[2][2]*FmTangential[2][0] + c[0]*FmTangential[2][2] - a[2][0]*FmTangential[2][2] + a[3][2]*FmTangential[3][0] - c[2]*(FmTangential[0][0] + FmTangential[1][0] + FmTangential[2][0] + FmTangential[3][0]) + c[0]*FmTangential[3][2] - a[3][0]*FmTangential[3][2]);

            theta1[2] = sqrt(2)*sqrt(DCargoRotation)*sqrt(dt)*Rbc[2] + theta[2] + dt*muCargoRotation*(TorqeExt[2] - a[0][1]*FmTangential[0][0] - c[0]*FmTangential[0][1] + a[0][0]*FmTangential[0][1] - a[1][1]*FmTangential[1][0] - c[0]*FmTangential[1][1] + a[1][0]*FmTangential[1][1] - a[2][1]*FmTangential[2][0] - c[0]*FmTangential[2][1] + a[2][0]*FmTangential[2][1] - a[3][1]*FmTangential[3][0] + c[1]*(FmTangential[0][0] + FmTangential[1][0] + FmTangential[2][0] + FmTangential[3][0]) - c[0]*FmTangential[3][1] + a[3][0]*FmTangential[3][1]);

            a1[0][0] = -c[0] + c1[0] + c[2]*theta[1] - c[1]*theta[2] - c[2]*theta1[1] + c[1]*theta1[2] + a[0][0] + theta[2]*a[0][1] - theta1[2]*a[0][1] - theta[1]*a[0][2] + theta1[1]*a[0][2];

            a1[0][1] = -c[1] + c1[1] - c[2]*theta[0] + c[0]*theta[2] + c[2]*theta1[0] - c[0]*theta1[2] - theta[2]*a[0][0] + theta1[2]*a[0][0] + a[0][1] + theta[0]*a[0][2] - theta1[0]*a[0][2];

            a1[0][2] = -c[2] + c1[2] + c[1]*theta[0] - c[0]*theta[1] - c[1]*theta1[0] + c[0]*theta1[1] + theta[1]*a[0][0] - theta1[1]*a[0][0] - theta[0]*a[0][1] + theta1[0]*a[0][1] + a[0][2];

            a1[1][0] = -c[0] + c1[0] + c[2]*theta[1] - c[1]*theta[2] - c[2]*theta1[1] + c[1]*theta1[2] + a[1][0] + theta[2]*a[1][1] - theta1[2]*a[1][1] - theta[1]*a[1][2] + theta1[1]*a[1][2];

            a1[1][1] = -c[1] + c1[1] - c[2]*theta[0] + c[0]*theta[2] + c[2]*theta1[0] - c[0]*theta1[2] - theta[2]*a[1][0] + theta1[2]*a[1][0] + a[1][1] + theta[0]*a[1][2] - theta1[0]*a[1][2];

            a1[1][2] = -c[2] + c1[2] + c[1]*theta[0] - c[0]*theta[1] - c[1]*theta1[0] + c[0]*theta1[1] + theta[1]*a[1][0] - theta1[1]*a[1][0] - theta[0]*a[1][1] + theta1[0]*a[1][1] + a[1][2];

            a1[2][0] = -c[0] + c1[0] + c[2]*theta[1] - c[1]*theta[2] - c[2]*theta1[1] + c[1]*theta1[2] + a[2][0] + theta[2]*a[2][1] - theta1[2]*a[2][1] - theta[1]*a[2][2] + theta1[1]*a[2][2];

            a1[2][1] = -c[1] + c1[1] - c[2]*theta[0] + c[0]*theta[2] + c[2]*theta1[0] - c[0]*theta1[2] - theta[2]*a[2][0] + theta1[2]*a[2][0] + a[2][1] + theta[0]*a[2][2] - theta1[0]*a[2][2];

            a1[2][2] = -c[2] + c1[2] + c[1]*theta[0] - c[0]*theta[1] - c[1]*theta1[0] + c[0]*theta1[1] + theta[1]*a[2][0] - theta1[1]*a[2][0] - theta[0]*a[2][1] + theta1[0]*a[2][1] + a[2][2];

            a1[3][0] = -c[0] + c1[0] + c[2]*theta[1] - c[1]*theta[2] - c[2]*theta1[1] + c[1]*theta1[2] + a[3][0] + theta[2]*a[3][1] - theta1[2]*a[3][1] - theta[1]*a[3][2] + theta1[1]*a[3][2];

            a1[3][1] = -c[1] + c1[1] - c[2]*theta[0] + c[0]*theta[2] + c[2]*theta1[0] - c[0]*theta1[2] - theta[2]*a[3][0] + theta1[2]*a[3][0] + a[3][1] + theta[0]*a[3][2] - theta1[0]*a[3][2];

            a1[3][2] = -c[2] + c1[2] + c[1]*theta[0] - c[0]*theta[1] - c[1]*theta1[0] + c[0]*theta1[1] + theta[1]*a[3][0] - theta1[1]*a[3][0] - theta[0]*a[3][1] + theta1[0]*a[3][1] + a[3][2];

            break;

        case 5:
            c1[0] = c[0] + sqrt(2)*sqrt(DCargoTranslation)*sqrt(dt)*Dbc[0] + dt*muCargoTranslation*(Fsteric[0] + Ftrap[0] + FmRadial[0][0] + FmRadial[1][0] + FmRadial[2][0] + FmRadial[3][0] + FmRadial[4][0] + FmTangential[0][0] + FmTangential[1][0] + FmTangential[2][0] + FmTangential[3][0] + FmTangential[4][0]);

            c1[1] = c[1] + sqrt(2)*sqrt(DCargoTranslation)*sqrt(dt)*Dbc[1] + dt*muCargoTranslation*(Fsteric[1] + Ftrap[1] + FmRadial[0][1] + FmRadial[1][1] + FmRadial[2][1] + FmRadial[3][1] + FmRadial[4][1] + FmTangential[0][1] + FmTangential[1][1] + FmTangential[2][1] + FmTangential[3][1] + FmTangential[4][1]);

            c1[2] = c[2] + sqrt(2)*sqrt(DCargoTranslation)*sqrt(dt)*Dbc[2] + dt*muCargoTranslation*(Fsteric[2] + Ftrap[2] + FmRadial[0][2] + FmRadial[1][2] + FmRadial[2][2] + FmRadial[3][2] + FmRadial[4][2] + FmTangential[0][2] + FmTangential[1][2] + FmTangential[2][2] + FmTangential[3][2] + FmTangential[4][2]);

            theta1[0] = sqrt(2)*sqrt(DCargoRotation)*sqrt(dt)*Rbc[0] + theta[0] + dt*muCargoRotation*(TorqeExt[0] - a[0][2]*FmTangential[0][1] - c[1]*FmTangential[0][2] + a[0][1]*FmTangential[0][2] - a[1][2]*FmTangential[1][1] - c[1]*FmTangential[1][2] + a[1][1]*FmTangential[1][2] - a[2][2]*FmTangential[2][1] - c[1]*FmTangential[2][2] + a[2][1]*FmTangential[2][2] - a[3][2]*FmTangential[3][1] - c[1]*FmTangential[3][2] + a[3][1]*FmTangential[3][2] - a[4][2]*FmTangential[4][1] + c[2]*(FmTangential[0][1] + FmTangential[1][1] + FmTangential[2][1] + FmTangential[3][1] + FmTangential[4][1]) - c[1]*FmTangential[4][2] + a[4][1]*FmTangential[4][2]);

            theta1[1] = sqrt(2)*sqrt(DCargoRotation)*sqrt(dt)*Rbc[1] + theta[1] + dt*muCargoRotation*(TorqeExt[1] + a[0][2]*FmTangential[0][0] + c[0]*FmTangential[0][2] - a[0][0]*FmTangential[0][2] + a[1][2]*FmTangential[1][0] + c[0]*FmTangential[1][2] - a[1][0]*FmTangential[1][2] + a[2][2]*FmTangential[2][0] + c[0]*FmTangential[2][2] - a[2][0]*FmTangential[2][2] + a[3][2]*FmTangential[3][0] + c[0]*FmTangential[3][2] - a[3][0]*FmTangential[3][2] + a[4][2]*FmTangential[4][0] - c[2]*(FmTangential[0][0] + FmTangential[1][0] + FmTangential[2][0] + FmTangential[3][0] + FmTangential[4][0]) + c[0]*FmTangential[4][2] - a[4][0]*FmTangential[4][2]);

            theta1[2] = sqrt(2)*sqrt(DCargoRotation)*sqrt(dt)*Rbc[2] + theta[2] + dt*muCargoRotation*(TorqeExt[2] - a[0][1]*FmTangential[0][0] - c[0]*FmTangential[0][1] + a[0][0]*FmTangential[0][1] - a[1][1]*FmTangential[1][0] - c[0]*FmTangential[1][1] + a[1][0]*FmTangential[1][1] - a[2][1]*FmTangential[2][0] - c[0]*FmTangential[2][1] + a[2][0]*FmTangential[2][1] - a[3][1]*FmTangential[3][0] - c[0]*FmTangential[3][1] + a[3][0]*FmTangential[3][1] - a[4][1]*FmTangential[4][0] + c[1]*(FmTangential[0][0] + FmTangential[1][0] + FmTangential[2][0] + FmTangential[3][0] + FmTangential[4][0]) - c[0]*FmTangential[4][1] + a[4][0]*FmTangential[4][1]);

            a1[0][0] = -c[0] + c1[0] + c[2]*theta[1] - c[1]*theta[2] - c[2]*theta1[1] + c[1]*theta1[2] + a[0][0] + theta[2]*a[0][1] - theta1[2]*a[0][1] - theta[1]*a[0][2] + theta1[1]*a[0][2];

            a1[0][1] = -c[1] + c1[1] - c[2]*theta[0] + c[0]*theta[2] + c[2]*theta1[0] - c[0]*theta1[2] - theta[2]*a[0][0] + theta1[2]*a[0][0] + a[0][1] + theta[0]*a[0][2] - theta1[0]*a[0][2];

            a1[0][2] = -c[2] + c1[2] + c[1]*theta[0] - c[0]*theta[1] - c[1]*theta1[0] + c[0]*theta1[1] + theta[1]*a[0][0] - theta1[1]*a[0][0] - theta[0]*a[0][1] + theta1[0]*a[0][1] + a[0][2];

            a1[1][0] = -c[0] + c1[0] + c[2]*theta[1] - c[1]*theta[2] - c[2]*theta1[1] + c[1]*theta1[2] + a[1][0] + theta[2]*a[1][1] - theta1[2]*a[1][1] - theta[1]*a[1][2] + theta1[1]*a[1][2];

            a1[1][1] = -c[1] + c1[1] - c[2]*theta[0] + c[0]*theta[2] + c[2]*theta1[0] - c[0]*theta1[2] - theta[2]*a[1][0] + theta1[2]*a[1][0] + a[1][1] + theta[0]*a[1][2] - theta1[0]*a[1][2];

            a1[1][2] = -c[2] + c1[2] + c[1]*theta[0] - c[0]*theta[1] - c[1]*theta1[0] + c[0]*theta1[1] + theta[1]*a[1][0] - theta1[1]*a[1][0] - theta[0]*a[1][1] + theta1[0]*a[1][1] + a[1][2];

            a1[2][0] = -c[0] + c1[0] + c[2]*theta[1] - c[1]*theta[2] - c[2]*theta1[1] + c[1]*theta1[2] + a[2][0] + theta[2]*a[2][1] - theta1[2]*a[2][1] - theta[1]*a[2][2] + theta1[1]*a[2][2];

            a1[2][1] = -c[1] + c1[1] - c[2]*theta[0] + c[0]*theta[2] + c[2]*theta1[0] - c[0]*theta1[2] - theta[2]*a[2][0] + theta1[2]*a[2][0] + a[2][1] + theta[0]*a[2][2] - theta1[0]*a[2][2];

            a1[2][2] = -c[2] + c1[2] + c[1]*theta[0] - c[0]*theta[1] - c[1]*theta1[0] + c[0]*theta1[1] + theta[1]*a[2][0] - theta1[1]*a[2][0] - theta[0]*a[2][1] + theta1[0]*a[2][1] + a[2][2];

            a1[3][0] = -c[0] + c1[0] + c[2]*theta[1] - c[1]*theta[2] - c[2]*theta1[1] + c[1]*theta1[2] + a[3][0] + theta[2]*a[3][1] - theta1[2]*a[3][1] - theta[1]*a[3][2] + theta1[1]*a[3][2];

            a1[3][1] = -c[1] + c1[1] - c[2]*theta[0] + c[0]*theta[2] + c[2]*theta1[0] - c[0]*theta1[2] - theta[2]*a[3][0] + theta1[2]*a[3][0] + a[3][1] + theta[0]*a[3][2] - theta1[0]*a[3][2];

            a1[3][2] = -c[2] + c1[2] + c[1]*theta[0] - c[0]*theta[1] - c[1]*theta1[0] + c[0]*theta1[1] + theta[1]*a[3][0] - theta1[1]*a[3][0] - theta[0]*a[3][1] + theta1[0]*a[3][1] + a[3][2];

            a1[4][0] = -c[0] + c1[0] + c[2]*theta[1] - c[1]*theta[2] - c[2]*theta1[1] + c[1]*theta1[2] + a[4][0] + theta[2]*a[4][1] - theta1[2]*a[4][1] - theta[1]*a[4][2] + theta1[1]*a[4][2];

            a1[4][1] = -c[1] + c1[1] - c[2]*theta[0] + c[0]*theta[2] + c[2]*theta1[0] - c[0]*theta1[2] - theta[2]*a[4][0] + theta1[2]*a[4][0] + a[4][1] + theta[0]*a[4][2] - theta1[0]*a[4][2];

            a1[4][2] = -c[2] + c1[2] + c[1]*theta[0] - c[0]*theta[1] - c[1]*theta1[0] + c[0]*theta1[1] + theta[1]*a[4][0] - theta1[1]*a[4][0] - theta[0]*a[4][1] + theta1[0]*a[4][1] + a[4][2];

            break;

        default:
            printf("Bad value for total_motors\n");
            exit(0);
    }
}
