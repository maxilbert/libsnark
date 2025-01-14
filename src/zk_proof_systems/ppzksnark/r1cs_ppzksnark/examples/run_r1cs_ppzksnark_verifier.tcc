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

#ifndef RUN_R1CS_PPZKSNARK_VERIFIER_TCC_
#define RUN_R1CS_PPZKSNARK_VERIFIER_TCC_

#include "zk_proof_systems/ppzksnark/r1cs_ppzksnark/r1cs_ppzksnark.hpp"

#include <iostream>
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
//template<typename ppT>
//bool run_r1cs_ppzksnark_verifier(const r1cs_primary_input<Fr<ppT> > &primary_input)
template<typename ppT>
bool run_r1cs_ppzksnark_verifier(std::string vk_path, std::string primary_input_path, std::string proof_path)
{
    enter_block("Call to run_r1cs_ppzksnark_verifier");  

    //Verifier needs proof and primary input
    //Verifier produce answer
    print_header("R1CS ppzkSNARK Verifier");

    enter_block("Reconstitution of Proof");
    r1cs_ppzksnark_proof<ppT> proof = reconstituteFromFile<r1cs_ppzksnark_proof<ppT> >(proof, proof_path);
    leave_block("Reconstitution of Proof");

    enter_block("Reconstitution of Verification Key");
    r1cs_ppzksnark_verification_key<ppT> vk = reconstituteFromFile<r1cs_ppzksnark_verification_key<ppT> >(vk_path);
    leave_block("Reconstitution of Verification Key");


    r1cs_ppzksnark_processed_verification_key<ppT> pvk = r1cs_ppzksnark_verifier_process_vk<ppT>(vk);
    //std::cout<<pvk.pp_G2_one_precomp<<std::endl;
    //std::cout<<"=============================="<<std::endl;	
    //std::cout<<pvk.vk_alphaA_g2_precomp<<std::endl;
    //std::cout<<"=============================="<<std::endl;	
    //std::cout<<pvk.vk_alphaB_g1_precomp<<std::endl;
    //std::cout<<"=============================="<<std::endl;	
    //std::cout<<pvk.vk_alphaC_g2_precomp<<std::endl;
    //std::cout<<"=============================="<<std::endl;	
    //std::cout<<pvk.vk_rC_Z_g2_precomp<<std::endl;
    //std::cout<<"=============================="<<std::endl;	
    //std::cout<<pvk.vk_gamma_g2_precomp<<std::endl;
    //std::cout<<"=============================="<<std::endl;	
    //std::cout<<pvk.vk_gamma_beta_g1_precomp<<std::endl;
    //std::cout<<"=============================="<<std::endl;	
    //std::cout<<pvk.vk_gamma_beta_g2_precomp<<std::endl;
    enter_block("Serialization of processed verification key");
    serializeToFile<r1cs_ppzksnark_processed_verification_key<ppT> > (pvk, "Processed_Verification_Key");
    leave_block("Serialization of processed verification key");

    enter_block("Reconstitution of Primary Input");
    r1cs_ppzksnark_primary_input<ppT> primary_input_1 = reconstituteFromFile<r1cs_ppzksnark_primary_input<ppT> > (primary_input_path); 
    leave_block("Reconstitution of Primary Input");


    const bool ans = r1cs_ppzksnark_verifier_strong_IC<ppT>(vk, primary_input_1, proof);
    printf("\n"); print_indent(); print_mem("after verifier");
    printf("* The verification result is: %s\n", (ans ? "PASS" : "FAIL"));

    leave_block("Call to run_r1cs_ppzksnark_verifier");

    return ans;
}



} // libsnark

#endif // RUN_R1CS_PPZKSNARK_VERIFIER_TCC_
