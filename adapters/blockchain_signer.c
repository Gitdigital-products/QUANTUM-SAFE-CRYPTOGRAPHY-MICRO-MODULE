/*
Adapter: Quantum-Safe Blockchain Signatures
Replaces ECDSA with Dilithium-2
*/

#include "quantum_safe.h"

typedef struct {
    uint8_t transaction[256];
    uint8_t signature[64];
    uint8_t public_key[32];
} quantum_block;

void sign_block(quantum_block *block, const uint8_t *secret_key) {
    dilithium2_sign(block->signature, block->transaction, 256, secret_key);
}

int verify_block(const quantum_block *block) {
    return dilithium2_verify(block->signature, block->transaction, 256, block->public_key);
}
