/*
 * run_libsnark_verifier.cpp
 *
 *      Author: Yuan Lu
 */

#include "../interface/CircuitReader.hpp"
#include "gadgetlib2/examples/simple_example.hpp"
#include "gadgetlib2/adapters.hpp"
#include "gadgetlib2/gadget.hpp"
#include "gadgetlib2/integration.hpp"

#include <string>
#include <iostream>
#include <typeinfo>

using namespace std;

int main(int argc, char **argv) {

        std::string vk_path = "Verification_Key";
        std::string primary_input_path = "Primary_Input";
        std::string proof_path = "Proof";

        if (argc==4) {
            vk_path = argv[1];
            primary_input_path = argv[2];
            proof_path = argv[3];
        }

        if (argc != 1 && argc != 4) {
            std::cout<<"run_libsnark_verifier <vk_path> <primary_input_path> <proof_path>"<<std::endl;
            return 255;
        }

	start_profiling();
	GadgetLibAdapter::resetVariableIndex();
	gadgetlib2::initPublicParamsFromDefaultPp();
	gadgetlib2::GadgetLibAdapter::resetVariableIndex();

	const bool bit = libsnark::run_r1cs_ppzksnark_verifier<libsnark::default_ec_pp>(vk_path, primary_input_path, proof_path);
	assert(bit);
	return 0;
}

