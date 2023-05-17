#include "common.h"
#include "spin_boson.h"

std::vector< double > matvec(std::vector< std::vector <double> >,
                             std::vector< double>, int);

int integrate_eoms() {

	double hdt = 0.5 * input.dt;
	double qdt = 0.5 * hdt;

	// Velocit verlet algorithm
	// Calculate potential and forces
	sb_pot();

	// Half-step in nuclear momenta
	for ( int i=0; i<input.F; ++i) {
		 traj.pn[i] = traj.pn[i] - hdt * pot.G0[i];
		 for ( int j=0; j<input.S; ++j) {
		 	traj.pn[i] = traj.pn[i] - qdt * pot.G[i][j][j] * \
		 		(std::pow(traj.Xe[j],2) + std::pow(traj.Pe[j], 2));
		 }
	}

	// Half-step in mapping Ps
	for ( int i=0; i<input.S; ++i ) {
		for ( int j=0; j<input.S; ++j ){
			traj.Pe[i] = traj.Pe[i] - hdt * traj.Xe[j] * pot.V[i][j];
		}
	}
 
	// Full-step in nulear positions
	for ( int i=0; i<input.F; ++i) {
		traj.xn[i] = traj.xn[i] + input.dt * traj.pn[i];
	}

	// Full-step in mapping Xs
	sb_pot();
	for ( int i=0; i<input.S; ++i) {
		for ( int j=0; j<input.S; ++j) {
			traj.Xe[i] = traj.Xe[i] + input.dt * traj.Pe[j] * pot.V[i][j];
		}
	}

	// Half-step in mapping Ps
	for ( int i=0; i<input.S; ++i ) {
		for ( int j=0; j<input.S; ++j ){
			traj.Pe[i] = traj.Pe[i] - hdt * traj.Xe[j] * pot.V[i][j];
		}
	}

	// Half-step in nuclear momenta
	for ( int i=0; i<input.F; ++i) {
		 traj.pn[i] = traj.pn[i] - hdt * pot.G0[i];
		 for ( int j=0; j<input.S; ++j) {
		 	traj.pn[i] = traj.pn[i] - qdt * pot.G[i][j][j] * \
		 		(std::pow(traj.Xe[j],2) + std::pow(traj.Pe[j], 2));
		 }
	}

	return 0;
}

// Simple and SLOW matrix and vector product
std::vector< double > matvec(std::vector< std::vector <double> > mat,
                             std::vector< double>vec, int d) {

	std::vector< double > result(d, 0.0);

	for ( int i=0; i<d; ++i ){
		for ( int j=0; j<d; ++j ){
			result[i] = result[i] + ( vec[i] * mat[i][j]);
		}
	}

	return result;
}