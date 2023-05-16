#include "common.h"

void observables_init() {

    obs.CII.resize( input.steps+1 );
    obs.CIx.resize( input.steps+1 );
    obs.CIy.resize( input.steps+1 );
    obs.CIz.resize( input.steps+1 );
    obs.CxI.resize( input.steps+1 );
    obs.Cxx.resize( input.steps+1 );
    obs.Cxy.resize( input.steps+1 );
    obs.Cxz.resize( input.steps+1 );
    obs.CyI.resize( input.steps+1 );
    obs.Cyx.resize( input.steps+1 );
    obs.Cyy.resize( input.steps+1 );
    obs.Cyz.resize( input.steps+1 );
    obs.CzI.resize( input.steps+1 );
    obs.Czx.resize( input.steps+1 );
    obs.Czy.resize( input.steps+1 );
    obs.Czz.resize( input.steps+1 );

    for ( int i=0; i<input.steps+1; ++i ) {
      obs.CII[i] = 0.; obs.CIx[i] = 0.; obs.CIy[i] = 0.; obs.CIz[i] = 0.;
      obs.CxI[i] = 0.; obs.Cxx[i] = 0.; obs.Cxy[i] = 0.; obs.Cxz[i] = 0.;
      obs.CyI[i] = 0.; obs.Cyx[i] = 0.; obs.Cyy[i] = 0.; obs.Cyz[i] = 0.;
      obs.CzI[i] = 0.; obs.Czx[i] = 0.; obs.Czy[i] = 0.; obs.Czz[i] = 0.;
    }

}

void time_zero_ops() {

    obs.si0 = 0.5 * ( traj.Xe[0] * traj.Xe[0] + traj.Pe[0] * traj.Pe[0] + \
                      traj.Xe[1] * traj.Xe[1] + traj.Pe[1] * traj.Pe[1] + 1 );

    obs.sx0 = traj.Xe[0] * traj.Xe[1] + traj.Pe[0] * traj.Pe[1];

    obs.sy0 = traj.Xe[0] * traj.Pe[1] - traj.Pe[0] * traj.Xe[1];

    obs.sz0 = 0.5 * ( traj.Xe[0] * traj.Xe[0] + traj.Pe[0] * traj.Pe[0] - \
                      traj.Xe[1] * traj.Xe[1] - traj.Pe[1] * traj.Pe[1] );

    obs.si = obs.si0;
    obs.sx = obs.sx0;
    obs.sy = obs.sy0;
    obs.sz = obs.sz0;

}

void time_t_ops() {

    obs.si = 0.5 * ( traj.Xe[0] * traj.Xe[0] + traj.Pe[0] * traj.Pe[0] + \
                      traj.Xe[1] * traj.Xe[1] + traj.Pe[1] * traj.Pe[1] + 1 );

    obs.sx = traj.Xe[0] * traj.Xe[1] + traj.Pe[0] * traj.Pe[1];

    obs.sy = traj.Xe[0] * traj.Pe[1] - traj.Pe[0] * traj.Xe[1];

    obs.sz = 0.5 * ( traj.Xe[0] * traj.Xe[0] + traj.Pe[0] * traj.Pe[0] - \
                      traj.Xe[1] * traj.Xe[1] - traj.Pe[1] * traj.Pe[1] );
}

void observables( int ts ) {
  obs.CII[ts] += obs.si0 * obs.si;
  obs.CIx[ts] += obs.si0 * obs.sx;
  obs.CIy[ts] += obs.si0 * obs.sy;
  obs.CIz[ts] += obs.si0 * obs.sz;
  obs.CxI[ts] += obs.sx0 * obs.si;
  obs.Cxx[ts] += obs.sx0 * obs.sx;
  obs.Cxy[ts] += obs.sx0 * obs.sy;
  obs.Cxz[ts] += obs.sx0 * obs.sz;
  obs.CyI[ts] += obs.sy0 * obs.si;
  obs.Cyx[ts] += obs.sy0 * obs.sx;
  obs.Cyy[ts] += obs.sy0 * obs.sy;
  obs.Cyz[ts] += obs.sy0 * obs.sz;
  obs.CzI[ts] += obs.sz0 * obs.si;
  obs.Czx[ts] += obs.sz0 * obs.sx;
  obs.Czy[ts] += obs.sz0 * obs.sy;
  obs.Czz[ts] += obs.sz0 * obs.sz;
}

void average() {
  double norm = 1.0;

  // Determine "normalization" factors of 2
  // based on initial electornic distribution
  if ( input.rhoe.compare( "phi" ) == 0 ) {
    norm = 2.0;
  } else if ( input.rhoe.compare( "phi2" ) == 0 ) {
    norm = 8.0;
  }

  // Average Pauli matrix correlation functions
  for ( int ts=0; ts<input.steps+1; ++ts ) {
    obs.CII[ts] = obs.CII[ts] * norm / input.traj;
    obs.CIx[ts] = obs.CIx[ts] * norm / input.traj;
    obs.CIy[ts] = obs.CIy[ts] * norm / input.traj;
    obs.CIz[ts] = obs.CIz[ts] * norm / input.traj;
    obs.CxI[ts] = obs.CxI[ts] * norm / input.traj;
    obs.Cxx[ts] = obs.Cxx[ts] * norm / input.traj;
    obs.Cxy[ts] = obs.Cxy[ts] * norm / input.traj;
    obs.Cxz[ts] = obs.Cxz[ts] * norm / input.traj;
    obs.CyI[ts] = obs.CyI[ts] * norm / input.traj;
    obs.Cyx[ts] = obs.Cyx[ts] * norm / input.traj;
    obs.Cyy[ts] = obs.Cyy[ts] * norm / input.traj;
    obs.Cyz[ts] = obs.Cyz[ts] * norm / input.traj;
    obs.CzI[ts] = obs.CzI[ts] * norm / input.traj;
    obs.Czx[ts] = obs.Czx[ts] * norm / input.traj;
    obs.Czy[ts] = obs.Czy[ts] * norm / input.traj;
    obs.Czz[ts] = obs.Czz[ts] * norm / input.traj;
  }
}
