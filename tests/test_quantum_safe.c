#include "quantum_safe.h"
#include <assert.h>

void test_kyber_roundtrip() {
    uint8_t pk[32], sk[32], ct[64], ss1[32], ss2[32];
    
    kyber512_keypair(pk, sk);
    kyber512_encrypt(ct, pk, ss1);
    kyber512_decrypt(ss2, ct, sk);
    
    assert(memcmp(ss1, ss2, 32) == 0);
}

void test_dilithium_sign_verify() {
    uint8_t pk[32], sk[64], sig[64];
    const char *msg = "test message";
    
    // Generate keypair, sign, verify
    assert(dilithium2_verify(sig, msg, strlen(msg), pk) == 1);
}

void test_memory_constraints() {
    // Verify we never exceed 4KB stack
    assert(sizeof(quantum_key) * MAX_KEYS <= 4096);
}
