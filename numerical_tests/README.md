# Numerical Tests of the Simulation

These are a series of tests which demonstrate the code conforms to expectations
in a variety of situations.

In all figures, solid lines represent inputs into the simulation.

## Rates

### Off rate

Tests the time for a single motor to unbind from the microtubule when under force.

![Bovyn 2018 Off Rate](off_rate/Bovyn2018%20off%20rate/association%20time%20vs%20force.png "Off rate with force")

We assume unbinding is a Poisson process, so times to unbind are exponentially distributed.

![Association time distributions](off_rate/Bovyn2018%20off%20rate/association%20time%20distributions.png "Association time distributions")

### On rate

Tests the time for a motor to bind the microtubule.

![Mean binding time with on rate](on_rate/sweep%20on%20rate/mean%20binding%20time%20with%20on%20rate.png "Binding time with on rate")

The binding rate is a function of the distance from the anchor to the microtubule surface.

![Binding time with distance](on_rate/with%20distance/mean%20binding%20time%20with%20anchor-MT%20distance.png "On rate with distance")

We assume binding to be a Poisson process, so times to bind are exponentially distributed.

![Binding time distributions](on_rate/sweep%20on%20rate/binding%20time%20distributions.png "Binding time distributions")

### Stepping rate

![Velocity with force](stepping_rate/mean%20velocity%20vs%20force.png)

![Step number distributions](stepping_rate/distributions%20of%20numbers%20of%20steps.png)

## Forces

### Radial Force

![Radial force test](forces/radial%20motor%20-%20external%20force/position%20vs%20time.png)

### Tangential Force

![Tangential force test](forces/tangential%20motor%20-%20external%20torque/free/rotational%20velocity%20vs%20time.png)

## Diffusion

### Cargo Translational Diffusion

![Cargo translational diffusion](cargo_diffusion/translation/MSD-t.png)

![location distributions](cargo_diffusion/translation/location%20distributions.png)

### Cargo Rotational Diffusion

![Rotation MFP](cargo_diffusion/rotation/bead/Mean%20First%20Passage%20time%20with%20elevation.png)

![rotational first passage time distributions](cargo_diffusion/rotation/bead/First%20passage%20time%20distributions.png)

### Anchor diffusion in the cargo membrane

![Anchor MFP](motor_diffusion/Mean%20First%20Passage%20Time%20with%20Elevation.png)

![Anchor first passage time distributions](motor_diffusion/First%20Passage%20Time%20Distributions.png)
