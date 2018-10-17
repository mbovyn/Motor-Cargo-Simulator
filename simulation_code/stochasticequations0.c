//prototypes
void stochastic_equations();

void stochastic_equations(){
    switch(total_motors){
        case 0:
            c1[0] = c[0] + sqrt(2)*sqrt(DCargoTranslation)*sqrt(dt)*Dbc[0] + dt*muCargoTranslation*(Fsteric[0] + Ftrap[0]);

            c1[1] = c[1] + sqrt(2)*sqrt(DCargoTranslation)*sqrt(dt)*Dbc[1] + dt*muCargoTranslation*(Fsteric[1] + Ftrap[1]);

            c1[2] = c[2] + sqrt(2)*sqrt(DCargoTranslation)*sqrt(dt)*Dbc[2] + dt*muCargoTranslation*(Fsteric[2] + Ftrap[2]);

            theta1[0] = sqrt(2)*sqrt(DCargoRotation)*sqrt(dt)*Rbc[0] + theta[0] + dt*muCargoRotation*TorqeExt[0];

            theta1[1] = sqrt(2)*sqrt(DCargoRotation)*sqrt(dt)*Rbc[1] + theta[1] + dt*muCargoRotation*TorqeExt[1];

            theta1[2] = sqrt(2)*sqrt(DCargoRotation)*sqrt(dt)*Rbc[2] + theta[2] + dt*muCargoRotation*TorqeExt[2];

            break;

        default:
            printf("Bad value for total_motors\n");
            exit(0);
    }
}
