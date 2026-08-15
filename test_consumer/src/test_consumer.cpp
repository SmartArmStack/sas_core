#include <iostream>
#include <sas_core/sas_core.hpp>
#include <sas_core/sas_clock.hpp>
#include <sas_core/sas_shutdown_signaler.hpp>

int main(int argc, char** argv)
{
    // Test sas_core namespace is accessible and usable
    VectorXd a(2);
    a << 1.0, 2.0;

    VectorXd b(2);
    b << 3.0, 4.0;

    VectorXd c = sas::concatenate(a, b);
    std::cout << "concatenate result: " << c.transpose() << std::endl;

    // Test incremental_mean
    double mean = sas::incremental_mean(1.0, 1, 3.0);
    std::cout << "incremental_mean(1.0, 1, 3.0) = " << mean << std::endl;

    std::cout << "sas_core imported successfully from test_consumer!" << std::endl;
    return 0;
}