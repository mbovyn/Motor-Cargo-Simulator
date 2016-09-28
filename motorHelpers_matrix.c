//prototypes
void setup_matrix( void );

void setup_matrix(void)
{
    if (total_motors_attached==4){
        double a_data[]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
           -((az[4]*xiAnchor[4])/dt) + (cz[4]*xiAnchor[4])/dt,
           (ay[4]*xiAnchor[4])/dt - (cy[4]*xiAnchor[4])/dt,0,0,0,
           -xiCargoRotation + pow(ay[4],2)*xiAnchor[4] + pow(az[4],2)*xiAnchor[4] -
            2*ay[4]*cy[4]*xiAnchor[4] + pow(cy[4],2)*xiAnchor[4] - 2*az[4]*cz[4]*xiAnchor[4] +
            pow(cz[4],2)*xiAnchor[4],-(ax[4]*ay[4]*xiAnchor[4]) + ay[4]*cx[4]*xiAnchor[4] +
            ax[4]*cy[4]*xiAnchor[4] - cx[4]*cy[4]*xiAnchor[4],
           -(ax[4]*az[4]*xiAnchor[4]) + az[4]*cx[4]*xiAnchor[4] + ax[4]*cz[4]*xiAnchor[4] -
            cx[4]*cz[4]*xiAnchor[4],0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
           (az[4]*xiAnchor[4])/dt - (cz[4]*xiAnchor[4])/dt,0,
           -((ax[4]*xiAnchor[4])/dt) + (cx[4]*xiAnchor[4])/dt,0,0,0,
           -(ax[4]*ay[4]*xiAnchor[4]) + ay[4]*cx[4]*xiAnchor[4] + ax[4]*cy[4]*xiAnchor[4] -
            cx[4]*cy[4]*xiAnchor[4],-xiCargoRotation + pow(ax[4],2)*xiAnchor[4] +
            pow(az[4],2)*xiAnchor[4] - 2*ax[4]*cx[4]*xiAnchor[4] + pow(cx[4],2)*xiAnchor[4] -
            2*az[4]*cz[4]*xiAnchor[4] + pow(cz[4],2)*xiAnchor[4],
           -(ay[4]*az[4]*xiAnchor[4]) + az[4]*cy[4]*xiAnchor[4] + ay[4]*cz[4]*xiAnchor[4] -
            cy[4]*cz[4]*xiAnchor[4],0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
           -((ay[4]*xiAnchor[4])/dt) + (cy[4]*xiAnchor[4])/dt,
           (ax[4]*xiAnchor[4])/dt - (cx[4]*xiAnchor[4])/dt,0,0,0,0,
           -(ax[4]*az[4]*xiAnchor[4]) + az[4]*cx[4]*xiAnchor[4] + ax[4]*cz[4]*xiAnchor[4] -
            cx[4]*cz[4]*xiAnchor[4],-(ay[4]*az[4]*xiAnchor[4]) + az[4]*cy[4]*xiAnchor[4] +
            ay[4]*cz[4]*xiAnchor[4] - cy[4]*cz[4]*xiAnchor[4],
           -xiCargoRotation + pow(ax[4],2)*xiAnchor[4] + pow(ay[4],2)*xiAnchor[4] -
            2*ax[4]*cx[4]*xiAnchor[4] + pow(cx[4],2)*xiAnchor[4] - 2*ay[4]*cy[4]*xiAnchor[4] +
            pow(cy[4],2)*xiAnchor[4],0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
           xiAnchor[4]/dt,0,0,-(xiCargoTranslation/dt),0,0,0,
           az[4]*xiAnchor[4] - cz[4]*xiAnchor[4],-(ay[4]*xiAnchor[4]) + cy[4]*xiAnchor[4],0,0,0,0,
           0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,xiAnchor[4]/dt,0,0,
           -(xiCargoTranslation/dt),0,-(az[4]*xiAnchor[4]) + cz[4]*xiAnchor[4],0,
           ax[4]*xiAnchor[4] - cx[4]*xiAnchor[4],0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
           0,0,0,0,0,xiAnchor[4]/dt,0,0,-(xiCargoTranslation/dt),
           ay[4]*xiAnchor[4] - cy[4]*xiAnchor[4],-(ax[4]*xiAnchor[4]) + cx[4]*xiAnchor[4],0,0,0,0,
           0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,-(xiAnchor[4]/dt),0,0,0,0,0,0,
           -(az[4]*xiAnchor[4]) + cz[4]*xiAnchor[4],ay[4]*xiAnchor[4] - cy[4]*xiAnchor[4],0,0,0,0,
           0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,-(xiAnchor[4]/dt),0,0,0,0,
           az[4]*xiAnchor[4] - cz[4]*xiAnchor[4],0,-(ax[4]*xiAnchor[4]) + cx[4]*xiAnchor[4],0,0,0,
           0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,-(xiAnchor[4]/dt),0,0,0,
           -(ay[4]*xiAnchor[4]) + cy[4]*xiAnchor[4],ax[4]*xiAnchor[4] - cx[4]*xiAnchor[4],0,0,0,0,
           0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,-((az[3]*xiAnchor[3])/dt) + (cz[3]*xiAnchor[3])/dt,
           (ay[3]*xiAnchor[3])/dt - (cy[3]*xiAnchor[3])/dt,0,0,0,
           -xiCargoRotation + pow(ay[3],2)*xiAnchor[3] + pow(az[3],2)*xiAnchor[3] -
            2*ay[3]*cy[3]*xiAnchor[3] + pow(cy[3],2)*xiAnchor[3] - 2*az[3]*cz[3]*xiAnchor[3] +
            pow(cz[3],2)*xiAnchor[3],-(ax[3]*ay[3]*xiAnchor[3]) + ay[3]*cx[3]*xiAnchor[3] +
            ax[3]*cy[3]*xiAnchor[3] - cx[3]*cy[3]*xiAnchor[3],
           -(ax[3]*az[3]*xiAnchor[3]) + az[3]*cx[3]*xiAnchor[3] + ax[3]*cz[3]*xiAnchor[3] -
            cx[3]*cz[3]*xiAnchor[3],0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
           (az[3]*xiAnchor[3])/dt - (cz[3]*xiAnchor[3])/dt,0,
           -((ax[3]*xiAnchor[3])/dt) + (cx[3]*xiAnchor[3])/dt,0,0,0,
           -(ax[3]*ay[3]*xiAnchor[3]) + ay[3]*cx[3]*xiAnchor[3] + ax[3]*cy[3]*xiAnchor[3] -
            cx[3]*cy[3]*xiAnchor[3],-xiCargoRotation + pow(ax[3],2)*xiAnchor[3] +
            pow(az[3],2)*xiAnchor[3] - 2*ax[3]*cx[3]*xiAnchor[3] + pow(cx[3],2)*xiAnchor[3] -
            2*az[3]*cz[3]*xiAnchor[3] + pow(cz[3],2)*xiAnchor[3],
           -(ay[3]*az[3]*xiAnchor[3]) + az[3]*cy[3]*xiAnchor[3] + ay[3]*cz[3]*xiAnchor[3] -
            cy[3]*cz[3]*xiAnchor[3],0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
           -((ay[3]*xiAnchor[3])/dt) + (cy[3]*xiAnchor[3])/dt,
           (ax[3]*xiAnchor[3])/dt - (cx[3]*xiAnchor[3])/dt,0,0,0,0,
           -(ax[3]*az[3]*xiAnchor[3]) + az[3]*cx[3]*xiAnchor[3] + ax[3]*cz[3]*xiAnchor[3] -
            cx[3]*cz[3]*xiAnchor[3],-(ay[3]*az[3]*xiAnchor[3]) + az[3]*cy[3]*xiAnchor[3] +
            ay[3]*cz[3]*xiAnchor[3] - cy[3]*cz[3]*xiAnchor[3],
           -xiCargoRotation + pow(ax[3],2)*xiAnchor[3] + pow(ay[3],2)*xiAnchor[3] -
            2*ax[3]*cx[3]*xiAnchor[3] + pow(cx[3],2)*xiAnchor[3] - 2*ay[3]*cy[3]*xiAnchor[3] +
            pow(cy[3],2)*xiAnchor[3],0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
           xiAnchor[3]/dt,0,0,-(xiCargoTranslation/dt),0,0,0,
           az[3]*xiAnchor[3] - cz[3]*xiAnchor[3],-(ay[3]*xiAnchor[3]) + cy[3]*xiAnchor[3],0,0,0,0,
           0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,xiAnchor[3]/dt,0,0,
           -(xiCargoTranslation/dt),0,-(az[3]*xiAnchor[3]) + cz[3]*xiAnchor[3],0,
           ax[3]*xiAnchor[3] - cx[3]*xiAnchor[3],0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
           0,0,0,0,0,xiAnchor[3]/dt,0,0,-(xiCargoTranslation/dt),
           ay[3]*xiAnchor[3] - cy[3]*xiAnchor[3],-(ax[3]*xiAnchor[3]) + cx[3]*xiAnchor[3],0,0,0,0,
           0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,-(xiAnchor[3]/dt),0,0,0,0,0,0,
           -(az[3]*xiAnchor[3]) + cz[3]*xiAnchor[3],ay[3]*xiAnchor[3] - cy[3]*xiAnchor[3],0,0,0,0,
           0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,-(xiAnchor[3]/dt),0,0,0,0,
           az[3]*xiAnchor[3] - cz[3]*xiAnchor[3],0,-(ax[3]*xiAnchor[3]) + cx[3]*xiAnchor[3],0,0,0,
           0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,-(xiAnchor[3]/dt),0,0,0,
           -(ay[3]*xiAnchor[3]) + cy[3]*xiAnchor[3],ax[3]*xiAnchor[3] - cx[3]*xiAnchor[3],0,0,0,0,
           0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,-((az[2]*xiAnchor[2])/dt) + (cz[2]*xiAnchor[2])/dt,
           (ay[2]*xiAnchor[2])/dt - (cy[2]*xiAnchor[2])/dt,0,0,0,
           -xiCargoRotation + pow(ay[2],2)*xiAnchor[2] + pow(az[2],2)*xiAnchor[2] -
            2*ay[2]*cy[2]*xiAnchor[2] + pow(cy[2],2)*xiAnchor[2] - 2*az[2]*cz[2]*xiAnchor[2] +
            pow(cz[2],2)*xiAnchor[2],-(ax[2]*ay[2]*xiAnchor[2]) + ay[2]*cx[2]*xiAnchor[2] +
            ax[2]*cy[2]*xiAnchor[2] - cx[2]*cy[2]*xiAnchor[2],
           -(ax[2]*az[2]*xiAnchor[2]) + az[2]*cx[2]*xiAnchor[2] + ax[2]*cz[2]*xiAnchor[2] -
            cx[2]*cz[2]*xiAnchor[2],0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
           (az[2]*xiAnchor[2])/dt - (cz[2]*xiAnchor[2])/dt,0,
           -((ax[2]*xiAnchor[2])/dt) + (cx[2]*xiAnchor[2])/dt,0,0,0,
           -(ax[2]*ay[2]*xiAnchor[2]) + ay[2]*cx[2]*xiAnchor[2] + ax[2]*cy[2]*xiAnchor[2] -
            cx[2]*cy[2]*xiAnchor[2],-xiCargoRotation + pow(ax[2],2)*xiAnchor[2] +
            pow(az[2],2)*xiAnchor[2] - 2*ax[2]*cx[2]*xiAnchor[2] + pow(cx[2],2)*xiAnchor[2] -
            2*az[2]*cz[2]*xiAnchor[2] + pow(cz[2],2)*xiAnchor[2],
           -(ay[2]*az[2]*xiAnchor[2]) + az[2]*cy[2]*xiAnchor[2] + ay[2]*cz[2]*xiAnchor[2] -
            cy[2]*cz[2]*xiAnchor[2],0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
           -((ay[2]*xiAnchor[2])/dt) + (cy[2]*xiAnchor[2])/dt,
           (ax[2]*xiAnchor[2])/dt - (cx[2]*xiAnchor[2])/dt,0,0,0,0,
           -(ax[2]*az[2]*xiAnchor[2]) + az[2]*cx[2]*xiAnchor[2] + ax[2]*cz[2]*xiAnchor[2] -
            cx[2]*cz[2]*xiAnchor[2],-(ay[2]*az[2]*xiAnchor[2]) + az[2]*cy[2]*xiAnchor[2] +
            ay[2]*cz[2]*xiAnchor[2] - cy[2]*cz[2]*xiAnchor[2],
           -xiCargoRotation + pow(ax[2],2)*xiAnchor[2] + pow(ay[2],2)*xiAnchor[2] -
            2*ax[2]*cx[2]*xiAnchor[2] + pow(cx[2],2)*xiAnchor[2] - 2*ay[2]*cy[2]*xiAnchor[2] +
            pow(cy[2],2)*xiAnchor[2],0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
           xiAnchor[2]/dt,0,0,-(xiCargoTranslation/dt),0,0,0,
           az[2]*xiAnchor[2] - cz[2]*xiAnchor[2],-(ay[2]*xiAnchor[2]) + cy[2]*xiAnchor[2],0,0,0,0,
           0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,xiAnchor[2]/dt,0,0,
           -(xiCargoTranslation/dt),0,-(az[2]*xiAnchor[2]) + cz[2]*xiAnchor[2],0,
           ax[2]*xiAnchor[2] - cx[2]*xiAnchor[2],0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
           0,0,0,0,0,xiAnchor[2]/dt,0,0,-(xiCargoTranslation/dt),
           ay[2]*xiAnchor[2] - cy[2]*xiAnchor[2],-(ax[2]*xiAnchor[2]) + cx[2]*xiAnchor[2],0,0,0,0,
           0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,-(xiAnchor[2]/dt),0,0,0,0,0,0,
           -(az[2]*xiAnchor[2]) + cz[2]*xiAnchor[2],ay[2]*xiAnchor[2] - cy[2]*xiAnchor[2],0,0,0,0,
           0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,-(xiAnchor[2]/dt),0,0,0,0,
           az[2]*xiAnchor[2] - cz[2]*xiAnchor[2],0,-(ax[2]*xiAnchor[2]) + cx[2]*xiAnchor[2],0,0,0,
           0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,-(xiAnchor[2]/dt),0,0,0,
           -(ay[2]*xiAnchor[2]) + cy[2]*xiAnchor[2],ax[2]*xiAnchor[2] - cx[2]*xiAnchor[2],0,0,0,0,
           0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,-((az[1]*xiAnchor[1])/dt) + (cz[1]*xiAnchor[1])/dt,
           (ay[1]*xiAnchor[1])/dt - (cy[1]*xiAnchor[1])/dt,0,0,0,
           -xiCargoRotation + pow(ay[1],2)*xiAnchor[1] + pow(az[1],2)*xiAnchor[1] -
            2*ay[1]*cy[1]*xiAnchor[1] + pow(cy[1],2)*xiAnchor[1] - 2*az[1]*cz[1]*xiAnchor[1] +
            pow(cz[1],2)*xiAnchor[1],-(ax[1]*ay[1]*xiAnchor[1]) + ay[1]*cx[1]*xiAnchor[1] +
            ax[1]*cy[1]*xiAnchor[1] - cx[1]*cy[1]*xiAnchor[1],
           -(ax[1]*az[1]*xiAnchor[1]) + az[1]*cx[1]*xiAnchor[1] + ax[1]*cz[1]*xiAnchor[1] -
            cx[1]*cz[1]*xiAnchor[1],0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
           (az[1]*xiAnchor[1])/dt - (cz[1]*xiAnchor[1])/dt,0,
           -((ax[1]*xiAnchor[1])/dt) + (cx[1]*xiAnchor[1])/dt,0,0,0,
           -(ax[1]*ay[1]*xiAnchor[1]) + ay[1]*cx[1]*xiAnchor[1] + ax[1]*cy[1]*xiAnchor[1] -
            cx[1]*cy[1]*xiAnchor[1],-xiCargoRotation + pow(ax[1],2)*xiAnchor[1] +
            pow(az[1],2)*xiAnchor[1] - 2*ax[1]*cx[1]*xiAnchor[1] + pow(cx[1],2)*xiAnchor[1] -
            2*az[1]*cz[1]*xiAnchor[1] + pow(cz[1],2)*xiAnchor[1],
           -(ay[1]*az[1]*xiAnchor[1]) + az[1]*cy[1]*xiAnchor[1] + ay[1]*cz[1]*xiAnchor[1] -
            cy[1]*cz[1]*xiAnchor[1],0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
           -((ay[1]*xiAnchor[1])/dt) + (cy[1]*xiAnchor[1])/dt,
           (ax[1]*xiAnchor[1])/dt - (cx[1]*xiAnchor[1])/dt,0,0,0,0,
           -(ax[1]*az[1]*xiAnchor[1]) + az[1]*cx[1]*xiAnchor[1] + ax[1]*cz[1]*xiAnchor[1] -
            cx[1]*cz[1]*xiAnchor[1],-(ay[1]*az[1]*xiAnchor[1]) + az[1]*cy[1]*xiAnchor[1] +
            ay[1]*cz[1]*xiAnchor[1] - cy[1]*cz[1]*xiAnchor[1],
           -xiCargoRotation + pow(ax[1],2)*xiAnchor[1] + pow(ay[1],2)*xiAnchor[1] -
            2*ax[1]*cx[1]*xiAnchor[1] + pow(cx[1],2)*xiAnchor[1] - 2*ay[1]*cy[1]*xiAnchor[1] +
            pow(cy[1],2)*xiAnchor[1],0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
           xiAnchor[1]/dt,0,0,-(xiCargoTranslation/dt),0,0,0,
           az[1]*xiAnchor[1] - cz[1]*xiAnchor[1],-(ay[1]*xiAnchor[1]) + cy[1]*xiAnchor[1],0,0,0,0,
           0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,xiAnchor[1]/dt,0,0,
           -(xiCargoTranslation/dt),0,-(az[1]*xiAnchor[1]) + cz[1]*xiAnchor[1],0,
           ax[1]*xiAnchor[1] - cx[1]*xiAnchor[1],0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
           0,0,0,0,0,xiAnchor[1]/dt,0,0,-(xiCargoTranslation/dt),
           ay[1]*xiAnchor[1] - cy[1]*xiAnchor[1],-(ax[1]*xiAnchor[1]) + cx[1]*xiAnchor[1],0,0,0,0,
           0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,-(xiAnchor[1]/dt),0,0,0,0,0,0,
           -(az[1]*xiAnchor[1]) + cz[1]*xiAnchor[1],ay[1]*xiAnchor[1] - cy[1]*xiAnchor[1],0,0,0,0,
           0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,-(xiAnchor[1]/dt),0,0,0,0,
           az[1]*xiAnchor[1] - cz[1]*xiAnchor[1],0,-(ax[1]*xiAnchor[1]) + cx[1]*xiAnchor[1],0,0,0,
           0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,-(xiAnchor[1]/dt),0,0,0,
           -(ay[1]*xiAnchor[1]) + cy[1]*xiAnchor[1],ax[1]*xiAnchor[1] - cx[1]*xiAnchor[1],0,0,0,0,
           0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    }
}
