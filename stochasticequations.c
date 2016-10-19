//prototypes
void stochastic_equations();

void stochastic_equations(){
    switch(total_motors){
        case 0:
            c1[0] = c[0] + dt*muCargoTranslation*(Dbc[0] + Fsteric[0] + Ftrap[0]);

            c1[1] = c[1] + dt*muCargoTranslation*(Dbc[1] + Fsteric[1] + Ftrap[1]);

            c1[2] = c[2] + dt*muCargoTranslation*(Dbc[2] + Fsteric[2] + Ftrap[2]);

//            theta1[0] = theta[0] + dt*muCargoRotation*(Rbc[0] + TorqeExt[0]);

//            theta1[1] = theta[1] + dt*muCargoRotation*(Rbc[1] + TorqeExt[1]);

//            theta1[2] = theta[2] + dt*muCargoRotation*(Rbc[2] + TorqeExt[2]);

            break;

        case 1:
            a1[0][0] = a[0][0] + dt*(muAnchor[0]*(Dba[0][0] + FmTangential[0][0]) + muCargoTranslation*(Dbc[0] + Fsteric[0] + Ftrap[0] + Dba[0][0] + FmRadial[0][0] + FmTangential[0][0]) + muCargoRotation*(-(Rbc[2]*a[0][1]) - TorqeExt[2]*a[0][1] + Rbc[1]*a[0][2] + TorqeExt[1]*a[0][2] + pow(a[0][1],2)*Dba[0][0] + pow(a[0][2],2)*Dba[0][0] + c[0]*a[0][1]*Dba[0][1] - a[0][0]*a[0][1]*Dba[0][1] + c[0]*a[0][2]*Dba[0][2] - a[0][0]*a[0][2]*Dba[0][2] + pow(a[0][1],2)*FmTangential[0][0] + pow(a[0][2],2)*FmTangential[0][0] + pow(c[1],2)*(Dba[0][0] + FmTangential[0][0]) + pow(c[2],2)*(Dba[0][0] + FmTangential[0][0]) + c[0]*a[0][1]*FmTangential[0][1] - a[0][0]*a[0][1]*FmTangential[0][1] + c[1]*(Rbc[2] + TorqeExt[2] - 2*a[0][1]*Dba[0][0] - c[0]*Dba[0][1] + a[0][0]*Dba[0][1] - 2*a[0][1]*FmTangential[0][0] - c[0]*FmTangential[0][1] + a[0][0]*FmTangential[0][1]) + c[0]*a[0][2]*FmTangential[0][2] - a[0][0]*a[0][2]*FmTangential[0][2] - c[2]*(Rbc[1] + TorqeExt[1] + 2*a[0][2]*Dba[0][0] + c[0]*Dba[0][2] - a[0][0]*Dba[0][2] + 2*a[0][2]*FmTangential[0][0] + c[0]*FmTangential[0][2] - a[0][0]*FmTangential[0][2])));

            a1[0][1] = a[0][1] + dt*(muAnchor[0]*(Dba[0][1] + FmTangential[0][1]) + muCargoTranslation*(Dbc[1] + Fsteric[1] + Ftrap[1] + Dba[0][1] + FmRadial[0][1] + FmTangential[0][1]) + muCargoRotation*(Rbc[2]*a[0][0] + TorqeExt[2]*a[0][0] - Rbc[0]*a[0][2] - TorqeExt[0]*a[0][2] + c[1]*a[0][0]*Dba[0][0] - a[0][0]*a[0][1]*Dba[0][0] + pow(a[0][0],2)*Dba[0][1] + pow(a[0][2],2)*Dba[0][1] + c[1]*a[0][2]*Dba[0][2] - a[0][1]*a[0][2]*Dba[0][2] + c[1]*a[0][0]*FmTangential[0][0] - a[0][0]*a[0][1]*FmTangential[0][0] + pow(a[0][0],2)*FmTangential[0][1] + pow(a[0][2],2)*FmTangential[0][1] + pow(c[0],2)*(Dba[0][1] + FmTangential[0][1]) + pow(c[2],2)*(Dba[0][1] + FmTangential[0][1]) - c[0]*(Rbc[2] + TorqeExt[2] + c[1]*Dba[0][0] - a[0][1]*Dba[0][0] + 2*a[0][0]*Dba[0][1] + c[1]*FmTangential[0][0] - a[0][1]*FmTangential[0][0] + 2*a[0][0]*FmTangential[0][1]) + c[1]*a[0][2]*FmTangential[0][2] - a[0][1]*a[0][2]*FmTangential[0][2] + c[2]*(Rbc[0] + TorqeExt[0] - 2*a[0][2]*Dba[0][1] - c[1]*Dba[0][2] + a[0][1]*Dba[0][2] - 2*a[0][2]*FmTangential[0][1] - c[1]*FmTangential[0][2] + a[0][1]*FmTangential[0][2])));

            a1[0][2] = a[0][2] + dt*(muAnchor[0]*(Dba[0][2] + FmTangential[0][2]) + muCargoTranslation*(Dbc[2] + Fsteric[2] + Ftrap[2] + Dba[0][2] + FmRadial[0][2] + FmTangential[0][2]) + muCargoRotation*(-(Rbc[1]*a[0][0]) - TorqeExt[1]*a[0][0] + Rbc[0]*a[0][1] + TorqeExt[0]*a[0][1] + c[2]*a[0][0]*Dba[0][0] - a[0][0]*a[0][2]*Dba[0][0] + c[2]*a[0][1]*Dba[0][1] - a[0][1]*a[0][2]*Dba[0][1] + pow(a[0][0],2)*Dba[0][2] + pow(a[0][1],2)*Dba[0][2] + c[2]*a[0][0]*FmTangential[0][0] - a[0][0]*a[0][2]*FmTangential[0][0] + c[2]*a[0][1]*FmTangential[0][1] - a[0][1]*a[0][2]*FmTangential[0][1] + pow(a[0][0],2)*FmTangential[0][2] + pow(a[0][1],2)*FmTangential[0][2] + pow(c[0],2)*(Dba[0][2] + FmTangential[0][2]) + pow(c[1],2)*(Dba[0][2] + FmTangential[0][2]) + c[0]*(Rbc[1] + TorqeExt[1] - c[2]*Dba[0][0] + a[0][2]*Dba[0][0] - 2*a[0][0]*Dba[0][2] - c[2]*FmTangential[0][0] + a[0][2]*FmTangential[0][0] - 2*a[0][0]*FmTangential[0][2]) - c[1]*(Rbc[0] + TorqeExt[0] + c[2]*Dba[0][1] - a[0][2]*Dba[0][1] + 2*a[0][1]*Dba[0][2] + c[2]*FmTangential[0][1] - a[0][2]*FmTangential[0][1] + 2*a[0][1]*FmTangential[0][2])));

            c1[0] = c[0] + dt*muCargoTranslation*(Dbc[0] + Fsteric[0] + Ftrap[0] + Dba[0][0] + FmRadial[0][0] + FmTangential[0][0]);

            c1[1] = c[1] + dt*muCargoTranslation*(Dbc[1] + Fsteric[1] + Ftrap[1] + Dba[0][1] + FmRadial[0][1] + FmTangential[0][1]);

            c1[2] = c[2] + dt*muCargoTranslation*(Dbc[2] + Fsteric[2] + Ftrap[2] + Dba[0][2] + FmRadial[0][2] + FmTangential[0][2]);

//            theta1[0] = theta[0] + dt*muCargoRotation*(Rbc[0] + TorqeExt[0] + c[2]*Dba[0][1] - a[0][2]*Dba[0][1] - c[1]*Dba[0][2] + a[0][1]*Dba[0][2] + c[2]*FmTangential[0][1] - a[0][2]*FmTangential[0][1] - c[1]*FmTangential[0][2] + a[0][1]*FmTangential[0][2]);

//            theta1[1] = theta[1] + dt*muCargoRotation*(Rbc[1] + TorqeExt[1] - c[2]*Dba[0][0] + a[0][2]*Dba[0][0] + c[0]*Dba[0][2] - a[0][0]*Dba[0][2] - c[2]*FmTangential[0][0] + a[0][2]*FmTangential[0][0] + c[0]*FmTangential[0][2] - a[0][0]*FmTangential[0][2]);

//            theta1[2] = theta[2] + dt*muCargoRotation*(Rbc[2] + TorqeExt[2] + c[1]*Dba[0][0] - a[0][1]*Dba[0][0] - c[0]*Dba[0][1] + a[0][0]*Dba[0][1] + c[1]*FmTangential[0][0] - a[0][1]*FmTangential[0][0] - c[0]*FmTangential[0][1] + a[0][0]*FmTangential[0][1]);

            break;

        case 2:
            a1[0][0] = a[0][0] + dt*muCargoRotation*(Rbc[2] + TorqeExt[2])*(c[1] - a[0][1]) - dt*muCargoRotation*(Rbc[1] + TorqeExt[1])*(c[2] - a[0][2]) + dt*muCargoTranslation*(Dbc[0] + Fsteric[0] + Ftrap[0] + FmRadial[0][0] + FmRadial[1][0]) + dt*(muCargoTranslation + muAnchor[0] + muCargoRotation*(pow(c[1],2) + pow(c[2],2) - 2*c[1]*a[0][1] + pow(a[0][1],2) - 2*c[2]*a[0][2] + pow(a[0][2],2)))*(Dba[0][0] + FmTangential[0][0]) - dt*muCargoRotation*(c[0] - a[0][0])*(c[1] - a[0][1])*(Dba[0][1] + FmTangential[0][1]) - dt*muCargoRotation*(c[0] - a[0][0])*(c[2] - a[0][2])*(Dba[0][2] + FmTangential[0][2]) + dt*(muCargoTranslation + muCargoRotation*(pow(c[1],2) + pow(c[2],2) + a[0][1]*a[1][1] - c[1]*(a[0][1] + a[1][1]) + a[0][2]*a[1][2] - c[2]*(a[0][2] + a[1][2])))*(Dba[1][0] + FmTangential[1][0]) - dt*muCargoRotation*(c[1] - a[0][1])*(c[0] - a[1][0])*(Dba[1][1] + FmTangential[1][1]) - dt*muCargoRotation*(c[2] - a[0][2])*(c[0] - a[1][0])*(Dba[1][2] + FmTangential[1][2]);

            a1[0][1] = -(dt*muCargoRotation*(Rbc[2] + TorqeExt[2])*(c[0] - a[0][0])) + a[0][1] + dt*muCargoRotation*(Rbc[0] + TorqeExt[0])*(c[2] - a[0][2]) + dt*muCargoTranslation*(Dbc[1] + Fsteric[1] + Ftrap[1] + FmRadial[0][1] + FmRadial[1][1]) - dt*muCargoRotation*(c[0] - a[0][0])*(c[1] - a[0][1])*(Dba[0][0] + FmTangential[0][0]) + dt*(muCargoTranslation + muAnchor[0] + muCargoRotation*(pow(c[0],2) + pow(c[2],2) - 2*c[0]*a[0][0] + pow(a[0][0],2) - 2*c[2]*a[0][2] + pow(a[0][2],2)))*(Dba[0][1] + FmTangential[0][1]) - dt*muCargoRotation*(c[1] - a[0][1])*(c[2] - a[0][2])*(Dba[0][2] + FmTangential[0][2]) - dt*muCargoRotation*(c[0] - a[0][0])*(c[1] - a[1][1])*(Dba[1][0] + FmTangential[1][0]) + dt*(muCargoTranslation + muCargoRotation*(pow(c[0],2) + pow(c[2],2) + a[0][0]*a[1][0] - c[0]*(a[0][0] + a[1][0]) + a[0][2]*a[1][2] - c[2]*(a[0][2] + a[1][2])))*(Dba[1][1] + FmTangential[1][1]) - dt*muCargoRotation*(c[2] - a[0][2])*(c[1] - a[1][1])*(Dba[1][2] + FmTangential[1][2]);

            a1[0][2] = dt*(muCargoRotation*(Rbc[1] + TorqeExt[1])*(c[0] - a[0][0]) + muCargoRotation*(Rbc[0] + TorqeExt[0])*(-c[1] + a[0][1]) + a[0][2]/dt + muCargoTranslation*(Dbc[2] + Fsteric[2] + Ftrap[2] + FmRadial[0][2] + FmRadial[1][2]) - muCargoRotation*(c[0] - a[0][0])*(c[2] - a[0][2])*(Dba[0][0] + FmTangential[0][0]) - muCargoRotation*(c[1] - a[0][1])*(c[2] - a[0][2])*(Dba[0][1] + FmTangential[0][1]) + (muCargoTranslation + muAnchor[0] + muCargoRotation*(pow(c[0],2) + pow(c[1],2) - 2*c[0]*a[0][0] + pow(a[0][0],2) - 2*c[1]*a[0][1] + pow(a[0][1],2)))*(Dba[0][2] + FmTangential[0][2]) - muCargoRotation*(c[0] - a[0][0])*(c[2] - a[1][2])*(Dba[1][0] + FmTangential[1][0]) - muCargoRotation*(c[1] - a[0][1])*(c[2] - a[1][2])*(Dba[1][1] + FmTangential[1][1]) + (muCargoTranslation + muCargoRotation*(c[0] - a[0][0])*(c[0] - a[1][0]) + muCargoRotation*(c[1] - a[0][1])*(c[1] - a[1][1]))*(Dba[1][2] + FmTangential[1][2]));

            a1[1][0] = a[1][0] + dt*muCargoRotation*(Rbc[2] + TorqeExt[2])*(c[1] - a[1][1]) - dt*muCargoRotation*(Rbc[1] + TorqeExt[1])*(c[2] - a[1][2]) + dt*muCargoTranslation*(Dbc[0] + Fsteric[0] + Ftrap[0] + FmRadial[0][0] + FmRadial[1][0]) + dt*(muCargoTranslation + muCargoRotation*(pow(c[1],2) + pow(c[2],2) + a[0][1]*a[1][1] - c[1]*(a[0][1] + a[1][1]) + a[0][2]*a[1][2] - c[2]*(a[0][2] + a[1][2])))*(Dba[0][0] + FmTangential[0][0]) - dt*muCargoRotation*(c[0] - a[0][0])*(c[1] - a[1][1])*(Dba[0][1] + FmTangential[0][1]) - dt*muCargoRotation*(c[0] - a[0][0])*(c[2] - a[1][2])*(Dba[0][2] + FmTangential[0][2]) + dt*(muCargoTranslation + muAnchor[1] + muCargoRotation*(pow(c[1],2) + pow(c[2],2) - 2*c[1]*a[1][1] + pow(a[1][1],2) - 2*c[2]*a[1][2] + pow(a[1][2],2)))*(Dba[1][0] + FmTangential[1][0]) - dt*muCargoRotation*(c[0] - a[1][0])*(c[1] - a[1][1])*(Dba[1][1] + FmTangential[1][1]) - dt*muCargoRotation*(c[0] - a[1][0])*(c[2] - a[1][2])*(Dba[1][2] + FmTangential[1][2]);

            a1[1][1] = -(dt*muCargoRotation*(Rbc[2] + TorqeExt[2])*(c[0] - a[1][0])) + a[1][1] + dt*muCargoRotation*(Rbc[0] + TorqeExt[0])*(c[2] - a[1][2]) + dt*muCargoTranslation*(Dbc[1] + Fsteric[1] + Ftrap[1] + FmRadial[0][1] + FmRadial[1][1]) - dt*muCargoRotation*(c[1] - a[0][1])*(c[0] - a[1][0])*(Dba[0][0] + FmTangential[0][0]) + dt*(muCargoTranslation + muCargoRotation*(pow(c[0],2) + pow(c[2],2) + a[0][0]*a[1][0] - c[0]*(a[0][0] + a[1][0]) + a[0][2]*a[1][2] - c[2]*(a[0][2] + a[1][2])))*(Dba[0][1] + FmTangential[0][1]) - dt*muCargoRotation*(c[1] - a[0][1])*(c[2] - a[1][2])*(Dba[0][2] + FmTangential[0][2]) - dt*muCargoRotation*(c[0] - a[1][0])*(c[1] - a[1][1])*(Dba[1][0] + FmTangential[1][0]) + dt*(muCargoTranslation + muAnchor[1] + muCargoRotation*(pow(c[0],2) + pow(c[2],2) - 2*c[0]*a[1][0] + pow(a[1][0],2) - 2*c[2]*a[1][2] + pow(a[1][2],2)))*(Dba[1][1] + FmTangential[1][1]) - dt*muCargoRotation*(c[1] - a[1][1])*(c[2] - a[1][2])*(Dba[1][2] + FmTangential[1][2]);

            a1[1][2] = dt*(muCargoRotation*(Rbc[1] + TorqeExt[1])*(c[0] - a[1][0]) + muCargoRotation*(Rbc[0] + TorqeExt[0])*(-c[1] + a[1][1]) + a[1][2]/dt + muCargoTranslation*(Dbc[2] + Fsteric[2] + Ftrap[2] + FmRadial[0][2] + FmRadial[1][2]) - muCargoRotation*(c[2] - a[0][2])*(c[0] - a[1][0])*(Dba[0][0] + FmTangential[0][0]) - muCargoRotation*(c[2] - a[0][2])*(c[1] - a[1][1])*(Dba[0][1] + FmTangential[0][1]) + (muCargoTranslation + muCargoRotation*(c[0] - a[0][0])*(c[0] - a[1][0]) + muCargoRotation*(c[1] - a[0][1])*(c[1] - a[1][1]))*(Dba[0][2] + FmTangential[0][2]) - muCargoRotation*(c[0] - a[1][0])*(c[2] - a[1][2])*(Dba[1][0] + FmTangential[1][0]) - muCargoRotation*(c[1] - a[1][1])*(c[2] - a[1][2])*(Dba[1][1] + FmTangential[1][1]) + (muCargoTranslation + muAnchor[1] + muCargoRotation*(pow(c[0],2) + pow(c[1],2) - 2*c[0]*a[1][0] + pow(a[1][0],2) - 2*c[1]*a[1][1] + pow(a[1][1],2)))*(Dba[1][2] + FmTangential[1][2]));

            c1[0] = c[0] + dt*muCargoTranslation*(Dbc[0] + Fsteric[0] + Ftrap[0] + Dba[0][0] + Dba[1][0] + FmRadial[0][0] + FmRadial[1][0] + FmTangential[0][0] + FmTangential[1][0]);

            c1[1] = c[1] + dt*muCargoTranslation*(Dbc[1] + Fsteric[1] + Ftrap[1] + Dba[0][1] + Dba[1][1] + FmRadial[0][1] + FmRadial[1][1] + FmTangential[0][1] + FmTangential[1][1]);

            c1[2] = c[2] + dt*muCargoTranslation*(Dbc[2] + Fsteric[2] + Ftrap[2] + Dba[0][2] + Dba[1][2] + FmRadial[0][2] + FmRadial[1][2] + FmTangential[0][2] + FmTangential[1][2]);

//            theta1[0] = dt*(theta[0]/dt + muCargoRotation*(Rbc[0] + TorqeExt[0]) + muCargoRotation*(c[2] - a[0][2])*(Dba[0][1] + FmTangential[0][1]) + muCargoRotation*(-c[1] + a[0][1])*(Dba[0][2] + FmTangential[0][2]) + muCargoRotation*(c[2] - a[1][2])*(Dba[1][1] + FmTangential[1][1]) + muCargoRotation*(-c[1] + a[1][1])*(Dba[1][2] + FmTangential[1][2]));

//            theta1[1] = dt*(theta[1]/dt + muCargoRotation*(Rbc[1] + TorqeExt[1]) + muCargoRotation*(-c[2] + a[0][2])*(Dba[0][0] + FmTangential[0][0]) + muCargoRotation*(c[0] - a[0][0])*(Dba[0][2] + FmTangential[0][2]) + muCargoRotation*(-c[2] + a[1][2])*(Dba[1][0] + FmTangential[1][0]) + muCargoRotation*(c[0] - a[1][0])*(Dba[1][2] + FmTangential[1][2]));

//            theta1[2] = dt*(theta[2]/dt + muCargoRotation*(Rbc[2] + TorqeExt[2]) + muCargoRotation*(c[1] - a[0][1])*(Dba[0][0] + FmTangential[0][0]) + muCargoRotation*(-c[0] + a[0][0])*(Dba[0][1] + FmTangential[0][1]) + muCargoRotation*(c[1] - a[1][1])*(Dba[1][0] + FmTangential[1][0]) + muCargoRotation*(-c[0] + a[1][0])*(Dba[1][1] + FmTangential[1][1]));

            break;

        case 3:
            a1[0][0] = dt*(a[0][0]/dt + muCargoRotation*(Rbc[2] + TorqeExt[2])*(c[1] - a[0][1]) - muCargoRotation*(Rbc[1] + TorqeExt[1])*(c[2] - a[0][2]) + muCargoTranslation*(Dbc[0] + Fsteric[0] + Ftrap[0] + FmRadial[0][0] + FmRadial[1][0] + FmRadial[2][0]) + (muCargoTranslation + muAnchor[0] + muCargoRotation*(pow(c[1],2) + pow(c[2],2) - 2*c[1]*a[0][1] + pow(a[0][1],2) - 2*c[2]*a[0][2] + pow(a[0][2],2)))*(Dba[0][0] + FmTangential[0][0]) - muCargoRotation*(c[0] - a[0][0])*(c[1] - a[0][1])*(Dba[0][1] + FmTangential[0][1]) - muCargoRotation*(c[0] - a[0][0])*(c[2] - a[0][2])*(Dba[0][2] + FmTangential[0][2]) + (muCargoTranslation + muCargoRotation*(pow(c[1],2) + pow(c[2],2) + a[0][1]*a[1][1] - c[1]*(a[0][1] + a[1][1]) + a[0][2]*a[1][2] - c[2]*(a[0][2] + a[1][2])))*(Dba[1][0] + FmTangential[1][0]) - muCargoRotation*(c[1] - a[0][1])*(c[0] - a[1][0])*(Dba[1][1] + FmTangential[1][1]) - muCargoRotation*(c[2] - a[0][2])*(c[0] - a[1][0])*(Dba[1][2] + FmTangential[1][2]) + (muCargoTranslation + muCargoRotation*(pow(c[1],2) + pow(c[2],2) + a[0][1]*a[2][1] - c[1]*(a[0][1] + a[2][1]) + a[0][2]*a[2][2] - c[2]*(a[0][2] + a[2][2])))*(Dba[2][0] + FmTangential[2][0]) - muCargoRotation*(c[1] - a[0][1])*(c[0] - a[2][0])*(Dba[2][1] + FmTangential[2][1]) - muCargoRotation*(c[2] - a[0][2])*(c[0] - a[2][0])*(Dba[2][2] + FmTangential[2][2]));

            a1[0][1] = dt*(-(muCargoRotation*(Rbc[2] + TorqeExt[2])*(c[0] - a[0][0])) + a[0][1]/dt + muCargoRotation*(Rbc[0] + TorqeExt[0])*(c[2] - a[0][2]) + muCargoTranslation*(Dbc[1] + Fsteric[1] + Ftrap[1] + FmRadial[0][1] + FmRadial[1][1] + FmRadial[2][1]) - muCargoRotation*(c[0] - a[0][0])*(c[1] - a[0][1])*(Dba[0][0] + FmTangential[0][0]) + (muCargoTranslation + muAnchor[0] + muCargoRotation*(pow(c[0],2) + pow(c[2],2) - 2*c[0]*a[0][0] + pow(a[0][0],2) - 2*c[2]*a[0][2] + pow(a[0][2],2)))*(Dba[0][1] + FmTangential[0][1]) - muCargoRotation*(c[1] - a[0][1])*(c[2] - a[0][2])*(Dba[0][2] + FmTangential[0][2]) - muCargoRotation*(c[0] - a[0][0])*(c[1] - a[1][1])*(Dba[1][0] + FmTangential[1][0]) + (muCargoTranslation + muCargoRotation*(pow(c[0],2) + pow(c[2],2) + a[0][0]*a[1][0] - c[0]*(a[0][0] + a[1][0]) + a[0][2]*a[1][2] - c[2]*(a[0][2] + a[1][2])))*(Dba[1][1] + FmTangential[1][1]) - muCargoRotation*(c[2] - a[0][2])*(c[1] - a[1][1])*(Dba[1][2] + FmTangential[1][2]) - muCargoRotation*(c[0] - a[0][0])*(c[1] - a[2][1])*(Dba[2][0] + FmTangential[2][0]) + (muCargoTranslation + muCargoRotation*(pow(c[0],2) + pow(c[2],2) + a[0][0]*a[2][0] - c[0]*(a[0][0] + a[2][0]) + a[0][2]*a[2][2] - c[2]*(a[0][2] + a[2][2])))*(Dba[2][1] + FmTangential[2][1]) - muCargoRotation*(c[2] - a[0][2])*(c[1] - a[2][1])*(Dba[2][2] + FmTangential[2][2]));

            a1[0][2] = dt*(muCargoRotation*(Rbc[1] + TorqeExt[1])*(c[0] - a[0][0]) - muCargoRotation*(Rbc[0] + TorqeExt[0])*(c[1] - a[0][1]) + a[0][2]/dt + muCargoTranslation*(Dbc[2] + Fsteric[2] + Ftrap[2] + FmRadial[0][2] + FmRadial[1][2] + FmRadial[2][2]) - muCargoRotation*(c[0] - a[0][0])*(c[2] - a[0][2])*(Dba[0][0] + FmTangential[0][0]) - muCargoRotation*(c[1] - a[0][1])*(c[2] - a[0][2])*(Dba[0][1] + FmTangential[0][1]) + (muCargoTranslation + muAnchor[0] + muCargoRotation*(pow(c[0],2) + pow(c[1],2) - 2*c[0]*a[0][0] + pow(a[0][0],2) - 2*c[1]*a[0][1] + pow(a[0][1],2)))*(Dba[0][2] + FmTangential[0][2]) - muCargoRotation*(c[0] - a[0][0])*(c[2] - a[1][2])*(Dba[1][0] + FmTangential[1][0]) - muCargoRotation*(c[1] - a[0][1])*(c[2] - a[1][2])*(Dba[1][1] + FmTangential[1][1]) + (muCargoTranslation + muCargoRotation*(pow(c[0],2) + pow(c[1],2) + a[0][0]*a[1][0] - c[0]*(a[0][0] + a[1][0]) + a[0][1]*a[1][1] - c[1]*(a[0][1] + a[1][1])))*(Dba[1][2] + FmTangential[1][2]) - muCargoRotation*(c[0] - a[0][0])*(c[2] - a[2][2])*(Dba[2][0] + FmTangential[2][0]) - muCargoRotation*(c[1] - a[0][1])*(c[2] - a[2][2])*(Dba[2][1] + FmTangential[2][1]) + (muCargoTranslation + muCargoRotation*(pow(c[0],2) + pow(c[1],2) + a[0][0]*a[2][0] - c[0]*(a[0][0] + a[2][0]) + a[0][1]*a[2][1] - c[1]*(a[0][1] + a[2][1])))*(Dba[2][2] + FmTangential[2][2]));

            a1[1][0] = dt*(a[1][0]/dt + muCargoRotation*(Rbc[2] + TorqeExt[2])*(c[1] - a[1][1]) - muCargoRotation*(Rbc[1] + TorqeExt[1])*(c[2] - a[1][2]) + muCargoTranslation*(Dbc[0] + Fsteric[0] + Ftrap[0] + FmRadial[0][0] + FmRadial[1][0] + FmRadial[2][0]) + (muCargoTranslation + muCargoRotation*(pow(c[1],2) + pow(c[2],2) + a[0][1]*a[1][1] - c[1]*(a[0][1] + a[1][1]) + a[0][2]*a[1][2] - c[2]*(a[0][2] + a[1][2])))*(Dba[0][0] + FmTangential[0][0]) - muCargoRotation*(c[0] - a[0][0])*(c[1] - a[1][1])*(Dba[0][1] + FmTangential[0][1]) - muCargoRotation*(c[0] - a[0][0])*(c[2] - a[1][2])*(Dba[0][2] + FmTangential[0][2]) + (muCargoTranslation + muAnchor[1] + muCargoRotation*(pow(c[1],2) + pow(c[2],2) - 2*c[1]*a[1][1] + pow(a[1][1],2) - 2*c[2]*a[1][2] + pow(a[1][2],2)))*(Dba[1][0] + FmTangential[1][0]) - muCargoRotation*(c[0] - a[1][0])*(c[1] - a[1][1])*(Dba[1][1] + FmTangential[1][1]) - muCargoRotation*(c[0] - a[1][0])*(c[2] - a[1][2])*(Dba[1][2] + FmTangential[1][2]) + (muCargoTranslation + muCargoRotation*(pow(c[1],2) + pow(c[2],2) + a[1][1]*a[2][1] - c[1]*(a[1][1] + a[2][1]) + a[1][2]*a[2][2] - c[2]*(a[1][2] + a[2][2])))*(Dba[2][0] + FmTangential[2][0]) - muCargoRotation*(c[1] - a[1][1])*(c[0] - a[2][0])*(Dba[2][1] + FmTangential[2][1]) - muCargoRotation*(c[2] - a[1][2])*(c[0] - a[2][0])*(Dba[2][2] + FmTangential[2][2]));

            a1[1][1] = dt*(-(muCargoRotation*(Rbc[2] + TorqeExt[2])*(c[0] - a[1][0])) + a[1][1]/dt + muCargoRotation*(Rbc[0] + TorqeExt[0])*(c[2] - a[1][2]) + muCargoTranslation*(Dbc[1] + Fsteric[1] + Ftrap[1] + FmRadial[0][1] + FmRadial[1][1] + FmRadial[2][1]) - muCargoRotation*(c[1] - a[0][1])*(c[0] - a[1][0])*(Dba[0][0] + FmTangential[0][0]) + (muCargoTranslation + muCargoRotation*(pow(c[0],2) + pow(c[2],2) + a[0][0]*a[1][0] - c[0]*(a[0][0] + a[1][0]) + a[0][2]*a[1][2] - c[2]*(a[0][2] + a[1][2])))*(Dba[0][1] + FmTangential[0][1]) - muCargoRotation*(c[1] - a[0][1])*(c[2] - a[1][2])*(Dba[0][2] + FmTangential[0][2]) - muCargoRotation*(c[0] - a[1][0])*(c[1] - a[1][1])*(Dba[1][0] + FmTangential[1][0]) + (muCargoTranslation + muAnchor[1] + muCargoRotation*(pow(c[0],2) + pow(c[2],2) - 2*c[0]*a[1][0] + pow(a[1][0],2) - 2*c[2]*a[1][2] + pow(a[1][2],2)))*(Dba[1][1] + FmTangential[1][1]) - muCargoRotation*(c[1] - a[1][1])*(c[2] - a[1][2])*(Dba[1][2] + FmTangential[1][2]) - muCargoRotation*(c[0] - a[1][0])*(c[1] - a[2][1])*(Dba[2][0] + FmTangential[2][0]) + (muCargoTranslation + muCargoRotation*(pow(c[0],2) + pow(c[2],2) + a[1][0]*a[2][0] - c[0]*(a[1][0] + a[2][0]) + a[1][2]*a[2][2] - c[2]*(a[1][2] + a[2][2])))*(Dba[2][1] + FmTangential[2][1]) - muCargoRotation*(c[2] - a[1][2])*(c[1] - a[2][1])*(Dba[2][2] + FmTangential[2][2]));

            a1[1][2] = dt*(muCargoRotation*(Rbc[1] + TorqeExt[1])*(c[0] - a[1][0]) - muCargoRotation*(Rbc[0] + TorqeExt[0])*(c[1] - a[1][1]) + a[1][2]/dt + muCargoTranslation*(Dbc[2] + Fsteric[2] + Ftrap[2] + FmRadial[0][2] + FmRadial[1][2] + FmRadial[2][2]) - muCargoRotation*(c[2] - a[0][2])*(c[0] - a[1][0])*(Dba[0][0] + FmTangential[0][0]) - muCargoRotation*(c[2] - a[0][2])*(c[1] - a[1][1])*(Dba[0][1] + FmTangential[0][1]) + (muCargoTranslation + muCargoRotation*(pow(c[0],2) + pow(c[1],2) + a[0][0]*a[1][0] - c[0]*(a[0][0] + a[1][0]) + a[0][1]*a[1][1] - c[1]*(a[0][1] + a[1][1])))*(Dba[0][2] + FmTangential[0][2]) - muCargoRotation*(c[0] - a[1][0])*(c[2] - a[1][2])*(Dba[1][0] + FmTangential[1][0]) - muCargoRotation*(c[1] - a[1][1])*(c[2] - a[1][2])*(Dba[1][1] + FmTangential[1][1]) + (muCargoTranslation + muAnchor[1] + muCargoRotation*(pow(c[0],2) + pow(c[1],2) - 2*c[0]*a[1][0] + pow(a[1][0],2) - 2*c[1]*a[1][1] + pow(a[1][1],2)))*(Dba[1][2] + FmTangential[1][2]) - muCargoRotation*(c[0] - a[1][0])*(c[2] - a[2][2])*(Dba[2][0] + FmTangential[2][0]) - muCargoRotation*(c[1] - a[1][1])*(c[2] - a[2][2])*(Dba[2][1] + FmTangential[2][1]) + (muCargoTranslation + muCargoRotation*(pow(c[0],2) + pow(c[1],2) + a[1][0]*a[2][0] - c[0]*(a[1][0] + a[2][0]) + a[1][1]*a[2][1] - c[1]*(a[1][1] + a[2][1])))*(Dba[2][2] + FmTangential[2][2]));

            a1[2][0] = dt*(a[2][0]/dt + muCargoRotation*(Rbc[2] + TorqeExt[2])*(c[1] - a[2][1]) - muCargoRotation*(Rbc[1] + TorqeExt[1])*(c[2] - a[2][2]) + muCargoTranslation*(Dbc[0] + Fsteric[0] + Ftrap[0] + FmRadial[0][0] + FmRadial[1][0] + FmRadial[2][0]) + (muCargoTranslation + muCargoRotation*(pow(c[1],2) + pow(c[2],2) + a[0][1]*a[2][1] - c[1]*(a[0][1] + a[2][1]) + a[0][2]*a[2][2] - c[2]*(a[0][2] + a[2][2])))*(Dba[0][0] + FmTangential[0][0]) - muCargoRotation*(c[0] - a[0][0])*(c[1] - a[2][1])*(Dba[0][1] + FmTangential[0][1]) - muCargoRotation*(c[0] - a[0][0])*(c[2] - a[2][2])*(Dba[0][2] + FmTangential[0][2]) + (muCargoTranslation + muCargoRotation*(pow(c[1],2) + pow(c[2],2) + a[1][1]*a[2][1] - c[1]*(a[1][1] + a[2][1]) + a[1][2]*a[2][2] - c[2]*(a[1][2] + a[2][2])))*(Dba[1][0] + FmTangential[1][0]) - muCargoRotation*(c[0] - a[1][0])*(c[1] - a[2][1])*(Dba[1][1] + FmTangential[1][1]) - muCargoRotation*(c[0] - a[1][0])*(c[2] - a[2][2])*(Dba[1][2] + FmTangential[1][2]) + (muCargoTranslation + muAnchor[2] + muCargoRotation*(pow(c[1],2) + pow(c[2],2) - 2*c[1]*a[2][1] + pow(a[2][1],2) - 2*c[2]*a[2][2] + pow(a[2][2],2)))*(Dba[2][0] + FmTangential[2][0]) - muCargoRotation*(c[0] - a[2][0])*(c[1] - a[2][1])*(Dba[2][1] + FmTangential[2][1]) - muCargoRotation*(c[0] - a[2][0])*(c[2] - a[2][2])*(Dba[2][2] + FmTangential[2][2]));

            a1[2][1] = dt*(-(muCargoRotation*(Rbc[2] + TorqeExt[2])*(c[0] - a[2][0])) + a[2][1]/dt + muCargoRotation*(Rbc[0] + TorqeExt[0])*(c[2] - a[2][2]) + muCargoTranslation*(Dbc[1] + Fsteric[1] + Ftrap[1] + FmRadial[0][1] + FmRadial[1][1] + FmRadial[2][1]) - muCargoRotation*(c[1] - a[0][1])*(c[0] - a[2][0])*(Dba[0][0] + FmTangential[0][0]) + (muCargoTranslation + muCargoRotation*(pow(c[0],2) + pow(c[2],2) + a[0][0]*a[2][0] - c[0]*(a[0][0] + a[2][0]) + a[0][2]*a[2][2] - c[2]*(a[0][2] + a[2][2])))*(Dba[0][1] + FmTangential[0][1]) - muCargoRotation*(c[1] - a[0][1])*(c[2] - a[2][2])*(Dba[0][2] + FmTangential[0][2]) - muCargoRotation*(c[1] - a[1][1])*(c[0] - a[2][0])*(Dba[1][0] + FmTangential[1][0]) + (muCargoTranslation + muCargoRotation*(pow(c[0],2) + pow(c[2],2) + a[1][0]*a[2][0] - c[0]*(a[1][0] + a[2][0]) + a[1][2]*a[2][2] - c[2]*(a[1][2] + a[2][2])))*(Dba[1][1] + FmTangential[1][1]) - muCargoRotation*(c[1] - a[1][1])*(c[2] - a[2][2])*(Dba[1][2] + FmTangential[1][2]) - muCargoRotation*(c[0] - a[2][0])*(c[1] - a[2][1])*(Dba[2][0] + FmTangential[2][0]) + (muCargoTranslation + muAnchor[2] + muCargoRotation*(pow(c[0],2) + pow(c[2],2) - 2*c[0]*a[2][0] + pow(a[2][0],2) - 2*c[2]*a[2][2] + pow(a[2][2],2)))*(Dba[2][1] + FmTangential[2][1]) - muCargoRotation*(c[1] - a[2][1])*(c[2] - a[2][2])*(Dba[2][2] + FmTangential[2][2]));

            a1[2][2] = dt*(muCargoRotation*(Rbc[1] + TorqeExt[1])*(c[0] - a[2][0]) - muCargoRotation*(Rbc[0] + TorqeExt[0])*(c[1] - a[2][1]) + a[2][2]/dt + muCargoTranslation*(Dbc[2] + Fsteric[2] + Ftrap[2] + FmRadial[0][2] + FmRadial[1][2] + FmRadial[2][2]) - muCargoRotation*(c[2] - a[0][2])*(c[0] - a[2][0])*(Dba[0][0] + FmTangential[0][0]) - muCargoRotation*(c[2] - a[0][2])*(c[1] - a[2][1])*(Dba[0][1] + FmTangential[0][1]) + (muCargoTranslation + muCargoRotation*(pow(c[0],2) + pow(c[1],2) + a[0][0]*a[2][0] - c[0]*(a[0][0] + a[2][0]) + a[0][1]*a[2][1] - c[1]*(a[0][1] + a[2][1])))*(Dba[0][2] + FmTangential[0][2]) - muCargoRotation*(c[2] - a[1][2])*(c[0] - a[2][0])*(Dba[1][0] + FmTangential[1][0]) - muCargoRotation*(c[2] - a[1][2])*(c[1] - a[2][1])*(Dba[1][1] + FmTangential[1][1]) + (muCargoTranslation + muCargoRotation*(pow(c[0],2) + pow(c[1],2) + a[1][0]*a[2][0] - c[0]*(a[1][0] + a[2][0]) + a[1][1]*a[2][1] - c[1]*(a[1][1] + a[2][1])))*(Dba[1][2] + FmTangential[1][2]) - muCargoRotation*(c[0] - a[2][0])*(c[2] - a[2][2])*(Dba[2][0] + FmTangential[2][0]) - muCargoRotation*(c[1] - a[2][1])*(c[2] - a[2][2])*(Dba[2][1] + FmTangential[2][1]) + (muCargoTranslation + muAnchor[2] + muCargoRotation*(pow(c[0],2) + pow(c[1],2) - 2*c[0]*a[2][0] + pow(a[2][0],2) - 2*c[1]*a[2][1] + pow(a[2][1],2)))*(Dba[2][2] + FmTangential[2][2]));

            c1[0] = c[0] + dt*muCargoTranslation*(Dbc[0] + Fsteric[0] + Ftrap[0] + Dba[0][0] + Dba[1][0] + Dba[2][0] + FmRadial[0][0] + FmRadial[1][0] + FmRadial[2][0] + FmTangential[0][0] + FmTangential[1][0] + FmTangential[2][0]);

            c1[1] = c[1] + dt*muCargoTranslation*(Dbc[1] + Fsteric[1] + Ftrap[1] + Dba[0][1] + Dba[1][1] + Dba[2][1] + FmRadial[0][1] + FmRadial[1][1] + FmRadial[2][1] + FmTangential[0][1] + FmTangential[1][1] + FmTangential[2][1]);

            c1[2] = c[2] + dt*muCargoTranslation*(Dbc[2] + Fsteric[2] + Ftrap[2] + Dba[0][2] + Dba[1][2] + Dba[2][2] + FmRadial[0][2] + FmRadial[1][2] + FmRadial[2][2] + FmTangential[0][2] + FmTangential[1][2] + FmTangential[2][2]);

//            theta1[0] = dt*(theta[0]/dt + muCargoRotation*(Rbc[0] + TorqeExt[0]) + muCargoRotation*(c[2] - a[0][2])*(Dba[0][1] + FmTangential[0][1]) + muCargoRotation*(-c[1] + a[0][1])*(Dba[0][2] + FmTangential[0][2]) + muCargoRotation*(c[2] - a[1][2])*(Dba[1][1] + FmTangential[1][1]) + muCargoRotation*(-c[1] + a[1][1])*(Dba[1][2] + FmTangential[1][2]) + muCargoRotation*(c[2] - a[2][2])*(Dba[2][1] + FmTangential[2][1]) + muCargoRotation*(-c[1] + a[2][1])*(Dba[2][2] + FmTangential[2][2]));

//            theta1[1] = dt*(theta[1]/dt + muCargoRotation*(Rbc[1] + TorqeExt[1]) + muCargoRotation*(-c[2] + a[0][2])*(Dba[0][0] + FmTangential[0][0]) + muCargoRotation*(c[0] - a[0][0])*(Dba[0][2] + FmTangential[0][2]) + muCargoRotation*(-c[2] + a[1][2])*(Dba[1][0] + FmTangential[1][0]) + muCargoRotation*(c[0] - a[1][0])*(Dba[1][2] + FmTangential[1][2]) + muCargoRotation*(-c[2] + a[2][2])*(Dba[2][0] + FmTangential[2][0]) + muCargoRotation*(c[0] - a[2][0])*(Dba[2][2] + FmTangential[2][2]));

//            theta1[2] = dt*(theta[2]/dt + muCargoRotation*(Rbc[2] + TorqeExt[2]) + muCargoRotation*(c[1] - a[0][1])*(Dba[0][0] + FmTangential[0][0]) + muCargoRotation*(-c[0] + a[0][0])*(Dba[0][1] + FmTangential[0][1]) + muCargoRotation*(c[1] - a[1][1])*(Dba[1][0] + FmTangential[1][0]) + muCargoRotation*(-c[0] + a[1][0])*(Dba[1][1] + FmTangential[1][1]) + muCargoRotation*(c[1] - a[2][1])*(Dba[2][0] + FmTangential[2][0]) + muCargoRotation*(-c[0] + a[2][0])*(Dba[2][1] + FmTangential[2][1]));

            break;

        default:
            printf("Bad value for total_motors\n");
    }
}
