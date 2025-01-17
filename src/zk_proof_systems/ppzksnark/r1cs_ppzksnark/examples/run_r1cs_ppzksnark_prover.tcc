/** @file
 *****************************************************************************

 Implementation of functionality that runs the R1CS ppzkSNARK for
 a given R1CS example.

 See run_r1cs_ppzksnark.hpp .

 *****************************************************************************
 * @author     This file is part of libsnark, developed by SCIPR Lab
 *             and contributors (see AUTHORS).
 * @copyright  MIT license (see LICENSE file)
 *****************************************************************************/

#ifndef RUN_R1CS_PPZKSNARK_PROVER_TCC_
#define RUN_R1CS_PPZKSNARK_PROVER_TCC_

#include "zk_proof_systems/ppzksnark/r1cs_ppzksnark/r1cs_ppzksnark.hpp"

#include <string>
#include <sstream>
#include <fstream>
#include <type_traits>

#include "common/profiling.hpp"

namespace libsnark {


/**
 * The code below provides an example of all stages of running a R1CS ppzkSNARK.
 *
 * Of course, in a real-life scenario, we would have three distinct entities,
 * mangled into one in the demonstration below. The three entities are as follows.
 * (1) The "generator", which runs the ppzkSNARK generator on input a given
 *     constraint system CS to create a proving and a verification key for CS.
 * (2) The "prover", which runs the ppzkSNARK prover on input the proving key,
 *     a primary input for CS, and an auxiliary input for CS.
 * (3) The "verifier", which runs the ppzkSNARK verifier on input the verification key,
 *     a primary input for CS, and a proof.
 */



template<typename ppT>
int run_r1cs_ppzksnark_prover(const r1cs_primary_input<Fr<ppT> > &primary_input, const r1cs_auxiliary_input<Fr<ppT> > &auxiliary_input)
{
    enter_block("Call to run_r1cs_ppzksnark_prover");

    //Prover needs 1. proving key, 2. primary input, 3. auxiliary input;
    //Prover produces proof
    print_header("R1CS ppzkSNARK Prover");

    enter_block("Reconstitution of Proving Key");
    r1cs_ppzksnark_proving_key<ppT> pk = reconstituteFromFile<r1cs_ppzksnark_proving_key<ppT> >("Proving_Key");
    leave_block("Reconstitution of Proving Key");

    r1cs_ppzksnark_proof<ppT> proof = r1cs_ppzksnark_prover<ppT>(pk, primary_input, auxiliary_input);
    printf("\n"); print_indent(); print_mem("after prover");

    enter_block("Serialization of Proof");
    serializeToFile<r1cs_ppzksnark_proof<ppT> > (proof, "Proof");
    leave_block("Serialization of Proof");

    enter_block("Serialization of Primary Input");   
    serializeToFile<r1cs_ppzksnark_primary_input<ppT> > (primary_input, "Primary_Input"); 
    leave_block("Serialization of Primary Input");


    leave_block("Call to run_r1cs_ppzksnark_prover");

    return 1;

}





} // libsnark

#endif // RUN_R1CS_PPZKSNARK_PROVER_TCC_
