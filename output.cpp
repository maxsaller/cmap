#include "common.h"

/*
 * void print_help()
 *
 * Prints command line help
 *
 */
void print_help() {
    std::cout << "HELP!" << std::endl;
}


void print_header() {
    std::cout   << "========================================\n"
                << "                  CMAP                  \n"
                << "             Version: 0.1.4             \n"
                << " Copyright 2020 Maximilian A. C. Saller \n"
                << "========================================\n\n";
}

void write_observables() {
    std::ofstream ofile;
    ofile.open( "C.out" );

    // Define time vector
    obs.time.resize(input.steps + 1);
    for ( int i=0; i<input.steps + 1; ++i) {
        obs.time[i] = i*input.dt;
    }

    for ( int i=0; i<input.steps+1; ++i ) {
        ofile << std::scientific
        << std::setprecision(4) << std::setw(12) << obs.time[i]
        << std::setprecision(7) << std::setw(15) << obs.CII[i]
        << std::setprecision(7) << std::setw(15) << obs.CIx[i]
        << std::setprecision(7) << std::setw(15) << obs.CIy[i]
        << std::setprecision(7) << std::setw(15) << obs.CIz[i]
        << std::setprecision(7) << std::setw(15) << obs.CxI[i]
        << std::setprecision(7) << std::setw(15) << obs.Cxx[i]
        << std::setprecision(7) << std::setw(15) << obs.Cxy[i]
        << std::setprecision(7) << std::setw(15) << obs.Cxz[i]
        << std::setprecision(7) << std::setw(15) << obs.CyI[i]
        << std::setprecision(7) << std::setw(15) << obs.Cyx[i]
        << std::setprecision(7) << std::setw(15) << obs.Cyy[i]
        << std::setprecision(7) << std::setw(15) << obs.Cyz[i]
        << std::setprecision(7) << std::setw(15) << obs.CzI[i]
        << std::setprecision(7) << std::setw(15) << obs.Czx[i]
        << std::setprecision(7) << std::setw(15) << obs.Czy[i]
        << std::setprecision(7) << std::setw(15) << obs.Czz[i] << "\n";
    }

    ofile.close();
}
