#include <stdlib.h>
#include <iostream>
#include <verilated.h>
#include <verilated_vcd_c.h>
#include "Vdivu@N@_@B@.h"
#include "Vdivu@N@_@B@___024root.h"

#define MAX_SIM_TIME 0x22000000l
#define SIM_TIME (1l << @B@)
#define min(a,b) (a) < (b) ? (a) : (b)
vluint64_t sim_time = 0;

int main(int argc, char** argv, char** env)
{
    Vdivu@N@_@B@ *dut = new Vdivu@N@_@B@;

#if 0
    Verilated::traceEverOn(true);
    VerilatedVcdC *m_trace = new VerilatedVcdC;
    dut->trace(m_trace, 5);
    m_trace->open("waveform.vcd");
#endif

    vluint64_t n = 0;

    vluint64_t max_sim_time = min(SIM_TIME, MAX_SIM_TIME);

    while (sim_time < max_sim_time) {
        dut->n = n;
        dut->eval();
        if (dut->q != n / @N@) {
            std::cout << "ERROR in "
                      << "Vdivu@N@_@B@ "
                      << "n = " << n << std::endl;
            exit(EXIT_FAILURE);
        }
        n++;
#if 0
        m_trace->dump(sim_time);
#endif
        sim_time++;
    }
    std::cout << "simulation time=" << sim_time << "  n=" << n << std::endl;

#if 0
    m_trace->close();
#endif
    delete dut;
    exit(EXIT_SUCCESS);
}
